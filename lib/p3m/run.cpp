/*
  Copyright (C) 2014 Olaf Lenz
  
  This file is part of ScaFaCoS.
  
  ScaFaCoS is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  ScaFaCoS is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>. 
*/
#include "scafacos.h"
#include "src/Solver.hpp"
#include <stdexcept>

using namespace P3M;

extern "C" {

  FCSResult 
  ifcs_p3m_run(void* rd,
               fcs_int num_particles,
               fcs_int _max_num_particles,
               fcs_float *positions,
               fcs_float *charges,
               fcs_float *fields,
               fcs_float *potentials) {
    /* Here we assume, that the method is already tuned and that all
       parameters are valid */
    Solver *d = reinterpret_cast<Solver*>(rd);
    
    try {
      d->run(num_particles, positions, charges, fields, potentials);
    } catch (std::exception &e) {
      return fcs_result_create(FCS_ERROR_LOGICAL_ERROR, "ifcs_p3m_run", e.what());
    }
    
    return FCS_RESULT_SUCCESS;
  }
  
}
