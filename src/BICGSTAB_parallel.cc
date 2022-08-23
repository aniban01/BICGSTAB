#include "BICGSTAB_parallel.h"

namespace parallel_solver
{
        template <typename index_type , typename value_type>
	void BICGSTAB<index_type, value_type> :: display()
	{
		int myid, nprocs;
		
		MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	        MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	
        	printf("Attempting to print in order\n");
        	sleep(1);
        	MPI_Barrier(comm);
		
        	for( auto k=0; k<nprocs; k++){
                	if( k == myid )
			{
				int colid, rowid, rowprocs, colprocs;               
				if(mmult_comm != MPI_COMM_NULL)
				{
					MPI_Comm_rank(mmult_comm, &rowid);
                        		MPI_Comm_size(mmult_comm, &rowprocs);
				}
				else
				{
					rowid = -1;
					rowprocs = -1;
				}
				MPI_Comm_rank(col_comm, &colid);
                                MPI_Comm_size(col_comm, &colprocs);

				std::cout << "output for rank " << myid << " out of " << nprocs << " from col " << col_start << " to " << col_end << " and row " << row_start << " to " << row_end << std::endl;
				std::cout << "Neighbour : top " << top << " bottom " << bottom << " left " << left << " right " << right << std::endl;
			
				std::cout <<"MMULT rank : " << rowid << " out of " << rowprocs << std::endl;

				std::cout <<"Column rank : " << colid << " out of " << colprocs << std::endl; 	                	
				
				int row_counter = 0;
				for( auto i = row_start ; i <= row_end ; i++)
				{
					std::cout << "|\t";
					for( auto j = col_start ; j <= col_end ; j++)
                			{
						std::cout << A.matrix_value(i,j) << "\t";
                			}
					if(row_counter < col_end - col_start + 1)
					{
						std::cout <<"|\t|\t" << x.value(row_counter) << "\t|\t|\t" << b.value(row_counter) << "\t|"; 
						row_counter++;
					}
					std::cout<<std::endl;
				}
			}
			fflush(stdout);
                	sleep(1);
               		MPI_Barrier(MPI_COMM_WORLD);

		}	


	}
/*
        template <typename index_type , typename value_type>
	value_type BICGSTAB<index_type, value_type> :: solve( value_type tolerance , unsigned long int max_sim )
	{
		auto sim_num = 0ul;
		value_type alpha = (value_type) 1;
		value_type omega = (value_type) 1;
		value_type rho = (value_type) 1;
		value_type rho_next = (value_type) 1;
		value_type norm_rhs = b.norm();
		value_type beta = (value_type) 0;
		if(norm_rhs < tolerance)
		{
			norm_rhs = 1;
		}

		matrix_calculations::sparse_matrix_operations<index_type , value_type> pre_condition(b.return_size() , b.return_size());
		matrix_calculations::vector<index_type, value_type> s_hat (b.return_size() , 0);
		matrix_calculations::vector<index_type, value_type> t (b.return_size() , 0);

		matrix_calculations::vector<index_type, value_type> r = b - (A.SPMM(x));
		matrix_calculations::vector<index_type, value_type> r_hat = r;
		
		rho = r.dot_product(r_hat);
		
		matrix_calculations::vector<index_type, value_type> p = r;
		matrix_calculations::vector<index_type, value_type> p_hat = pre_condition.SPMM(p);
		matrix_calculations::vector<index_type, value_type> v = A.SPMM(p_hat);
		alpha =  rho / (r_hat.dot_product(v));
		matrix_calculations::vector<index_type, value_type> s  = r - (v * alpha);
		if( s.norm()/norm_rhs < tolerance)
		{
			x = x +  p_hat *  alpha; 
			return s.norm()/norm_rhs;
		}
		else
		{
			s_hat = pre_condition.SPMM(s);
			t = A.SPMM(s_hat);
			omega = t.dot_product(s) / t.dot_product(t);
			x = x + (p * alpha) + (s_hat * omega);
			r = s - (t * omega);
			rho_next = rho;
			if( r.norm() < tolerance)
	                {
        			return r.norm();	        	
			}
 
		}	
		while(sim_num < max_sim)
		{
		
			++sim_num;
			std::cout << "\n\n\n-------------------- Running Iteration " << sim_num << " with residual " << r.norm() << " -------------------------------------" << std::endl;
	
			rho = r.dot_product(r_hat);
			
			beta = (rho * alpha)/(rho_next * omega);	
		 	p = r + ((p - (v * omega)) * beta); 	
			p_hat = pre_condition.SPMM(p);
		 	v = A.SPMM(p_hat);
			alpha =  rho / (r_hat.dot_product(v));
		 	s  = r - (v * alpha);
			if( s.norm()/norm_rhs < tolerance)
			{
				x = x +  (p_hat *  alpha); 
				std::cout << "\n\n\n-------------------- Exiting after completing Iteration " << sim_num << " with relative residual" << s.norm()/norm_rhs<< " -------------------------------------" << std::endl;

				return s.norm()/norm_rhs;
			}
			else
			{
				s_hat = pre_condition.SPMM(s);
				t = A.SPMM(s_hat);
				omega = t.dot_product(s) / t.dot_product(t);
				x = x + (p * alpha) + (s_hat * omega);
				r = s - (t * omega);
				rho_next = rho;
	
				if( r.norm() < tolerance)
	               	 	{
                        		x = x +  p_hat *  alpha;
                			std::cout << "\n\n\n-------------------- Exiting after completing Iteration " << sim_num << " with residual " << r.norm() << " -------------------------------------" << std::endl;

		        		return r.norm();
        	        	}
 
			}			
			
		}
		std::cout << "\n\n\n-------------------- Exiting after completing Iteration " << sim_num << " with residual " << r.norm() << " -------------------------------------" << std::endl;
		return r.norm();	
	}
*/
	template class BICGSTAB <int , double>;
	template class BICGSTAB <int , float>;
	template class BICGSTAB <long int , double>;
	template class BICGSTAB <long int , float>;

}
