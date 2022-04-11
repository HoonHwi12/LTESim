#ifndef Agent_h
#define Agent_h

#include <random>
#include <chrono>
#include <torch/torch.h>

template <typename T, typename R>
class Agent{
	private:
		int current_step;
		T* strategy;
		int num_actions;
		torch::DeviceType device;
		// seed the RNG
        std::random_device rd;
        std::mt19937 mt;
        // inference time
        std::chrono::steady_clock::time_point start;
        std::chrono::steady_clock::time_point end;
	public:
		Agent(T* strategy_, int num_actions_){
			strategy     = strategy_;
			num_actions  = num_actions_ - 1; // include 0
			current_step = 0;
			device = (torch::cuda::is_available() ? torch::kCUDA : torch::kCPU);
			std::cout << "Agent Ready ~" << std::endl;
		}
		~Agent();

		torch::Tensor explore(torch::Tensor state){
			std::uniform_int_distribution<int> dist_actions(0, num_actions);
			torch::Tensor explore_action = torch::zeros(5);

			for(int ada_index=0; ada_index < 4; ada_index++)
			{
				mt.seed(rd());
				explore_action.index_put_({ada_index}, dist_actions(mt));
			}			

			explore_action.index_put_({4}, 1);
			printf("Explore!\n");
			start, end = std::chrono::steady_clock::now(); // time of zero is explore
			return explore_action;
		}


		torch::Tensor exploit(torch::Tensor state, R policy_net0, R policy_net1, R policy_net2, R policy_net3, bool timeLog){
			torch::NoGradGuard no_grad;

			start = std::chrono::steady_clock::now();
			clock_t infstart = clock();

			torch::Tensor output0 = policy_net0->forward(state);
			torch::Tensor output1 = policy_net1->forward(state);
			torch::Tensor output2 = policy_net2->forward(state);
			torch::Tensor output3 = policy_net3->forward(state);

			end = std::chrono::steady_clock::now();

			torch::Tensor exploit_action = torch::zeros(5);
			exploit_action.index_put_({0}, at::argmax(output0, 1));
			exploit_action.index_put_({1}, at::argmax(output1, 1));
			exploit_action.index_put_({2}, at::argmax(output2, 1));
			exploit_action.index_put_({3}, at::argmax(output3, 1));
			exploit_action.index_put_({4}, 0);
			
			if(timeLog) printf("InferenceTime %0.7f ms/ Exploit! \n", (float)(clock()-infstart)/CLOCKS_PER_SEC);
			else printf("Exploit! \n");
			return exploit_action;
		}



		torch::Tensor selectAction(torch::Tensor state, R policy_net0, R policy_net1, R policy_net2, R policy_net3){
			float exploration_rate = strategy->explorationRate(current_step);
			// printf("eps: %f\n", exploration_rate);
			current_step++;
			std::uniform_int_distribution<int> dist_actions(0, num_actions);
	        std::uniform_real_distribution<double> dist_rate(0.0, 1.0);
	        mt.seed(rd());
			float random_rate = dist_rate(mt);
			// printf("rdr: %f\n", random_rate)
			if(exploration_rate > random_rate){ // explore
				return explore(state);
			} else { 				
				return explore(state);			// exploit
				//return exploit(state, policy_net0, policy_net1, policy_net2, policy_net3, false);
			}
		}


		torch::Tensor CurrentQ(R policy_net, torch::Tensor states, torch::Tensor actions){
			torch::Tensor q_values = policy_net->forward(states.to(device));
			torch::Tensor max_qs   = std::get<0>(q_values.max(1));
			return max_qs;
		}

		torch::Tensor NextQ(R target_net, torch::Tensor next_states){
			torch::Tensor q_values = target_net->forward(next_states.to(device));
			torch::Tensor max_qs   = std::get<0>(q_values.max(1));
			return max_qs;
		}

		std::chrono::nanoseconds inferenceTime(){
			std::chrono::nanoseconds nano = end - start;
			return nano;
		}





	
};

#endif