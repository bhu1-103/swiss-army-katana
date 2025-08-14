#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int main()
{
  int prec;
  double pi025;
  double p1,p2,p3;
	cout << "enter number of digits of precision required: ";
  cin >> prec;
  for(int i=0;i<prec;i++)
  {
    p1 = pow(-1,i);
    p2 = 2*i + 1;
    p3 = p1 / p2;
    pi025 += p3;
  }
  cout << "value of pi is: " << fixed << setprecision(20) << pi025 * 4;
	return 0;
}
