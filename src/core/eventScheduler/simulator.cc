/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010,2011,2012,2013 TELEMATICS LAB, Politecnico di Bari
 *
 * This file is part of LTE-Sim
 *
 * LTE-Sim is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation;
 *
 * LTE-Sim is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LTE-Sim; if not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Giuseppe Piro <g.piro@poliba.it>
 */

#include "simulator.h"
#include "make-event.h"
#include "../../componentManagers/FrameManager.h"
#include "../../componentManagers/FlowsManager.h"
#include "../../flows/application/Application.h"
#include "../../flows/radio-bearer.h"
#include "../../device/UserEquipment.h"
#include "../../flows/QoS/QoSParameters.h"
#include "../../protocolStack/mac/packet-scheduler/packet-scheduler.h"
#include "../../protocolStack/mac/packet-scheduler/mt-uplink-packet-scheduler.h"
#include "../../protocolStack/mac/packet-scheduler/dl-pf-packet-scheduler.h"
#include "../../protocolStack/mac/packet-scheduler/dl-mlwdf-packet-scheduler.h"
#include "../../protocolStack/mac/packet-scheduler/dl-exp-packet-scheduler.h"
#include "../../protocolStack/mac/packet-scheduler/dl-fls-packet-scheduler.h"
#include "../../protocolStack/mac/packet-scheduler/exp-rule-downlink-packet-scheduler.h"
#include "../../protocolStack/mac/packet-scheduler/log-rule-downlink-packet-scheduler.h"
#include "../../protocolStack/mac/packet-scheduler/enhanced-uplink-packet-scheduler.h"
#include "../../protocolStack/mac/packet-scheduler/roundrobin-uplink-packet-scheduler.h"

#include "../../protocolStack/mac/packet-scheduler/dqn-packet-scheduler.h"

#include <math.h>
#include <fstream>
#include <list>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
// cout stream buffer redirect
#include <sstream>
#include <cstdio>
#include <string>
#include <cstring>
// pipe server
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>

// by HH
#include "../../../src/shared-memory.h"

Simulator* Simulator::ptr=NULL;

#define STATE_FIFO "state_fifo"
#define SCHED_FIFO "sched_fifo"
#define CQI_FIFO   "cqi_fifo"

double d_dqn_output0, d_dqn_output1, d_dqn_output2, d_dqn_output3; 

Simulator::Simulator ()
{
  m_stop = false;
  m_currentUid = 0;
  m_currentTs = 0;
  m_unscheduledEvents = 0;
  m_calendar = new Calendar;
  m_uid = 0;
}

Simulator::~Simulator ()
{
  while (!m_calendar->IsEmpty ())
    {
    m_calendar->RemoveEvent ();
    }
  delete m_calendar;
}

double
Simulator::Now (void)
{
  return m_currentTs;
}

void Simulator::NumberToString(double number, std::string *target){
  std::stringstream ss;
  ss << number;
  *target = ss.str();
}

void Simulator::NumberToString(int number, std::string *target){
  std::stringstream ss;
  ss << number;
  *target = ss.str();
}

void Simulator::OpenSchedulerFifo(int *fd){
  mkfifo(SCHED_FIFO, S_IFIFO|0640);
  printf("LTESIM: SCHED Pipe Opened! Waiting for DQN..\n");
  *fd = open(SCHED_FIFO, O_RDONLY);
  close(*fd);
  printf("LTESIM: DQN connected to SCHED Pipe.\n");
}

void Simulator::ConnectCQIFifo(int *fd){
  printf("LTESIM: Waiting for CQI_FIFO.\n");
  *fd = open(CQI_FIFO, O_CREAT|O_WRONLY);
  printf("LTESIM: Connected to CQI_FIFO.\n");
  close(*fd);
}

