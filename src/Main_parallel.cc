#include "BICGSTAB_parallel.h"
int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	auto tolerance = 1.0E-11;
	 

	long int row_size  = 30; 
	parallel_solver::BICGSTAB<long int, double> D(row_size,row_size,&initializer_parallel::Matrix_initializer<long int,double>  );
	auto error =  D.solve(tolerance , 100000);

	D.display();
	std::cout << "Final error of the west0479 data set is " << error << std::endl;


	MPI_Finalize();
	return 0;
	
}
