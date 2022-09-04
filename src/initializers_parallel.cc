
#include "initializers_parallel.h"

namespace initializer_parallel
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
                else if(r == c-4 || c == r - 4)
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
	template double Matrix_initializer<long int, double>(long int,long int);
	template float Matrix_initializer<long int, float>(long int, long  int);
	
	template <typename index_type , typename value_type>
	value_type Matrix_initializer_1(index_type r , index_type c )
	{
		if(c % r == 0)
                {
                        return (value_type) (c%r) / r ;
                }
                else if(c == r - 2 || c == r - 5 || c == r - 7)
                {
                        return (value_type) c / r ;
                }
		else
                {
                        return (value_type)0;
                }	
	}
	template double Matrix_initializer_1<int, double>(int, int);
        template float Matrix_initializer_1<int, float>(int, int);
        template double Matrix_initializer_1<long int, double>(long int,long int);
        template float Matrix_initializer_1<long int, float>(long int, long int);


	template <typename index_type , typename value_type>
        value_type Vector_initializer(index_type r , std::vector<value_type> A)
        {

                return A[r];

        }
 	template double Vector_initializer<int, double>(int, std::vector<double, std::allocator<double> >);
 	template float Vector_initializer<int, float>(int, std::vector<float, std::allocator<float> >);
	template double Vector_initializer<long int, double>(long int, std::vector<double, std::allocator<double> >);
 	template float Vector_initializer<long int, float>(long int, std::vector<float, std::allocator<float> >);

	template <typename index_type , typename value_type>
        value_type Vector_initializer_1(index_type r , value_type i)
        {

                return (value_type) r * i;

        }
 	template double Vector_initializer_1<int, double>(int, double);
 	template float Vector_initializer_1<int, float>(int, float);
	template double Vector_initializer_1<long int, double>(long int, double);
 	template float Vector_initializer_1<long int, float>(long int,float );



	template <typename index_type , typename value_type>
        matrix_calculations_parallel::vector<index_type , value_type> Vector_constant_initializer_matrix( matrix_calculations_parallel::sparse_matrix_operations<index_type , value_type> A ,index_type lower ,  value_type v) 
	{
		matrix_calculations_parallel::vector<index_type , value_type> rhs{A.return_col_size() , lower , v};
 		matrix_calculations_parallel::vector<index_type , value_type> ret = A.SPMM(rhs);
		return ret;
	}
	template matrix_calculations_parallel::vector<int, double > Vector_constant_initializer_matrix( matrix_calculations_parallel::sparse_matrix_operations<int, double>, int , double);
	template matrix_calculations_parallel::vector<int , float> Vector_constant_initializer_matrix(matrix_calculations_parallel::sparse_matrix_operations<int, float>, int , float);
	template matrix_calculations_parallel::vector<long int , double > Vector_constant_initializer_matrix( matrix_calculations_parallel::sparse_matrix_operations<long int, double>,long int, double);
	template matrix_calculations_parallel::vector<long int , float > Vector_constant_initializer_matrix( matrix_calculations_parallel::sparse_matrix_operations<long int, float>,long int,  float);


}

