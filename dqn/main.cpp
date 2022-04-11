#include "DQN.h"
TORCH_MODULE(DQN); // shared ownership
#include "ReplayMemory.h"
#include "EpsilonGreedy.h"
#include "Agent.h"
#include "LTENetworkState.h"
#include <torch/torch.h>
// pipe includes
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
// others
#include <iostream>
#include <cstdlib>

#define STATE_FIFO "../../state_fifo"
#define SCHED_FIFO "../../sched_fifo"
#define CQI_FIFO   "../../cqi_fifo"

//extern int i_replay;

typedef std::tuple<torch::Tensor, torch::Tensor, torch::Tensor, torch::Tensor> experience;

void ConnectSchedulerFifo(int *fd);
void OpenStateFifo(int *fd, int *noUEs);
void OpenCQIFifo(int *fd);
std::string FetchState(int *fd);
std::string FetchCQIs(int *fd);
void FetchInitUEs(int *fd, LTENetworkState *network_state);
LTENetworkState* initConnections(int* _sh_fd, int* _st_fd, int* _cqi_fd);

//void SendScheduler(int *fd, int scheduler0, int scheduler1=0, int scheduler2=0, int scheduler3=0);
void SendScheduler(int *fd, int scheduler0, int scheduler1=0, int scheduler2=0, int scheduler3=0);

experience processSamples(std::vector<experience> _samples);
void loadStateDict(DQN model, DQN target_model);


/* HyperParams*/
const int BATCH_SIZE        = 32;
int TRAIN_TTI               = 7500;//7500;
const int TEST_TTI          = 2500;//2500;
const int MIN_REPLAY_MEM    = 1000;//1000;
const float GAMMA           = 0.999;  // discount factor for bellman equation
const float EPS_START       = 1.0;    // greedy stuff
const float EPS_END         = 0.01;
const float EPS_DECAY       = 0.0001;
const int NET_UPDATE        = 10;     // how many episodes until we update the target DQN 
const int MEM_SIZE          = 50000; // replay memory size
//const float LR              = 0.01;  // learning rate
const float LR_START        = 0.01;
const float LR_END          = 0.000001;
const float LR_DECAY        = 0.0001;
const float MOMENTUM        = 0.05;  // SGD MOMENTUM
 // environment concerns
const int NUM_ACTIONS       = 6;    // number of schedulers
const int CQI_SIZE          = 25;   // number of downlink channels per eNB

//Adaptive DQN
const int ADA_ACTIONS       = 10000;    // 21*21*21*21=194481
const int NUM_OUTPUT       = 4;    // 0~100 * 0.01

// training times
//std::chrono::steady_clock::time_point start;
//std::chrono::steady_clock::time_point end;
//std::chrono::nanoseconds duration;

