#include <iostream>
#include <stdlib.h>     /* exit, EXIT_FAILURE */

#include "./classes/class_Machine.h"
#include "./ext_functions/read_input_file.h"

using namespace std;

int main (int argc, char *argv[])
{
	// check the number of arguments
	if (argc!=2) {
		cerr << "\nERRORE!!! Numero di argomenti sbagliato!"	;
		cerr << "\nUSO: >> ./main  location/name_input"; // existing_directory_output";
		cerr << "\nEsempio: >> ./main ./input/input_file.txt"; // ./output\n";
		exit(-1);
	}

	string FILE_INPUT=argv[1];
	//string DIR_OUTPUT=argv[2];
 	cout << "\nNAME_INPUT = " << FILE_INPUT;
 	//cout << "\nNAME_OUTPUT = " << DIR_OUTPUT;



	cout << "\n Software selezione antivibranti per UTA McQuay a 4-6 appoggi" << endl;

	// declare Machine
	Machine UTA; // (total_weight, min_freq, isolation_c, components_no, components, mounts_no, mounts_position, mounts_type);

	// read input file and assign member values
	read_input_file(FILE_INPUT, &UTA);

	//UTA.print_members();
	UTA.compute_mount_loads();
	UTA.compute_required_deflection();



	system("PAUSE");
	return EXIT_SUCCESS;
}


#include "./classes/class_Machine.cpp"
#include "./ext_functions/read_input_file.cpp"

