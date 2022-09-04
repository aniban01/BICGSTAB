#include "BICGSTAB_parallel.h"
#include <chrono>
int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	auto tolerance = 1.0E-11;
	 
	long int row_size  = 100; 

	parallel_solver::BICGSTAB<long int, double> D(row_size,row_size,&initializer_parallel::Matrix_initializer<long int,double>  );


	auto start_init = std::chrono::high_resolution_clock::now();


	auto error =  D.solve(tolerance , 1000);

	auto stop_init = std::chrono::high_resolution_clock::now();


        std::cout << stop_init - start_init << std::endl;




	MPI_Finalize();
	return 0;
	
}
