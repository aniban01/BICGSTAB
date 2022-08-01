#include "BICGSTAB.h"

int main()
{
	std::cout << "............................................................................Generating sparse matrix " << std::endl;
	matrix_calculations::sparse_matrix_operations<int , double> A(10,10, &initializer::Matrix_initializer<int,double>); 
	std::cout << "...................................................................................Generating vector " << std::endl;
	std::vector<double> V = initializer::Vector_constant_initializer_matrix<int , double>(10 , A, (double)4);
	std::cout << ".................................................................................Generating BICGSTAB" << std::endl;
	solver::BICGSTAB<int, double> B(30,30,&initializer::Matrix_initializer<int,double>, &initializer::Vector_initializer<int,double> ,V);
	std::cout << "....................................................................................Outputing matrix" << std::endl;
	B.display();
	std::cout << "..................................................................................Computing BICGSTAB" << std::endl;
	B.solve(0.0001 , 1000000);
	std::cout << "..................................................................................BICGSTAB completed" << std::endl << std::endl;;
	B.display( );

	std::cout << std::endl << "..................................................................................Execution completed" << std::endl;

	return 0;
	
}
