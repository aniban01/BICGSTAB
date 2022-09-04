
#include "matrix_calculations.h"
#include "initializers.h"
#include <chrono>

int main()
{
	int row = 100;
//	for(auto i = 0 ; i < 5 ; i++)
//	{
		std::cout << "1," << row << "," ;	
		auto start_init = std::chrono::high_resolution_clock::now();
		matrix_calculations::sparse_matrix_operations<int , float> A_int_float (row, row , &initializer::Matrix_initializer<int , float> ) ;
		matrix_calculations::vector<int , float> B_int_float(row , (float)7 );
		auto stop_init = std::chrono::high_resolution_clock::now();
		std::cout << stop_init - start_init << ",";
		auto start_calc = std::chrono::high_resolution_clock::now();	
		A_int_float.SPMM(B_int_float);
		auto stop_calc = std::chrono::high_resolution_clock::now();
		std::cout << stop_calc - start_calc << std::endl;
		std::cout << "2," << row << "," ;	
		start_init = std::chrono::high_resolution_clock::now();

	
		matrix_calculations::sparse_matrix_operations<int , double> A_int_double (row, row , &initializer::Matrix_initializer<int , double> ) ;
		matrix_calculations::vector<int , double> B_int_double(row , (double)7 );
		stop_init = std::chrono::high_resolution_clock::now();
		std::cout << stop_init - start_init << ",";
		start_calc = std::chrono::high_resolution_clock::now();	
		A_int_double.SPMM(B_int_double);
		stop_calc = std::chrono::high_resolution_clock::now();
		std::cout << stop_calc - start_calc << std::endl;


		std::cout << "3," << row << "," ;	
		start_init = std::chrono::high_resolution_clock::now();
		matrix_calculations::sparse_matrix_operations<long int , float> A_long_float (row, row , &initializer::Matrix_initializer<long int , float> ) ;
		matrix_calculations::vector<long int , float> B_long_float(row , (float)7 );
		stop_init = std::chrono::high_resolution_clock::now();
		std::cout << stop_init - start_init << ",";
		start_calc = std::chrono::high_resolution_clock::now();	
		A_long_float.SPMM(B_long_float);
		stop_calc = std::chrono::high_resolution_clock::now();
		std::cout << stop_calc - start_calc << std::endl;

	
		std::cout << "4," << row << "," ;	
		start_init = std::chrono::high_resolution_clock::now();
		matrix_calculations::sparse_matrix_operations<long int , double> A_long_double (row, row , &initializer::Matrix_initializer<long int , double> ) ;
		matrix_calculations::vector<long int , double> B_long_double(row , (double)7 );
		stop_init = std::chrono::high_resolution_clock::now();
		std::cout << stop_init - start_init << ",";
		start_calc = std::chrono::high_resolution_clock::now();	
		A_long_double.SPMM(B_long_double);
		stop_calc = std::chrono::high_resolution_clock::now();
		std::cout << stop_calc - start_calc << std::endl;
		row *= 10;
//	}		
}

