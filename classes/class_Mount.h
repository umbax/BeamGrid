/*
 * class_Mount.h
 *
 *  Created on: 21/gen/2014
 *      Author: rd
 */

#ifndef CLASS_MOUNT_H_
#define CLASS_MOUNT_H_

#include <iostream>
#include <string.h>

using namespace std;

class Mount {
  public:
	double coord_x;
	double coord_y;
	double deflection;
	double load;
	double stiffness;
	string model;
	double max_deflection;
	double max_load;

	// constructor
	Mount();

    void print_members();
};



#endif /* CLASS_MOUNT_H_ */
