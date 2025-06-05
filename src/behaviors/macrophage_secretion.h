#ifndef MACROPHAGE_SECRETION_H_
#define MACROPHAGE_SECRETION_H_


#include "biodynamo.h"
#include "agents/primitive_agents/wd_cells.h"

namespace bdm {
	//check if the cell is inside the wound area
	struct MacrophageSecretion : public Behavior {
		BDM_BEHAVIOR_HEADER(MacrophageSecretion, Behavior, 2);
	
		public:
			MacrophageSecretion() {
				AlwaysCopyToNew();
				NeverRemoveFromExisting();
			}
			
			void Initialize(const NewAgentEvent& event) override { //initialize daughters
				Base::Initialize(event);
				auto* other = event.existing_behavior;
				if (MacrophageSecretion* casted = dynamic_cast<MacrophageSecretion*>(other)) {
					position_ = casted->position_;
				} else {
					Log::Fatal("PlateletSecretion::EventConstructor",
						"other was not of type PlateletSecretion");
				}
			}
  			
  			void Run(Agent* agent) override {
  				if (auto* cell = dynamic_cast<macrophage*>(agent)) {
  						auto* rm = Simulation::GetActive()->GetResourceManager();
      						auto* dgrid = rm->GetDiffusionGrid(0);
      						real_t conc = dgrid->GetValue(cell->GetPosition());
      						
      						if (conc > 2000) {
      							cell->SetCanDivide(true);
      						}
  			
  						if (cell->GetInsideWoundArea() && cell->GetCanDivide()) {
    							cell->AddBehavior(new Secretion("TGF-b", 2));
    						}
	
  				}
  			}
  			
		private: 
			//cell position
			Real3 position_ ;
	
	};


}//namespace bdm

#endif // MACROPHAGE_SECRETION_H_