int main(int argc, char** argv) {
	int constant_scheduler = 0;
  bool use_dqn = true;

  printf("batch(%d)/minReplay(%d)/EPS(%0.2f~%0.2f/%0.4f)/Update(%d)\n",
    BATCH_SIZE, MIN_REPLAY_MEM, EPS_START, EPS_END, EPS_DECAY, NET_UPDATE);
  // file naming
  std::string scheduler_string;

  // test time
  clock_t test_start = clock();

	if(argc > 1 ){

    // use fixed scheduler or dqn
		constant_scheduler = atoi(argv[1]);
    if(constant_scheduler==7) scheduler_string = "dqn";
    else
    {
      scheduler_string = argv[1];
      use_dqn = false;
    }
	} else {
    scheduler_string = "dqn";
  }

  std::cout << "PYTORCH version " << TORCH_VERSION << std::endl;
  
	// Decide CPU or GPU
	torch::Device device = torch::kCPU;
	std::cout << "CUDA DEVICE COUNT: " << torch::cuda::device_count() << std::endl;
	if (torch::cuda::is_available()) {
    	std::cout << "CUDA available - working on GPU." << std::endl;
    	device = torch::kCUDA;
  }
  // pipe 
  int sh_fd, st_fd, cqi_fd;
  // initial connections
  LTENetworkState* networkEnv = initConnections(&sh_fd, &st_fd, &cqi_fd);
  int noUEs = networkEnv->noUEs;

  // simulation output traces
  std::string update;
  std::string cqi_update;

   // DQN components
  torch::Tensor reset_state        =   networkEnv->reset().to(device);
  torch::Tensor state;
  ReplayMemory* exp                = new ReplayMemory(MEM_SIZE);

  EpsilonGreedy* eps               = new EpsilonGreedy(EPS_START, EPS_END, EPS_DECAY);// start, end, decay
  EpsilonGreedy* lr_rate           = new EpsilonGreedy(LR_START, LR_END, LR_DECAY);

  //Agent<EpsilonGreedy, DQN>* agent = new Agent<EpsilonGreedy, DQN>(eps,NUM_ACTIONS);
  
  Agent<EpsilonGreedy, DQN>* agent = new Agent<EpsilonGreedy, DQN>(eps,ADA_ACTIONS);

h_log("debug-1\n");
  DQN policyNet(reset_state.size(1), ADA_ACTIONS);
  DQN targetNet(reset_state.size(1), ADA_ACTIONS);
h_log("debug-2\n");

  // logging files for training 
  //  ~ please make sure that test_results/ is valid folder
  std::string log_file_name, model_name, base;
  base               = "test_results/" + scheduler_string + std::to_string(noUEs);
  log_file_name      = base + "_training.txt";
  model_name         = base + "_model.pt";

h_log("debug-3\n");
  //std::ofstream output_file0(log_file_name0);

  // std::string log_file_name1, model_name1, base1;
  // base1               = "test_results/" + scheduler_string + "1_" + std::to_string(noUEs);
  // log_file_name1      = base1 + "_training.txt";
  // model_name1         = base1 + "_model.pt";
  // //std::ofstream output_file1(log_file_name1);

  // std::string log_file_name2, model_name2, base2;
  // base2               = "test_results/" + scheduler_string + "2_" + std::to_string(noUEs);
  // log_file_name2      = base2 + "_training.txt";
  // model_name2         = base2 + "_model.pt";
  // //std::ofstream output_file2(log_file_name2);
  
  // std::string log_file_name3, model_name3, base3;
  // base3               = "test_results/" + scheduler_string + "3_" + std::to_string(noUEs);
  // log_file_name3      = base3 + "_training.txt";
  // model_name3         = base3 + "_model.pt";
  //std::ofstream output_file3(log_file_name3);
h_log("debug100\n");

  // copy weights to targetnet
  loadStateDict(policyNet, targetNet); 
  policyNet->to(device);
  targetNet->to(device);

  // setting up training variables
  std::vector<experience> samples;
h_log("debug101\n");
  torch::Tensor current_q_values, next_q_values, target_q_values;
  torch::optim::Adam optimizer(policyNet->parameters(), torch::optim::AdamOptions(LR_START));

h_log("debug102\n");


  // get update from first update packets
  update     = FetchState(&st_fd); 
  h_log("debug110\n");
  cqi_update = FetchCQIs(&cqi_fd);
  h_log("debug111\n");
  networkEnv->UpdateNetworkState(update); 
  h_log("debug112\n");
  networkEnv->ProcessCQIs(cqi_update);
  
  // training loop variables
  int valid_TTI_explore = 0;
  int valid_TTI_exploit = 0;
  float reward_copy = 0;
  int update_counter = 0;
  bool explore = true;

h_log("debug103\n");
  if(!use_dqn)
  {
    TRAIN_TTI += TEST_TTI;
  }
  while(1){ // training loop
h_log("debug while(1)\n");
  	torch::Tensor state = networkEnv->CurrentState(true);
  	networkEnv->TTI_increment();

  	// selecting an action
    torch::Tensor action = torch::zeros({2,4});
    h_log("debug200\n");

    if(use_dqn){ // select action explore/exploit in dqn
      action = agent->selectAction(state.to(device), policyNet);
    } else { // use fixed scheduler
      action.index_put_({0,0}, -1);
      action.index_put_({0,1}, constant_scheduler);
      action.index_put_({0,2}, -1);
      action.index_put_({0,3}, -1);
      action.index_put_({1}, -1);
    }
h_log("debug104\n");
  	//SendScheduler(&sh_fd, action[0].item<int>(), action[1].item<int>(), action[2].item<int>(), action[3].item<int>());
    SendScheduler(&sh_fd, action[0][0].item<int>(), action[0][1].item<int>(), action[0][2].item<int>(), action[0][3].item<int>());

  	// observe new state
  	update     = FetchState(&st_fd); 
    cqi_update = FetchCQIs(&cqi_fd);
    if(strcmp(update.c_str(), "end") == 0){ // check if end of simulation
      std::cout << "END signal received!" << std::endl;
      break;
  	}
    update_counter++;
    
    // process new state + cqis
    networkEnv->UpdateNetworkState(update); 
    networkEnv->ProcessCQIs(cqi_update);
    // next state and reward
    torch::Tensor next_state  = networkEnv->CurrentState(false);
    torch::Tensor reward = networkEnv->CalculateReward(); 
    reward_copy = reward[0].item<float>();

    // store experiece in replay memory
    exp->push(state.to(torch::kCPU), action.to(torch::kCPU), next_state.to(torch::kCPU), reward.to(torch::kCPU)); 

    //start = std::chrono::steady_clock::now(); //training time logging
    clock_t infstart=clock();

    if(use_dqn){ // if we are using dqn
    	// if enough samples
	    if(exp->canProvideSamples((size_t)MIN_REPLAY_MEM)){ 
        update_counter++;
        // access learning rate
        auto options = static_cast<torch::optim::AdamOptions&> (optimizer.defaults());
        options.lr(lr_rate->explorationRate(networkEnv->TTIcounter - MIN_REPLAY_MEM));
h_log("debug1\n");
	    	//sample random batch and process
	    	samples = exp->sampleMemory(BATCH_SIZE); 
        experience batch = processSamples(samples);
    
        // work out the qs
        current_q_values = agent->CurrentQ(policyNet, std::get<0>(batch), std::get<1>(batch));
h_log("debug2\n");
	      next_q_values = (agent->NextQ(targetNet, std::get<2>(batch))).to(torch::kCPU);
        // bellman equation
        target_q_values = (next_q_values.multiply(GAMMA)) +  std::get<3>(batch);
        // loss and backprop
        torch::Tensor loss = (torch::mse_loss(current_q_values.to(device), target_q_values.to(device))).to(device);
printf("loss %f\n", loss.item().toFloat());

        loss.set_requires_grad(true);
        optimizer.zero_grad();
        loss.backward();
        optimizer.step();
h_log("debug3\n");
        // update targetNet with policyNey parameters
        if(update_counter > NET_UPDATE){
	        // copy weights to targetnet
	        loadStateDict(policyNet, targetNet);
	        update_counter = 0;
        }
	    } // enough samples
    }// fixed scheduler

    // training time logging
    //end = std::chrono::steady_clock::now();
    //duration = end - start;    
    h_log("debug4\n");
    // checks the valid-TTI's explore/exploitation count
    if (action[1][0].item<int>() == 0) valid_TTI_exploit++;
    else if(action[1][0].item<int>() > 0) valid_TTI_explore++;
    h_log("debug5\n");
    printf("\tInferenceTime %0.7f ms\tExploit %d,\tExplore %d\n", (float)(clock()-infstart)/CLOCKS_PER_SEC, valid_TTI_exploit, valid_TTI_explore);

    //output to file 
    /*
    if((int)networkEnv->TTIcounter % 100 == 0){
      if(use_dqn){
        output_file0 << networkEnv->TTIcounter << ", " << reward_copy << ", " << valid_TTI_explore << ", " << valid_TTI_exploit << ", "  << duration.count() << std::endl;
        output_file1 << networkEnv->TTIcounter << ", " << reward_copy << ", " << valid_TTI_explore << ", " << valid_TTI_exploit << ", "  << duration.count() << std::endl;
        output_file2 << networkEnv->TTIcounter << ", " << reward_copy << ", " << valid_TTI_explore << ", " << valid_TTI_exploit << ", "  << duration.count() << std::endl;
        output_file3 << networkEnv->TTIcounter << ", " << reward_copy << ", " << valid_TTI_explore << ", " << valid_TTI_exploit << ", "  << duration.count() << std::endl;
      } else {
        output_file0 << networkEnv->TTIcounter << ", " << reward_copy <<  ", "  << duration.count() << std::endl;
        output_file1 << networkEnv->TTIcounter << ", " << reward_copy <<  ", "  << duration.count() << std::endl;
        output_file2 << networkEnv->TTIcounter << ", " << reward_copy <<  ", "  << duration.count() << std::endl;
        output_file3 << networkEnv->TTIcounter << ", " << reward_copy <<  ", "  << duration.count() << std::endl;
      }
    }
    */
    
    // decide to break to testing
    if((networkEnv->TTIcounter > TRAIN_TTI )){
      networkEnv->TTI_increment();
      // scheduler 11 stops the UEs at current position
      SendScheduler(&sh_fd, 11); 
      update     = FetchState(&st_fd); 
      cqi_update = FetchCQIs(&cqi_fd);
      if (update.size() > 0 ){
        networkEnv->UpdateNetworkState(update); 
        networkEnv->ProcessCQIs(cqi_update); 
      }
      break; // break out of training loog
    }
  }// training loop

  // log training loop satisfaction rates, false flag signals training
  //networkEnv->log_satisfaction_rates(scheduler_string, noUEs, false);
  /*
  output_file0.close();
  output_file1.close();
  output_file2.close();
  output_file3.close();
  */



  if(use_dqn){ // only testing loops for DQN
    torch::save(policyNet, model_name);
h_log("debug-10\n");
    //log_file_name0 = base0 + "_training.txt";
    //log_file_name1 = base1 + "_training.txt";
    //log_file_name2 = base2 + "_training.txt";
    //log_file_name3 = base3 + "_training.txt";

/*
    output_file0.open(log_file_name0);
    output_file1.open(log_file_name1);
    output_file2.open(log_file_name2);
    output_file3.open(log_file_name3);

    output_file0 << "TTIcounter" << ", Reward" << ", InferenceTime" << std::endl;
    output_file1 << "TTIcounter" << ", Reward" << ", InferenceTime" << std::endl;
    output_file2 << "TTIcounter" << ", Reward" << ", InferenceTime" << std::endl;
    output_file3 << "TTIcounter" << ", Reward" << ", InferenceTime" << std::endl;
*/
    int training_ttis = networkEnv->TTIcounter;

    while(1){ // testing loop
      torch::Tensor state = networkEnv->CurrentState(true); 
      networkEnv->TTI_increment();

    	// select action explore/exploit
      torch::Tensor action = agent->exploit(state.to(device), policyNet, true);

    	// execute action
      //HH
      //printf(" parameter: %d / %d / %d / %d\n", action[0].item<int>(), action[1].item<int>(), action[2].item<int>(), action[3].item<int>());

      //SendScheduler(&sh_fd, action[0].item<int>(), action[1].item<int>(), action[2].item<int>(), action[3].item<int>());
      SendScheduler(&sh_fd, action[0][0].item<int>(), action[0][1].item<int>(), action[0][2].item<int>(), action[0][3].item<int>());
      h_log("debug-11\n");
      // observe new state
      update     = FetchState(&st_fd); 
      cqi_update = FetchCQIs(&cqi_fd);
      // check if end of simulation
      if(strcmp(update.c_str(), "end") == 0){
        std::cout << "END signal received!" << std::endl;
        break;
      }
      networkEnv->UpdateNetworkState(update); // process new state
      networkEnv->ProcessCQIs(cqi_update); // process cqis
      torch::Tensor reward = networkEnv->CalculateReward(); // observe reward
      reward_copy = reward[0].item<float>();

/*
      output_file0 << networkEnv->TTIcounter << ", " << reward_copy << ", "<< agent->inferenceTime().count() << std::endl;
      output_file1 << networkEnv->TTIcounter << ", " << reward_copy << ", "<< agent->inferenceTime().count() << std::endl;
      output_file2 << networkEnv->TTIcounter << ", " << reward_copy << ", "<< agent->inferenceTime().count() << std::endl;
      output_file3 << networkEnv->TTIcounter << ", " << reward_copy << ", "<< agent->inferenceTime().count() << std::endl;
*/
h_log("debug-12\n");
      if(networkEnv->TTIcounter == (training_ttis + TEST_TTI)) break;
    } // testing loop

    /*
    output_file0.close();
    output_file1.close();
    output_file2.close();
    output_file3.close();
    */

    //networkEnv->log_satisfaction_rates(scheduler_string, noUEs, true);
  } // only dqn should test loop

  close(sh_fd);
  close(st_fd);
  close(cqi_fd);
  delete networkEnv;

  printf("TEST END, Test Duration: %0.4f s\n", (float)(clock()-test_start) / CLOCKS_PER_SEC);

  return 0;
}

