#include "BICGSTAB_parallel.h"
int main(int argc, char **argv)
{
	
	auto tolerance = 1.0E-11;
	 

	int myid, nprocs;

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &myid);
        MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

	int row_num = 10 , bottom , top , row_start , row_end;

	generate_vals_1d(bottom , top , row_start , row_end , row_num, MPI_COMM_WORLD);
	matrix_calculations_parallel ::vector<int , double> x;
	matrix_calculations_parallel ::vector<int , double> y;
	x.allocate(row_start , row_end , 1);	
	y.allocate(row_start , row_end , 10);
	
	matrix_calculations_parallel ::vector<int , double> add = x + 2;
	matrix_calculations_parallel ::vector<int , double> sub = add - 2;
	matrix_calculations_parallel ::vector<int , double> mult = x * 2;
	matrix_calculations_parallel ::vector<int , double> div = mult / 2;


	matrix_calculations_parallel ::vector<int , double> add_vec = x + y;
        matrix_calculations_parallel ::vector<int , double> sub_vec = add_vec - y;
        matrix_calculations_parallel ::vector<int , double> mult_vec = x * y;
        matrix_calculations_parallel ::vector<int , double> div_vec = mult_vec / y;


	double norm_val_y = y.norm();
	double dot = y.dot_product(x);

	if(myid == 0)
	{
		std::cout << "Norm value of y is " << norm_val_y << std::endl << "Dot product of x and y is " << dot << std::endl;
		std::cout << "\tAdd\t|\tSub\t|\tMult\t|\tDiv\t|\tAdd_vec\t|\tSub_vec\t| Mult_vec\t|Div_vec\t|" << std::endl;
	}
	
	long int row_size  = 30; 

	for( auto k=0; k<nprocs; k++)
	{
         	if( k == myid )
		{
			for(int t = row_start ; t <= row_end ; t++)
			{
				std::cout << "\t" <<  add.value(t) <<  "\t|\t" <<  sub.value(t)<< "\t|\t" << mult.value(t) << "\t|\t"<<  div.value(t) <<"\t|\t" <<  add_vec.value(t) << "\t|\t" << sub_vec.value(t) << "\t|\t" << mult_vec.value(t) <<"\t|\t" << div_vec.value(t) << "\t|" << std::endl;
			}
		}
		 fflush(stdout);
                        sleep(1);
                        MPI_Barrier(MPI_COMM_WORLD);

	}
		
	//long int nbrleft , nbrright , nbrbottom , nbrtop , row_start, row_end , col_start , col_end;
	//generate_vals( &nbrleft , & nbrright , &nbrbottom , & nbrtop , & s , & e , & top , & bottom, row_size , row_size , MPI_Comm comm = MPI_COMM_WORLD);

//	std::cout << "...................................................................................Generating matrix " << std::endl;
//	matrix_calculations::sparse_matrix_operations<int , double> A1(row_start, row_end, col_start, col_end,  &initializer::Matrix_initializer<int,double>);
//	std::cout << "...................................................................................Generating vector " << std::endl;

//  	std::cout << "row size :" << row_size << std::endl;
//	std::vector<double> V = initializer::Vector_constant_initializer_matrix<long int , double>(row_size, row_size, A, (double)4);
	
	std::cout << ".................................................................................Generating BICGSTAB" << std::endl;
//	parallel_solver::BICGSTAB<long int, double> B(row_size,row_size,&initializer::Matrix_initializer<long int,double>, &initializer::Vector_initializer<long int,double> ,V);
	parallel_solver::BICGSTAB<long int, double> D(row_size,row_size,&initializer_parallel::Matrix_initializer<long int,double>  );
	D.display();
	D.solve(tolerance , 10000);
	D.display();
	MPI_Finalize();
	return 0;
	
}
