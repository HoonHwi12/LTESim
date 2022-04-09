#ifndef LTENetworkState_h
#define LTENetworkState_h

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <sstream> 

#include <torch/torch.h>

typedef std::pair<int, int> id_size_pair;

enum ApplicationType
{
	APPLICATION_TYPE_VOIP,
	APPLICATION_TYPE_TRACE_BASED,
	APPLICATION_TYPE_INFINITE_BUFFER,
	APPLICATION_TYPE_CBR,
	APPLICATION_TYPE_WEB
};

struct Application
{
	int id;
	ApplicationType type; // not used yet
	float QoSgbr;
	float QoSdelay;
	float QoSplr;
	float appTXCount;
	float appRXCount;
	float appSatDelayCount;
	float appSatDelayRate;
	float appSatPLRCount;
	float appSatPLRRate;
	float appSatGBRCount;
	float appSatGBRRate;
	float appMessageSizes;

	float running_gbr;

	
	float realgbr;
	float realdelay;
	float realplr;
	float reward;
	Application(int id_ ,float gbr, float delay, float plr){
		id = id_;
		QoSgbr           = gbr;
		QoSdelay         = delay;
		QoSplr           = plr;
		appTXCount       = 0;
		appRXCount       = 0;
		appSatPLRCount   = 0;
		appSatPLRRate    = 0;
		appSatDelayCount = 0;
		appSatDelayRate  = 0;
		appSatGBRCount   = 0;
		appSatGBRRate    = 0;
		appMessageSizes  = 0;
		reward           = 0;
		realplr          = 0;
		realdelay        = 0;
		realgbr          = 0;
	}
};

struct UESummary
{
	int id;
	float ave_gbr;
	float ave_delay;
	float ave_plr;
	float TXCount;
	float RXCount;
	float SatDelayCount;
	float SatDelayRate;
	float SatPLRCount;
	float SatPLRRate;
	float SatGBRCount;
	float SatGBRRate;
	std::vector<Application*> *applications;
	std::vector<int> *cqi;
	UESummary(int id_){
		applications = new std::vector<Application*>;
		cqi          = new std::vector<int>;
		id           = id_;
		TXCount      = 0;
		RXCount      = 0;
		SatPLRCount  = 0;
		SatPLRRate   = 0;
		SatDelayCount= 0;
		SatDelayRate = 0;
		SatGBRCount  = 0;
		SatGBRRate   = 0;
	}

	~UESummary(){
		for (std::vector<Application*>::iterator it = applications->begin(); it != applications->end(); ++it){
			delete *it;
		}
		delete applications;
		delete cqi;
	}

	int GetID(){
		return id;
	}

	std::vector<Application*>* GetApplicationContainer(){
		return applications;
	};

	std::vector<int>* GetCQIContainer(){
		return cqi;
	}

	Application* GetApplication(float test_id){
		float known_id;
		Application* summary;
		for (std::vector<Application*>::iterator it = applications->begin(); it != applications->end(); ++it){
			known_id = (*it)->id;
			if(known_id == test_id){
				summary = *it;
				return summary;
			}
		}
		return summary;
	}
};

class LTENetworkState{
	public:
		LTENetworkState(int noUEs_, int _cqi_size){
			UESummaries  = new std::vector<UESummary*>;
			TTIbuffer    = new std::deque<std::vector<id_size_pair>>;
			noUEs        = noUEs_;
			cqi_size     = _cqi_size;
			noAPPs       = 0;
			TTIcounter   = 0;
			Accum_Reward = 0;
		}

		~LTENetworkState(){
			for (std::vector<UESummary*>::iterator it = UESummaries->begin(); it != UESummaries->end(); ++it){
				delete *it;
			}
			delete UESummaries;
			delete TTIbuffer;
		}

