#include "BICGSTAB.h"

namespace solver
{
        template <typename index_type , typename value_type>
	void BICGSTAB<index_type, value_type> :: display()
	{
		auto num_rows = A.return_row_size();
		auto num_cols = A.return_col_size();
		index_type vector_index = 0;
		for(auto i = (index_type)1 ; i < num_rows ; ++i)
		{
			std::cout << " | " ;
			for(auto j = (index_type)1 ; j < num_cols ; ++j)
			{
				std::cout<< " " << matrix_value(i,j) << " " ; 
			}
			if(i == (index_type) num_rows/2)
			{
				std::cout << " | " << x.value(vector_index) << " |   =   | " << b.value(vector_index) << " | "; 
			}
			else
			{
				std::cout << " | " << x.value(vector_index) << " |       | " << b.value(vector_index) << " | ";  
			}	
			std::cout << std::endl;

		
		}
	}
}
