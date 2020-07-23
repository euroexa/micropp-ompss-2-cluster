/*
 * This source code is part of MicroPP: a finite element library
 * to solve microstructural problems for composite materials.
 *
 * Copyright (C) - 2018 - Jimmy Aguilar Mena <kratsbinovish@gmail.com>
 *                        Guido Giuntoli <gagiuntoli@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#pragma once


#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>

#include "tasks.hpp"

using namespace std;

template <int dim>
class gp_t {

	static constexpr int nvoi = dim * (dim + 1) / 2;  // 3, 6

	public:

	double strain_old[nvoi] = { 0.0 };
	double strain[nvoi];
	double stress[nvoi];
	double ctan[nvoi * nvoi];

	bool allocated; // flag for memory optimization

	double *vars_n; // vectors for calculations
	double *vars_k;
	double *u_n;
	double *u_k;
	int nvars;
	int nndim;

	long int cost;
	bool converged;
	bool subiterated;
	int coupling;

	gp_t() = delete;
        
            void init(double *_vars_n, double *_vars_k,
                      double *_u_n, double *_u_k, int nndim)
                      // double *ctan_lin)
            {
                    assert(nndim > 0);
                    allocated = false;
                    cost = 0;
                    converged = true;
                    subiterated = false;

                    vars_n = _vars_n;
                    vars_k = _vars_k;

                    u_n = _u_n;
                    u_k = _u_k;

                    // macro_ctan = ctan_lin;

                    memset(_u_n, 0, nndim * sizeof(double));

                    dbprintf("gp: %p \t u_n: %p u_k: %p vars_n: %p vars_k: %p "
                             "allocated: %d node: %d/%d\n",
                             this, u_k, u_k, vars_n, vars_k, allocated,
                             get_node_id(), get_nodes_nr());
            }

	~gp_t() {}

	void allocate_u()
	{
	}

	void allocate()
	{
		assert(!allocated);
		allocated = true;
	}


	void update_vars()
	{
		double *tmp = vars_n;
		vars_n = vars_k;
		vars_k = tmp;

		tmp = u_n;
		u_n = u_k;
		u_k = tmp;

		memcpy(strain_old, strain, nvoi * sizeof(double));
	}

	void write_restart(std::ofstream& file)
	{
		file.write((char *)&allocated, sizeof(bool));
		if (allocated) {
			file.write((char *)vars_n, nvars * sizeof(double));
			file.write((char *)u_n, nndim * sizeof(double));
		}
	}

	void read_restart(std::ifstream& file)
	{
		file.read((char *)&allocated, sizeof(bool));
		if (allocated) {
			vars_n = (double *)calloc(nvars, sizeof(double));
			vars_k = (double *)calloc(nvars, sizeof(double));

			file.read((char *)vars_n, nvars * sizeof(double));
			file.read((char *)u_n, nndim * sizeof(double));
		}
	}
};
