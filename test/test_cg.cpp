/*
 *  This is a test example for MicroPP: a finite element library
 *  to solve microstructural problems for composite materials.
 *
 *  Copyright (C) - 2018 - Jimmy Aguilar Mena <kratsbinovish@gmail.com>
 *                         Guido Giuntoli <gagiuntoli@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <iomanip>

#include <ctime>
#include <cassert>

#include "micro.hpp"

using namespace std;

#define D_EPS 1.0e-3

int main (int argc, char *argv[])
{
	class test_t : public micropp<3> {

		public:
			test_t(const int size[3], const int micro_type, const double micro_params[5],
			       const material_t mat_params[2])
				:micropp<3> (1, size, micro_type, micro_params, mat_params)
			{};

			~test_t() {};

			void assembly_and_solve(double eps[6])
			{

				double lerr, cg_err;
				memset(u_aux, 0.0, nndim * sizeof(double));

				set_displ_bc(eps, u_aux);
				lerr = assembly_rhs(u_aux, vars_new_aux);

				assembly_mat(&A, u_aux, vars_new_aux);
				int cg_its = ell_solve_cgpd(&A, b, du, &cg_err);
				cout << "|RES| : " << lerr << " CG_ITS : " << cg_its << " CG_TOL : " << cg_err << endl;

			};

	};

	const int nx = atoi(argv[1]);
	const int ny = atoi(argv[2]);
	const int nz = atoi(argv[3]);
	const int dir = atoi(argv[4]);

	int size[3] = { nx, ny, nz };

	int micro_type = MIC_QUAD_FIB_XZ;
	double micro_params[4] = { 1., 1., 1., 0.166666667 };

	material_t mat_params[2];
	mat_params[0].set(3.0e7, 0.25, 1.0e4, 1.0e5, 0);
	mat_params[1].set(6.0e7, 0.25, 1.0e5, 1.0e5, 1);

	double eps[6] = { 0. };
	eps[dir] += D_EPS;

	test_t test(size, micro_type, micro_params, mat_params);
	test.assembly_and_solve(eps);

	return 0;
}