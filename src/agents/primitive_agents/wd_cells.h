#ifndef wd_cells_H_
#define wd_cells_H_

#include "biodynamo.h"

namespace bdm { 
	
	class wd_cells : public Cell {
		BDM_AGENT_HEADER(wd_cells, Cell, 1);	
	
		public:
			wd_cells() {}
			explicit wd_cells(const Real3& position) : Base(position) {}
			virtual ~wd_cells() {}
		
		
		
			//Getters and Setters of private functions
			void SetCanDivide(bool a) { can_divide_ =  a; }   //can divide
  			bool GetCanDivide() const { return can_divide_; }

			void SetInsideWoundArea(bool b) { InsideWoundArea_ =  b; }  //InsideWoundArea
  			bool GetInsideWoundArea() const { return InsideWoundArea_; }

			void SetCellType(int c) { cell_type_ =  c; } // CellType
  			bool GetCellType() const { return cell_type_; }

			void SetColor(int a) { cell_color_ = a ;}
			int GetColor() { return cell_color_ ;}
			
		private:
			//True if cells are inside wound area
			bool InsideWoundArea_;
		
			//Can_divide
			bool can_divide_;
		
			//Cell Type 
			int cell_type_;
			
			size_t cell_color_ ; 
		
	};

};
#endif //wd_cells_H_
