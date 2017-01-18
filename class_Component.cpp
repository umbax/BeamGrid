#include <iostream>
#include <string.h>
#include "./class_Mount.h"

using namespace std;


// constructor
Component::Component()
{
	coord_x= 0.0;
	coord_y = 0.0;
	weight = 0.0;
	type = 0;  // 0 = undefined; 1 for concentrated; 2 for distributed load
}


// function that prints on screen class members
void Component::print_members()
{
	cout << "\n\nComponent::print_members()";
	cout << "\n Size of Component : " << sizeof(Component);
	cout << "\ncoord_x = " << coord_x;
	cout << "\ncoord_y = " << coord_y;
	cout << "\nweight = " << weight;
	cout << "\ntype = " << type;
}
