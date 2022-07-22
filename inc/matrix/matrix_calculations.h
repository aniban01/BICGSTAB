#include <omp.h>
#include <vector>
#include <cmath>
#include "matrix_allocation.h"
#include "global_variables.h"

namespace matrix_calculations
{
	
	template <typename index_type , typename value_type>
	class vector
	{
		value_type *A;
		index_type size;
		public:
		
		vector(index_type r , value_type v = (value_type)0 ) : size{r}
		{
			if(r*sizeof*A % allignment != 0)
			{
				generate_error(21);
			}
			A = std::aligned_alloc(allignment, r * sizeof *A);		
		
				
			for(index_type a = 0 ; a < r ; a++)
			{
				A[a] = v;
			}
		
		}
		
		vector(index_type r , value_type val , std::function<value_type (index_type , value_type)>  init ) : size{r}
		{
	
			if(r*sizeof*A % allignment != 0)
                        {
                                generate_error(21);
                        }

			A = std::aligned_alloc(allignment, r * sizeof *A);
		
			for(index_type a = 0 ; a < r ; a++)
			{
				A[a] = init(a,val);
			}
		}
				
						
	
		index_type return_size() 
		{
			return size;
		}
		value_type value(index_type c) 
		{
			if(c >= size)
			{

				generate_error(23);
			} 
			else
			{
				return A[c];
			} 
		}	
		value_type norm();		
		value_type dot_product(matrix_calculations::vector <index_type , value_type>);	

	};


	template <typename index_type , typename value_type>

	class sparse_matrix_operations
	{
		matrix::sparse_matrix <index_type , value_type> A;

		public:
		// Constructor to generate identity matrix
		sparse_matrix_operations(index_type r , index_type c)
		{
			for(index_type i = (index_type) 1 ; i <= r && i <= c ; i++)
			{
				A.add_element(i,i,1);
			}	
		}
		sparse_matrix_operations(index_type r , index_type c , std::function<value_type (index_type , index_type)> init )
		{
			for(index_type i = (index_type) 1 ; i <= r  ; i++)
			{
				for(index_type j = (index_type) 1 ; j <= c ; j++)
				{
					A.add_element(i, j , init(i,j));
				}
			}
		}		
		value_type matrix_value( index_type r , index_type c)
		{
			auto index = A.return_element_index(r,c); 
			if (index == -1)
 			{
				return 0;
			}
			else
			{
				return A.value[index];
			}
		}				
		
	
		
		index_type return_row_size()
		{
			return A.row_size();
		}
		index_type return_col_size() 
		{
			return A.col_size(); 
		}
		value_type row_sum( index_type r);
		value_type norm();		
		std::vector<value_type> SPMM(matrix_calculations::vector <index_type , value_type> ) ;	
	};

	
	
}
