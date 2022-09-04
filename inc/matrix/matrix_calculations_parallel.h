#ifndef Vector_matrix_caluclations_parallel_2022
#define Vector_matrix_caluclations_parallel_2022 

#include <omp.h>
#include <vector>
#include <cmath>
#include <fstream>
#include <map>
#include "matrix_allocation.h"
#include "global_variables.h"
#include "parallel_alg.h"


namespace matrix_calculations_parallel
{
	
	/**
	* \brief  vector class which efficiently performs all vector operations required for the program in parallel
	* \description 
     	* The class has two member objects 1) size (data type : index_type) which stores size of the vector 2) A (data type : value_type) which is a pointer to an alligned data block of type vector type
     	* The functions are created to utilize SIMD operations with alligned data sets for efficient implimentation of vector operations in parallel
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
		index_type lower;
		value_type *A;

		public:
		// constructors	
			
		vector()
		{
			A = NULL;
			size = 0;
			lower = 0;
		}
	
		vector(index_type r , index_type l = 0 , value_type v = (value_type)0 ) : size{r} , lower{l}
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
                
		vector (const vector < index_type ,  value_type> & rhs) : size{rhs.size} , lower {rhs.lower}
		{
		   	A = (value_type * )std::aligned_alloc(allignment, size* sizeof *A);	
			for( auto i = (index_type)0 ; i < size ; i++)
			{
				A[i] = rhs.A[i];

			}
		}

                vector (vector  < index_type ,  value_type> && rhs) : size{rhs.size} , lower{rhs.lower},  A{nullptr}
                {
			A = rhs.A;
		}
		vector& operator=(const vector  < index_type ,  value_type> & rhs )
		{
			if (this != &rhs)
   			{
      				std::free(A);    
      				size  = rhs.size;
				lower = rhs.lower;
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
      				lower = rhs.lower;
				rhs.A = nullptr;
     				rhs.size= 0;
				rhs.lower = 0;
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
			if(c-lower >= size)
			{

				generate_error(23);
				return A[0];
			} 
			else
			{
				return A[c-lower];
			} 
		}	
		
		index_type return_lower()
		{
			return lower;
		}	

		// Functions to carry out vactor operations
		value_type norm();		
		value_type dot_product(matrix_calculations_parallel::vector <index_type , value_type>);	
		value_type local_dot_product(matrix_calculations_parallel::vector <index_type , value_type>);
		void display(); 
		void update_value( index_type i , value_type val)
		{
			if(i < 0 || i-lower >= size)
			{
				 generate_error(24);
			}
			else
			{
				A[i-lower] = val;	
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
		void allocate(index_type row_start , index_type row_end  ,  value_type v = (value_type)0 ) 
		{
			if((row_end - row_start + 1)*sizeof*A % allignment != 0)
			{
				generate_error(21);

			}
			A = (value_type * )std::aligned_alloc(allignment, (row_end - row_start + 1) * sizeof *A);		
			size = (row_end - row_start + 1);	
			lower = row_start;						
			for(index_type a = 0 ; a < (row_end - row_start + 1) ; a++)
			{
				A[a] = v;
			}
		}
		
		void allocate(index_type row_start , index_type row_end ,  std::function<value_type (index_type , value_type)>  init , value_type val ) 
		{
	
			if((row_end - row_start + 1)*sizeof*A % allignment != 0)
                        {
                                generate_error(21);

			 }

			A = (value_type * ) std::aligned_alloc(allignment, (row_end - row_start + 1) * sizeof *A);
			size = (row_end - row_start + 1);
			lower = row_start;
			for(index_type a = 0 ; a < (row_end - row_start + 1) ; a++)
			{
				A[a] = init(a+lower,val);
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
                	lower = row_start; 
			for(index_type a = 0 ; a < (row_end - row_start + 1) ; a++)
                        {
                                A[a] = init(a+lower,init_v_values);

		       	}
		}	
		void allocate(vector  < index_type ,  value_type> rhs ) 
		{
	
			size  = rhs.size;
                        lower = rhs.lower;
                        A = (value_type * )std::aligned_alloc(allignment, size* sizeof *A);
                       	for( auto i = (index_type)0 ; i < size ; i++)
                      	{
                            	A[i] = rhs.A[i];

                        }

		
		}	


	};


	struct communicator_info
	{

		int rank;
		int num_element;
		int start_index;
		int dest_index;
		int dest_num_element;
	};
	
	template <typename index_type , typename value_type>


	/**
	* \brief sparse_matrix_operations  class which efficiently performs all matrix operations required for the program in parallel 
	* \description 
     	* The class has one member object : A : Built on the sparse_matrix class defined in matrix_allocation.h
     	* The functions are created to utilize functions defined in sparse_matrix class efficiently impliment of matrix operations in parallel
     	* 
     	* \functions
	* return_row_size() : returns row size of the vector
	* return_col_size() : returns col size of the vector
	* matrix_value( index_type r , index_type c ) : return value at position row = r , column = c
	* norm() : calculates second norm of the matrix
	* update_value( index_type i , value_type val) : updates value provided by val at position i
	* row_sum( index_type r) : returns the sum of the row value for row r
	* SPMM (matrix_calculations_parallel::vector <index_type , value_type> ) : performs matrix vector multiplication 
	* allocate : initialized the value
	* allocate_grid() : distributes the grid among different processors
	* setup_communication() : sets up the communication between different processors
	* */