		void InitState(std::string UESummaries){
			UESummary* this_UE;
			// {UE id} {APP id} {APP GBR} {APP delay} {APP PLR}
			std::stringstream s_summary;
			std::string line;
			double UEid_field, APPid_field, APPgbr_field, APPdelay_field, APPplr_field;
		    //Storing the whole string into string stream
		    s_summary << UESummaries; 
		    // get a line
		    while (std::getline(s_summary, line)) 
		    { 
		    	std::stringstream s_line;
		    	s_line << line;
		    	// get each field
		    	s_line >> UEid_field;
		    	// check if the UE is already known
		    	if(!CheckIfUERegistered(UEid_field)){
		    		// if unknown make a new summary for it
		    		this_UE = new UESummary((int)UEid_field);
		    		GetUESummaryContainer()->push_back(this_UE);
		    	} else {
		    		// otherwise find and return its existing summary
		    		this_UE = GetUESummary(UEid_field);
		    	}
		    	// each line is a unique app, so  we can assume that it is new
		    	s_line >> APPid_field;
		    	s_line >> APPgbr_field;
		    	s_line >> APPdelay_field;
		    	s_line >> APPplr_field;
		    	Application* this_app = new Application((int)APPid_field, APPgbr_field, APPdelay_field, APPplr_field);
		    	this_UE->applications->push_back(this_app);
		    	
		    }
		    // gather number of apps
		    for (std::vector<UESummary*>::iterator it = GetUESummaryContainer()->begin(); it != GetUESummaryContainer()->end(); ++it){
				this_UE = (*it);
				noAPPs += (int)(this_UE->applications->size());
			}
			// form the state size
			// 1(#ues) + Each UE's(App QoS + cqi)
		    state_size = 1+noUEs*(3*noAPPs + cqi_size);
		    reset_state = torch::ones({1, state_size});
		}

		bool CheckIfUERegistered(float test_id){
			int known_id;
			for (std::vector<UESummary*>::iterator it = GetUESummaryContainer()->begin(); it != GetUESummaryContainer()->end(); ++it){
				known_id = (*it)->GetID();
				if(known_id == (int)test_id){
					return true;
				}
			}
			return false;
		}

		UESummary* GetUESummary(float test_id){
			float known_id;
			UESummary* summary;
			for (std::vector<UESummary*>::iterator it = GetUESummaryContainer()->begin(); it != GetUESummaryContainer()->end(); ++it){
				known_id = (*it)->id;
				if(known_id == test_id){
					summary = *it;
					return summary;
				}
			}
			return summary;
		}

		std::vector<UESummary*>* GetUESummaryContainer(){
			return UESummaries;
		};

		torch::Tensor CurrentState(bool print_qos){
			
			UESummary* this_UE;
			Application* this_app;
			float gbr_indicator, plr_indicator, delay_indicator;
			std::vector<int> *this_UE_cqis;
			state = torch::ones({1, state_size});
			using namespace torch::indexing;
			// Number of UEs
			state.index_put_({0,0}, noUEs); 
			int index = 1;

			//HH
			int sum_counter=0;
			float gbr_sum = 0;
			float plr_sum = 0;
			float delay_sum = 0;

			for (std::vector<UESummary*>::iterator it = GetUESummaryContainer()->begin(); it != GetUESummaryContainer()->end(); ++it){
				this_UE = (*it);
				// app QoS
				for (std::vector<Application*>::iterator itt = this_UE->GetApplicationContainer()->begin(); itt != this_UE->GetApplicationContainer()->end(); ++itt){
					this_app = (*itt);
					// indicator = requirement - measured
					//gbr_indicator = this_app->QoSgbr - this_app->realgbr;
					gbr_indicator = this_app->realgbr - this_app->QoSgbr;
					state.index_put_({0,index}, gbr_indicator);
					index++;
					delay_indicator = this_app->QoSdelay - this_app->realdelay;
					state.index_put_({0,index}, delay_indicator);
					index++;
					plr_indicator = this_app->QoSplr - this_app->realplr;
					state.index_put_({0,index}, plr_indicator);
					index++;

					gbr_sum += this_app->realgbr;
					plr_sum += this_app->realplr;
					delay_sum += this_app->realdelay;
					sum_counter++;
				}
				// UE CQIs
				this_UE_cqis = this_UE->GetCQIContainer();
				for (std::vector<int>::iterator ittt = this_UE_cqis->begin(); ittt != this_UE_cqis->end(); ++ittt){
					state.index_put_({0,index}, (*ittt));
					index++;
				}
			}

			if(print_qos) printf("TTI:%f/ AVgbr/AVdelay/AVplr %f %f %f\n", TTIcounter, gbr_sum/sum_counter,delay_sum/sum_counter, plr_sum/sum_counter);

			return state;

		}

