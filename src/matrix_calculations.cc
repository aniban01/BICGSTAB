#include "matrix_calculations.h"

namespace matrix_calculations
{
		
	template class vector <int , double>;
        template class vector <int, float >;
        template class vector <long int , double>;
        template class vector <long int , float>;

// Functions for class vector
	template <typename index_type , typename value_type>
	value_type vector<index_type , value_type> :: norm()
	{
 		
	       	value_type sum = (value_type) 0;
		for (index_type i  = 0 ; i < size ; i++)
		{
			sum += A[i]* A[i];
		}
		return std::sqrt(sum);
	}


	template <typename index_type , typename value_type>
        value_type vector<index_type , value_type> :: dot_product(matrix_calculations::vector <index_type , value_type> B )
        {
	       value_type sum = (value_type)0 ;
                if(size != B.return_size())
		{
			generate_error(22);
		}
                for(index_type a = 0 ; a < size ; a++)
                {
                        sum += A[a] * B.value(a);
                }
                return sum;
        }



	template <typename index_type , typename value_type>

	vector <index_type , value_type> vector<index_type , value_type>::operator + (value_type num)
        {
                vector<index_type, value_type> B{size}; 
                for( auto i = (index_type) 0 ; i < size ; i ++)
                {
                        B.update_value(i  , A[i] + num );
                }
                return B;
        }
        template <typename index_type , typename value_type>
	vector <index_type , value_type> vector<index_type , value_type>::operator * (value_type num)
        {
                vector<index_type, value_type> B{size}; 
                for( auto i = (index_type) 0 ; i < size ; i ++)
                {
                        B.update_value(i  , A[i] * num );
                }
                return B;
        }
	template <typename index_type , typename value_type>
        vector <index_type , value_type> vector<index_type , value_type>::operator / (value_type num)
        {
                vector<index_type, value_type> B{size}; 
                for( auto i = (index_type) 0 ; i < size ; i ++)
                {
                        B.update_value(i  , A[i] / num );
                }
                return B;
        }
	template <typename index_type , typename value_type>
        vector <index_type , value_type> vector<index_type , value_type>::operator - (value_type num)
        {
                vector<index_type, value_type> B{size};
                for( auto i = (index_type) 0 ; i < size ; i ++)
                {
                        B.update_value(i  , A[i] - num );
                }
                return B;
        }
	
	template <typename index_type , typename value_type>
	vector <index_type , value_type> vector<index_type , value_type>::operator + (vector<index_type , value_type > num)
        {
                
		vector<index_type, value_type> B{size};
                for( auto i = (index_type) 0 ; i < size ; i ++)
                {
                        B.update_value(i  , A[i] + num.value(i) );
                }
                return B;
        }
        template <typename index_type , typename value_type>
	vector <index_type , value_type> vector<index_type , value_type>::operator * (vector<index_type , value_type > num)
        {

		vector<index_type, value_type> B{size};
                for( auto i = (index_type) 0 ; i < size ; i ++)
                {
                        B.update_value(i  , A[i] * num.value(i) );
                }
                return B;
        }

        template <typename index_type , typename value_type>
	vector <index_type , value_type> vector<index_type , value_type>::operator / (vector<index_type , value_type > num)
        {

		vector<index_type, value_type> B{size};
                for( auto i = (index_type) 0 ; i < size ; i ++)
                {
                        B.update_value(i  , A[i] / num.value(i) );
                }
                return B;
        }

        template <typename index_type , typename value_type>
	vector <index_type , value_type> vector<index_type , value_type>::operator - (vector<index_type , value_type >  num)
        {

		vector<index_type, value_type> B{size};
                for( auto i = (index_type) 0 ; i < size ; i ++)
                {
                        B.update_value(i  , A[i] - num.value(i) );
                }
                return B;
        }
	
	template <typename index_type , typename value_type>
        void vector<index_type , value_type> :: display()
	{
		for( auto i = 0 ; i < size; i++)
          	{
               		std::cout << " " << A[i];
             	}
	}

	template class sparse_matrix_operations <int , double>;
        template class sparse_matrix_operations <int, float >;
        template class sparse_matrix_operations <long int , double>;
        template class sparse_matrix_operations <long int , float>;




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
	matrix_calculations::vector<index_type , value_type>  sparse_matrix_operations<index_type , value_type> :: SPMM(matrix_calculations::vector <index_type , value_type> B) 
	{
		index_type row_index = 1 , col_index = 0 , col;
		auto row_size  =  (index_type) A.row.size();
		auto col_size  =  (index_type) A.col.size();
		
		value_type sum = (value_type) 0 ;
		matrix_calculations::vector <index_type , value_type> product(B.return_size());
		
		for(auto value : A.value)
		{
			col = A.col[col_index];

			sum += value * B.value(col-1);
			++col_index;
		
			if(col_index == A.row[row_index] )
			{
				product.update_value(row_index -1 , sum);
				sum = 0;

				if(A.row[row_index] == A.row[row_index+1])
				{	
					while(col_index == A.row[row_index] && row_index < row_size )
					{
						++row_index;
						product.update_value(row_index - 1, sum);	
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
		std::cout << "sum of row " << r << " is " << sum;
		return sum;
	}

}




