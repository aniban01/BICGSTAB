#include "BICGSTAB.h"

namespace solver
{
        template <typename index_type , typename value_type>
	void BICGSTAB<index_type, value_type> :: display()
	{
		auto num_rows = A.return_row_size();
		auto num_cols = A.return_col_size();
		index_type vector_index = 0;
		for(auto i = (index_type)1 ; i < num_rows ; ++i)
		{
			std::cout << " | " ;
			for(auto j = (index_type)1 ; j < num_cols ; ++j)
			{
				std::cout<< " " << A.matrix_value(i,j) << " " ; 
			}
			if(i == (index_type) num_rows/2)
			{
				std::cout << " | " << x.value(vector_index) << " |   =   | " << b.value(vector_index) << " | "; 
			}
			else
			{
				std::cout << " | " << x.value(vector_index) << " |       | " << b.value(vector_index) << " | ";  
			}	
			std::cout << std::endl;

		
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

	template class BICGSTAB <int , double>;
	template class BICGSTAB <int , float>;
	template class BICGSTAB <long unsigned int , double>;
	template class BICGSTAB <long unsigned int , float>;

}
