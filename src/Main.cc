#include "BICGSTAB.h"

int main()
{
	
	auto tolerance = 1.0E-5;
	matrix_calculations::sparse_matrix_operations<long int , double> A(30,30,&initializer::Matrix_initializer<long int,double>); 	
	auto row_size  = (long int)A.return_row_size();
	std::vector<double> V = initializer::Vector_constant_initializer_matrix<long int , double>(row_size, A, (double)2);
	solver::BICGSTAB<long int, double> B(row_size,row_size,&initializer::Matrix_initializer<long int,double>, &initializer::Vector_initializer<long int,double> ,V);
	auto error = B.solve(tolerance, 1000000);
	B.display( );
	std::cout << "Error after convergance " << error << std::endl;
	return 0;
	
}
