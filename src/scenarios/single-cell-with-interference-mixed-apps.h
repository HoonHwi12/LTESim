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

#include "../channel/LteChannel.h"
#include "../phy/enb-lte-phy.h"
#include "../phy/ue-lte-phy.h"
#include "../core/spectrum/bandwidth-manager.h"
#include "../networkTopology/Cell.h"
#include "../protocolStack/packet/packet-burst.h"
#include "../protocolStack/packet/Packet.h"
#include "../core/eventScheduler/simulator.h"
#include "../flows/application/InfiniteBuffer.h"
#include "../flows/application/VoIP.h"
#include "../flows/application/CBR.h"
#include "../flows/application/TraceBased.h"
#include "../device/IPClassifier/ClassifierParameters.h"
#include "../flows/QoS/QoSParameters.h"
#include "../flows/QoS/QoSForEXP.h"
#include "../flows/QoS/QoSForFLS.h"
#include "../flows/QoS/QoSForM_LWDF.h"
#include "../componentManagers/FrameManager.h"
#include "../utility/seed.h"
#include "../utility/RandomVariable.h"
#include "../phy/wideband-cqi-eesm-error-model.h"
#include "../phy/simple-error-model.h"
#include "../channel/propagation-model/macrocell-urban-area-channel-realization.h"
#include "../load-parameters.h"
#include <queue>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <iostream>