void Simulator::ConnectStateFifo(int *fd){
  int noUEs = 0;
  std::vector<ENodeB*> *eNBs = NetworkManager::Init()->GetENodeBContainer ();
  for (std::vector<ENodeB*>::iterator it = eNBs->begin(); it != eNBs->end(); ++it){
    noUEs += (*it)->GetNbOfUserEquipmentRecords();
  }
  char noUEs_send[80];
  int n = sprintf (noUEs_send, "%d", noUEs);
  printf("LTESIM: Waiting for STATE_FIFO.\n");
  *fd = open(STATE_FIFO, O_CREAT|O_WRONLY);
  printf("LTESIM: Connected to STATE_FIFO, Sending #UEs\n");
   // get the total number of UEs;
   // send size of message
  write(*fd, noUEs_send, strlen(noUEs_send));
  close(*fd);
  printf("LTESIM: Sent #UEs: \"%s\" and string length is %d\n", noUEs_send, n);

}

bool Simulator::makeUEsStationary(){  
  std::vector<UserEquipment*>* UEs = NetworkManager::Init()->GetUserEquipmentContainer();
  UserEquipment* this_ue;
  for (std::vector<UserEquipment*>::iterator it = UEs->begin(); it != UEs->end(); ++it){
    this_ue = (*it);
    this_ue->GetMobilityModel()->SetSpeed(0);
  }

}

//int dqn_output0, dqn_output1, dqn_output2, dqn_output3 = 0;
ENodeB::DLSchedulerType Simulator::FetchScheduler(int *fd){
  char c_readbuf[80];
  char *c_read_ptr;
  int i_input_bytes;
  ENodeB::DLSchedulerType downlink_scheduler_type;

  *fd = open(SCHED_FIFO, O_RDONLY);
  i_input_bytes = read(*fd, c_readbuf, sizeof(c_readbuf));
  close(*fd);

  c_read_ptr = strtok(c_readbuf, "|");
  d_dqn_output0 = 10*atoi(c_read_ptr);
  c_read_ptr = strtok(NULL,"|");  
  d_dqn_output1 = 10*atoi(c_read_ptr);
  c_read_ptr = strtok(NULL,"|");  
  d_dqn_output2 = 10*atoi(c_read_ptr);
  c_read_ptr = strtok(NULL,"|");  
  d_dqn_output3 = 10*atoi(c_read_ptr);

  c_readbuf[i_input_bytes] = '\0';
//  printf("LTESIM: Received scheduler: \"%f / %f / %f / %f\"\n", d_dqn_output0, d_dqn_output1, d_dqn_output2, d_dqn_output3);

  if (strcmp(c_readbuf, "end") == 0)
  {
    m_stop = true;
    downlink_scheduler_type = ENodeB::DLScheduler_TYPE_PROPORTIONAL_FAIR;
    printf("LTESIM: Scheduler is PF_Fair.\n");
    return downlink_scheduler_type;
  }

  if(d_dqn_output0 >= 0)
  {
        downlink_scheduler_type = ENodeB::DLScheduler_TYPE_DQN;
        printf("LTESIM: Scheduler is DQN\n");
  }
  else
  {
    switch ((int)d_dqn_output1/10)
      {
        case 0:
          downlink_scheduler_type = ENodeB::DLScheduler_TYPE_PROPORTIONAL_FAIR;
          printf("LTESIM: Scheduler is PF_Fair.\n");
          break;
        case 1:
          downlink_scheduler_type = ENodeB::DLScheduler_TYPE_MLWDF;
          printf("LTESIM: Scheduler is MLWDF.\n");
          break;
        case 2:
          downlink_scheduler_type = ENodeB::DLScheduler_TYPE_EXP;
          printf("LTESIM: Scheduler is EXP.\n");
          break;
        case 3:
          downlink_scheduler_type = ENodeB::DLScheduler_TYPE_FLS;
          printf("LTESIM: Scheduler is FLS.\n");
          break;
        case 4:
          downlink_scheduler_type = ENodeB::DLScheduler_EXP_RULE;
          printf("LTESIM: Scheduler is EXP_RULE.\n");
          break;
        case 5:
          downlink_scheduler_type = ENodeB::DLScheduler_LOG_RULE;
          printf("LTESIM: Scheduler is LOG_RULE.\n");
          break;
        case 11:
          downlink_scheduler_type = ENodeB::DLScheduler_TYPE_PROPORTIONAL_FAIR;
          printf("LTESIM: SETTING UEs stationary.\n");
          makeUEsStationary();
          break;
        default:
          downlink_scheduler_type = ENodeB::DLScheduler_TYPE_PROPORTIONAL_FAIR;
          break;
      }
  }

    return downlink_scheduler_type;
}

