#ifndef KERATINOCYTE_H_
#define KERATINOCYTE_H_

#include "biodynamo.h"
#include "agents/primitive_agents/wd_cells.h"

namespace bdm {

	class keratinocyte : public wd_cells {
		BDM_AGENT_HEADER(keratinocyte, wd_cells, 3);
		
		public:
			keratinocyte() {}
			explicit keratinocyte(const Real3& position) :Base(position) {}
			
			void Initialize(const NewAgentEvent& event) override { 
    				Base::Initialize(event);
    			
    				if (auto* mother = dynamic_cast<keratinocyte*>(event.existing_agent)) { 
    				//daughter's attributes
    					if (event.GetUid() == CellDivisionEvent::kUid) {
						//cell division event actions
					}
    			
    				}
    			}
    			void Update(const NewAgentEvent& event) override {
    				Base::Update(event);

    				if (event.GetUid() == CellDivisionEvent::kUid) {
      					auto* daughter_2 = bdm_static_cast<keratinocyte*>(event.new_agents[0]);
      					//mother attributes
      					
    				}
  			}
    			
		
			//getters and setters 
			void SetActivation(bool a) {is_activated_ = a;}
			bool GetActivation() {return is_activated_;}
			
	  	private:
	  		// activation for proliferation and migration
	  		bool is_activated_;
	  	
	  	
	};

}  // namespace bdm

#endif  // KERATINOCYTE_H_
