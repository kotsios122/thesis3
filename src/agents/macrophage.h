#ifndef MACROPHAGE_H_
#define MACROPHAGE_H_

#include "biodynamo.h"
#include "agents/primitive_agents/wd_cells.h"

namespace bdm {

	class macrophage : public wd_cells {
		BDM_AGENT_HEADER(macrophage, wd_cells, 2);
		
		public:
			macrophage() {}
			explicit macrophage(const Real3& position) :Base(position) {}
			virtual ~macrophage() {}
			
			void Initialize(const NewAgentEvent& event) override { 
    				Base::Initialize(event);
    			
    				if (auto* mother = dynamic_cast<macrophage*>(event.existing_agent)) { 
    					//daughter's attributes
    					//cell_color_ = mother->cell_color_;
    				if (event.GetUid() == CellDivisionEvent::kUid) {
					AddBehavior(new Chemotaxis("PDGF", 1));
					SetColor(mother->GetColor());
					
				}
    			
    			}
    		}
		
			
	  	private:
	  		// The color that will be used for visualization purposes
	  				
	  	
	  	
	};

}  // namespace bdm

#endif  // MACROPHAGE_H_
