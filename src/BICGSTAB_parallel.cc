#include "BICGSTAB_parallel.h"

namespace parallel_solver
{
        template <typename index_type , typename value_type>
	void BICGSTAB<index_type, value_type> :: display()
	{
		int myid, nprocs;
		MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	        MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
		MPI_Barrier(comm);	
 	//	std::cout << "Rank " << myid << " Attempting to multiply" << std::endl;
//		x = A.SPMM(b);
	//       	std::cout << "Rank " << myid << " Attempting to print in order" << std::endl;
        	sleep(1);
        	MPI_Barrier(comm);
		
        	for( auto k=0; k<nprocs; k++){
                	if( k == myid )
			{
				int colid, rowid, rowprocs, colprocs, row_sendid, row_sendprocs;               
			/*	if(mmult_comm_recv != MPI_COMM_NULL)
				{
					MPI_Comm_rank(mmult_comm_recv, &rowid);
                        		MPI_Comm_size(mmult_comm_recv, &rowprocs);
				}
				else
				{
					rowid = -1;
					rowprocs = -1;
				}
				
				MPI_Comm_rank(mmult_comm_send, &row_sendid);
                                MPI_Comm_size(mmult_comm_send, &row_sendprocs);

		
				MPI_Comm_rank(col_comm, &colid);
                                MPI_Comm_size(col_comm, &colprocs);
*/
//				std::cout << "output for rank " << myid << " out of " << nprocs << " from  and row " << row_start << " to " << row_end << std::endl;
//				std::cout << "Neighbour : top " << top << " bottom " << bottom << std::endl;
//				A.print_matrix();	
//				std::cout <<"MMULT recv rank : " << rowid << " out of " << rowprocs << std::endl;

//				 std::cout <<"MMULT send rank : " << row_sendid << " out of " << row_sendprocs << std::endl;


//				std::cout <<"Column rank : " << colid << " out of " << colprocs << std::endl; 	                	
				int row_counter = 0;	
				for( auto i = row_start ; i <= row_end ; i++)
				{
					std::cout << "|\t";
					for( auto j = 1 ; j <= col ; j++)
                			{
						std::cout << A.matrix_value(i,j) << "  ";
                			}
					
					std::cout <<"|\t|\t" << x.value(i) << "\t|\t|\t" << b.value(i) << "\t|"; 
					std::cout<<std::endl;
					row_counter++;
				}
			}
			fflush(stdout);
                	sleep(1);
               		MPI_Barrier(MPI_COMM_WORLD);

		}	


	}

        template <typename index_type , typename value_type>
	value_type BICGSTAB<index_type, value_type> :: solve( value_type tolerance , unsigned long int max_sim )
	{
		std::cout << "Entering BICGSTAB solver " <<std::endl;
		auto sim_num = 0ul;
		value_type alpha = (value_type) 1;
		value_type omega = (value_type) 1;
		value_type rho = (value_type) 1;
		value_type rho_next = (value_type) 1;
		value_type norm_rhs = b.norm();
		value_type beta = (value_type) 0;
		std::cout << "value types initialized " <<std::endl;
		if(norm_rhs < tolerance)
		{
			norm_rhs = 1;
		}

		matrix_calculations_parallel::sparse_matrix_operations<index_type , value_type> pre_condition;
		pre_condition.allocate(col , row_start , row_end,col);
		matrix_calculations_parallel::vector<index_type, value_type> s_hat (b.return_size() , b.return_lower(),  0);
		matrix_calculations_parallel::vector<index_type, value_type> t (b.return_size() , b.return_lower() , 0);
		matrix_calculations_parallel::vector<index_type, value_type> r = b - (A.SPMM(x));
		matrix_calculations_parallel::vector<index_type, value_type> r_hat = r;
		 rho = r.dot_product(r_hat);
		matrix_calculations_parallel::vector<index_type, value_type> p = r;
		matrix_calculations_parallel::vector<index_type, value_type> p_hat = pre_condition.SPMM(p);
		matrix_calculations_parallel::vector<index_type, value_type> v = A.SPMM(p_hat);
		
		alpha =  rho / (r_hat.dot_product(v));
		/*
		std::cout << "Alpha before entering loop " << alpha << std::endl;
		std::cout << "rho before entering loop " << rho << std::endl;
		std::cout << "norm_rhs before entering loop " << norm_rhs << std::endl;
	

		fflush(stdout);
                sleep(1);
                MPI_Barrier(MPI_COMM_WORLD);
		pre_condition.print_matrix();
	
		fflush(stdout);
                sleep(1);
		MPI_Barrier(MPI_COMM_WORLD);
		p.display(); 
                std::cout << std::endl;
	
	
	
		fflush(stdout);
                sleep(1);
		MPI_Barrier(MPI_COMM_WORLD);
		p_hat.display(); 
                std::cout << std::endl;
	
		fflush(stdout);
                sleep(1);
		MPI_Barrier(MPI_COMM_WORLD);
		v.display();
		std::cout << std::endl;
		
		fflush(stdout);
                sleep(1);
		
		MPI_Barrier(MPI_COMM_WORLD);
		r_hat.display();
		std::cout << std::endl;
		fflush(stdout);
                sleep(1);
		MPI_Barrier(MPI_COMM_WORLD);	
		std::cout << "(r_hat.dot_product(v)) before entering loop " << (r_hat.dot_product(v)) << std::endl;
		*/
	
		matrix_calculations_parallel::vector<index_type, value_type> s  = r - (v * alpha);
		
		
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
			
	//	display();
		}
		std::cout << "\n\n\n-------------------- Exiting after completing Iteration " << sim_num << " with residual " << r.norm() << " -------------------------------------" << std::endl;
		return r.norm();	

	}

	template class BICGSTAB <int , double>;
	template class BICGSTAB <int , float>;
	template class BICGSTAB <long int , double>;
	template class BICGSTAB <long int , float>;

}
