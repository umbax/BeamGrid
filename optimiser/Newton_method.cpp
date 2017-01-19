#include <cstdlib>
#include <iostream>
#include <math.h>

using namespace std;

// Newton-Raphson algorithm to find the zero of a function
// function f(x) = x^2

double f(double x, double level) // function f(x)
{
	//double c_isol = .9;
    return 1.0-1.0/(x*x-1.0)-level;   // only for x>=1
	//return (x*x*x*x - x - 10);
}

double ff(double x) //Differentiating function f(x)
{
	return 2*x/((x*x-1)*(x*x-1));
	//return (4*x*x*x - 1);
}

double Newton_R_optimiser(double aerr, int maxitr, double a, double level)
{
     int i = 0;
     double b, prev;
     while (i <= maxitr)
     {
           b = a - (f(a, level))/ff(a);
           //cout << "Iter " << i << ": x = " << b << endl;
           i++;
           if (fabs(b - a) < aerr)
              break;
           a = b;
     }

     // return point of zero
     return b;
}

//int main()
//{
//    double aerr, a, b;
//    int maxitr;
//    cout << "\n\nNewton method to find the zero x | f(x)=0" << endl;
//    cout << "Enter aerr, maxitr, a." << endl;
//    cin >> aerr;
//    cin >> maxitr;
//    cin >> a;
//    NR(aerr, maxitr, a);
//
//    system("PAUSE");
//    return EXIT_SUCCESS;
//}
