
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
	template double Matrix_initializer<long int, double>(long int,long int);
	template float Matrix_initializer<long int, float>(long int, long  int);
	
	template <typename index_type , typename value_type>
	value_type Matrix_initializer_1(index_type r , index_type c )
	{
		std::cout << "Returning 1 for element " << r << " , " << c << std::endl;
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
        std::vector<value_type> Vector_constant_initializer_matrix(index_type r , matrix_calculations::sparse_matrix_operations<index_type , value_type> A , value_type v) 
	{
		std::vector<value_type> vec;
		for(auto i = (index_type) 1 ; i <= r ; i++)
		{
			auto sum = (value_type) 0;
			for(auto k = (index_type) 1 ; k <= r ; k++)
			{
				std::cout << "Adding for element " << i << " , " << k << " which has value " << A.matrix_value(i,k) <<std::endl;  
				sum += A.matrix_value(i,k)*v;
			}
			vec.push_back(sum);
		}	
		return vec;
	}
	template std::vector<double, std::allocator<double> > Vector_constant_initializer_matrix<int, double>(int, matrix_calculations::sparse_matrix_operations<int, double>, double);
	template std::vector<float, std::allocator<float> > Vector_constant_initializer_matrix<int, float>(int, matrix_calculations::sparse_matrix_operations<int, float>, float);
	template std::vector<double, std::allocator<double> > Vector_constant_initializer_matrix<long int, double>(long int, matrix_calculations::sparse_matrix_operations<long int, double>, double);
	template std::vector<float, std::allocator<float> > Vector_constant_initializer_matrix<long int, float>(long int, matrix_calculations::sparse_matrix_operations<long int, float>, float);



}

