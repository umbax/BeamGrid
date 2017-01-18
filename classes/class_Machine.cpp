/*
 * class_Machine.cpp
 *
 *  Created on: 21/gen/2014
 *      Author: rd
 */


#include <iostream>
#include <string.h>
#include <stdlib.h>     /* qsort */
//#include <algorithm>  //sort
#include "./class_Mount.h"
#include "./class_Component.h"
#include "./class_Machine.h"
#include "../ext_functions/compare_vectors.h"
#include "../optimiser/Newton_method.h"

using namespace std;


// constructor
Machine::Machine (void) //
//(double tw, double mf, double ic, int cn, double** c, int mn, double** mp, string mt)
{
	// default machine initialisation
	total_weight = 0.0; //tw;
	min_freq = 0.0; //mf;
	isolation_c = 0.0; //ic;
	components_no = 0.0; //cn;
	mounts_no = 0.0; //mn;
	mounts_type = "undefined";
	mounts_list = NULL;
	components_list = NULL;

	// useful to compute minimum deflection of the mount to achieve desired isolation
	min_th_a_ratio = 1.414;
	min_th_defl = 0.0;



}


// function to set member values
void Machine::set_members (double tw, double mf, double ic, int cn, double** ca, int mn, double** mp, string mt)
{
	// machine initialisation
	total_weight = tw;
	min_freq = mf;
	isolation_c = ic;  // still in percentage (from 0 to 100)
	components_no = cn;
	mounts_no = mn;
	mounts_type = mt;

	// mounts_list initialisation
	mounts_list = new Mount[mounts_no];  // remember that you have to delete at the end!
	for (int k=0; k<mounts_no; k++) {
			mounts_list[k].coord_x = mp[k][0];
			mounts_list[k].coord_y = mp[k][1];
	}

	// components_list initialisation
	components_list = new Component[components_no];  // remember that you have to delete at the end!
	for (int k=0; k<components_no; k++) {
		components_list[k].coord_x = ca[k][0];
		components_list[k].coord_y = ca[k][1];
		components_list[k].weight = ca[k][2];
		components_list[k].type = int(ca[k][3]);
	}

}




// function that prints on screen class members
void Machine::print_members()
{
	cout << "\n\nMachine::print_members()";
	cout << "\ntotal_weight = " << total_weight;
	cout << "\nmin_freq = " << min_freq;
	cout << "\nisolation_c = " << isolation_c;

	cout << "\n\ncomponents_no = " << components_no << endl;
	for (int k=0; k<components_no; k++) {
		cout << "\n\nCOMPONENT :" << k+1;
		components_list[k].print_members();
	}

	cout << "\n\nmounts_no = " << mounts_no;
	cout << "\nmounts_type = " << mounts_type << endl;
	for (int k=0; k<mounts_no; k++) {
		cout << "\n\nMOUNT :" << k+1;
		mounts_list[k].print_members();
	}


}


