// function to read machine data
// from a text file where each field is separated by a blank space
//#include <iostream>  // basic i/o commands
//#include <fstream>  // file I/O
//#include <vector>
//#include <string>


#include <string>
#include <cstring>
#include <sstream>
#include <fstream>  // file I/O
#include <vector>
#include <stdlib.h>
#include <iomanip>      // std::setw


using namespace std;


// SpringTable is an array of struct
void read_input_file(string FILE_INPUT, Machine* pm)
{

	int COMMENT=0;


	// declare the name
	string file;
	const char *expr1;
	// string to char conversion
	file =  FILE_INPUT;
	expr1 = file.c_str();

	// open the stream
	ifstream fin;
	fin.open(expr1);

	// check that the file exists and opened in the right mode
	if (!fin.is_open()) {   //open attempt failed
		cerr << "\nERROR: The input file doesn't exist!!!" << endl;
		exit(-1);
	}
	else {
		cout << "\nReading from file : " << FILE_INPUT << endl;
	}


	// in capital letters the parameters to import
	char linea[300];
	char ch;
	int check_header = 0;
	int m = 0;
	int count=0;
	string word;
	double p_par_values[5];
	int n_par = 5;
	string PAR_LABELS[5] = {"total_weight=", "min_freq=", "isolation_c=", "components_no=", "mounts_no="};

	//----------------------------------------------------------------------------------------------------
	// Parameters acquisition
	//----------------------------------------------------------------------------------------------------
	// 1st step - READ PARAMETERS, discarding commented lines (#) or not recognised lines
	int max_checks = 5;
	int n_checks = 0;
	while ((!check_header) && (n_checks<max_checks)) {
		cout << "\nReading " << PAR_LABELS[count] << "...";
		fin >> word;
		if (!word.compare(PAR_LABELS[count])) {
			fin >> p_par_values[count];
			count++;
			cout << "Ok.";
			n_checks = 0;
		}
		fin.getline(linea, 300); // go to next line, the rest is comment
		n_checks++;
		if (count==n_par) check_header=1;
	}

	if (!check_header) {
		cout << "\n" << PAR_LABELS[count] << " not found. Exit.";
		cerr << "\nERROR : " << PAR_LABELS[count] << " not found. Exit";
		exit(-1);
	}
	else
		cout << "\nParameters imported." << endl;

	// copy values
	double tw = p_par_values[0];
	double mf =  p_par_values[1];
	double ic = p_par_values[2];
	int cn = p_par_values[3];
	int mn = p_par_values[4];


	//----------------------------------------------------------------------------------------------------
	// Dynamic allocation of mounts position (DATA - mn rows, 2 columns: first allocate the row, then the columns for each row (no other way)
	//-----------------------------------------------------------------------------------------------------
	double **DATA = NULL;  // use address
	DATA = new double*[mn];
	if (DATA==NULL)  {
		cerr << "\nERROR: dynamic allocation of DATA failed!! Input data can't be imported" << endl;
		exit(-1);
	}
	for (int i=0; i<mn; i++) {
		DATA[i] = new double[2];  // 2 COLUMNS!!!
		if (DATA[i]==NULL)  {
			cerr << "\nERROR: dynamic allocation of DATA[" << i << "]  failed!! Input data can't be imported" << endl;
			exit(-1);
		}
	}


	// get DATA line by line
	string Input;
	double Value;
	int row = 0;
	int col = 0;
	while (getline(fin, Input) && (row<mn)) {
		if (COMMENT) cout << "result of getline : " << Input << endl;
		// Input contains entire line
	    if (Input[0]!='#') {
				stringstream Parse;
	    		Parse << Input;
	    		vector<double> Line;
	    		while (Parse >> Value) {
	    			// only the values that are double are actually copied... so comment is recognised!
	    			Line.push_back( Value );
	    			col++;
	    			if (COMMENT) cout << "filling Line... col = " << col << endl;
	    		}
	    		if (COMMENT) cout << "size of Line = "<< Line.size() << endl;
	    		if (Line.size() != 2) {
	    			cerr << "Line " << row << ": expected 2 values, received " << Line.size() << " values, aborting." << endl;
	    			cerr << "CHECK THE NUMBER OF VARIABLES DECLARED IN THE INPUT FILE!" << endl;
	    			exit(-1);
	    		}
	    		if (COMMENT) cout << "DATA:" << endl;
	    		for (int i=0; i<2; i++) {
	    			DATA[row][i] = Line[i];
	    			if (COMMENT) cout << scientific << DATA[row][i] << "  ";
	    		}
	    		row++;
	    		col = 0;
	    		if (COMMENT) cout << endl;
	    }
	    else
	    	if (COMMENT) cout << "comment" << endl;
	}



	// checks (m is the number of record imported)
	if (row < mn) {
		cerr << "\nERROR: the number of valid records imported (" << m << ") is smaller than mounts_no (" << mn << ").";
		cerr << "\nCheck the input file (see commented lines...)!!" << endl;
		exit(-1);
	}

	// show the results
	//if (COMMENT) {
		cout << "\nFile content." << endl;
		cout << "Value of the parameters:" << endl;
		for (int k=0; k<n_par; k++)
		 	cout << PAR_LABELS[k] << p_par_values[k] << endl;

		cout << "Content of DATA(" <<  mn << ",2):" << endl;
		cout << setw(3) << " ";
		for (int j=0; j< 2;  j++) cout << left << setw(22) << j ;
		cout << endl;
		for (int i=0; i< mn; i++)  {//m must be equal to mn
			cout << left << setw(3) << i;
			for (int j=0; j< 2;  j++) {
				cout <<  scientific <<  left << setw(22)  << DATA[i][j];
			}
			cout << endl;
		}
	//}

	// FIN QUI OK!!!
	// copia DATA in components_list




	//----------------------------------------------------------------------------------------------------
	// Dynamic allocation of components list (DATA2 - cn rows, 4 columns: first allocate the row, then the columns for each row (no other way)
	//-----------------------------------------------------------------------------------------------------
	double **DATA2 = NULL;  // use address
	DATA2 = new double*[cn];
	if (DATA2==NULL)  {
		cerr << "\nERROR: dynamic allocation of DATA failed!! Input data can't be imported" << endl;
		exit(-1);
	}
	for (int i=0; i<cn; i++) {
		DATA2[i] = new double[4];  // 4 COLUMNS!!!
		if (DATA2[i]==NULL)  {
			cerr << "\nERROR: dynamic allocation of DATA2[" << i << "]  failed!! Input data can't be imported" << endl;
			exit(-1);
		}
	}


	// get DATA2 line by line
	row = 0;
	col = 0;
	while (getline(fin, Input) && (row<cn)) {
		if (COMMENT) cout << "result of getline : " << Input << endl;

		// Input contains entire line
		if (Input[0]!='#') {
			stringstream Parse;
			Parse << Input;
			vector<double> Line;
			while (Parse >> Value) {
			    // only the values that are double are actually copied... so comment is recognised!
			    Line.push_back( Value );
			    col++;
			    if (COMMENT) cout << "filling Line... col = " << col << endl;
			}
			if (COMMENT) cout << "size of Line = "<< Line.size() << endl;
			if (Line.size() != 4) {
				cerr << "Line " << row << ": expected 4 values, received " << Line.size() << " values, aborting." << endl;
			 	cerr << "CHECK THE NUMBER OF VARIABLES DECLARED IN THE INPUT FILE!" << endl;
			 	exit(-1);
			}
			if (COMMENT) cout << "DATA2:" << endl;
			for (int i=0; i<4; i++) {
				DATA2[row][i] = Line[i];
			    if (COMMENT) cout << scientific << DATA2[row][i] << "  ";
			}
			row++;
			col = 0;
			if (COMMENT) cout << endl;
		}
		else
			if (COMMENT) cout << "comment" << endl;
	}

	// checks (m is the number of record imported)
	if (row < cn) {
		cerr << "\nERROR: the number of valid records imported (" << m << ") is smaller than mounts_no (" << mn << ").";
		cerr << "\nCheck the input file (see commented lines...)!!" << endl;
		exit(-1);
	}

	// show the results
	//if (COMMENT) {
		cout << "Content of DATA2(" <<  cn << ",4):" << endl;
		cout << setw(3) << " ";
		for (int j=0; j< 4;  j++) cout << left << setw(18) << j ;
		cout << endl;
		for (int i=0; i< cn; i++)  {//m must be equal to mn
			cout << left << setw(3) << i;
			for (int j=0; j< 4;  j++) {
				cout <<  scientific <<  left << setw(18)  << DATA2[i][j];
			}
			cout << endl;
		}
	//}


	// call Machine member function to copy the data
	pm->set_members (tw,mf, ic, cn, DATA2, mn, DATA, "undefined");
}
