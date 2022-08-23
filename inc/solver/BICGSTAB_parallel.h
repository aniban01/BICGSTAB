#ifndef BICGSTAB_parallel_2022
#define BICGSTAB_parallel_2022



#include "initializers.h"
#include "parallel_alg.h"
 
namespace parallel_solver
{
	template <typename index_type , typename value_type>
	
	class BICGSTAB
	{
		//Elements in the equation Ax = b 
		matrix_calculations_parallel ::sparse_matrix_operations<index_type , value_type> A;
                matrix_calculations_parallel ::vector<index_type, value_type> x;
		matrix_calculations_parallel ::vector<index_type , value_type> b;
		

		//BICGSTAB variables
		double tolerance_level = 0.000001;


		//Parallelization variables
		MPI_Comm comm = MPI_COMM_WORLD;
		int top;		
		int bottom;
		int left;
		int right;
		index_type row_start;
		index_type row_end;
		index_type col_start;
		index_type col_end;


		MPI_Comm mmult_comm;
		MPI_Comm col_comm;

		public:
		
		BICGSTAB(index_type row_num ,  index_type col_num,    value_type val_1 = (value_type)0 ,  value_type val_2 = (value_type)2 , MPI_Comm communicator = MPI_COMM_WORLD )  
		{
			comm = communicator;
//			std::cout<<"Communicator generated"<< std::endl;
			generate_vals( left , right , bottom , top , row_start , row_end , col_start , col_end,  col_num , row_num, comm );
		//	if(proc_num < num_procs)
		//	{
//			 std::cout<<"values generated"<< std::endl;

				A.allocate(row_start, row_end , col_start, col_end);
//			 std::cout<<"A generated"<< std::endl;

				x.allocate(col_start , col_end , val_1);
//			 std::cout<<"x generated"<< std::endl;

				b.allocate(col_start , col_end , val_2);
//			 std::cout<<"b generated"<< std::endl;

				communicator_initialization();
//			 std::cout<<"mmult Communicator generated"<< std::endl;

		//	}
		//	else 
                //      {
		//		generate_error(32);
                //       }
		}
		BICGSTAB(index_type row_num ,index_type col_num ,   std::function<value_type (index_type , index_type)> init , value_type val_1 = (value_type)0 ,  value_type val_2 = (value_type)2) 
		{
			generate_vals( left , right , bottom , top , row_start , row_end , col_start , col_end,  col_num , row_num, comm );

			A.allocate(row_start, row_end , col_start, col_end , init);
			x.allocate(col_start , col_end , val_1);
			b.allocate(col_start , col_end , val_2);		
//			 std::cout<<"b generated"<< std::endl;
			MPI_Barrier(MPI_COMM_WORLD);
			communicator_initialization();
			MPI_Barrier(MPI_COMM_WORLD);
//			 std::cout<<"mmult Communicator generated"<< std::endl;
			
		} 
		
		BICGSTAB(index_type row_num ,index_type col_num ,   std::function<value_type (index_type , index_type)> init , std::function<value_type (index_type ,  std::vector<value_type>)> init_v , std::vector<value_type> init_v_values , value_type val_1 = (value_type)0  )  
		{
				generate_vals( left , right , bottom , top , row_start , row_end , col_start , col_end,  col_num , row_num, comm );


				A.allocate(row_start, row_end , col_start, col_end , init);
				x.allocate(col_start , col_end , val_1);
				b.allocate(col_start , col_end , init_v , init_v_values);		
				communicator_initialization();
		}
		
		BICGSTAB( index_type row_num ,  index_type col_num ,std::string path , value_type val_1 = (value_type)0 ,  value_type val_2 = (value_type)2) 
		{
		
			 generate_vals( left , right , bottom , top , row_start , row_end , col_start , col_end,  col_num , row_num, comm );	
				A.allocate(row_start, row_end , col_start, col_end , path);
				x.allocate(col_start , col_end , val_1);
				b.allocate(col_start , col_end , val_2);		
			communicator_initialization();
		}
		
		 BICGSTAB(index_type row_num , index_type col_num ,  std::string path , std::function<value_type (index_type ,  std::vector<value_type>)> init_v , std::vector<value_type> init_v_values , value_type val_1 = (value_type)0  ) 
		{
                		generate_vals( left , right , bottom , top , row_start , row_end , col_start , col_end,  col_num , row_num, comm );               
                                A.allocate(row_start, row_end , col_start, col_end , path);
                                x.allocate(col_start , col_end , val_1);
                                b.allocate(col_start , col_end , init_v , init_v_values);                     
				communicator_initialization();
		}

		//value_type solve( value_type tolerance , unsigned long int max_sim);
		void display();
	


		void communicator_initialization() 
		{
         		

			int myid , nprocs , proc_grid[2] = {0,0};
         		MPI_Comm_rank(comm, &myid);
			MPI_Comm_size(comm, &nprocs);
//			std::cout << "\tProc " << myid << " out of " << nprocs << " determined " <<std::endl;
        	
			MPI_Barrier(MPI_COMM_WORLD);	
			MPI_Dims_create(nprocs, 2, proc_grid);
//			std::cout << "\tProc " << myid << ": proc_grid[0] = " << proc_grid[0] << " proc_grid[1] : " << proc_grid[1] << std::endl;
        		fflush(stdout);
			sleep(1);
			MPI_Barrier(MPI_COMM_WORLD);
			int mmult_color = 0;
			if(A.return_row_size() > 0)
        		{

                		mmult_color = myid % proc_grid[0] ;
//                		std::cout << "\tProc " << myid << " has colour " << mmult_color << std::endl;	
		//		MPI_Comm_split(comm , mmult_color, myid, &mmult_comm);
        	//		std::cout << "\tProc " << myid << " added to row communicator "  << std::endl;
        		
			}
			else
			{	
//				mmult_comm = MPI_COMM_NULL;
//				std::cout << "\tProc " << myid << " not added to row communicator "  << std::endl;
				
				mmult_color = MPI_UNDEFINED;
//				std::cout << "\tProc " << myid << " has colour " << mmult_color << std::endl;
			}

			MPI_Comm_split(comm , mmult_color, myid, &mmult_comm);
//			std::cout << "\tProc " << myid << " added to row communicator "  << std::endl;

			fflush(stdout);
                        sleep(1);
		
        		MPI_Barrier(MPI_COMM_WORLD);
			int col_color = myid / proc_grid[1];
        		
//			std::cout << "\tProc " << myid << " has col colour"  << col_color << std::endl;

			MPI_Comm_split(comm , col_color, myid, &col_comm);
//			std::cout << "\tProc " << myid << " added to column communicator "  << std::endl;	
	}
		
		
	};

}

#endif
