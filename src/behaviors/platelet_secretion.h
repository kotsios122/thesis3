#ifndef PLATELET_SECRETION_H_
#define PLATELET_SECRETION_H_


#include "biodynamo.h"
#include "agents/primitive_agents/wd_cells.h"

namespace bdm {
	//check if the cell is inside the wound area
	struct PlateletSecretion : public Behavior {
		BDM_BEHAVIOR_HEADER(PlateletSecretion, Behavior, 2);
	
		public:
			PlateletSecretion() {
				AlwaysCopyToNew();
				NeverRemoveFromExisting();
			}
			
			void Initialize(const NewAgentEvent& event) override { //initialize daughters
				Base::Initialize(event);
				auto* other = event.existing_behavior;
				if (PlateletSecretion* casted = dynamic_cast<PlateletSecretion*>(other)) {
					position_ = casted->position_;
				} else {
					Log::Fatal("PlateletSecretion::EventConstructor",
						"other was not of type PlateletSecretion");
				}
			}
  			
  			void Run(Agent* agent) override {
  				if (auto* cell = dynamic_cast<platelet*>(agent)) {
  					if (cell->GetInsideWoundArea()) {
    						cell->AddBehavior(new Secretion("PDGF", 1));
    						cell->SetColor(4);
    						//cell->AddBehavior(new Chemotaxis("PDGF", 0.25)); //not needed
    						//cell->AddBehavior(new GrowthDivision(5,1));
  					}
  				}
  			}
  			
		private: 
			//cell position
			Real3 position_ ;
	
	};


}//namespace bdm

#endif // PLATELET_SECRETION_H_
