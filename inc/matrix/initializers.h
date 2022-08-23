

#include "matrix_calculations.h"
#include "matrix_calculations_parallel.h"

#ifndef initializer_2022
#define initializer_2022


/**
 * \brief Initializer namespace contains all initialization functions for vectors and matrices used in our program     
 *  
 * \description 
 *    	The namespace contains a group of functions which can be used to initialize the matrix and vector used for this program 
 *     
 * \functions
 *	value_type Matrix_initializer(index_type r , index_type c ) : 	The templated function returns a value of type value type to initialize a matrix when the row (r) and column (c) value for the position 
 *									is provided	
 *     	
 *  	value_type Vector_initializer(index_type r , std::vector<value_type> A) :	The templated function returns a value of type value type to initialize a vector when the index (r) and vector of value
 *  											of type std::vector <value_type> is provided 
 *  	std::vector<value_type> Vector_constant_initializer_matrix(index_type r , matrix_calculations::sparse_matrix_operations<index_type , value_type> A , value_type v) : 	
 *  											The templated function return a std::vector<value_type> which returns the vector b in Ax = b when matrix A and vector 
 *  											with constant value v is given.  
 **/

namespace initializer
{

	template <typename index_type , typename value_type>
        value_type Matrix_initializer(index_type r , index_type c );
       	       
	template <typename index_type , typename value_type>
        value_type Matrix_initializer_1(index_type r , index_type c );

 
       template <typename index_type , typename value_type>
        value_type Vector_initializer(index_type r , std::vector<value_type> A);

	template <typename index_type , typename value_type>
        std::vector<value_type> Vector_constant_initializer_matrix(index_type r , matrix_calculations::sparse_matrix_operations<index_type , value_type> A , value_type v); 
}

#endif
