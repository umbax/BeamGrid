#include <cstdlib>
#include <iostream>
#include <math.h>

using namespace std;

// Newton-Raphson algorithm to find the zero of a function
// function f(x) = x^2

double f(double x) // function f(x)
{
	double c_isol = .9;
    return 1.0-1.0/(x*x-1.0)-c_isol;   // only for x>=1
	//return (x*x*x*x - x - 10);
}

double ff(double x) //Differentiating function f(x)
{
	return 2*x/((x*x-1)*(x*x-1));
	//return (4*x*x*x - 1);
}

void NR(double aerr, int maxitr, double a)
{
     int i = 0;
     double b, prev;
     while (i <= maxitr)
     {
           b = a - (f(a))/ff(a);
           cout << "Iter " << i << ": x = " << b << endl;
           i++;
           if (fabs(b - a) < aerr)
              break;
           a = b;
     }

}

int main()
{
    double aerr, a, b;
    int maxitr;
    cout << "\n\nNewton method to find the zero x | f(x)=0" << endl;
    cout << "Enter aerr, maxitr, a." << endl;
    cin >> aerr;
    cin >> maxitr;
    cin >> a;
    NR(aerr, maxitr, a);

    system("PAUSE");
    return EXIT_SUCCESS;
}
