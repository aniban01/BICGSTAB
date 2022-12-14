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
        	sleep(1);
        	MPI_Barrier(comm);
		
        	for( auto k=0; k<nprocs; k++){
                	if( k == myid )
			{
 	                	
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
		auto sim_num = 0ul;
		value_type alpha = (value_type) 1;
		value_type omega = (value_type) 1;
		value_type rho = (value_type) 1;
		value_type rho_next = (value_type) 1;
		value_type beta = (value_type) 0;
		matrix_calculations_parallel::sparse_matrix_operations<index_type , value_type> pre_condition;
		pre_condition.allocate(col , row_start , row_end,col);


		matrix_calculations_parallel::vector<index_type, value_type> s_hat (b.return_size() , b.return_lower(),  0);
		matrix_calculations_parallel::vector<index_type, value_type> t (b.return_size() , b.return_lower() , 0);
		matrix_calculations_parallel::vector<index_type, value_type> r = b - (A.SPMM(x));
		matrix_calculations_parallel::vector<index_type, value_type> r_hat = r;
		matrix_calculations_parallel::vector<index_type, value_type> p = r;
		matrix_calculations_parallel::vector<index_type, value_type> p_hat = pre_condition.SPMM(p);
		matrix_calculations_parallel::vector<index_type, value_type> v = A.SPMM(p_hat);
		rho = r.dot_product(r_hat);
		alpha =  rho / (r_hat.dot_product(v));
		value_type norm_rhs = b.norm();
		if(norm_rhs < tolerance)
		{
			norm_rhs = 1;
		}
		
	
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
			auto dot_t_s = t.dot_product(s);
			auto dot_t_t = t.dot_product(t);
			omega = dot_t_s / dot_t_t;
			x = x + (p * alpha) + (s_hat * omega);
			r = s - (t * omega);
			rho_next = rho;
			if( r.norm() < tolerance)
	                {
        			return r.norm();	        	
			}
 
		}
	//	auto error = r.norm(); 	
		while(sim_num < max_sim)
		{
			MPI_Barrier(MPI_COMM_WORLD);	
			++sim_num;
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
				return s.norm()/norm_rhs;
			}
			else
			{
				s_hat = pre_condition.SPMM(s);
				t = A.SPMM(s_hat);
				
				auto dot_t_s = t.dot_product(s);
                        	auto dot_t_t = t.dot_product(t);
				omega = dot_t_s / dot_t_t;
				x = x + (p * alpha) + (s_hat * omega);
				r = s - (t * omega);
				rho_next = rho;
	
				if( r.norm() < tolerance)
	               	 	{
                        		x = x +  p_hat *  alpha;
		        		return r.norm();
        	        	}
 
			}			
//			error = r.norm();			
		}
		return r.norm();	

	}
	
	template class BICGSTAB <int , double>;
	template class BICGSTAB <int , float>;
	template class BICGSTAB <long int , double>;
	template class BICGSTAB <long int , float>;

}