		void UpdateNetworkState(std::string update){
			std::stringstream s_summary;
			std::string line;
			std::string txrx_field, app_field, ID_field, b_field, size_field, src_field, dst_field, td_field;
			float  ID_num_field, b_num_field, size_num_field, src_num_field, td_num_field, empt_field;
			int dst_num_field;
			// hold the id_size pairs for this TTI
			std::vector<id_size_pair> tti_pairs;
			
			s_summary << update; 
			// for each lines in the update
		    while (std::getline(s_summary, line)) { 
		    	std::stringstream s_line;
		    	s_line << line;
		    	// get each field
		    	s_line >> txrx_field;
		    	if(txrx_field == "TX"){
		    		s_line >> app_field;
					s_line >> ID_field;
					s_line >> ID_num_field;
					s_line >> b_field;
					s_line >> b_num_field;
					s_line >> size_field;
					s_line >> size_num_field;
					s_line >> src_field;
					s_line >> src_num_field;
					s_line >> dst_field;
					s_line >> dst_num_field;
					s_line >> td_field;	
					s_line >> td_num_field;
					s_line >> empt_field;

					UESummary* this_UE = GetUESummary(dst_num_field);
					Application* this_app = this_UE->GetApplication(b_num_field);

					// update the application real PLR
					this_app->appTXCount ++;
					this_UE->TXCount++;
					this_app->realplr = 1 - (this_app->appRXCount) / (this_app->appTXCount);

					//PLR satisfied
					if (this_app->realplr < this_app->QoSplr) {
						this_app->appSatPLRCount ++;
						this_UE->SatPLRCount++;
					}
					// PLR satisification rates
					this_UE->SatPLRRate = (this_UE->SatPLRCount)/((this_UE->TXCount)+(this_UE->RXCount));
					this_app->appSatPLRRate = (this_app->appSatPLRCount)/(TTIcounter);
		    	// RX case
				} else {
		    		s_line >> app_field;
					s_line >> ID_field;
					s_line >> ID_num_field;
					s_line >> b_field;
					s_line >> b_num_field;
					s_line >> size_field;
					s_line >> size_num_field;
					s_line >> src_field;
					s_line >> src_num_field;
					s_line >> dst_field;
					s_line >> dst_num_field;
					s_line >> td_field;
					s_line >> td_num_field;
					s_line >> empt_field;

					UESummary* this_UE = GetUESummary(dst_num_field);
					Application* this_app = this_UE->GetApplication(b_num_field);
					
					// Update this RX's delay and PLR
					this_app->realdelay = td_num_field; // we said that we will use the running average?
					this_app->appRXCount++;
					this_UE->RXCount++;
					this_app->realplr = 1 - (this_app->appRXCount) / (this_app->appTXCount);

					//PLR satisfied
					if (this_app->realplr < this_app->QoSplr) {
						this_app->appSatPLRCount ++;
						this_UE->SatPLRCount++;
					}
					// PLR satisification rates
					this_UE->SatPLRRate = (this_UE->SatPLRCount)/((this_UE->TXCount)+(this_UE->RXCount));
					this_app->appSatPLRRate = (this_app->appSatPLRCount)/(TTIcounter);


					//Delay satisfied
					if (this_app->realdelay < this_app->QoSdelay) {
						this_app->appSatDelayCount ++;
						this_UE->SatDelayCount++;
					}
					// Delay satisification rates
					this_UE->SatDelayRate = (this_UE->SatDelayCount)/(this_UE->RXCount);
					this_app->appSatDelayRate = (this_app->appSatDelayCount)/(TTIcounter);

					// add the id_size pair for this application
					tti_pairs.push_back(id_size_pair((int)b_num_field,(int)size_num_field));

					// Calculate application's GBR (running average over the buffer)
					// find all received messages in the buffer
					int message_sizes_in_buffer = 0;
					int tti_index = 0;
					for (std::deque<std::vector<id_size_pair>>::iterator tti = TTIbuffer->begin(); tti != TTIbuffer->end(); ++tti){
						tti_index++;
						std::vector<id_size_pair> this_tti = *tti;
						for (std::vector<id_size_pair>::iterator this_pair = this_tti.begin(); this_pair != this_tti.end(); ++this_pair){
							if(this_pair->first == b_num_field){
								message_sizes_in_buffer += this_pair->second;
							}
						}
					}
					this_app->appMessageSizes += size_num_field;
					this_app->realgbr = (8*message_sizes_in_buffer) / (TTIbuffer->size());

					//GBR satisfied
					if (this_app->realgbr > this_app->QoSgbr) {
						this_app->appSatGBRCount ++;
						this_UE->SatGBRCount++;
					}
					// GBR satisification rates
					this_UE->SatGBRRate = (this_UE->SatGBRCount)/(this_UE->RXCount);
					this_app->appSatGBRRate = (this_app->appSatGBRCount)/(TTIcounter);
		    	}
		    }
		    // pop if we reached capacity
		    if(TTIbuffer->size() == 1000) TTIbuffer->pop_back();
		    // save this TTI id_size pair to the buffer
			TTIbuffer->push_front(tti_pairs);
			
		}

