#include "BICGSTAB.h"

int main()
{
	
	auto tolerance = 0.0000000001;
	std::string path = "input/west0479.csv";
	std::cout << "............................................................................Generating sparse matrix " << std::endl;
	matrix_calculations::sparse_matrix_operations<long int , double> A(path); 
	//A.print_matrix();
	std::cout << "...................................................................................Generating vector " << std::endl;
	auto row_size  = (long int)A.return_row_size();
  	std::cout << "row size :" << row_size << std::endl;
	std::vector<double> V = initializer::Vector_constant_initializer_matrix<long int , double>(row_size, A, (double)4);
	std::cout << ".................................................................................Generating BICGSTAB" << std::endl;
//	solver::BICGSTAB<long int, double> B(row_size,row_size,&initializer::Matrix_initializer<long int,double>, &initializer::Vector_initializer<long int,double> ,V);
	solver::BICGSTAB<long int, double> B(row_size,  path, &initializer::Vector_initializer<long int,double> ,V);

//	std::cout << "....................................................................................Outputing matrix" << std::endl;
//	B.display();
	std::cout << "..................................................................................Computing BICGSTAB" << std::endl;
	auto error = B.solve(tolerance, 1000000);
	std::cout << "..................................................................................BICGSTAB completed" << std::endl << std::endl;;
//	B.display( );
	std::cout << "Error after convergance " << error << std::endl;
	//std::cout << std::endl << "..................................................................................Execution completed" << std::endl;
/*		
	std::cout << "..................................................................................new Matrix of 1s" << std::endl << std::endl;
	matrix_calculations::sparse_matrix_operations<int , double> A1(10,10, &initializer::Matrix_initializer<int,double>);
	std::cout << "Matrix Generated " << std::endl;
	matrix_calculations::vector <int,double>B1 (10 , (double)4);
	std::cout << "Vector B1 generated " << std::endl; 
	matrix_calculations::vector<int,double> C1 = A1.SPMM(B1);
	std::cout<< "Vector C1 Generated " << std::endl;
	A1.print_matrix();

	std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
	for(int i = 1; i <= 10 ;i++)
	{
		std::cout << "|";
		for(int j = 1; j <= 10; j++)
		{
			std::cout << A1.matrix_value(i,j) << "\t";
		}
		std::cout << "|\t|" << B1.value(i-1) << "|\t|" << C1.value(i-1) << "|" << std::endl;
	}
		

 	matrix::sparse_matrix <int, float> A;
	std::cout << "-----------------------------------------------------------------------------------------" << std::endl;

	A.add_element(1,2,10);
	A.print_elements();
        std::cout << "-----------------------------------------------------------------------------------------" << std::endl;

	A.add_element(1,1,9);
	A.print_elements();
        std::cout << "-----------------------------------------------------------------------------------------" << std::endl;

	A.add_element(1,3,10);
	A.print_elements();
        std::cout << "-----------------------------------------------------------------------------------------" << std::endl;

	A.add_element(1,4,9);
	A.print_elements();
        std::cout << "-----------------------------------------------------------------------------------------" << std::endl;

	A.add_element(1,5,10);
	A.print_elements();
        std::cout << "-----------------------------------------------------------------------------------------" << std::endl;

	A.add_element(2,1,9);
	A.print_elements();
        std::cout << "-----------------------------------------------------------------------------------------" << std::endl;

	A.add_element(2,2,10);
	A.print_elements();
        std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
	
	A.add_element(2,3,9);
	A.print_elements();
        std::cout << "-----------------------------------------------------------------------------------------" << std::endl;

	A.add_element(2,4,10);
	A.print_elements();
        std::cout << "-----------------------------------------------------------------------------------------" << std::endl;

	A.add_element(2,5,0);
	A.print_elements();
        std::cout << "-----------------------------------------------------------------------------------------" << std::endl;

        std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
	
	A.print_elements();
	A.print_matrix(2,5);
	
*/
	return 0;
	
}
