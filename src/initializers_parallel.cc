
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
//		std::cout << "Returning 1 for element " << r << " , " << c << std::endl;
		return (value_type)1;
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

                return (value_type) 1;

        }
 	template double Vector_initializer_1<int, double>(int, double);
 	template float Vector_initializer_1<int, float>(int, float);
	template double Vector_initializer_1<long int, double>(long int, double);
 	template float Vector_initializer_1<long int, float>(long int,float );



	template <typename index_type , typename value_type>
        matrix_calculations_parallel::vector<index_type , value_type> Vector_constant_initializer_matrix( matrix_calculations_parallel::sparse_matrix_operations<index_type , value_type> A ,index_type lower ,  value_type v) 
/*	{
		std::vector<value_type> vec;
		for(auto i = (index_type) 1 ; i <= r ; i++)
		{
//			std::cout << "row size : " << r << std::endl;
			auto sum = (value_type) 0;
			for(auto k = (index_type) 1 ; k <= r ; k++)
//			for(long int k =  1 ; k <= r ; k++)
			{
//				std::cout << "Adding for element " << i << " , " << k <<std::endl ; //" which has value " << A.matrix_value(i,k) <<std::endl;  
				sum += A.matrix_value(i,k);
//				std::cout << "Element " << i << " , " << k << " which has value " <<std::endl; //<< A.matrix_value(i,k) << " added " << std::endl;   
			//	if(A.matrix_value(i,k))
			//		break;
			}
			vec.push_back(sum*v);
//			std::cout << "Vector element " << i   << " added " << std::endl;

		}	
		return vec;
	}
*/
	{
		matrix_calculations_parallel::vector<index_type , value_type> rhs{A.return_col_size() , lower , v};
 		matrix_calculations_parallel::vector<index_type , value_type> ret = A.SPMM(rhs);
		return ret;
	}
/*
	template matrix_calculations_parallel::vector<int, double > Vector_constant_initializer_matrix<int, double>(int, matrix_calculations_parallel::sparse_matrix_operations<int, double>, double);
	template matrix_calculations_parallel::vector<int , float> Vector_constant_initializer_matrix<int, float>(int, matrix_calculations_parallel::sparse_matrix_operations<int, float>, float);
	template matrix_calculations_parallel::vector<long int , double > Vector_constant_initializer_matrix<long int, double>(long int, matrix_calculations_parallel::sparse_matrix_operations<long int, double>, double);
	template matrix_calculations_parallel::vector<long int , float > Vector_constant_initializer_matrix<long int, float>(long int, matrix_calculations_parallel::sparse_matrix_operations<long int, float>, float);

*/	

	template matrix_calculations_parallel::vector<int, double > Vector_constant_initializer_matrix( matrix_calculations_parallel::sparse_matrix_operations<int, double>, int , double);
	template matrix_calculations_parallel::vector<int , float> Vector_constant_initializer_matrix(matrix_calculations_parallel::sparse_matrix_operations<int, float>, int , float);
	template matrix_calculations_parallel::vector<long int , double > Vector_constant_initializer_matrix( matrix_calculations_parallel::sparse_matrix_operations<long int, double>,long int, double);
	template matrix_calculations_parallel::vector<long int , float > Vector_constant_initializer_matrix( matrix_calculations_parallel::sparse_matrix_operations<long int, float>,long int,  float);


}

