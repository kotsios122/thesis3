// -----------------------------------------------------------------------------

// Copyright (C) 2021 CERN & University of Surrey for the benefit of the
// BioDynaMo collaboration. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
//
// See the LICENSE file distributed with this work for details.
// See the NOTICE file distributed with this work for additional information
// regarding copyright ownership.
//
// -----------------------------------------------------------------------------
#ifndef WOUNDHEALING_CELLS_H_
#define WOUNDHEALING_CELLS_H_


#include "biodynamo.h"
#include "agents/primitive_agents/wd_cells.h"
#include "agents/platelet.h"
#include "agents/macrophage.h"
#include "agents/keratinocyte.h"

#include "behaviors/inside_wound_area.h"
#include "behaviors/random_walk_module.h"
#include "behaviors/platelet_secretion.h"
#include "behaviors/macropage_proliferation.h"
#include "behaviors/macrophage_secretion.h"
#include "behaviors/fibroblast_proliferation.h"
#include "behaviors/fibroblast_secretion.h"
#include "behaviors/keratinocyte_proliferation.h"

namespace bdm {

enum CellType { kplatelet, kmacrophage };
enum Substances { kPDGF, kTGFb, kKGF };

/*
inline void CleanWoundArea() {
	auto* rm = Simulation::GetActive()->GetResourceManager();
	if (auto* cell = dynamic_cast<macrophage*>(Agent* a)) {
		if (cell->GetInsideWoundArea()) {
			//cell->RemoveBehaviors();
			cell->RemoveFromSimulation();
		}
	}
}
*/
inline int Simulate(int argc, const char** argv) {
	auto set_param = [](Param* param) {
    	// Create an artificial bound for the simulation space
    		param->use_progress_bar = true;
    		param->bound_space = Param::BoundSpaceMode::kClosed;
    		param->min_bound = 0;
    		param->max_bound = 500;
  	};
  	
  	
	Simulation simulation(argc, argv, set_param);
	
	auto* param = simulation.GetParam();
  	
  	ModelInitializer::DefineSubstance(Substances::kPDGF, "PDGF",0.05, 0.001, 50);
  	ModelInitializer::DefineSubstance(Substances::kTGFb, "TGF-b",0.05, 0.001, 50);
  	ModelInitializer::DefineSubstance(Substances::kKGF, "KGF",0.05, 0.001, 50);
  	
  	int num_cells = 4000;

	auto plt_builder = [&](const Real3& position) { //platelet builder
    		auto* cell = new platelet(position);
    		cell->SetDiameter(5);
    		cell->SetMass(2);
    		cell->AddBehavior(new InsideWoundArea());
    		cell->AddBehavior(new RandomWalk(2));
    		cell->AddBehavior(new PlateletSecretion()); //secretion of platelets when inside wound area
    		//cell->AddBehavior(new Chemotaxis("PDGF", 0.75));
    		cell->SetCanDivide(false);
    		cell->SetColor(0);
    	return cell;
  	};
  	
  	auto mac_builder = [&](const Real3& position) { //macrophage builder
    		auto* cell = new macrophage(position);
    		cell->SetDiameter(4);
    		cell->SetMass(3);
    		cell->AddBehavior(new InsideWoundArea());
    		cell->AddBehavior(new RandomWalk(2));
    		cell->AddBehavior(new Chemotaxis("PDGF", 0.50));
    		cell->SetCanDivide(false);
    		cell->AddBehavior(new MacrophageProliferation(4)); //the behavior that makes macs to proliferate when contact platelets
    		cell->AddBehavior(new MacrophageSecretion());
    		cell->SetColor(1);
    	return cell;
  	};
  	
  	auto krt_builder = [&](const Real3& position) { //keratinocyte builder
  		auto* cell = new keratinocyte(position);
    		cell->SetDiameter(8);
    		cell->SetMass(3);
    		cell->SetColor(2);
    		cell->SetCanDivide(true);
    		cell->AddBehavior(new Chemotaxis("KGF", 1));
    		cell->AddBehavior(new InsideWoundArea());
    		cell->AddBehavior(new KeratinocyteProliferation(8));
  	return cell;
  	};
  	
  	auto fbr_builder = [&](const Real3& position) { //fibroblast builder
  		auto* cell = new fibroblast(position);
    		cell->SetDiameter(5);
    		cell->SetMass(6);
    		cell->SetColor(3);
    		cell->AddBehavior(new InsideWoundArea());
    		cell->SetCanDivide(false);
    		cell->AddBehavior(new Chemotaxis("TGF-b", 0.50));
    		cell->AddBehavior(new FibroblastProliferation(5));
    		cell->AddBehavior(new FibroblastSecretion());
    		
  	return cell;
  	};
  	const uint64_t cell_cube_length = 100;
  	
	ModelInitializer::CreateAgentsRandom(param->max_bound / 2 - cell_cube_length ,
                                       param->max_bound / 2 + cell_cube_length,
                                       num_cells, plt_builder);
	
	
	ModelInitializer::CreateAgentsRandom(param->max_bound / 2 - cell_cube_length,
                                       param->max_bound / 2 + cell_cube_length,
                                       num_cells, mac_builder);
        
	ModelInitializer::CreateAgentsRandom(param->max_bound / 2 - cell_cube_length,
                                       param->max_bound / 2 + cell_cube_length,
                                       num_cells*4, krt_builder);     
        
        ModelInitializer::CreateAgentsRandom(param->max_bound / 2 - cell_cube_length,
                                       param->max_bound / 2 + cell_cube_length,
                                       num_cells, fbr_builder);                          

	std::cout<< simulation.GetActive()->GetScheduler()->GetSimulatedSteps() <<std::endl;
	std::cout<< "-1" <<std::endl;
	
	
	
  	
	//Run simulation for one timestep
	simulation.GetScheduler()->Simulate(500);

	std::cout << "Simulation completed successfully!" << std::endl;
	return 0;
}

}  // namespace bdm

#endif  // WOUNDHEALING_CELLS_H_
