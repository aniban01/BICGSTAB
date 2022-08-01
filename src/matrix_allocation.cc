
#include "matrix_allocation.h"

namespace matrix
{

	template <typename index_type , typename value_type>

	void sparse_matrix<index_type, value_type> ::print_elements()
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
	

	template <typename index_type , typename value_type>
	void sparse_matrix <index_type, value_type> :: print_matrix(index_type r  , index_type c )
	{
			if(r < 0 || c < 0)
			{
				r = row.size() - 1;
				c = *std::max_element(std::execution::par ,  col.begin() , col.end()  );
				
				std::cout<< "Printing the matrix with rows " << r << " and columns " << c << std::endl;
			}	
			
			for( index_type i = 1 ; i <= r ; i++)
        		{
                		for(index_type j = 1; j <= c ; j++)
                		{
                        		auto index =    return_element_index(i , j );
                        		if(index >= 0)
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
			
	
	template <typename index_type , typename value_type>
	void sparse_matrix <index_type, value_type> :: add_element(index_type r, index_type c , value_type val)		
	{
					
				if(r < 1 || c < 1)
				{
					generate_error(10);
				}
				else if(val == (index_type)0)
				{
					return;
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

	template <typename index_type , typename value_type>			
	index_type sparse_matrix <index_type, value_type> :: return_element_index(index_type r , index_type c)
	{

				if((index_type)row.size() < r-1)
				{
					generate_error(11);
					return 0;
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
	
	template class sparse_matrix <int , double>;
	template class sparse_matrix <int , float>;	
	template class sparse_matrix <long unsigned int , double>;
	template class sparse_matrix <long unsigned int , float>;
}