static void SingleCellWithInterferenceMixedApps (int nbCells, double radius,
                                        int nbUE,
                                        int nbVideo, int nbCBR, int nbBE, int nbVoIP,
                                        int sched_type,
                                        int frame_struct,
                                        int speed,
		                                double maxDelay, int videoBitRate,
                                        int seed)
{

	// define simulation times
	double duration = 46;
	double flow_duration = 40;


  	int cluster = 4;
  	double bandwidth = 5;

  	// CREATE COMPONENT MANAGER
  	// main event handler
  	Simulator *simulator = Simulator::Init();
  	// track TTIs
  	FrameManager *frameManager = FrameManager::Init();
  	// list of enBS and UEs
  	NetworkManager* nm = NetworkManager::Init();
  	// list of applications
  	FlowsManager *flowsManager = FlowsManager::Init(); 

  	// CONFIGURE SEED
  	if (seed >= 0){
  		int commonSeed = GetCommonSeed (seed);
	  	srand (commonSeed);
	} else {
	  	srand (0);
	}
  	std::cout << "Simulation with SEED = " << seed << std::endl;

  	// SET SCHEDULING ALLOCATION SCHEME
  	ENodeB::DLSchedulerType downlink_scheduler_type;
  	switch (sched_type){
	  	case 1:
			downlink_scheduler_type = ENodeB::DLScheduler_TYPE_PROPORTIONAL_FAIR;
			std::cout << "Scheduler PF "<< std::endl;
			break;
	  	case 2:
			downlink_scheduler_type = ENodeB::DLScheduler_TYPE_MLWDF;
			std::cout << "Scheduler MLWDF "<< std::endl;
			break;
	  	case 3:
			downlink_scheduler_type = ENodeB::DLScheduler_TYPE_EXP;
			std::cout << "Scheduler EXP "<< std::endl;
			break;
	  	case 4:
			downlink_scheduler_type = ENodeB::DLScheduler_TYPE_FLS;
			std::cout << "Scheduler FLS "<< std::endl;
			break;
      	case 5:
  	    	downlink_scheduler_type = ENodeB::DLScheduler_EXP_RULE;
  	    	std::cout << "Scheduler EXP_RULE "<< std::endl;
	    	break;
      	case 6:
  	    	downlink_scheduler_type = ENodeB::DLScheduler_LOG_RULE;
  	    	std::cout << "Scheduler LOG RULE "<< std::endl;
	    	break;
	  	default:
			downlink_scheduler_type = ENodeB::DLScheduler_TYPE_PROPORTIONAL_FAIR;
			break;
	}

  	// SET FRAME STRUCTURE
  	FrameManager::FrameStructure frame_structure;
  	switch (frame_struct){
	  	case 1:
			frame_structure = FrameManager::FRAME_STRUCTURE_FDD;
			break;
	  	case 2:
			frame_structure = FrameManager::FRAME_STRUCTURE_TDD;
			break;
	  	default:
			frame_structure = FrameManager::FRAME_STRUCTURE_FDD;
			break;
	}
  	frameManager->SetFrameStructure(FrameManager::FRAME_STRUCTURE_FDD);

  	//create cells
  	std::vector <Cell*> *cells = new std::vector <Cell*>;
  	for (int i = 0; i < nbCells; i++){
  		CartesianCoordinates center =
			  GetCartesianCoordinatesForCell(i, radius * 1000.);

		Cell *c = new Cell (i, radius, 0.035, center.GetCoordinateX (), center.GetCoordinateY ());
	  	cells->push_back (c);
	  	nm->GetCellContainer ()->push_back (c);

	  	std::cout << "Created Cell, id " << c->GetIdCell ()
			  <<", position: " << c->GetCellCenterPosition ()->GetCoordinateX ()
			  << " " << c->GetCellCenterPosition ()->GetCoordinateY () << std::endl;
	}


  	std::vector <BandwidthManager*> spectrums = RunFrequencyReuseTechniques (nbCells, cluster, bandwidth);

  	//Create a set of a couple of channels
  	std::vector <LteChannel*> *dlChannels = new std::vector <LteChannel*>;
  	std::vector <LteChannel*> *ulChannels = new std::vector <LteChannel*>;
  	for (int i= 0; i < nbCells; i++){
  		LteChannel *dlCh = new LteChannel ();
	  	dlCh->SetChannelId (i);
	  	dlChannels->push_back (dlCh);

	  	LteChannel *ulCh = new LteChannel ();
	  	ulCh->SetChannelId (i);
	  	ulChannels->push_back (ulCh);
	}

  	//create eNBs
  	std::vector <ENodeB*> *eNBs = new std::vector <ENodeB*>;
  	for(int i = 0; i < nbCells; i++){
  		ENodeB* enb = new ENodeB (i, cells->at (i));
		enb->GetPhy ()->SetDlChannel (dlChannels->at (i));
		enb->GetPhy ()->SetUlChannel (ulChannels->at (i));
		enb->SetDLScheduler (downlink_scheduler_type);
		enb->GetPhy ()->SetBandwidthManager (spectrums.at (i));

		std::cout << "Created enb, id " << enb->GetIDNetworkNode()
			  << ", cell id " << enb->GetCell ()->GetIdCell ()
			  <<", position: " << enb->GetMobilityModel ()->GetAbsolutePosition ()->GetCoordinateX ()
			  << " " << enb->GetMobilityModel ()->GetAbsolutePosition ()->GetCoordinateY ()
			  << ", channels id " << enb->GetPhy ()->GetDlChannel ()->GetChannelId ()
			  << enb->GetPhy ()->GetUlChannel ()->GetChannelId ()  << std::endl;

		spectrums.at (i)->Print ();
		ulChannels->at (i)->AddDevice((NetworkNode*) enb);
		nm->GetENodeBContainer ()->push_back (enb);
		eNBs->push_back (enb);
  	}

	//Define Application Container
  	int nbCell=1;
  	TraceBased VideoApplication[nbVideo];
	InfiniteBuffer BEApplication[nbBE];
	VoIP VoIPApplication[nbVoIP];
  	CBR CBRApplication[nbCBR];
  	int voipApplication = 0;
  	int videoApplication = 0;
  	int cbrApplication = 0;
  	int beApplication = 0;
  	int destinationPort = 101;
  	int applicationID = 0;
  	// QoS goal Definitions
  	int gbrCBR = 256;     // 256kbps
  	float delayCBR = 0.3; // 300 ms
  	float plrCBR = 10e-6;

  	int gbrVideoBuff = 128;    // 128kbps
  	float delayVideoBuff = 0.3;// 300 ms
  	float plrVideoBuff = 10e-6;

  	//int gbrVideoLive = 128;    // 180kbps
	int gbrVideoLive = 242;	// 242kbps
  	float delayVideoLive = 0.15;// 150ms
  	float plrVideoLive = 10e-3;

  	//Create GW
 	 Gateway *gw = new Gateway ();
  	nm->GetGatewayContainer ()->push_back (gw);

  	//Create UEs
  	int idUE = nbCells;
  	for (int i = 0; i < nbVideo; i++){
  		//ue's random position
  		double posX = (double)rand()/RAND_MAX; posX = 0.95 *
	  	  	  (((2*radius*1000)*posX) - (radius*1000));
	  	double posY = (double)rand()/RAND_MAX; posY = 0.95 *
		  (((2*radius*1000)*posY) - (radius*1000));

	  	double speedDirection = GetRandomVariable (360.) * ((2.*3.14)/360.);

	  	UserEquipment* ue = new UserEquipment (idUE,
			                                 posX, posY, speed, speedDirection,
											 cells->at (0),
											 eNBs->at (0),
			                                 0, //handover false!
			                                 Mobility::RANDOM_DIRECTION);

	  	std::cout << "Created UE - id " << idUE << " position " << posX << " " << posY << " direction " << speedDirection << std::endl;

	  	ue->GetMobilityModel()->GetAbsolutePosition()->Print();
	  	ue->GetPhy ()->SetDlChannel (eNBs->at (0)->GetPhy ()->GetDlChannel ());
	  	ue->GetPhy ()->SetUlChannel (eNBs->at (0)->GetPhy ()->GetUlChannel ());

      	FullbandCqiManager *cqiManager = new FullbandCqiManager ();
      	cqiManager->SetCqiReportingMode (CqiManager::PERIODIC);
      	cqiManager->SetReportingInterval (1);
      	cqiManager->SetDevice (ue);
      	ue->SetCqiManager (cqiManager);

      	WidebandCqiEesmErrorModel *errorModel = new WidebandCqiEesmErrorModel ();
      	ue->GetPhy ()->SetErrorModel (errorModel);

	  	nm->GetUserEquipmentContainer ()->push_back (ue);

	  	// register ue to the enb
	  	eNBs->at (0)->RegisterUserEquipment (ue);

	  	// define the channel realization
	  	MacroCellUrbanAreaChannelRealization* c_dl = new MacroCellUrbanAreaChannelRealization (eNBs->at (0), ue);
	  	eNBs->at (0)->GetPhy ()->GetDlChannel ()->GetPropagationLossModel ()->AddChannelRealization (c_dl);
	  	MacroCellUrbanAreaChannelRealization* c_ul = new MacroCellUrbanAreaChannelRealization (ue, eNBs->at (0));
	  	eNBs->at (0)->GetPhy ()->GetUlChannel ()->GetPropagationLossModel ()->AddChannelRealization (c_ul);


	  	// CREATE DOWNLINK APPLICATION FOR THIS UE
	  	double start_time = 0.1 + GetRandomVariable (5.);
	  	double duration_time = start_time + flow_duration;

	  	// *** LIVE video application
	  	// create application
	  	VideoApplication[videoApplication].SetSource (gw);
	  	VideoApplication[videoApplication].SetDestination (ue);
	  	VideoApplication[videoApplication].SetApplicationID (applicationID);
	  	VideoApplication[videoApplication].SetStartTime(start_time);
	  	VideoApplication[videoApplication].SetStopTime(duration_time);
	  	string video_trace ("foreman_H264_");
	  	//string video_trace ("highway_H264_");
	  	//string video_trace ("mobile_H264_");
	  	switch (videoBitRate){
	  		case 128:
			{
				string _file (path + "src/flows/application/Trace/" + video_trace + "128k.dat");
				VideoApplication[videoApplication].SetTraceFile(_file);
				std::cout << "		selected video @ 128k " << _file << std::endl;
				break;
			}
			case 242:
			{
				string _file (path + "src/flows/application/Trace/" + video_trace + "242k.dat");
				VideoApplication[videoApplication].SetTraceFile(_file);
				std::cout << "		selected video @ 242k"<< std::endl;
				break;
			}
			case 440:
			{
				string _file (path + "src/flows/application/Trace/" + video_trace + "440k.dat");
 			    VideoApplication[videoApplication].SetTraceFile(_file);
				std::cout << "		selected video @ 440k"<< std::endl;
				break;
			}
			default:
			{
				string _file (path + "src/flows/application/Trace/" + video_trace + "128k.dat");
				VideoApplication[videoApplication].SetTraceFile(_file);
				std::cout << "		selected video @ 128k as default"<< std::endl;
				break;
			}
		}
		// create qos parameters for LIVE video
		QoSForFLS *qosFLS      = new QoSForFLS ();
		// Doesnt play well with coefficients
		qosFLS  ->SetMaxDelay(maxDelay); // problem
		qosFLS ->SetGBR(gbrVideoLive);
		qosFLS ->SetDropPorbability(plrVideoLive);

		QoSForEXP *qosEXP      = new QoSForEXP ();
		qosEXP ->SetMaxDelay(delayVideoLive);
		qosEXP ->SetGBR(gbrVideoLive);
		qosEXP ->SetDropPorbability(plrVideoLive);

		QoSForM_LWDF *qosMLWDF = new QoSForM_LWDF ();
		qosMLWDF ->SetMaxDelay(delayVideoLive);
		qosMLWDF ->SetGBR(gbrVideoLive);
		qosMLWDF ->SetDropPorbability(plrVideoLive);

		QoSParameters *qosBase = new QoSParameters ();
		qosBase ->SetMaxDelay(delayVideoLive);
		qosBase ->SetGBR(gbrVideoLive);
		qosBase ->SetDropPorbability(plrVideoLive);

		if (maxDelay == 0.1){
			// std::cout << "Target Delay = 0.1 s, M = 9" << std::endl;
		  	qosFLS->SetNbOfCoefficients (9);
		} else if (maxDelay == 0.08){
			// std::cout << "Target Delay = 0.08 s, M = 7" << std::endl;
			qosFLS->SetNbOfCoefficients (7);
		} else if (maxDelay == 0.06){
		// std::cout << "Target Delay = 0.06 s, M = 5" << std::endl;
			qosFLS->SetNbOfCoefficients (5);
		} else if (maxDelay == 0.04){
		// std::cout << "Target Delay = 0.04 s, M = 3" << std::endl;
			qosFLS->SetNbOfCoefficients (3);
		} else {
			std::cout << "ERROR: target delay is not available"<< std::endl;
			return;
		}

		// assign qos parameters
		if (downlink_scheduler_type == ENodeB::DLScheduler_TYPE_FLS){
			VideoApplication[videoApplication].SetQoSParameters (qosFLS);
		} else if (downlink_scheduler_type == ENodeB::DLScheduler_TYPE_EXP) {
			VideoApplication[videoApplication].SetQoSParameters (qosEXP);
		} else if (downlink_scheduler_type == ENodeB::DLScheduler_TYPE_MLWDF) {
			VideoApplication[videoApplication].SetQoSParameters (qosMLWDF);
		} else {
			VideoApplication[videoApplication].SetQoSParameters (qosBase);
		}

		// VERY NB
		VideoApplication[videoApplication].SetQoSAllTypes(qosEXP, qosFLS, qosMLWDF, qosBase);

		//create classifier parameters
		ClassifierParameters *cp = new ClassifierParameters (gw->GetIDNetworkNode(),
															   ue->GetIDNetworkNode(),
															   0,
															   destinationPort,
															   TransportProtocol::TRANSPORT_PROTOCOL_TYPE_UDP);
		VideoApplication[videoApplication].SetClassifierParameters (cp);

		std::cout << "CREATED VIDEO APPLICATION, ID " << applicationID << std::endl;
		  // VERY NB
		flowsManager->GetApplicationContainer()->push_back(&VideoApplication[videoApplication]);

		//update counter
		destinationPort++;
		applicationID++;
		videoApplication++;
		idUE++;

	}

	
	for (int i = 0; i < nbBE; i++)
	{
  		//ue's random position
  		double posX = (double)rand()/RAND_MAX; posX = 0.95 *
	  	  	  (((2*radius*1000)*posX) - (radius*1000));
	  	double posY = (double)rand()/RAND_MAX; posY = 0.95 *
		  (((2*radius*1000)*posY) - (radius*1000));

	  	double speedDirection = GetRandomVariable (360.) * ((2.*3.14)/360.);

	  	UserEquipment* ue = new UserEquipment (idUE,
			                                 posX, posY, speed, speedDirection,
											 cells->at (0),
											 eNBs->at (0),
			                                 0, //handover false!
			                                 Mobility::RANDOM_DIRECTION);

	  	std::cout << "Created UE - id " << idUE << " position " << posX << " " << posY << " direction " << speedDirection << std::endl;

	  	ue->GetMobilityModel()->GetAbsolutePosition()->Print();
	  	ue->GetPhy ()->SetDlChannel (eNBs->at (0)->GetPhy ()->GetDlChannel ());
	  	ue->GetPhy ()->SetUlChannel (eNBs->at (0)->GetPhy ()->GetUlChannel ());

      	FullbandCqiManager *cqiManager = new FullbandCqiManager ();
      	cqiManager->SetCqiReportingMode (CqiManager::PERIODIC);
      	cqiManager->SetReportingInterval (1);
      	cqiManager->SetDevice (ue);
      	ue->SetCqiManager (cqiManager);

      	WidebandCqiEesmErrorModel *errorModel = new WidebandCqiEesmErrorModel ();
      	ue->GetPhy ()->SetErrorModel (errorModel);

	  	nm->GetUserEquipmentContainer ()->push_back (ue);

	  	// register ue to the enb
	  	eNBs->at (0)->RegisterUserEquipment (ue);

	  	// define the channel realization
	  	MacroCellUrbanAreaChannelRealization* c_dl = new MacroCellUrbanAreaChannelRealization (eNBs->at (0), ue);
	  	eNBs->at (0)->GetPhy ()->GetDlChannel ()->GetPropagationLossModel ()->AddChannelRealization (c_dl);
	  	MacroCellUrbanAreaChannelRealization* c_ul = new MacroCellUrbanAreaChannelRealization (ue, eNBs->at (0));
	  	eNBs->at (0)->GetPhy ()->GetUlChannel ()->GetPropagationLossModel ()->AddChannelRealization (c_ul);


	  	// CREATE DOWNLINK APPLICATION FOR THIS UE
	  	double start_time = 0.1 + GetRandomVariable (5.);
	  	double duration_time = start_time + flow_duration;

		// *** be application
		// create application
		BEApplication[beApplication].SetSource (gw);
		BEApplication[beApplication].SetDestination (ue);
		BEApplication[beApplication].SetApplicationID (applicationID);
		BEApplication[beApplication].SetStartTime(start_time);
		BEApplication[beApplication].SetStopTime(duration_time);


		// create qos parameters
		// BE only uses qosBase it seems, but this is here just for completeness
		QoSForFLS *qosFLS      = new QoSForFLS ();
		QoSForEXP *qosEXP      = new QoSForEXP ();
		QoSForM_LWDF *qosMLWDF = new QoSForM_LWDF ();
		QoSParameters *qosBase = new QoSParameters ();
		qosFLS  ->SetMaxDelay(maxDelay);
		qosEXP  ->SetMaxDelay(maxDelay);
		qosMLWDF->SetMaxDelay(maxDelay);
		qosBase ->SetMaxDelay(maxDelay);
		if (maxDelay == 0.1)
		{
			// std::cout << "Target Delay = 0.1 s, M = 9" << std::endl;
			qosFLS->SetNbOfCoefficients (9);
		}
		else if (maxDelay == 0.08)
		{
			// std::cout << "Target Delay = 0.08 s, M = 7" << std::endl;
			qosFLS->SetNbOfCoefficients (7);
		}
		else if (maxDelay == 0.06)
		{
			// std::cout << "Target Delay = 0.06 s, M = 5" << std::endl;
			qosFLS->SetNbOfCoefficients (5);
		}
		else if (maxDelay == 0.04)
		{
			// std::cout << "Target Delay = 0.04 s, M = 3" << std::endl;
			qosFLS->SetNbOfCoefficients (3);
		}
		else
		{
			std::cout << "ERROR: target delay is not available"<< std::endl;
			return;
		}

		// assign qos parameters
		if (downlink_scheduler_type == ENodeB::DLScheduler_TYPE_FLS)
		{
			BEApplication[beApplication].SetQoSParameters (qosFLS);
		}
		else if (downlink_scheduler_type == ENodeB::DLScheduler_TYPE_EXP)
		{
			BEApplication[beApplication].SetQoSParameters (qosEXP);
		}
		else if (downlink_scheduler_type == ENodeB::DLScheduler_TYPE_MLWDF)
		{
			BEApplication[beApplication].SetQoSParameters (qosMLWDF);
		}
		else
		{
			BEApplication[beApplication].SetQoSParameters (qosBase);
		}
		BEApplication[beApplication].SetQoSAllTypes(qosEXP, qosFLS, qosMLWDF, qosBase);


		//create classifier parameters
		ClassifierParameters *cp = new ClassifierParameters (gw->GetIDNetworkNode(),
															ue->GetIDNetworkNode(),
															0,
															destinationPort,
															TransportProtocol::TRANSPORT_PROTOCOL_TYPE_UDP);
		BEApplication[beApplication].SetClassifierParameters (cp);

		std::cout << "CREATED BE APPLICATION, ID " << applicationID << std::endl;
		flowsManager->GetApplicationContainer()->push_back(&BEApplication[beApplication]);

		//update counter
		destinationPort++;
		applicationID++;
		beApplication++;
		idUE++;

	}


  	for (int i = 0; i < nbVoIP; i++){
  		//ue's random position
  		double posX = (double)rand()/RAND_MAX; posX = 0.95 *
	  	  	  (((2*radius*1000)*posX) - (radius*1000));
	  	double posY = (double)rand()/RAND_MAX; posY = 0.95 *
		  (((2*radius*1000)*posY) - (radius*1000));

	  	double speedDirection = GetRandomVariable (360.) * ((2.*3.14)/360.);

	  	UserEquipment* ue = new UserEquipment (idUE,
			                                 posX, posY, speed, speedDirection,
											 cells->at (0),
											 eNBs->at (0),
			                                 0, //handover false!
			                                 Mobility::RANDOM_DIRECTION);

	  	std::cout << "Created UE - id " << idUE << " position " << posX << " " << posY << " direction " << speedDirection << std::endl;

	  	ue->GetMobilityModel()->GetAbsolutePosition()->Print();
	  	ue->GetPhy ()->SetDlChannel (eNBs->at (0)->GetPhy ()->GetDlChannel ());
	  	ue->GetPhy ()->SetUlChannel (eNBs->at (0)->GetPhy ()->GetUlChannel ());

      	FullbandCqiManager *cqiManager = new FullbandCqiManager ();
      	cqiManager->SetCqiReportingMode (CqiManager::PERIODIC);
      	cqiManager->SetReportingInterval (1);
      	cqiManager->SetDevice (ue);
      	ue->SetCqiManager (cqiManager);

      	WidebandCqiEesmErrorModel *errorModel = new WidebandCqiEesmErrorModel ();
      	ue->GetPhy ()->SetErrorModel (errorModel);

	  	nm->GetUserEquipmentContainer ()->push_back (ue);

	  	// register ue to the enb
	  	eNBs->at (0)->RegisterUserEquipment (ue);

	  	// define the channel realization
	  	MacroCellUrbanAreaChannelRealization* c_dl = new MacroCellUrbanAreaChannelRealization (eNBs->at (0), ue);
	  	eNBs->at (0)->GetPhy ()->GetDlChannel ()->GetPropagationLossModel ()->AddChannelRealization (c_dl);
	  	MacroCellUrbanAreaChannelRealization* c_ul = new MacroCellUrbanAreaChannelRealization (ue, eNBs->at (0));
	  	eNBs->at (0)->GetPhy ()->GetUlChannel ()->GetPropagationLossModel ()->AddChannelRealization (c_ul);


	  	// CREATE DOWNLINK APPLICATION FOR THIS UE
	  	double start_time = 0.1 + GetRandomVariable (5.);
	  	double duration_time = start_time + flow_duration;

	  	// *** VOIP application
		// create application
		VoIPApplication[voipApplication].SetSource (gw);
		VoIPApplication[voipApplication].SetDestination (ue);
		VoIPApplication[voipApplication].SetApplicationID (applicationID);
		VoIPApplication[voipApplication].SetStartTime(start_time);
		VoIPApplication[voipApplication].SetStopTime(duration_time);

		QoSForFLS *qosFLS      = new QoSForFLS ();
		QoSForEXP *qosEXP      = new QoSForEXP ();
		QoSForM_LWDF *qosMLWDF = new QoSForM_LWDF ();
		QoSParameters *qosBase = new QoSParameters ();
		qosFLS  ->SetMaxDelay(maxDelay);
		qosEXP  ->SetMaxDelay(maxDelay);
		qosMLWDF->SetMaxDelay(maxDelay);
		qosBase ->SetMaxDelay(maxDelay);
		if (maxDelay == 0.1)
		{
			// std::cout << "Target Delay = 0.1 s, M = 9" << std::endl;
			qosFLS->SetNbOfCoefficients (9);
		}
		else if (maxDelay == 0.08)
		{
			// std::cout << "Target Delay = 0.08 s, M = 7" << std::endl;
			qosFLS->SetNbOfCoefficients (7);
		}
		else if (maxDelay == 0.06)
		{
			// std::cout << "Target Delay = 0.06 s, M = 5" << std::endl;
			qosFLS->SetNbOfCoefficients (5);
		}
		else if (maxDelay == 0.04)
		{
			// std::cout << "Target Delay = 0.04 s, M = 3" << std::endl;
			qosFLS->SetNbOfCoefficients (3);
		}
		else
		{
			std::cout << "ERROR: target delay is not available"<< std::endl;
			return;
		}

		// assign qos parameters
		if (downlink_scheduler_type == ENodeB::DLScheduler_TYPE_FLS)
		{
			VoIPApplication[voipApplication].SetQoSParameters (qosFLS);
		}
		else if (downlink_scheduler_type == ENodeB::DLScheduler_TYPE_EXP)
		{
			VoIPApplication[voipApplication].SetQoSParameters (qosEXP);
		}
		else if (downlink_scheduler_type == ENodeB::DLScheduler_TYPE_MLWDF)
		{
			VoIPApplication[voipApplication].SetQoSParameters (qosMLWDF);
		}
		else
		{
			VoIPApplication[voipApplication].SetQoSParameters (qosBase);
		}

		VoIPApplication[voipApplication].SetQoSAllTypes(qosEXP, qosFLS, qosMLWDF, qosBase);


		//create classifier parameters
		ClassifierParameters *cp = new ClassifierParameters (gw->GetIDNetworkNode(),
															ue->GetIDNetworkNode(),
															0,
															destinationPort,
															TransportProtocol::TRANSPORT_PROTOCOL_TYPE_UDP);
		VoIPApplication[voipApplication].SetClassifierParameters (cp);

		std::cout << "CREATED VOIP APPLICATION, ID " << applicationID << std::endl;
		flowsManager->GetApplicationContainer()->push_back(&VoIPApplication[voipApplication]);

		//update counter
		destinationPort++;
		applicationID++;
		voipApplication++;
		idUE++;
	}


  	for (int i = 0; i < nbCBR; i++){
  		//ue's random position
  		double posX = (double)rand()/RAND_MAX; posX = 0.95 *
	  	  	  (((2*radius*1000)*posX) - (radius*1000));
	  	double posY = (double)rand()/RAND_MAX; posY = 0.95 *
		  (((2*radius*1000)*posY) - (radius*1000));

	  	double speedDirection = GetRandomVariable (360.) * ((2.*3.14)/360.);

	  	UserEquipment* ue = new UserEquipment (idUE,
			                                 posX, posY, speed, speedDirection,
											 cells->at (0),
											 eNBs->at (0),
			                                 0, //handover false!
			                                 Mobility::RANDOM_DIRECTION);

	  	std::cout << "Created UE - id " << idUE << " position " << posX << " " << posY << " direction " << speedDirection << std::endl;

	  	ue->GetMobilityModel()->GetAbsolutePosition()->Print();
	  	ue->GetPhy ()->SetDlChannel (eNBs->at (0)->GetPhy ()->GetDlChannel ());
	  	ue->GetPhy ()->SetUlChannel (eNBs->at (0)->GetPhy ()->GetUlChannel ());

      	FullbandCqiManager *cqiManager = new FullbandCqiManager ();
      	cqiManager->SetCqiReportingMode (CqiManager::PERIODIC);
      	cqiManager->SetReportingInterval (1);
      	cqiManager->SetDevice (ue);
      	ue->SetCqiManager (cqiManager);

      	WidebandCqiEesmErrorModel *errorModel = new WidebandCqiEesmErrorModel ();
      	ue->GetPhy ()->SetErrorModel (errorModel);

	  	nm->GetUserEquipmentContainer ()->push_back (ue);

	  	// register ue to the enb
	  	eNBs->at (0)->RegisterUserEquipment (ue);

	  	// define the channel realization
	  	MacroCellUrbanAreaChannelRealization* c_dl = new MacroCellUrbanAreaChannelRealization (eNBs->at (0), ue);
	  	eNBs->at (0)->GetPhy ()->GetDlChannel ()->GetPropagationLossModel ()->AddChannelRealization (c_dl);
	  	MacroCellUrbanAreaChannelRealization* c_ul = new MacroCellUrbanAreaChannelRealization (ue, eNBs->at (0));
	  	eNBs->at (0)->GetPhy ()->GetUlChannel ()->GetPropagationLossModel ()->AddChannelRealization (c_ul);


	  	// CREATE DOWNLINK APPLICATION FOR THIS UE
	  	double start_time = 0.1 + GetRandomVariable (5.);
	  	double duration_time = start_time + flow_duration;

	  	// *** CBR application
	  	// create application
	  	// create application
		CBRApplication[cbrApplication].SetSource (gw);
		CBRApplication[cbrApplication].SetDestination (ue);
		CBRApplication[cbrApplication].SetApplicationID (applicationID);
		CBRApplication[cbrApplication].SetStartTime(start_time);
		CBRApplication[cbrApplication].SetStopTime(duration_time);
		CBRApplication[cbrApplication].SetInterval (0.04);
		CBRApplication[cbrApplication].SetSize (5);

		// create qos parameters
		// create qos parameters for CBR
		// CBR only uses qosBase it seems, but this is here just for completeness
		QoSForFLS *qosFLS      = new QoSForFLS ();
		// Doesnt play well with coefficients?
		qosFLS  ->SetMaxDelay(maxDelay);
		qosFLS ->SetGBR(gbrCBR);
		qosFLS ->SetDropPorbability(plrCBR);

		QoSForEXP *qosEXP      = new QoSForEXP ();
		qosEXP ->SetMaxDelay(delayCBR);
		qosEXP ->SetGBR(gbrCBR);
		qosEXP ->SetDropPorbability(plrCBR);

		QoSForM_LWDF *qosMLWDF = new QoSForM_LWDF ();
		qosMLWDF ->SetMaxDelay(delayCBR);
		qosMLWDF ->SetGBR(gbrCBR);
		qosMLWDF ->SetDropPorbability(plrCBR);

		QoSParameters *qosBase = new QoSParameters ();
		qosBase ->SetMaxDelay(delayCBR);
		qosBase ->SetGBR(gbrCBR);
		qosBase ->SetDropPorbability(plrCBR);
		if (maxDelay == 0.1){
		  		// std::cout << "Target Delay = 0.1 s, M = 9" << std::endl;
			qosFLS->SetNbOfCoefficients (9);
		} else if (maxDelay == 0.08) {
				// std::cout << "Target Delay = 0.08 s, M = 7" << std::endl;
			qosFLS->SetNbOfCoefficients (7);
		} else if (maxDelay == 0.06) {
				// std::cout << "Target Delay = 0.06 s, M = 5" << std::endl;
			qosFLS->SetNbOfCoefficients (5);
		} else if (maxDelay == 0.04) {
				// std::cout << "Target Delay = 0.04 s, M = 3" << std::endl;
			qosFLS->SetNbOfCoefficients (3);
		} else {
			std::cout << "ERROR: target delay is not available"<< std::endl;
			return;
		}

		// assign qos parameters
		if (downlink_scheduler_type == ENodeB::DLScheduler_TYPE_FLS){
			CBRApplication[cbrApplication].SetQoSParameters (qosFLS);
		} else if (downlink_scheduler_type == ENodeB::DLScheduler_TYPE_EXP) {
			CBRApplication[cbrApplication].SetQoSParameters (qosEXP);
		} else if (downlink_scheduler_type == ENodeB::DLScheduler_TYPE_MLWDF) {
			CBRApplication[cbrApplication].SetQoSParameters (qosMLWDF);
		} else {
			CBRApplication[cbrApplication].SetQoSParameters (qosBase);
		}

		CBRApplication[cbrApplication].SetQoSAllTypes(qosEXP, qosFLS, qosMLWDF, qosBase);

		//create classifier parameters
		ClassifierParameters *cp = new ClassifierParameters (gw->GetIDNetworkNode(),
															   ue->GetIDNetworkNode(),
															   0,
															   destinationPort,
															   TransportProtocol::TRANSPORT_PROTOCOL_TYPE_UDP);
		CBRApplication[cbrApplication].SetClassifierParameters (cp);

		std::cout << "CREATED CBR APPLICATION, ID " << applicationID << std::endl;
		flowsManager->GetApplicationContainer()->push_back(&CBRApplication[cbrApplication]);

		//update counter
		destinationPort++;
		applicationID++;
		cbrApplication++;
		idUE++;
	}

	simulator->SetStop(duration);
	// main loop.
	simulator->Run ();
	//Delete created objects
	cells->clear ();
	delete cells;
	eNBs->clear ();
	delete eNBs;
	delete frameManager;
	//delete nm;
	delete simulator;
}
