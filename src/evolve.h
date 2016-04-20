// Copyright 2012 Bjoern Schenke, Sangyong Jeon, and Charles Gale
#ifndef SRC_EVOLVE_H_
#define SRC_EVOLVE_H_

#include <mpi.h>
#include <iostream>
#include "util.h"
#include "data.h"
#include "grid.h"
#include "grid_info.h"
#include "eos.h"
#include "reconst.h"
#include <time.h>
#include "reconst.h"
#include "advance.h"
#include "u_derivative.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include<vector>

// this is a control class for the hydrodynamic evolution
class Evolve {
 private:
    EOS *eos; // declare EOS object
    Reconst *reconst; // declare Reconst object
    Grid *grid; // declare Grid object
    Grid_info *grid_info;
    Util *util;
    Advance *advance;
    U_derivative *u_derivative;

    InitData *DATA_ptr;

    // simulation information
    int rk_order;
    int grid_nx, grid_ny, grid_neta;

    double SUM, SUM2;
    int warnings;
    int cells;
    int weirdCases;
    int facTau;

    // information about freeze-out surface
    // (only used when freezeout_method == 4)
    int n_freeze_surf;
    vector<double> epsFO_list;
  
 public:
    Evolve(EOS *eos, InitData *DATA_in);
    ~Evolve();
    int EvolveIt(InitData *DATA, Grid ***arena, Grid ***Lneighbor,
                 Grid ***Rneighbor, int size, int rank);
    
    int AdvanceRK(double tau, InitData *DATA, Grid ***arena,
                  Grid ***Lneighbor, Grid ***Rneighbor, int size, int rank);
    
    int UpdateArena(double tau, Grid ***arena);
    
    int FreezeOut_equal_tau_Surface(double tau, InitData *DATA,
                                    Grid ***arena, int size, int rank);
    void FindFreezeOutSurface(double tau, InitData *DATA,
                              Grid ***arena, int size, int rank);
    void FindFreezeOutSurface2(double tau, InitData *DATA,
                               Grid ***arena, int size, int rank);
    int FindFreezeOutSurface3(double tau, InitData *DATA,
                              Grid ***arena, int size, int rank);
    int FindFreezeOutSurface_Cornelius(double tau, InitData *DATA,
                                       Grid ***arena, int size, int rank);
    int FindFreezeOutSurface_boostinvariant_Cornelius(
                double tau, InitData *DATA, Grid ***arena, int size, int rank);

    void initial_prev_variables(Grid ***arena);
    void storePreviousEpsilon(Grid ***arena);
    void storePreviousW(Grid ***arena);
    void storePreviousT(Grid ***arena);

    void regulate_qmu(double* u, double* q, double* q_regulated);
    void regulate_Wmunu(double* u, double** Wmunu, double** Wmunu_regulated);

    void initialize_freezeout_surface_info();
};

#endif  // SRC_EVOLVE_H_
  
