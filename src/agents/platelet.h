#ifndef PLATELET_H_
#define PLATELET_H_

#include "biodynamo.h"
#include "agents/primitive_agents/wd_cells.h"

namespace bdm {

	class platelet : public wd_cells {
		BDM_AGENT_HEADER(platelet, wd_cells, 1);
		
		public:
			platelet() {}
			explicit platelet(const Real3& position) :Base(position) {}
			
			void Initialize(const NewAgentEvent& event) override { 
    				Base::Initialize(event);
    			
    				if (auto* mother = dynamic_cast<platelet*>(event.existing_agent)) { 
    				//daughter's attributes
    					if (event.GetUid() == CellDivisionEvent::kUid) {
						//AddBehavior(new Secretion("PDGF", 1));
						AddBehavior(new Chemotaxis("PDGF", 0.75));
						SetColor(mother->GetColor());
					}
    			
    				}
    			}
    			void Update(const NewAgentEvent& event) override {
    				Base::Update(event);

    				if (event.GetUid() == CellDivisionEvent::kUid) {
      					auto* daughter_2 = bdm_static_cast<platelet*>(event.new_agents[0]);
      					
      					
    				}
  			}
    			
		
			
	  	private:
	  		// The color that will be used for visualization purposes
	  		
	  	
	  	
	};

}  // namespace bdm

#endif  // platelet_H_