		torch::Tensor reset(){
			UESummary* this_UE;
			Application* this_app;
			std::vector<int> *this_UE_cqis;
			using namespace torch::indexing;
			// Number of UEs
			reset_state.index_put_({0,0}, noUEs); 
			int index = 1;
			for (std::vector<UESummary*>::iterator it = GetUESummaryContainer()->begin(); it != GetUESummaryContainer()->end(); ++it){
				this_UE = (*it);
				// app QoS
				for (std::vector<Application*>::iterator itt = this_UE->GetApplicationContainer()->begin(); itt != this_UE->GetApplicationContainer()->end(); ++itt){
					this_app = (*itt);
					reset_state.index_put_({0,index}, this_app->QoSgbr);
					index++;
					reset_state.index_put_({0,index}, this_app->QoSdelay);
					index++;
					reset_state.index_put_({0,index}, this_app->QoSplr);
					index++;
				}
				// UE CQIs
				this_UE_cqis = this_UE->GetCQIContainer();
				for (std::vector<int>::iterator ittt = this_UE_cqis->begin(); ittt != this_UE_cqis->end(); ++ittt){
					reset_state.index_put_({0,index}, (*ittt));
					index++;
				}
			}
			return reset_state;
		}
		torch::Tensor CalculateReward(){
			float reward = 0;
        	float gbrReward = 0;
         	float plrReward = 0;
         	float delayReward = 0;
         	float sum_reward = 0;

         	float gbr_coef = 0.3;
         	float plr_coef = 0.3;
         	float dly_coef = 0.3;

			int num_counter=0;
			float sumgbr=0;
			float sumdelay=0;
			float sumplr=0;

         	RealReward = torch::zeros(1);
	      	for (std::vector<UESummary*>::iterator it = GetUESummaryContainer()->begin(); it != GetUESummaryContainer()->end(); ++it){
	         	for (std::vector<Application*>::iterator itt = (*it)->GetApplicationContainer()->begin(); itt != (*it)->GetApplicationContainer()->end(); ++itt){

					if ((*(*itt)).realgbr >= (*(*itt)).QoSgbr) {
		               //gbrReward = 1;
					   gbrReward = 1;
		            }
		            else {
		               //gbrReward = 0;
					   gbrReward = (*(*itt)).realgbr/(*(*itt)).QoSgbr;
		            }   

		            // there has been a TX
		            if((*(*itt)).appTXCount > 0){
		            	if ((*(*itt)).realplr <= (*(*itt)).QoSplr) {
		               		plrReward = 1;
		            	} else {
		               		//plrReward = 0;
							plrReward = 1 - ((*(*itt)).realplr - (*(*itt)).QoSplr)/(*(*itt)).realplr;
							if(plrReward<0) plrReward=0;
		            	}  
		            // there hasnt been a TX
		            } else {
		            	plrReward = 0;
		            }
 					
 					//if there has been a RX
					if((*(*itt)).appRXCount > 0){
			            if ((*(*itt)).realdelay <= (*(*itt)).QoSdelay) {
			               delayReward = 1;
			            } else {
			               //delayReward = 0;
						   delayReward = 1 - ((*(*itt)).realdelay - (*(*itt)).QoSdelay)/(*(*itt)).realplr;
						   if(delayReward<0) delayReward=0;
			            }
			        // there hasnt been an RX
			        } else {
			        	delayReward = 0;
			        }

	            	(*(*itt)).reward = gbr_coef*gbrReward + plr_coef*plrReward + dly_coef*delayReward;  
					sum_reward += (*(*itt)).reward; 

					sumgbr += (*(*itt)).realgbr;
					sumdelay += (*(*itt)).realdelay;
					sumplr += (*(*itt)).realplr;
					num_counter++;
	         	}
	      	}
			sum_reward = sum_reward / (float) noUEs ;
			Accum_Reward += sum_reward;
			printf("\tAt %d TTI, TTI Reward= %f, \tAccum_reward= %f, #UEs %d\n", (int)TTIcounter, sum_reward, Accum_Reward, noUEs);
			
			RealReward.index_put_({0}, sum_reward);
	      	return RealReward;  
      	}  