void Simulator::SendUESummary(int *fd){
  std::vector<ENodeB*> *eNBs = NetworkManager::Init()->GetENodeBContainer ();
  // target message string
  std::string UEsummaries;
  for (std::vector<ENodeB*>::iterator it = eNBs->begin(); it != eNBs->end(); ++it){
    // form UE summary of this eNB
    FormUESummaryMessage(*it, &UEsummaries);
  }
  std::string::size_type size = UEsummaries.size();
  printf("LTESIM: Size of UEsummaries: %d \n", (int)size);
  *fd = open(STATE_FIFO, O_CREAT|O_WRONLY);
  // send the cqi size
  write(*fd, &size, sizeof(size));
  // then the whole message
  write(*fd, UEsummaries.c_str(), UEsummaries.size());
  printf("LTESIM: Sent UEsummaries.\n");
  close(*fd);
}

void  Simulator::SendCQISummary(int *fd){
  std::vector<ENodeB*> *eNBs = NetworkManager::Init()->GetENodeBContainer ();
  // cqi string to send
  std::string CQIs;
  for (std::vector<ENodeB*>::iterator it = eNBs->begin(); it != eNBs->end(); ++it){
    // form cqi message of this eNB
    FormCQIMessage(*it, &CQIs);
  }

  std::string::size_type size = CQIs.size();
  printf("LTESIM: Size of cqis: %d \n", (int)size);
  *fd = open(CQI_FIFO, O_CREAT|O_WRONLY);
  // send the cqi size
  write(*fd, &size, sizeof(size));
  // then the whole message
  write(*fd, CQIs.c_str(), CQIs.size());
  // printf("LTESIM: Sent cqis.\n%s\n", CQIs.c_str());
  printf("LTESIM: Sent cqis.\n");
  close(*fd);
}

void Simulator::SendState(int *fd, std::string state){
  std::string::size_type size = state.size();
  printf("LTESIM: Size of state: %d \n", (int)size);
  *fd = open(STATE_FIFO, O_CREAT|O_WRONLY);
  // send the size of message
  write(*fd, &size, sizeof(size));
  //  then the whole message
  write(*fd, state.c_str(), state.size());
  // printf("LTESIM: Sent state.\n%s\n", state.c_str());
  printf("LTESIM: Sent state.\n");
  close(*fd);
}

