
#include "initializers.h"

namespace initializer
{

	template <typename index_type , typename value_type>
        value_type Matrix_initializer(index_type r , index_type c )
       	{
         	if(r == c)
                {
                  	return 2;
              	}
                else if(r == c-1 || c == r-1)
                {
                        return 1;
                }
                else
                {
                       	return 0;
               	}
      	}
	template double Matrix_initializer<int, double>(int, int);
	template float Matrix_initializer<int, float>(int, int);
	template double Matrix_initializer<long unsigned int, double>(long unsigned int,long unsigned int);
	template float Matrix_initializer<long unsigned int, float>(long unsigned int, long  unsigned int);
	
	
	template <typename index_type , typename value_type>
        value_type Vector_initializer(index_type r , std::vector<value_type> A)
        {

                return A[r];

        }
 	template double Vector_initializer<int, double>(int, std::vector<double, std::allocator<double> >);
 	template float Vector_initializer<int, float>(int, std::vector<float, std::allocator<float> >);
	template double Vector_initializer<long unsigned int, double>(long unsigned int, std::vector<double, std::allocator<double> >);
 	template float Vector_initializer<long unsigned int, float>(long unsigned int, std::vector<float, std::allocator<float> >);



	template <typename index_type , typename value_type>
        std::vector<value_type> Vector_constant_initializer_matrix(index_type r , matrix_calculations::sparse_matrix_operations<index_type , value_type> A , value_type v) 
	{
		std::vector<value_type> Vec;
		for(index_type i = 0 ; i < r; i++)
		{
		
			Vec.push_back(A.row_sum(r)*v);
		}
		return Vec;
	}
	template std::vector<double, std::allocator<double> > Vector_constant_initializer_matrix<int, double>(int, matrix_calculations::sparse_matrix_operations<int, double>, double);
	template std::vector<float, std::allocator<float> > Vector_constant_initializer_matrix<int, float>(int, matrix_calculations::sparse_matrix_operations<int, float>, float);
	template std::vector<double, std::allocator<double> > Vector_constant_initializer_matrix<long unsigned int, double>(long unsigned int, matrix_calculations::sparse_matrix_operations<long unsigned int, double>, double);
	template std::vector<float, std::allocator<float> > Vector_constant_initializer_matrix<long unsigned int, float>(long unsigned int, matrix_calculations::sparse_matrix_operations<long unsigned int, float>, float);



}

