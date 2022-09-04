
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
		auto index = return_element_index(r,c);
		if(index >= 0)
		{
			if(val != (value_type)0)
			{
				value[index] = val;
			}
			else
			{
				auto val_begin = value.begin();
				auto column_begin = col.begin();
				
				std::advance(val_begin , index);
				std::advance(column_begin , index);
				value.erase(val_begin);
				col.erase(column_begin);
				
				while(r <= (index_type)row.size()-1)
				{
					row[r] -= 1;
					r++;
				}

			}	
		}	
		else
		{
			

			if( val == 0)
			{
				return;
			}
			if(index == (index_type)-3)
			{
				//row does not exist
 
				if((index_type)row.size() == 0)
				{
					row.push_back(0); 
				}
				auto temp_row_val = row[row.size() -1] ; 
				while((index_type)row.size() - 1 != r)
				{
					row.push_back(temp_row_val);
				}			
				row[row.size() -1] += 1;
				col.push_back(c);
				value.push_back(val);	
			}
			else
			{
				auto index_lower = row[r-1];
	                        auto index_upper = row[r] -1 ;
				
                	        if((index_upper - index_lower) < 0)    
                        	{
					auto column_iterator = col.begin();
					auto val_iterator = value.begin();
					std::advance(val_iterator , row[index_lower]);
                	                std::advance(column_iterator , row[index_lower]);
	 				
					col.insert(column_iterator , c);
					value.insert(val_iterator , val);
					
					while(r <= (index_type) row.size()-1)
	                                {
        	                                row[r] += 1;
                	                        r++;
                        	        }
			
					
                       		}
                        	else
                        	{
                          		if(c < col[index_lower])
					{
						auto column_iterator = col.begin();
	                                        auto val_iterator = value.begin();
        	                                std::advance(val_iterator , index_lower + 1);
                	                        std::advance(column_iterator , index_lower + 1);
	
						col.insert(column_iterator , c);
                                        	value.insert(val_iterator , val);

                                        	while(r <= (index_type) row.size()-1)
                                	        {
                        	                        row[r] += 1;
                	                                r++;
        	                                }

					}
					else if ( index_lower  == index_upper ||  c > col[index_upper])
					{
						auto column_iterator = col.begin();
                                                auto val_iterator = value.begin();
						
                                                std::advance(val_iterator , index_upper + 1);
                                                std::advance(column_iterator , index_upper + 1);
						
                                                col.insert(column_iterator , c);
                                                value.insert(val_iterator , val);
						
                                                while(r <= (index_type) row.size()-1)
                                                {
                                                        row[r] += 1;
                                                        r++;
                                                }


					}
					else
					{
						auto temp = index_lower;
						while(col[temp] > c && temp <= index_upper)
						{
							temp++;
						}
						auto column_iterator = col.begin();
                                                auto val_iterator = value.begin();
                                                std::advance(val_iterator , index_lower + temp);
                                                std::advance(column_iterator , index_lower + temp );

                                                col.insert(column_iterator , c);
                                                value.insert(val_iterator , val);

						
                                                while(r <= (index_type) row.size()-1)
                                                {
                                                        row[r] += 1;
                                                        r++;
                                                }
						
			
					}
				}
			}				
		}
	}

	template <typename index_type , typename value_type>			
	index_type sparse_matrix <index_type, value_type> :: return_element_index(index_type r , index_type c)
	{
		if(r < (index_type) 1 || c < (index_type) 1)
		{
			generate_error(11);
		}
		if( (index_type) row.size()-1 < r )
		{
			return -3; 
		}
		else
		{
			auto index = row[r-1];
			auto max_index = row[r]-1 ;
			if((max_index - index) < 0)	
			{
					
				return -2;
			}
			else
			{
				if(c < col[index] || c > col[max_index])
				{
					return -1;
				}
				if(c == col[index])
				{
					if((index_type)value.size() <= index)
					{
						std::cout << "index element (" << r << " , " << c << " greater than size of value vector " << value.size() << std::endl;       	
					}
					return index;
				}
				else if(c == col[max_index])
				{
					 if((index_type)value.size() <= max_index)
                                        {
						std::cout << "max_index index for " << r << " , " << c << " greater than size of vector " << value.size() <<  std::endl;       
					}
					return max_index;
				}
				for(auto temp_iterator = index ; temp_iterator <= max_index ; temp_iterator++)
				{
					if(col[temp_iterator] == c)
					{
						return temp_iterator;
					}
				}
				return -1;
			}
		}
	}
	
	template class sparse_matrix <int , double>;
	template class sparse_matrix <int , float>;	
	template class sparse_matrix <long int , double>;
	template class sparse_matrix <long int , float>;
}