void Simulator::FormUESummaryMessage(ENodeB *eNB, std::string *target_string){
  int ideNB;
  int UEid;
  std::string UEid_str;
  // collect all UE information
  int noUEs = eNB->GetNbOfUserEquipmentRecords();
  std::vector<ENodeB::UserEquipmentRecord*> *UErecords = eNB->GetUserEquipmentRecords();
  ENodeB::UserEquipmentRecord* UErecord;
  // collect all APP information
  std::vector<Application*> *apps = FlowsManager::Init()->GetApplicationContainer();
  Application* app;
  int appID, appDST;
  std::string appID_str;
  //all QoS information
  QoSParameters* appQoS;
  double appGBR, appDelay, appPLR;
  std::string appGBR_str, appDelay_str, appPLR_str;
  // message string used for each Application
  std::string message_string;
  for (std::vector<ENodeB::UserEquipmentRecord*>::iterator it = UErecords->begin(); it != UErecords->end(); ++it){
    UErecord = (*it);
    UEid = UErecord->GetUE()->GetIDNetworkNode();
    NumberToString(UEid, &UEid_str);
    // for each app check which app belongs to which UE
    for (std::vector<Application*>::iterator it = apps->begin(); it != apps->end(); ++it){
      app = (*it);
      appDST = app->GetDestination()->GetIDNetworkNode();
      if(appDST == UEid){ // app belongs to this UE
        appID = app->GetApplicationID();
        NumberToString(appID, &appID_str);
        // QoS Fetch
        appQoS = app->GetQoSParameters();
        appGBR = appQoS->GetGBR();
        appDelay = appQoS->GetMaxDelay();
        appPLR = appQoS->GetDropProbability();

        // QoS to strings
        NumberToString(appGBR, &appGBR_str);
        NumberToString(appDelay, &appDelay_str);
        NumberToString(appPLR, &appPLR_str);

        // add to the message string
        // {UE id} {APP id} {APP GBR} {APP delay} {APP PLR}
        *target_string += UEid_str + " " + appID_str + " " + appGBR_str + " " + appDelay_str + " " + appPLR_str + "\n";
      }
    }
  }
}

void Simulator::UpdateAllScheduler(ENodeB::DLSchedulerType new_scheduler){
  // vector of enbs
  std::vector<ENodeB*> *eNBs = NetworkManager::Init()->GetENodeBContainer ();
  // vector of Apps
  std::vector<Application*> *apps = FlowsManager::Init()->GetApplicationContainer();
  // vector of rrc bearers
  std::vector<RadioBearer*> *bearers;
  // QoS for changing rrc bearers
  QoSParameters* new_qos;
  // Update the QoS for each Application AND it's bearer based on scheduler
  for (std::vector<Application*>::iterator it = apps->begin(); it != apps->end(); ++it){
    new_qos = (*it)->UpdateQoSOnSchedulerChange(new_scheduler);
  }
  // for each enobeB
  for (std::vector<ENodeB*>::iterator it = eNBs->begin(); it != eNBs->end(); ++it){
    // Update Scheduler 
    (*it)->SetDLScheduler(new_scheduler);
    // get the bearer list from this enodeB's rrc 
    bearers = (*it)->GetDLScheduler()->GetMacEntity()->GetDevice()->GetProtocolStack()->GetRrcEntity()->GetRadioBearerContainer();
    // update each bearer in the rrc's list QoS based on scheduler
    for (std::vector<RadioBearer*>::iterator it = bearers->begin(); it != bearers->end(); ++it){        
      (*it)->SetQoSParameters(new_qos);
    }
  }
}

void Simulator::FormCQIMessage(ENodeB *eNB, std::string *target_string){
    std::vector<ENodeB::UserEquipmentRecord*> *UserEquipmentRecords = eNB->GetUserEquipmentRecords();
    ENodeB::UserEquipmentRecord* UErecord;
    // cqi vector for each UE
    std::vector<int> cqi;
    // cqi string for each UE
    std::string cqiString;
    // temp string
    std::string temp;
    for (std::vector<ENodeB::UserEquipmentRecord*>::iterator it = UserEquipmentRecords->begin(); it != UserEquipmentRecords->end(); ++it){
      UErecord = (*it);
      cqi = UErecord->GetCQI();
      for (int i = 0; i < cqi.size(); ++i){
        NumberToString(cqi[i], &temp);
        cqiString += temp + " ";
      }
      *target_string += cqiString + "\n";
      cqiString = "";
     
    }

}