void loadStateDict(DQN model, DQN target_model) {
  torch::autograd::GradMode::set_enabled(false);  // make parameters copying possible
  auto new_params = target_model->named_parameters(); // implement this
  auto params = model->named_parameters(true /*recurse*/);
  auto buffers = model->named_buffers(true /*recurse*/);
  for (auto& val : new_params) {
    auto name = val.key();
    auto* t = params.find(name);
    if (t != nullptr) {
      t->copy_(val.value());
    } else {
      t = buffers.find(name);
      if (t != nullptr) {
        t->copy_(val.value());
      }
    }
  }
}

experience processSamples(std::vector<experience> _samples){
  std::vector<torch::Tensor> states;
  std::vector<torch::Tensor> actions;
  std::vector<torch::Tensor> new_states;
  std::vector<torch::Tensor> rewards;
  for (auto i : _samples){
    states.push_back(std::get<0>(i));
    actions.push_back(std::get<1>(i));
    new_states.push_back(std::get<2>(i));
    rewards.push_back(std::get<3>(i));
  }

  torch::Tensor states_tensor = torch::zeros(0);
  torch::Tensor new_states_tensor = torch::zeros(0);
  torch::Tensor actions_tensor = torch::zeros({0,4});
  torch::Tensor rewards_tensor = torch::zeros(0);

  states_tensor = torch::cat(states, 0);
  actions_tensor = torch::cat(actions, 0);
  new_states_tensor = torch::cat(new_states, 0);
  rewards_tensor = torch::cat(rewards, 0);

  experience _batch(states_tensor , actions_tensor, new_states_tensor , rewards_tensor);
  return _batch;
}

