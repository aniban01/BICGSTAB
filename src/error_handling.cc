
#include "error_handling.h" 

void generate_error(int A)
{
	switch (A)
	{
		case 10: 
			std::cerr<<"Error (code 10) : <matrix::sparse_matrix::void add_element(index_type r, index_type c , value_type val)> : Problem adding element at row and column value. Minimum row value and column value has to be equal to 1 " << std::endl;
                        exit(1);
			break;
		
		case 11:	
			std::cerr << "Error (code 11): <matrix::sparse_matrix::index_type return_element_index(index_type r , index_type c)>: Attempted to access row  which is out of scope \n";
                        exit(1);
			break;
		
		case 20:
			std::cerr << "Error (code 20): <matrix_calculations::sparse_matrix_operations<index_type , value_type> :: SPMM(std::vector <value_type> B)>: matrix data issue : column index has not reached its end while row matrix has crossed bounds \n";
                        exit(1);
			break;

		case 21:
                        std::cerr << "Error (code 21): <matrix_calculations::vector<index_type , value_type> : contructor issue : number of rows is not divisible by allignment, please change allignment or number of rows \n";
                        exit(1);
                        break;
		
		case 22:
                        std::cerr << "Error (code 22): <matrix_calculations::vector<index_type , value_type>::dot_product(matrix_calculations::vector <index_type , value_type>) : The size of Matrix A and Matrix B used in the dot product calculation not the same \n";
                        exit(1);
                        break;
		
		case 23:
                        std::cerr << "Error (code 23): <matrix_calculations::vector<index_type , value_type>::value(index_type) : Attempting to access value out of bounds\n";
                        exit(1);
                        break;
		
		case 24:
                        std::cerr << "Error (code 23): <matrix_calculations::vector<index_type , value_type>::update_value(index_type) : Attempting to update value out of bounds\n";
                        exit(1);
                        break;
	

		default:
			std::cerr << "Error Unknown : Terminating execution \n";
			exit(1);

	}
}

