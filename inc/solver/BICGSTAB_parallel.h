#ifndef BICGSTAB_parallel_2022
#define BICGSTAB_parallel_2022



#include "initializers_parallel.h"
 
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
		index_type col;
		index_type row_start;
		index_type row_end;
		MPI_Comm col_comm;

		public:
		
		BICGSTAB(index_type row_num ,  index_type col_num,    value_type val_1 = (value_type)0 ,  value_type val_2 = (value_type)2 , MPI_Comm communicator = MPI_COMM_WORLD ) : col{col_num} 
		{
			comm = communicator;
			generate_vals_1d(bottom , top , row_start , row_end , row_num, comm );
				A.allocate(row_num , row_start, row_end, col_num , comm);
				x.allocate(row_start , row_end , val_1);
				b.allocate(row_start , row_end , val_2);
		}
		BICGSTAB(index_type row_num ,index_type col_num ,   std::function<value_type (index_type , index_type)> init , value_type val_1 = (value_type)0 ,  value_type val_2 = (value_type)2 , MPI_Comm communicator = MPI_COMM_WORLD) :col{col_num}
		{
			comm = communicator;
			generate_vals_1d(  bottom , top , row_start , row_end ,  row_num, comm );

			A.allocate(row_num , row_start, row_end , col_num,   init, comm);
			x.allocate(row_start , row_end , val_1);
			matrix_calculations_parallel ::vector<index_type , value_type> c;			
			c.allocate(row_start , row_end , val_2);
			b =  A.SPMM(c);		
			
		} 
		
		BICGSTAB(index_type row_num ,index_type col_num ,   std::function<value_type (index_type , index_type)> init , std::function<value_type (index_type ,  std::vector<value_type>)> init_v , std::vector<value_type> init_v_values , value_type val_1 = (value_type)0 , MPI_Comm communicator = MPI_COMM_WORLD ) : col{col_num}  
		{
				comm = communicator;
				generate_vals_1d( bottom , top , row_start , row_end , row_num, comm );
				A.allocate(row_num , row_start, row_end ,col_num, init, comm);
				x.allocate(row_start , row_end , val_1);
				b.allocate(row_start , row_end , init_v , init_v_values);		
		}
		
		BICGSTAB(index_type row_num ,index_type col_num ,   std::function<value_type (index_type , index_type)> init , std::function<value_type (index_type ,  value_type)> init_v , value_type val_2 = (value_type) 0 , value_type val_1 = (value_type)0 , MPI_Comm communicator = MPI_COMM_WORLD  ) : col{col_num}  
		{
				comm = communicator;
				generate_vals_1d( bottom , top , row_start , row_end , row_num, comm );
				A.allocate(row_num , row_start, row_end ,col_num, init, comm);
				x.allocate( row_start , row_end , val_1);
				b.allocate(row_start , row_end , init_v , val_2);		
		}
		
		BICGSTAB( index_type row_num ,  index_type col_num ,std::string path , value_type val_1 = (value_type)0 ,  value_type val_2 = (value_type)2 , MPI_Comm communicator = MPI_COMM_WORLD) : col{col_num} 
		{
			comm = communicator;
			 generate_vals_1d(bottom , top , row_start , row_end , row_num, comm );	
				A.allocate(row_num , row_start, row_end ,  path, comm);
				x.allocate(row_start , row_end , val_1);
				b.allocate(row_start , row_end , val_2);		
		}
		
		 BICGSTAB(index_type row_num , index_type col_num ,  std::string path , std::function<value_type (index_type ,  std::vector<value_type>)> init_v , std::vector<value_type> init_v_values , value_type val_1 = (value_type)0 , MPI_Comm communicator = MPI_COMM_WORLD ) : col{col_num} 
		{
				comm = communicator;
                		generate_vals_1d( bottom , top , row_start , row_end , row_num, comm );               
                                A.allocate(row_num , row_start, row_end , path, comm);
                                x.allocate(row_start , row_end , val_1);
                                b.allocate(row_start , row_end , init_v , init_v_values);                     
		}

		/* BICGSTAB(index_type row_num , index_type col_num  , value_type val , MPI_Comm communicator = MPI_COMM_WORLD )
                {
                                generate_vals_1d(  bottom , top , row_start , row_end , row_num, comm );
                       		A.allocate(row_start, row_end , &initializer_parallel::Matrix_initializer<long int,double>);
                                x.allocate(row_start , row_end , 0);
                                
                }

		*/
		value_type solve( value_type tolerance , unsigned long int max_sim);
		void display();
	};

}

#endif