void ConnectSchedulerFifo(int *fd){
  // connect to scheduler fifo
  *fd = open(SCHED_FIFO, O_CREAT|O_WRONLY);
  close(*fd);
}

void OpenCQIFifo(int *fd){
  // create the cqi fifo
  mkfifo(CQI_FIFO, S_IFIFO|0640);
  // block for LTESim to connect
  *fd = open(CQI_FIFO, O_RDONLY);
  close(*fd);
}

void OpenStateFifo(int *fd, int *noUEs){
  // create the state fifo
  mkfifo(STATE_FIFO, S_IFIFO|0777);
  char noUEs_in[80];
  int input_bytes;

  // block for LTESim to connect
  *fd = open(STATE_FIFO, O_RDONLY);
  
  // read the number of UEs
  input_bytes = read(*fd, noUEs_in, sizeof(noUEs_in));
  close(*fd);
  *noUEs = atoi(noUEs_in);
}

std::string FetchState(int *fd){
  // read state size
  *fd = open(STATE_FIFO, O_RDONLY);
  std::string::size_type size;
  read(*fd, &size, sizeof(size));
  // read state/update from LTEsim
  std::string message(size, ' ');
  read(*fd, &message[0], size);
  close(*fd);
  return message;
}

std::string FetchCQIs(int *fd){
  // read CQI message size
  *fd = open(CQI_FIFO, O_RDONLY);
  std::string::size_type size;
  read(*fd, &size, sizeof(size));
  std::string message(size, ' ');
  // read the CQIs
  read(*fd, &message[0], size);
  close(*fd);
  return message;
}