	class sparse_matrix_operations
	{
		matrix::sparse_matrix <index_type , value_type> A;
		std::vector<index_type> required_cols;
		MPI_Comm comm = MPI_COMM_WORLD;
		index_type low_row;
		index_type high_row;
		index_type row_size;


		int num_element_send;	
		int num_element_recv;
		std::vector <communicator_info> send_details;
		std::vector <communicator_info> recv_details;
		std::vector <int> send_index_buffer;
		std::vector <int> recv_index_buffer;

		public:
		// Constructor to generate identity matrix
		sparse_matrix_operations() 
		{};

		~sparse_matrix_operations() = default;
		
            		
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
		
			int myid, nprocs;
	                MPI_Comm_rank(MPI_COMM_WORLD, &myid);
        	        MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
               	 	MPI_Barrier(comm);
			for( auto k=0; k<nprocs; k++){
        	       		if( k == myid )
				{
					for( auto i = low_row ; i <= high_row ; i++)
                                	{
						for(auto j = 1 ;  j <= row_size ; j++) 					
						{
							std::cout << matrix_value(i,j) << "\t";
						}
						std::cout << std::endl;
					}
				}
				fflush(stdout);
	                        sleep(1);
        	                MPI_Barrier(MPI_COMM_WORLD);

			}
		}
		value_type norm();		
		matrix_calculations_parallel::vector<index_type , value_type> SPMM(matrix_calculations_parallel::vector <index_type , value_type> ) ;	
		


		void allocate_grid();
		void setup_communication();
		void allocate(index_type row_num , index_type row_start , index_type row_end , index_type col, MPI_Comm C = MPI_COMM_WORLD )
                {
			row_size = row_num;
			comm = C;	
			low_row = row_start;
                	high_row = row_end; 
                       for(index_type i = (index_type) row_start ; i <= row_end && i <= col; i++)
                        {
                                A.add_element(i,i,1);
			}
			
			allocate_grid();
                        setup_communication();
		 }

		void allocate(index_type row_num , index_type row_start ,  index_type row_end , index_type col, std::function<value_type (index_type , index_type)> init , MPI_Comm C = MPI_COMM_WORLD )
		{
			row_size = row_num;
			comm = C;
			low_row = row_start;
                	high_row = row_end;
			for(index_type i = (index_type) row_start ; i <= row_end  ; i++)
			{
				for(int j = 1; j <= col ; j++)
				{
					A.add_element(i, j , init(i,j));
					if(init(i,j) != 0)
					{
						required_cols.push_back(j);
						if(j < row_start || j > row_end)
						{
							recv_index_buffer.push_back(j);
						}
					}			
				}		
			}
			allocate_grid();
			setup_communication();		
		}		
		
		void allocate(index_type row_num , index_type row_start ,  index_type row_end ,std::string path, MPI_Comm C = MPI_COMM_WORLD )
		{
			row_size = row_num;
			comm = C;	
			low_row = row_start;
                	high_row = row_end;
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
        				if(row >= row_start && row <= row_end )			
					{
						A.add_element(row,col,value);
						required_cols.push_back(col);
						if(col < row_start || col > row_end)
						{
							recv_index_buffer.push_back(col);
						}
					}
					
				}

			}
			file.close();
			allocate_grid();
			setup_communication();			
		}
		void allocate(index_type row_num , index_type row_start ,  index_type row_end , matrix::sparse_matrix<index_type , value_type> Tran , MPI_Comm C = MPI_COMM_WORLD )
		{
			row_size = row_num;
                        comm = C;
                        low_row = row_start;
                        high_row = row_end;
			for(auto i : Tran.row)
			{
				A.row.push_back(i);
			}
			for(auto i : Tran.col)
                        {
                                A.col.push_back(i);
				required_cols.push_back(i);
				if(i < row_start || i > row_end)
				{
					recv_index_buffer.push_back(i);
				}
                        }
			for(auto i : Tran.value)
                        {
                                A.value.push_back(i);
                        }

			allocate_grid();
                        setup_communication();

		}


	};

		
}

#endif
