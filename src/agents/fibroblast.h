#ifndef FIBROBLAST_H_
#define FIBROBLAST_H_

#include "biodynamo.h"
#include "agents/primitive_agents/wd_cells.h"

namespace bdm {

	class fibroblast : public wd_cells {
		BDM_AGENT_HEADER(fibroblast, wd_cells, 4);
		
		public:
			fibroblast() {}
			explicit fibroblast(const Real3& position) :Base(position) {}
			
			void Initialize(const NewAgentEvent& event) override { 
    				Base::Initialize(event);
    			
    				if (auto* mother = dynamic_cast<fibroblast*>(event.existing_agent)) { 
    				//daughter's attributes

    					if (event.GetUid() == CellDivisionEvent::kUid) {
						//AddBehavior(new Secretion("PDGF", 1));
						AddBehavior(new Chemotaxis("TGF-b", 1.5));
						SetColor(mother->GetColor());
					}
    			
    				}
    			}
    			void Update(const NewAgentEvent& event) override {
    				Base::Update(event);

    				if (event.GetUid() == CellDivisionEvent::kUid) {
      					auto* daughter_2 = bdm_static_cast<fibroblast*>(event.new_agents[0]);
      					
      					
    				}
  			}
    			
		
			
	  	private:
	  		// The color that will be used for visualization purposes
	  		
	  	
	  	
	};

}  // namespace bdm

#endif  // fibroblast_H_
