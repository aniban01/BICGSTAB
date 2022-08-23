#ifndef Vector_matrix_caluclations_parallel_2022
#define Vector_matrix_caluclations_parallel_2022 

#include <omp.h>
#include <vector>
#include <cmath>
#include <fstream>
#include "matrix_allocation.h"
#include "global_variables.h"


namespace matrix_calculations_parallel
{
	
	/**
	* \brief  vector class which efficiently performs all vector operations required for the program 
	* \description 
     	* The class has two member objects 1) size (data type : index_type) which stores size of the vector 2) A (data type : value_type) which is a pointer to an alligned data block of type vector type
     	* The functions are created to utilize SIMD operations with alligned data sets for efficient implimentation of vector operations
     	* 
     	* \functions
	* return_size() : returns size of the vector
	* value( index_type c ) : return value at index c
	* norm() : calculates second norm of the vector
	* update_value( index_type i , value_type val) : updates value provided by val at position i
	* 
	* \operator overloading
	*  vector operator + (value_type num);
	*  vector operator * (value_type num);
	*  vector operator / (value_type num);
	*  vector operator - (value_type num);
	*  vector operator + (vector<index_type , value_type > num);
	*  vector operator * (vector<index_type , value_type > num);
	*  vector operator / (vector<index_type , value_type > num);
	*  vector operator - (vector<index_type , value_type > num);
	*
	* */


	template <typename index_type , typename value_type>
	class vector
	{
		index_type size;
		value_type *A;
		public:
		// constructors	
			
		vector()
		{
			A = NULL;
			size = 0;
		}
	
		vector(index_type r , value_type v = (value_type)0 ) : size{r}
                {
                        if(r*sizeof*A % allignment != 0)
                        {
                                generate_error(21);

                        }
                        A = (value_type * )std::aligned_alloc(allignment, r * sizeof *A);


                        for(index_type a = 0 ; a < r ; a++)
                        {
                                A[a] = v;
                        }
                }


                ~vector()
                {
			std::free(A);	
		};
                
		vector (const vector < index_type ,  value_type> & rhs) : size{rhs.size}
		{
		   	A = (value_type * )std::aligned_alloc(allignment, size* sizeof *A);	
			for( auto i = (index_type)0 ; i < size ; i++)
			{
				A[i] = rhs.A[i];

			}
		}

                vector (vector  < index_type ,  value_type> && rhs) : size{0} , A{nullptr}
                {
			A = rhs.A;
			size = rhs.size;	
		}
		vector& operator=(const vector  < index_type ,  value_type> & rhs )
		{
			if (this != &rhs)
   			{
      				std::free(A);    
      				size  = rhs.size;
				A = (value_type * )std::aligned_alloc(allignment, size* sizeof *A);
                        	for( auto i = (index_type)0 ; i < size ; i++)
                        	{
                                	A[i] = rhs.A[i];

                        	}

     			}
			return *this;
			
		}  
		vector& operator=(vector  < index_type ,  value_type> && rhs)
		{
			if (this != &rhs)
   			{
      				std::free(A);    
      				A = rhs.A;
      				size  = rhs.size;
      				rhs.A = nullptr;
     				rhs.size= 0;
     			}
			
			return *this;
		}

		


		// functions returning values
		index_type return_size() 
		{
			return size;
		}
		value_type value(index_type c) 
		{
			if(c >= size)
			{

				generate_error(23);
				return A[0];
			} 
			else
			{
				return A[c];
			} 
		}	
	

		// Functions to carry out vactor operations
		value_type norm();		
		value_type dot_product(matrix_calculations_parallel::vector <index_type , value_type>);	
		void update_value( index_type i , value_type val)
		{
			if(i < 0 || i >= size)
			{
				 generate_error(24);
			}
			else
			{
				A[i] = val;	
			}
		}
		

		vector operator + (value_type num);
        	vector operator * (value_type num);
        	vector operator / (value_type num);
        	vector operator - (value_type num);
		vector operator + (vector<index_type , value_type > num);
        	vector operator * (vector<index_type , value_type > num);
        	vector operator / (vector<index_type , value_type > num);
        	vector operator - (vector<index_type , value_type > num);

		// Parallel Constructors
		void allocate(index_type row_start , index_type row_end ,  value_type v = (value_type)0 ) 
		{
			if((row_end - row_start + 1)*sizeof*A % allignment != 0)
			{
				generate_error(21);

			}
			A = (value_type * )std::aligned_alloc(allignment, (row_end - row_start + 1) * sizeof *A);		
			size = (row_end - row_start + 1);	
							
			for(index_type a = 0 ; a < (row_end - row_start + 1) ; a++)
			{
				A[a] = v;
			}
		}
		
