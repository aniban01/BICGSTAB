
#include "matrix_calculations.h"
#include "initializers.h"
#include <chrono>

int main()
{
	int row = 100;
	for(auto i = 0 ; i < 5 ; i++)
	{
		std::cout << "1," << row << "," ;	
		auto start_init = std::chrono::high_resolution_clock::now();
		matrix_calculations::vector<int , float> A_int_float(row , (float)7 );
		matrix_calculations::vector<int , float> B_int_float(row , (float)7 );
		auto stop_init = std::chrono::high_resolution_clock::now();
		std::cout << stop_init - start_init << ",";
		auto start_calc = std::chrono::high_resolution_clock::now();	
		A_int_float.dot_product(B_int_float);
		auto stop_calc = std::chrono::high_resolution_clock::now();
		std::cout << stop_calc - start_calc << ",";
		
		start_calc = std::chrono::high_resolution_clock::now();	
		A_int_float.dot_product(B_int_float);
		stop_calc = std::chrono::high_resolution_clock::now();
		std::cout << stop_calc - start_calc << ",";

		start_calc = std::chrono::high_resolution_clock::now();	
		A_int_float + B_int_float;
		stop_calc = std::chrono::high_resolution_clock::now();
		std::cout << stop_calc - start_calc << ",";

		start_calc = std::chrono::high_resolution_clock::now();	
		A_int_float + (float)row;
		stop_calc = std::chrono::high_resolution_clock::now();
		std::cout << stop_calc - start_calc << std::endl;
			
		

		std::cout << "2," << row << "," ;	
		start_init = std::chrono::high_resolution_clock::now();

	
		matrix_calculations::vector<int , double> A_int_double (row, (double)7 ) ;
		matrix_calculations::vector<int , double> B_int_double(row , (double)7 );
	
		start_calc = std::chrono::high_resolution_clock::now();	
		A_int_double.dot_product(B_int_double);
		stop_calc = std::chrono::high_resolution_clock::now();
		std::cout << stop_calc - start_calc << ",";
		
		start_calc = std::chrono::high_resolution_clock::now();	
		A_int_double.dot_product(B_int_double);
		stop_calc = std::chrono::high_resolution_clock::now();
		std::cout << stop_calc - start_calc << ",";

		start_calc = std::chrono::high_resolution_clock::now();	
		A_int_double + B_int_double;
		stop_calc = std::chrono::high_resolution_clock::now();
		std::cout << stop_calc - start_calc << ",";

		start_calc = std::chrono::high_resolution_clock::now();	
		A_int_double + (float)row;
		stop_calc = std::chrono::high_resolution_clock::now();
		std::cout << stop_calc - start_calc << std::endl;
			
	
		std::cout << "3," << row << "," ;	
		start_init = std::chrono::high_resolution_clock::now();
		matrix_calculations::vector<long int , float> A_long_float (row, (float)7 ) ;
		matrix_calculations::vector<long int , float> B_long_float(row , (float)7 );
		stop_init = std::chrono::high_resolution_clock::now();
		std::cout << stop_init - start_init << ",";
		
		start_calc = std::chrono::high_resolution_clock::now();	
		A_long_float.dot_product(B_long_float);
		stop_calc = std::chrono::high_resolution_clock::now();
		std::cout << stop_calc - start_calc << ",";
		
		start_calc = std::chrono::high_resolution_clock::now();	
		A_long_float.dot_product(B_long_float);
		stop_calc = std::chrono::high_resolution_clock::now();
		std::cout << stop_calc - start_calc << ",";

		start_calc = std::chrono::high_resolution_clock::now();	
		A_long_float + B_long_float;
		stop_calc = std::chrono::high_resolution_clock::now();
		std::cout << stop_calc - start_calc << ",";

		start_calc = std::chrono::high_resolution_clock::now();	
		A_long_float + (float)row;
		stop_calc = std::chrono::high_resolution_clock::now();
		std::cout << stop_calc - start_calc << std::endl;
			
	
		std::cout << "4," << row << "," ;	
		start_init = std::chrono::high_resolution_clock::now();
		matrix_calculations::vector<long int , double> A_long_double (row, (double)7 ) ;
		matrix_calculations::vector<long int , double> B_long_double(row , (double)7 );
		stop_init = std::chrono::high_resolution_clock::now();
		std::cout << stop_init - start_init << ",";
		
		start_calc = std::chrono::high_resolution_clock::now();	
		A_long_double.dot_product(B_long_double);
		stop_calc = std::chrono::high_resolution_clock::now();
		std::cout << stop_calc - start_calc << ",";
		
		start_calc = std::chrono::high_resolution_clock::now();	
		A_long_double.dot_product(B_long_double);
		stop_calc = std::chrono::high_resolution_clock::now();
		std::cout << stop_calc - start_calc << ",";

		start_calc = std::chrono::high_resolution_clock::now();	
		A_long_double + B_long_double;
		stop_calc = std::chrono::high_resolution_clock::now();
		std::cout << stop_calc - start_calc << ",";

		start_calc = std::chrono::high_resolution_clock::now();	
		A_long_double + (float)row;
		stop_calc = std::chrono::high_resolution_clock::now();
		std::cout << stop_calc - start_calc << std::endl;
			

		row *= 10;
	}		
}

