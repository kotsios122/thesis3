#ifndef FIBROBLAST_SECRETION_H_
#define FIBROBLAST_SECRETION_H_


#include "biodynamo.h"
#include "agents/primitive_agents/wd_cells.h"

namespace bdm {
	//check if the cell is inside the wound area
	struct FibroblastSecretion : public Behavior {
		BDM_BEHAVIOR_HEADER(FibroblastSecretion, Behavior, 4);
	
		public:
			FibroblastSecretion() {
				AlwaysCopyToNew();
				NeverRemoveFromExisting();
			}
			
			void Initialize(const NewAgentEvent& event) override { //initialize daughters
				Base::Initialize(event);
				auto* other = event.existing_behavior;
				if (FibroblastSecretion* casted = dynamic_cast<FibroblastSecretion*>(other)) {
					position_ = casted->position_;
				} else {
					Log::Fatal("FibroblastSecretion::EventConstructor",
						"other was not of type FibroblastSecretion");
				}
			}
  			
  			void Run(Agent* agent) override {
  				if (auto* cell = dynamic_cast<fibroblast*>(agent)) {
  						auto* rm = Simulation::GetActive()->GetResourceManager();
      						auto* dgrid = rm->GetDiffusionGrid(1);
      						real_t conc = dgrid->GetValue(cell->GetPosition());
      						
      						if (conc > 500) {
      							cell->SetCanDivide(true);
      						
      						}
  			
  						if (cell->GetInsideWoundArea() && cell->GetCanDivide()) {
    							cell->AddBehavior(new Secretion("KGF", 2));
    							
    						}
	
  				}
  			}
  			
		private: 
			//cell position
			Real3 position_ ;
	
	};


}//namespace bdm

#endif // FIBROBLAST_SECRETION_H_
