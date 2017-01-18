/*
 * class_Component.h
 *
 *  Created on: 31/gen/2014
 *      Author: rd
 */

#ifndef CLASS_COMPONENT_H_
#define CLASS_COMPONENT_H_


#include <iostream>
#include <string.h>

using namespace std;

class Component {
  public:
	double coord_x;
	double coord_y;
	double weight;
	int type; // 1 for concentrated; 2 for distributed

	// constructor
	Component();

	void print_members();


};


#endif /* CLASS_COMPONENT_H_ */
