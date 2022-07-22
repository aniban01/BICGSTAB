#include <execution>
#include <vector>
#include <algorithm>
#include "error_handling.h"

void print_line()
{

	std::cout<<"-----------------------------------------------------------------------------------------------------"<<std::endl;

}
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
	
		void print_elements()
		{
			std::cout << "rows : " ;
	        	for ( auto a : row)
       			{
                		std::cout << a << " , ";
                	}
        
        		std::cout << std::endl << "columns : " ;
        		for ( auto a : col)
        		{
                		std::cout << a << " , ";
                
        		}
        		std::cout << std::endl << "values : " ;
        		for ( auto a : value)
        		{
                		std::cout << a << " , ";
               
        		}
			std::cout<<std::endl;
		}	
		
		index_type row_size()
		{
			return row.size() - 1;
		}
	
		index_type col_size()
		{
			return *std::max_element(std::execution::par ,  col.begin() , col.end()  );
		
		}
		void print_matrix(index_type r = -1  , index_type c = -1)
		{
			if(r < 0 || c < 0)
			{
				r = row.size() - 1;
				c = *std::max_element(std::execution::par ,  col.begin() , col.end()  );
				
				std::cout<< "Printing the matrix with rows " << r << " and columns " << c << std::endl;
			}	
			
			for( int i = 1 ; i <= r ; i++)
        		{
                		for(int j = 1; j <= c ; j++)
                		{
                        		auto index =    return_element_index(i , j );
                        		if(index > -1)
                        		{
                                		std::cout << "\t" << value[index];  
                        		}
                        		else
                        		{
                                		std::cout << "\t" << 0;       
                        		}
                		}
                		std::cout<<std::endl;

        		}


		}	
			
		void add_element(index_type r, index_type c , value_type val)		
		{
				
				if(r < 1 || c < 1)
				{
					generate_error(10);
				}
				else if((index_type) row.size() == (index_type)0)
				{
					// dealing with empty matrix
					row.push_back(0);
					
					while((index_type)row.size() < r)
					{
						row.push_back(0);
					}
					col.push_back(c);
					value.push_back(val);
					row.push_back(1);
				}
				else
				{
					if((index_type)row.size() < r+1)
					{
					
						//Add extra matrix rows
						index_type end_row_val = row.back(); 
					

						while((index_type)row.size() < r)
                                        	{
                                                	row.push_back(end_row_val);
                                        	}
                               			col.push_back(c);
						value.push_back(val);
						row.push_back(end_row_val + 1 );
	
					}
					else
					{

						// Add element to existing row
						typename std::vector<index_type>::iterator row_pointer= row.begin() + r ;
						typename std::vector<index_type>::iterator column = col.begin() + row[r-1]; 
                                        	typename std::vector<value_type>::iterator v = value.begin() + row[r-1];			
						auto diff = row[r] - row[r-1]; 
						if(diff == 0 )
						{	
							// Adding elements to empty row
							col.insert(column , c);
	                                                value.insert(v , val);
						}
						else
						{
							index_type counter = 0;
							// iterating through column values to find optimal location of column 	
							while(*column < c && counter < diff)
							{
								++column;
								++v;
								++counter;
							}
							if(*column == c)
							{
								// Update element if it already exists
								*v = val;           
							}	
							else
							{	

								// Add new non empty element
								col.insert(column , c);
                                                        	value.insert(v , val);
							}
						}

						while(row_pointer < row.end())
						{
							++*row_pointer;
							++row_pointer;
						}
					}	
				}

		}

			
		index_type return_element_index(index_type r , index_type c)
		{

				if((index_type)row.size() < r-1)
				{
					generate_error(11);
				} 
				else
				{
					if(row[r] - row[r-1] == 0)
					{
						return -1;
					}
					index_type index = row[r-1];
					while(col[index] < c && index < row[r]-1)
					{
						++index;
					}
					if(col[index] == c)
					{
					
						return index;  
					}
					else
					{
						return -1;
					}
					

				}	
			

		}
	
			
	}; 


}