		void allocate(index_type row_start , index_type row_end , value_type val , std::function<value_type (index_type , value_type)>  init ) 
		{
	
			if((row_end - row_start + 1)*sizeof*A % allignment != 0)
                        {
                                generate_error(21);

			 }

			A = (value_type * ) std::aligned_alloc(allignment, (row_end - row_start + 1) * sizeof *A);
			size = (row_end - row_start + 1);
			for(index_type a = 0 ; a < (row_end - row_start + 1) ; a++)
			{
				A[a] = init(a,val);
			}
		}
				
		void allocate(index_type row_start , index_type row_end , std::function<value_type (index_type , std::vector<value_type>)> init , std::vector<value_type> init_v_values ) 
                {

                        if((row_end - row_start + 1)*sizeof*A % allignment != 0)
                        {
                                generate_error(21);
			}

                        A = (value_type *) std::aligned_alloc(allignment, (row_end - row_start + 1) * sizeof *A);

			size = (row_end - row_start + 1);
                        for(index_type a = 0 ; a < (row_end - row_start + 1) ; a++)
                        {
                                A[a] = init(a,init_v_values);

		       }
		}	


	};

	template <typename index_type , typename value_type>


	/**
	* \brief sparse_matrix_operations  class which efficiently performs all matrix operations required for the program 
	* \description 
     	* The class has one member object : A : Built on the sparse_matrix class defined in matrix_allocation.h
     	* The functions are created to utilize functions defined in sparse_matrix class efficiently impliment of matrix operations
     	* 
     	* \functions
	* return_row_size() : returns row size of the vector
	* return_col_size() : returns col size of the vector
	* matrix_value( index_type r , index_type c ) : return value at position row = r , column = c
	* norm() : calculates second norm of the matrix
	* update_value( index_type i , value_type val) : updates value provided by val at position i
	* row_sum( index_type r) : returns the sum of the row value for row r
	* SPMM (matrix_calculations_parallel::vector <index_type , value_type> ) : performs matrix vector multiplication 
	*
	* */


	class sparse_matrix_operations
	{
		matrix::sparse_matrix <index_type , value_type> A;

		public:
		// Constructor to generate identity matrix
		sparse_matrix_operations() {};

		void allocate(index_type row_start , index_type row_end , index_type col_start, index_type col_end)
                {
			
                        for(index_type i = (index_type) row_start ; i>= col_start && i <= row_end && i <= col_end ; i++)
                        {
                                A.add_element(i,i,1);
                        }
                }

		void allocate(index_type row_start ,  index_type row_end , index_type col_start ,  index_type col_end , std::function<value_type (index_type , index_type)> init )
		{
			for(index_type i = (index_type) row_start ; i <= row_end  ; i++)
			{
				for(index_type j = (index_type) col_start ; j <= col_end ; j++)
				{
				//	std::cout << "In sparse matrix operation for element " << i << " , " << j << std::endl;
					A.add_element(i, j , init(i,j));
				//	std::cout << "Exiting sparse matrix operation  for element " << i << " , " << j << std::endl;
				}
		//		std::cout << "Row " << i << " created" <<std::endl;
			}

		}		
		
		void allocate(index_type row_start ,  index_type row_end , index_type col_start ,  index_type col_end , std::string path)
		{
			std::ifstream file;
		        file.open(path);
       			if(!file)
        		{
                		generate_error(25);		
       			}
			else
			{
				while(!file.eof())
			        {
                			int col , row;
                			double value;
                			file >> col;
                			file >> row;
                			file >> value;
        				if(row >= row_start && col >= col_start && row <= row_end && col <= col_end)			
					{
						A.add_element(row,col,value);
					}
					
				}

			}
			file.close();
			//	std::cout << "Exiting sparse matrix operation  for element " << i << " , " << j << std::endl;
		

		}


		~sparse_matrix_operations() = default;
		//sparse_matrix_operations (sparse_matrix_operations&&) = default;
		//sparse_matrix_operations& operator=(const sparse_matrix_operations&)  = default;
                //sparse_matrix_operations& operator=(sparse_matrix_operations&&) = default      ;
		
            		
		// Returning matrix values 
		value_type matrix_value( index_type r , index_type c)
		{
			auto index = A.return_element_index(r,c); 
			if (index < 0)
 			{
				return 0;
			}
			else
			{
				return A.value[index];
			}
		}				
		index_type return_row_size()
		{
			return A.row_size();
		}
		index_type return_col_size() 
		{
			return A.col_size(); 
		}
		
		void print_matrix()
		{
			std::cout << " Printing element " << std::endl;
			//A.print_elements();
			A.print_matrix(35 , 35);

		//	A.print_matrix(A.row_size() , A.col_size());
		}
		// matrix operations on the sparse matrix
		value_type row_sum( index_type r);
		value_type norm();		
		matrix_calculations_parallel::vector<index_type , value_type> SPMM(matrix_calculations_parallel::vector <index_type , value_type> ) ;	

	};

	
	
}

#endif