void FetchInitUEs(int *fd, LTENetworkState *network_state){
  // read size of UE summary
  *fd = open(STATE_FIFO, O_RDONLY);
  h_log("debug600\n");
  std::string::size_type size;
  read(*fd, &size, sizeof(size));
  h_log("debug601\n");
  std::string message(size, ' ');
  h_log("debug604\n");
  // read the UE summary
  read(*fd, &message[0], size);
  h_log("debug602\n");
  close(*fd);
  network_state->InitState(message);
  h_log("debug603\n");
}

void SendScheduler(int *fd, int scheduler0, int scheduler1, int scheduler2, int scheduler3){
  std::string sched = std::to_string(scheduler0)+"|"+
                      std::to_string(scheduler1)+"|"+
                      std::to_string(scheduler2)+"|"+
                      std::to_string(scheduler3);

  char const *scheduler_send = sched.c_str();
  // send scheduler
  *fd = open(SCHED_FIFO, O_CREAT|O_WRONLY);
  write(*fd, scheduler_send, strlen(scheduler_send));

  close(*fd);
}


LTENetworkState* initConnections(int* _sh_fd, int* _st_fd, int* _cqi_fd){
	// connect to the scheduler pipe
	ConnectSchedulerFifo(_sh_fd);
  printf("connect scheduler fifo\n");
	// open CQI fifo
  
  OpenCQIFifo(_cqi_fd);
printf("opencqi fifo\n");
  // open state fifo,connect and fetch #UEs
  int _noUEs = 0;
  OpenStateFifo(_st_fd, &_noUEs);
  printf("openstate fifo\n");
  
  // initialise the network state environment
  LTENetworkState *networkEnv = new LTENetworkState(_noUEs, CQI_SIZE);
  h_log("debug500\n");
  // initialise UE and Application from LTE-sim
  FetchInitUEs(_st_fd, networkEnv);
  h_log("debug501\n");
  // print a summary
  networkEnv->print_summary();
  return networkEnv;

}
