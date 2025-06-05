#ifndef INSIDE_WOUND_AREA_H_
#define INSIDE_WOUND_AREA_H_


#include "biodynamo.h"
#include "agents/primitive_agents/wd_cells.h"
#include "agents/macrophage.h"
#include "agents/platelet.h"
#include "agents/keratinocyte.h"
#include "agents/fibroblast.h"

namespace bdm {
	//check if the cell is inside the wound area
	struct InsideWoundArea : public Behavior {
		BDM_BEHAVIOR_HEADER(InsideWoundArea, Behavior, 1);
	
		public:
			InsideWoundArea() {
				AlwaysCopyToNew();
				
			}
			
			void Initialize(const NewAgentEvent& event) override { //initialize daughters
				Base::Initialize(event);
				auto* other = event.existing_behavior;
				if (InsideWoundArea* casted = dynamic_cast<InsideWoundArea*>(other)) {
					position_ = casted->position_;
				} else {
					Log::Fatal("InsideWoundArea::EventConstructor",
						"other was not of type InsideWoundArea");
				}
			}
  			
  			void Run(Agent* agent) override {
  				if (auto* cell = dynamic_cast<wd_cells*>(agent)) {
  					//check if is inside wound area
  					//if the coordinates are inside the V-cut shape
  					// position[2] > std::abs(-2 * position[1] + 100) + 20  <--Inside wound 
  					//position[2] < std::abs(-2 * position[1] + 100) + 20  <--outside wound

    					if (cell->GetPosition()[1] - 200 > std::abs(cell->GetPosition()[0]*2 - 500)) {  //Constant Behavior during the whole simulation
    							cell->SetInsideWoundArea(true);
    							
    					}	
    					uint64_t step = Simulation::GetActive()->GetScheduler()->GetSimulatedSteps();
    						
    					if (step == 0) { 					//For the first step it removes cells
    						if (cell->GetPosition()[1] - 200 > std::abs(cell->GetPosition()[0]*2 - 500) || cell->GetPosition()[1] > 275) { //mac removed from WA and epidermis
    							if (auto* mac = dynamic_cast<macrophage*>(agent)) {
    								mac->RemoveFromSimulation();
    							}
    							if (auto* fbr = dynamic_cast<fibroblast*>(agent)) {
    								fbr->RemoveFromSimulation();
    							}
    						}	
    						
    						if (cell->GetPosition()[1] - 200 < std::abs(cell->GetPosition()[0]*2 - 500) && cell->GetPosition()[1] > 275) { //platelets removed from epidermis
    							if(auto* plt = dynamic_cast<platelet*>(agent)) {
								plt->RemoveFromSimulation();
							}
    						}
    						
    						if (cell->GetPosition()[1] < 275 || cell->GetPosition()[1] - 200 > std::abs(cell->GetPosition()[0]*2 - 500)) { 	//keratinocyte remover
    							if(auto* krt = dynamic_cast<keratinocyte*>(agent)) {
								krt->RemoveFromSimulation();
							}
    						}
    							
    						
    					
    					
    							
  					
  					}
  				}
  			}
		private: 
			//cell position
			Real3 position_ ;
	
	};


}//namespace bdm

#endif // inside_wound_area.h
