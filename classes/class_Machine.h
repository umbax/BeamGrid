/*
 * class_Machine.h
 *
 *  Created on: 21/gen/2014
 *      Author: rd
 */

#ifndef CLASS_MACHINE_H_
#define CLASS_MACHINE_H_

#include <string.h>
#include "./class_Mount.h"
#include "./class_Component.h"

using namespace std;

class Machine {
  public:
	double total_weight;
	double min_freq;
	double isolation_c;
	int components_no;
	int mounts_no;
	//double** mounts_position;
	string mounts_type;
	Mount* mounts_list;
	Component* components_list;

	double min_th_a_ratio; // minimum theoretical ratio between forcing freq and mount natural freq
	double min_th_defl;  // minimum theoretical deflection of each mount

	// constructor
	Machine(void);  //(double, double, double, int, double**, int, double**, string);

	void set_members(double, double, double, int, double**, int, double**, string);
    void print_members();
    void compute_mount_loads();
    void compute_required_deflection();
};



#endif /* CLASS_MACHINE_H_ */
