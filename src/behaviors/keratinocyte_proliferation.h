#ifndef KERATINOCYTE_PROLIFERATION_H_
#define KERATINOCYTE_PROLIFERATION_H_


#include "biodynamo.h"
#include "agents/primitive_agents/wd_cells.h"

namespace bdm {
	//check if the cell is inside the wound area
	struct KeratinocyteProliferation : public Behavior {
		BDM_BEHAVIOR_HEADER(KeratinocyteProliferation, Behavior, 3);
	
		public:
			KeratinocyteProliferation(real_t radius = 1) : squared_radius_(radius * radius) {
				AlwaysCopyToNew();
				NeverRemoveFromExisting();
			}
			
			void Initialize(const NewAgentEvent& event) override { //initialize daughters
				Base::Initialize(event);
				auto* other = event.existing_behavior;
				if (KeratinocyteProliferation* casted = dynamic_cast<KeratinocyteProliferation*>(other)) {
					position_ = casted->position_;
				} else {
					Log::Fatal("MacrophageProliferation::EventConstructor",
						"other was not of type MacrophageProliferation");
				}
			}
  			
  			void Run(Agent* agent) override {
  				if (auto* this_cell = dynamic_cast<keratinocyte*>(agent)) {

					bool found_fibroblast = false;
			
					//std::cout <<  this_cell->GetCellType() << std::end;
					auto check_for_fibroblast = L2F([&](Agent* neighbor, real_t squared_distance) {
						if (squared_distance > squared_radius_) {
							return;
						}
      						if (dynamic_cast<fibroblast*>(neighbor)) {
        						found_fibroblast = true;
      						}
					});

    					auto* ctxt = Simulation::GetActive()->GetExecutionContext();
   					ctxt->ForEachNeighbor(check_for_fibroblast, *this_cell, squared_radius_);


 					if (found_fibroblast && this_cell->GetCanDivide()) {
      						//this_cell ->SetColor(3);
      						//this_cell ->AddBehavior(new Chemotaxis("KGF", 1));
      						this_cell ->AddBehavior(new GrowthDivision(9,10));
      							
    					}
    				}
  			}
  			
		private: 
			//cell position
			Real3 position_ ;
			
			real_t squared_radius_ = 0;
	
	};


}//namespace bdm

#endif // KERATINOCYTE_PROLIFERATION_H_
