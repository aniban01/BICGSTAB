#include "matrix_calculations.h"

namespace matrix_calculations
{

// Functions for class vector
	template <typename index_type , typename value_type>
	value_type vector<index_type , value_type> :: norm()
	{
        	value_type sum;
        	omp_set_num_threads(thread_num);
		#pragma omp parallel for simd reduction(+:sum) 
		for (value_type element : A.value)
		{
			sum += element * element;
		}
		return std::sqrt(sum);
	}


	template <typename index_type , typename value_type>
        value_type vector<index_type , value_type> :: dot_product(matrix_calculations::vector <index_type , value_type> B )
        {
                value_type sum;
                if(A.size != B.return_size())
		{
			generate_error(22);
		}
		omp_set_num_threads(thread_num);
                #pragma omp parallel for simd reduction(+:sum) 
                for(index_type a = 0 ; a < size ; a++)
                {
                        sum += A[a] * B.value(a);
                }
                return sum;
        }




// Function definitions for class sparse_matrix_operations
	template <typename index_type , typename value_type>
	value_type sparse_matrix_operations<index_type , value_type> :: norm()
	{
        	value_type sum_mat = 0;
        
		for (value_type element : A.value)
		{
			sum_mat += element * element;
		}
		return std::sqrt(sum_mat);
	}


	template <typename index_type , typename value_type>
	std::vector<value_type>  sparse_matrix_operations<index_type , value_type> :: SPMM(matrix_calculations::vector <index_type , value_type> B) 
	{
		index_type row_index = 1 , col_index = 0 , col;
		auto row_size  =  (index_type) A.row.size();
		auto col_size  =  (index_type) A.col.size();
		
		value_type sum = (value_type) 0 ;
		std::vector <value_type> product;
		for(auto value : A.value)
		{
			col = A.col[col_index];

			sum += value * B.value(col-1);
			++col_index;
		
			if(col_index == A.row[row_index] )
			{
				product.push_back(sum);
				sum = 0;

				if(A.row[row_index] == A.row[row_index+1])
				{	
					while(col_index == A.row[row_index] && row_index < row_size )
					{
						++row_index;
						product.push_back(sum);	
					}
					if(row_index == row_size && col_index != col_size)
					{
						generate_error(20);
					}
				}
				else
				{
					++row_index;
				} 		
		
				
			}	
		
		}

		return product;
	}

	template <typename index_type , typename value_type>
	value_type  sparse_matrix_operations<index_type , value_type> :: row_sum( index_type r) 
	{
		index_type index = A.row[r-1];
		index_type end_index = A.row[r];
		value_type sum = 0 ;		
		for(; index < end_index ; ++index)
		{
			sum += A.value[index] ;
		}
		return sum;
	}
}


int init(int i , int j)
{
	return (i*10 + j);
}


