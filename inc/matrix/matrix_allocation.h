#include <execution>
#include <vector>
#include <algorithm>
#include "error_handling.h"


namespace matrix
{

	
/**
 * \brief Sparse Matrix structure which helps store data in a compressed row storage method	
 *
 * \description 
 * 		The struct has two data types which are templated 1) index_type which represents the data type of the vector of row or column values 2) element_type which contains the value of the matrix
 * 		The method of interpretting the row, col and value vectors are discussed in the link as https://mc-stan.org/docs/2_19/functions-reference/CSR.html
 *
 * \functions
 * 		print_elements() : Prints elements stored in the row , col and value vector as is
 * 		print_matrix() : Prints elements stored in value in matrix format
 *		add_element(r, c, val) : Adds element with value (val) at point with row value r and column value c
 *		return_element_index(r , c ): Returns the index of the value vector for value stored at row value r and column value c. If function returns -1 then the value is non existant (0 value)
 *
 */
	template <typename index_type , typename value_type>

	struct sparse_matrix
	{
		std::vector<index_type> row;
		std::vector<index_type> col;
		std::vector<value_type> value;
	
		void print_elements();
			
		
		index_type row_size()
		{
			return row.size() - 1;
		}
	
		index_type col_size()
		{
			return *std::max_element(std::execution::par ,  col.begin() , col.end()  );
		
		}
		void print_matrix(index_type r   , index_type c );
		
		void add_element(index_type r, index_type c , value_type val);		
				
		index_type return_element_index(index_type r , index_type c);
				
	}; 


}


