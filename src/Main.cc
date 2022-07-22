#include "BICGSTAB.h"

int main()
{

	solver::BICGSTAB<int, double> B(10,10);
	B.display();
	return 0;
	
}
