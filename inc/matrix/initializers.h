

#include "matrix_calculations.h"

#ifndef initializer_2022
#define initializer_2022



namespace initializer
{

	template <typename index_type , typename value_type>
        value_type Matrix_initializer(index_type r , index_type c );
       	       

        template <typename index_type , typename value_type>
        value_type Vector_initializer(index_type r , std::vector<value_type> A);

	template <typename index_type , typename value_type>
        std::vector<value_type> Vector_constant_initializer_matrix(index_type r , matrix_calculations::sparse_matrix_operations<index_type , value_type> A , value_type v); 
}

#endif