// function that prints on screen class members
void Machine::compute_mount_loads()
{
	int COMMENT = 1;
	if (COMMENT) cout << "\n\nMachine::compute_mount_loads()" << endl;

	//------------------------------------------------------------------------
	// SORT MOUNTS AND COMPONENTS WITH RESPECT TO COORD_X
	//------------------------------------------------------------------------

	// define new array "mounts_p_array" containing addresses of Mounts in mounts_list
	Mount** mounts_p_array = new Mount*[mounts_no];
	for (int k=0; k<mounts_no; k++)
		mounts_p_array[k] = &(mounts_list[k]);

	// sort an array containing the addresses of each Mount in mounts_list according to coord_x
	qsort(mounts_p_array, mounts_no, sizeof(Mount*), compare_vectors);

	// check sorting mounts_p_array
	if (COMMENT) {
		cout << "\n\nMachine::compute_mount_loads() : check qsort mounts_p_array...";
		for (int k=0; k<mounts_no; k++)
			cout << "\nMount " << k+1 << " : (coord_x, coord_y) = " << mounts_p_array[k]->coord_x << ", " << mounts_p_array[k]->coord_y;
	}
	// ok, mounts_p_array correctly sorts its pointers so that coord_x is in increasing order (what about coord_y?)

	// define new array "comp_p_array" containing addresses of Mounts in mounts_list
	Component** comp_p_array = new Component*[components_no];
	for (int k=0; k<components_no; k++)
		comp_p_array[k] = &(components_list[k]);

	// sort an array containing the addresses of each Mount in mounts_list according to coord_x
		qsort(comp_p_array, components_no, sizeof(Component*), compare_vectors);

	// check sorting comp_p_array
	if (COMMENT) {
		cout << "\n\nMachine::compute_mount_loads() : check qsort comp_p_array...";
		for (int k=0; k<components_no; k++)
			cout << "\nComponent " << k+1 << " : (coord_x, coord_y, weight, type) = " << comp_p_array[k]->coord_x << ", " << comp_p_array[k]->coord_y << ", " << comp_p_array[k]->weight << ", " << comp_p_array[k]->type;
	}
	// ok, comp_p_array correctly sorts its pointers so that coord_x is in increasing order (what about coord_y?)


	// compute actual total load and actual total distributed load
	int n_squares = mounts_no/2 - 1;
	int cur_square = 1;
	// define initial corner mounts (4!)
	// Mind that it works only there are 2 mounts along y (so square made of 4 mounts), not more!!!
	Mount* bl;
	Mount* ul;
	Mount* br;
	Mount* ur;
	if (mounts_p_array[0]->coord_y < mounts_p_array[1]->coord_y) {
		bl = mounts_p_array[0];
		ul = mounts_p_array[1];
	} else {
		bl = mounts_p_array[1];
		ul = mounts_p_array[0];
	}
	if (mounts_p_array[2]->coord_y < mounts_p_array[3]->coord_y) {
		br = mounts_p_array[2];
		ur = mounts_p_array[3];
	} else {
		br = mounts_p_array[3];
		ur = mounts_p_array[2];
	}

	if (COMMENT) {
		cout << "\n\n cur_square =  " << cur_square;
		cout << "\n\n bl :\n";
		bl->print_members();
		cout << "\n ul :\n";
		ul->print_members();
		cout << "\n br :\n";
		br->print_members();
		cout << "\n ur :\n";
		ur->print_members();
	}

	// initialise weight collectors
	double act_tot_load = 0.0;
	double act_tot_dist_load = 0.0;
	double act_tot_load_mounts = 0.0;
	double cl, cr, cu, cb, l, h, xc, yc, c;

	for (int k=0; k<components_no; k++) {
		act_tot_load = act_tot_load + comp_p_array[k]->weight;

		if (COMMENT) cout << "\nCheck Component " << k+1 << " : (coord_x, coord_y, weight, type) = " << comp_p_array[k]->coord_x << ", " << comp_p_array[k]->coord_y << ", " << comp_p_array[k]->weight << ", " << comp_p_array[k]->type;


		// update the current square
		if (comp_p_array[k]->coord_x > br->coord_x) {
			if (COMMENT) cout << "\n\ncomp_p_array[k]->coord_x > br->coord_x";
			// increase cur_square and redefine corner mounts
			cur_square++;
			if (mounts_p_array[cur_square]->coord_y < mounts_p_array[cur_square+1]->coord_y) {
				bl = mounts_p_array[cur_square];
				ul = mounts_p_array[cur_square+1];
			} else {
				bl = mounts_p_array[cur_square+1];
				ul = mounts_p_array[cur_square];
			}
			if (mounts_p_array[2*cur_square]->coord_y < mounts_p_array[2*cur_square+1]->coord_y) {
				br = mounts_p_array[2*cur_square];
				ur = mounts_p_array[2*cur_square+1];
			} else {
				br = mounts_p_array[2*cur_square+1];
				ur = mounts_p_array[2*cur_square];
			}


			// check assignment
			//cout << "\n\n cur_square =  " << cur_square;
			//cout << "\n bl :";
			//bl->print_members();
			//cout << "\n ul :";
			//ul->print_members();
			//cout << "\n br :";
			//br->print_members();
			//cout << "\n ur :";
			//ur->print_members();

		}

		// fin qui OK!
		// select action according to the kind of component
		// type = 0 undefined; 1 for concentrated; 2 for distributed load
		if (comp_p_array[k]->type==1) {

			cout << "\n\n comp_p_array[k] k = " << k << endl;

			// point load : add portions to the four current mount corner
			// compute coefficients
			l = br->coord_x-bl->coord_x;
			xc = comp_p_array[k]->coord_x-bl->coord_x;
			cl = (l-xc)/l;
			cr = xc/l;
			h = ur->coord_y-br->coord_y;
			yc = comp_p_array[k]->coord_y-br->coord_y;
			cb = (h-yc)/h;
			cu = yc/h;

			// compute loads
			bl->load = bl->load + cb*cl*comp_p_array[k]->weight;
			ul->load = ul->load + cu*cl*comp_p_array[k]->weight;
			br->load = br->load + cb*cr*comp_p_array[k]->weight;
			ur->load = ur->load + cu*cr*comp_p_array[k]->weight;

			// check assignment
			cout << "\n\n cur_square =  " << cur_square;
			cout << "\n cl =" << cl;
			cout << "\n cr =" << cr;
			cout << "\n cu =" << cu;
			cout << "\n cb =" << cb;



		}

		if (comp_p_array[k]->type==2) {
			// distributed load : add equal portions to the four current mount corner
			act_tot_dist_load = act_tot_dist_load + comp_p_array[k]->weight;
		}


	}

	// add equal portion of distributed load to all mounts
	cout << "\n\n TEST : carico distribuito calcolato correttamente?" << endl;
	cout << "mounts_no=" << mounts_no << endl;
	for (int k=0; k<mounts_no; k++) {
		cout << "\n\n mounts_p_array[k]->load = " << mounts_p_array[k]->load;
		mounts_p_array[k]->load = mounts_p_array[k]->load + act_tot_dist_load/mounts_no;
		cout << "\n mounts_p_array[k]->load = " << mounts_p_array[k]->load;

		// check total load on mounts
		act_tot_load_mounts = act_tot_load_mounts + mounts_p_array[k]->load;
	}

	cout << "\n\nMachine::compute_mount_loads() : act_tot_load = " << act_tot_load;
	cout << "\nMachine::compute_mount_loads() : act_tot_dist_load = " << act_tot_dist_load;
	cout << "\nMachine::compute_mount_loads() : act_tot_load_mounts = " << act_tot_load_mounts << endl;

	for (int k=0; k<mounts_no; k++) {
		cout << "\n\nMOUNT " << k+1 << ":";
		mounts_p_array[k]->print_members();
	}

	for (int k=0; k<mounts_no; k++) {
		cout << "\n\nP_" << k+1 << ":" << fixed << mounts_p_array[k]->load << " kgf";
	}
	cout << endl;

}


void Machine::compute_required_deflection()
{
	int COMMENT = 1;
	if (COMMENT) cout << "\n\nMachine::compute_required_deflection()" << endl;

	double aerr = 0.00001;
	int maxitr = 100;
	double in_guess = min_th_a_ratio;

	// call optimiser
	min_th_a_ratio = Newton_R_optimiser(aerr, maxitr, in_guess, isolation_c/100.0);

	// compute minimum deflection in mm to achieve required isolation (see page 48 Diana-Cheli)
	double pi = 3.1415926535;
	min_th_defl = (9810.0/(4.0*pi*pi))*min_th_a_ratio*min_th_a_ratio/(min_freq*min_freq);

	if (COMMENT) {
			cout << "\n\n min_freq = " << min_freq;
			cout << "\n isolation_c = " << isolation_c << " %";
			cout << "\n min_th_a_ratio = " << min_th_a_ratio;
			cout << "\n min_th_defl = " << min_th_defl << endl;
	}
}

#include "./class_Mount.cpp"
#include "./class_Component.cpp"
#include "../ext_functions/compare_vectors.cpp"
#include "../optimiser/Newton_method.cpp"