		void ProcessCQIs(std::string cqis){
			// {ue1_CQI1} {ue1_CQI2} ... {ue1_CQIN}
			// {ue2_CQI1} {ue2_CQI2} ... {ue2_CQIN}
			// UE as sorted in ID ascending order.
			// Each line of the CQI update is for a new UE in the same order as they are stored.
			UESummary* thisUE;
			std::stringstream cqiStream;
			std::string line;
			int thisCQI;
		    //Storing the whole string into string stream
		    cqiStream << cqis; 
			for (std::vector<UESummary*>::iterator it = GetUESummaryContainer()->begin(); it != GetUESummaryContainer()->end(); ++it){
				thisUE = (*it);
				thisUE->GetCQIContainer()->clear();
				std::getline(cqiStream, line);
				std::stringstream lineStream;
				lineStream << line;
				int index = 0;
				while(lineStream >> thisCQI){
					thisUE->GetCQIContainer()->push_back(thisCQI);
				}
			}
		}

		void print_summary(){
			for (std::vector<UESummary*>::iterator it = GetUESummaryContainer()->begin(); it != GetUESummaryContainer()->end(); ++it){
				printf("UE id#%d\n", (*it)->GetID() );
				for (std::vector<Application*>::iterator itt = (*it)->GetApplicationContainer()->begin(); itt != (*it)->GetApplicationContainer()->end(); ++itt){
					printf("appID: %d appGBR: %f appDelay: %f appPLR: %f cqi:\n", (int)(*(*itt)).id,  (*(*itt)).QoSgbr, (*(*itt)).QoSdelay, (*(*itt)).QoSplr );
				}
				std::vector<int> *thisCQIs = (*it)->GetCQIContainer();		
				printf("[");
				for (int i = 0; i < thisCQIs->size(); i++){
					printf(" %d ", thisCQIs->at(i));
				}
				printf("]\n");
			}
		}

		void TTI_increment(){
			//increment TTI
			TTIcounter++;
		}
		
		
		void print_buffer(){
			int tti_index = 0;
			for (std::deque<std::vector<id_size_pair>>::iterator tti = TTIbuffer->begin(); tti != TTIbuffer->end(); ++tti){
				printf("TTI #%d {\n", tti_index);
				tti_index++;
				std::vector<id_size_pair> this_tti = *tti;
				for (std::vector<id_size_pair>::iterator this_pair = this_tti.begin(); this_pair != this_tti.end(); ++this_pair){
					printf(" App ID: %d Message Size: %d\n", (int)(this_pair->first), this_pair->second);
				}
				printf("}\n");
			}
		}

		void log_satisfaction_rates(std::string sched, int _noUEs, bool testing){
			  // satisfaction rates
			std::string file_name;
			if(testing){
				file_name = "test_results/" + sched + "_" + std::to_string(noUEs) + "_test_satis.txt";
			} else {
				file_name = "test_results/" + sched + "_" + std::to_string(noUEs) + "_train_satis.txt";
			}
  			
  			std::ofstream output_file(file_name);
			for (std::vector<UESummary*>::iterator it = UESummaries->begin(); it != UESummaries->end(); ++it){
				UESummary* this_UE = *it;
				std::vector<Application*> *appcontainer = this_UE->GetApplicationContainer();
				for(std::vector<Application*>::iterator itt = appcontainer->begin(); itt != appcontainer->end(); ++itt){
					Application* this_app = *itt;
					output_file << this_app->id << ", " << this_app->appSatPLRCount << std::endl;
					output_file << this_app->id << ", " << this_app->appSatDelayCount << std::endl;
					output_file << this_app->id << ", " << this_app->appSatGBRCount << std::endl;
				}
			} 
			output_file.close();

		}

	private:
		torch::Tensor reset_state;
		torch::Tensor RealReward;
		torch::Tensor state;
		int state_size;
		int cqi_size;
		
		float Accum_Reward;
		std::deque<std::vector<id_size_pair>>* TTIbuffer;

		std::vector<UESummary*> *UESummaries;
	public:
		float TTIcounter;
		int noAPPs;
		int noUEs;
};
#endif