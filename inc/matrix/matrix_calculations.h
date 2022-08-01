#ifndef Vector_matrix_caluclations_2022
#define Vector_matrix_caluclations_2022 

#include <omp.h>
#include <vector>
#include <cmath>
#include "matrix_allocation.h"
#include "global_variables.h"

namespace matrix_calculations
{
	template <typename index_type , typename value_type>
	class vector
	{
		index_type size;
		value_type *A;
		public:
		// constructors	
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
		
		vector(index_type r , value_type val , std::function<value_type (index_type , value_type)>  init ) : size{r}
		{
	
			if(r*sizeof*A % allignment != 0)
                        {
                                generate_error(21);

			 }

			A = (value_type * ) std::aligned_alloc(allignment, r * sizeof *A);
		
			for(index_type a = 0 ; a < r ; a++)
			{
				A[a] = init(a,val);
			}
		}
				
		vector(index_type r , std::function<value_type (index_type , std::vector<value_type>)> init , std::vector<value_type> init_v_values ) : size{r}
                {

                        if(r*sizeof*A % allignment != 0)
                        {
                                generate_error(21);
			}

                        A = (value_type *) std::aligned_alloc(allignment, r * sizeof *A);

                        for(index_type a = 0 ; a < r ; a++)
                        {
                                A[a] = init(a,init_v_values);

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

		


		// Functions returning values
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
		value_type dot_product(matrix_calculations::vector <index_type , value_type>);	
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
		void output_pointer()
		{
			std::cout << "Allocating pointer using other constructors" << A << std::endl;	
		}

	};

	template <typename index_type , typename value_type>

	class sparse_matrix_operations
	{
		matrix::sparse_matrix <index_type , value_type> A;

		public:
		// Constructor to generate identity matrix
		sparse_matrix_operations(index_type r , index_type c)
		{
			for(index_type i = (index_type) 1 ; i <= r && i <= c ; i++)
			{
				A.add_element(i,i,1);
				//std::cout << "Matrix value ["<< i << " , " << i << "] generated with value " << 1  << std::endl; 
			
			}	
//			std::cout << "Matrix sucessfully generated " << std::endl;
		}
		sparse_matrix_operations(index_type r , index_type c , std::function<value_type (index_type , index_type)> init )
		{
			for(index_type i = (index_type) 1 ; i <= r  ; i++)
			{
				for(index_type j = (index_type) 1 ; j <= c ; j++)
				{
					A.add_element(i, j , init(i,j));
					//std::cout << "Matrix value ["<< i << " , " << j << "] generated with value " << init(i,j) <<  std::endl; 
				}
			}
//			std::cout << "Matrix sucessfully generated " << std::endl;

		}		

		~sparse_matrix_operations() = default;
		//sparse_matrix_operations (sparse_matrix_operations&&) = default;
		//sparse_matrix_operations& operator=(const sparse_matrix_operations&)  = default;
                //sparse_matrix_operations& operator=(sparse_matrix_operations&&) = default      ;
		
		// Returning matrix values 
		value_type matrix_value( index_type r , index_type c)
		{
			auto index = A.return_element_index(r,c); 
			if (index <= 0)
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
		
		// matrix operations on the sparse matrix
		value_type row_sum( index_type r);
		value_type norm();		
		matrix_calculations::vector<index_type , value_type> SPMM(matrix_calculations::vector <index_type , value_type> ) ;	
	};

	
	
}

#endif
