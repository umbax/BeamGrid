/*
 * class_Mount.cpp
 *
 *  Created on: 21/gen/2014
 *      Author: rd
 */

#include <iostream>
#include <string.h>
#include "./class_Mount.h"

using namespace std;


// constructor
Mount::Mount(void)
{
	coord_x= 0.0;
	coord_y = 0.0;
	model = "undefined";  // 9 digits
	deflection = 0.0;
	load = 0.0; //kgf
	stiffness = 0.0;  //kgf/mm
	max_deflection = 0.0; //mm
	max_load = 0.0;  //mm

}

// function that prints on screen class members
void Mount::print_members()
{
	cout << "\n\nMount::print_members()";
	cout << "\n Size of Mount : " << sizeof(Mount);
	cout << "\ncoord_x = " << coord_x;
	cout << "\ncoord_y = " << coord_y;
	cout << "\nmodel = " << model;
	cout << "\ndeflection = " << deflection;
	cout << "\nload = " << load;
	cout << "\nstiffness = " << stiffness;
	cout << "\nmax_deflection = " << max_deflection;
	cout << "\nmax_load = " << max_load;

}