void 
Simulator::Run ()
{
 
  // scheduler type object
  ENodeB::DLSchedulerType scheduler;
  // Open, connect to pipes
  int sh_fd, st_fd, cqi_fd;
  OpenSchedulerFifo(&sh_fd);
  // open CQI Fifo
  ConnectCQIFifo(&cqi_fd);
  // connect and forward #UEs
  ConnectStateFifo(&st_fd);
  // form information about each eNB's UE's application QoS and send!
  SendUESummary(&st_fd);



	// by HH
  char *shared_buffer = (char*)malloc(SHARED_SIZE);
  char *lstm_buffer = (char*)malloc(SHARED_SIZE);
  char *dqn_buffer = (char*)malloc(SHARED_SIZE);
  int use_lstm = 0;
  int PID = -1;

  int lte_shmid = SharedMemoryCreate(LTE_KEY);
  int dqn_shmid;
  int lstm_shmid;

  int packet_index;
  int buffer_value=0;
  int index;


  // DQN에서 LSTM 사용여부 확인
  while(use_lstm != -1 && use_lstm != 0X89)
  {     
    dqn_shmid = SharedMemoryInit(DQN_KEY);  
    if(dqn_shmid != -1)
    {
      SharedMemoryRead(dqn_shmid, dqn_buffer);
      use_lstm = atoi(dqn_buffer);
    }
    sleep(0.001);
  }

  // LSTM 대기
  if(use_lstm==0x89)
  {
    // LSTM에 PID 전송
    sprintf(shared_buffer,"%d", getpid());
    if( SharedMemoryWrite(lte_shmid, shared_buffer) == -1 )
    {
      printf("shared memory write failed\n");
    }

    printf("waiting for LSTM\n");
    
    while(buffer_value != atoi(shared_buffer))
    {     
      lstm_shmid = SharedMemoryInit(LSTM_KEY);  
      if(lstm_shmid != -1)
      {
        SharedMemoryRead(lstm_shmid, lstm_buffer);
        buffer_value = atoi(lstm_buffer);
      }
      sleep(0.001);
    }

     // LSTM ready 이후 LSTM에 -1 전송
    sprintf(shared_buffer,"%d", -1);
    if( SharedMemoryWrite(lte_shmid, shared_buffer) == -1 )
    {
      printf("shared memory write failed\n");
    }  
  } 


  // tti trackers
  unsigned long tti_tr1, tti_tr2;
  // buffer contains the simulation output for the last TTI
  // buffer is written to the bigbig and then cleared each TTI
  std::stringstream buffer;
  // cout buffer redirect into the buffer
  std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
  // bigbuff is the whole trace of the simulation
  // run the simulation until first packets are sent and update tti trackers
  std::string bigbuf; 
  m_stop = false;
  while (!m_calendar->IsEmpty () && !m_stop){
    tti_tr1 = FrameManager::Init()->GetTTICounter();
    ProcessOneEvent ();
    tti_tr2 = FrameManager::Init()->GetTTICounter();
    // after each TTI change
    if(tti_tr1 != tti_tr2){
      printf("\nLTESIM: TTI Change! Now in TTI # %d.\n", tti_tr2);
      // append onto big buffer
      bigbuf = bigbuf + buffer.str();
      // if we are past empty TTIs
      if(!bigbuf.empty()){
        printf("bigbuf: %s\n", bigbuf.c_str() );
        // send the update TTI
        SendState(&st_fd, buffer.str().c_str());
        SendCQISummary(&cqi_fd);
        printf("LTESIM: Waiting for new Scheduler. \n");
        m_stop = true;
        tti_tr1 = tti_tr2;
        buffer.str("");
      }  

      if(use_lstm==0x89)
      {
        // Send packet size to LSTM every 10 TTI
        packet_index = tti_tr2 %10;
        lstm_packet_size[packet_index] = tti_packet_size;
        if(packet_index == 9 && tti_tr2<19999)
        {
          for(index=0; index < 10; index++)
          {
            //send signal to LSTM
            sprintf(shared_buffer, "%d", tti_tr2);
            SharedMemoryWrite(lstm_shmid, shared_buffer);

            // send SIZE to LSTM
            sprintf(shared_buffer, "%d", lstm_packet_size[index]);
            SharedMemoryWrite(lte_shmid, shared_buffer);
            //printf("Write %s to lte_shmid/ size:%d\n", shared_buffer, sizeof(shared_buffer));

            //check receive
            //printf("waiting for LSTM receive data\n");
            do{
              SharedMemoryRead(lstm_shmid, lstm_buffer);
              buffer_value = atoi(lstm_buffer);
            }while( buffer_value != -1);
          }
        }
      }
      buffer.str("");
    }
  }

  // continue with remainder
  m_stop = false;



  while (!m_calendar->IsEmpty () && !m_stop){
    // fetch the new scheduler
    scheduler = FetchScheduler(&sh_fd);

    // Update everything needed for scheduler changes
    UpdateAllScheduler(scheduler);
    // execute "action"
    while(tti_tr1 == tti_tr2 && !m_calendar->IsEmpty()){
        ProcessOneEvent ();
        tti_tr2 = FrameManager::Init()->GetTTICounter();
    }
    tti_tr1 = tti_tr2;
    
    printf("\nLTESIM: TTI Change! Now in TTI # %d.\n", tti_tr2);
    // append onto big buffer
    bigbuf = bigbuf + buffer.str();
    // send the last TTI
    SendState(&st_fd, buffer.str().c_str());
    SendCQISummary(&cqi_fd);

    if(use_lstm == 0x89)
    {
      // Send packet size to LSTM every 10 TTI
      packet_index = tti_tr2 %10;
      lstm_packet_size[packet_index] = tti_packet_size;
      if(packet_index == 9 && tti_tr2<19999)
      {
        printf("waiting for LSTM\n");
        for(int index=0; index < 10; index++)
        {
          //send signal to LSTM
          sprintf(shared_buffer, "%d", tti_tr2);
          SharedMemoryWrite(lstm_shmid, shared_buffer);

          // send SIZE to LSTM
          sprintf(shared_buffer, "%d", lstm_packet_size[index]);
          SharedMemoryWrite(lte_shmid, shared_buffer);
          //printf("Write %s to lte_shmid/ size:%d\n", shared_buffer, sizeof(shared_buffer));

          //check receive
          //printf("waiting for LSTM receive data\n");
          do{
            SharedMemoryRead(lstm_shmid, lstm_buffer);
            buffer_value = atoi(lstm_buffer);
          }while( buffer_value != -1);
        }
      }
    }

    printf("LTESIM: Waiting for new Scheduler. \n");
    // clear stream and output capture
    buffer.str("");
  }
  // close the streams
  scheduler = FetchScheduler(&sh_fd);
  SendState(&st_fd, "end");
  close(sh_fd);
  close(st_fd);
  close(cqi_fd);
  printf("Closed all pipes.\n");
}

void
Simulator::ProcessOneEvent(void)
{
  Event *next = m_calendar->GetEvent();

  --m_unscheduledEvents;
  m_currentTs = next->GetTimeStamp();
  m_currentUid = next->GetUID();

  next->RunEvent();

  m_calendar->RemoveEvent();
}

int
Simulator::GetUID (void)
{
  m_uid++;
  return (m_uid-1);
}

void 
Simulator::Stop (void)
{
  printf("SIMULATOR_DEBUG: Stop ()\n");
  // std::cout << " SIMULATOR_DEBUG: Stop ()"
  //     << std::endl;
  m_stop = true;
}

void 
Simulator::SetStop (double time)
{
  DoSchedule (time,
        MakeEvent (&Simulator::Stop, this));
}


void
Simulator::DoSchedule (double time,
             Event *event)
{
  double timeStamp = time + Now();
  event->SetTimeStamp(timeStamp);

  ++m_unscheduledEvents;

  m_calendar->InsertEvent(event);
}

void
Simulator::PrintMemoryUsage (void)
{
  system("pmap `ps aux | grep LTE  | grep -v grep | awk '{print $2}'` | grep total");
}
