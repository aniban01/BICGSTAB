
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
//		std::cout << "--------------------------------------------------------------------------" << std::endl;
//		std::cout << "checking for index value" << std::endl; 
		auto index = return_element_index(r,c);
		if(index >= 0)
		{
			// replacing value 
			if(val != (value_type)0)
			{
//				std::cout << "For input (" << r << " , " << c << ") updating existing value at index " << index << " which represents element at (" << r << " , " << col[index] << ") to " << val << std::endl;
				value[index] = val;
			}
			else
			{
				//new value is 0
//				std::cout << "For input (" << r << " , " << c << ") deleting value at index " << index << " which represents element at (" << r << " , " << col[index] << ") to " << val << std::endl;

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
//				std::cout << "Delete complete" << std::endl;


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
//				std::cout<< "For input (" << r << " , " << c << ") adding rows to add value " << val << std::endl;
 
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
//				std::cout << "Row addition and value update successfull" << std::endl;	
			}
			else
			{
				auto index_lower = row[r-1];
	                        auto index_upper = row[r] -1 ;
				
//        	                std::cout<< "For input (" << r << " , " << c << ") adding elemenet to existing rows " << r << " with index_lower " << index_lower  << " index_upper " << index_upper << std::endl;
                	        if((index_upper - index_lower) < 0)    
                        	{
//                                	std::cout << "Adding element to empty row " << std::endl;
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
//                                	std::cout << "Addition complete" << std::endl;
			
					
                       		}
                        	else
                        	{
                          		if(c < col[index_lower])
					{
//						std::cout<< "Adding element to begining of the column" <<  std::endl;
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
//	                                        std::cout << "Addition complete at first element in row" << std::endl;

					}
					else if ( index_lower  == index_upper ||  c > col[index_upper])
					{
//						std::cout<< "Adding element to the end of the column" <<  std::endl;
						auto column_iterator = col.begin();
                                                auto val_iterator = value.begin();
						
//						std::cout << "iterators created" << std::endl;
                                                std::advance(val_iterator , index_upper + 1);
                                                std::advance(column_iterator , index_upper + 1);
						
//						std::cout << "iterators advanced by amount" <<  std::endl;
                                                col.insert(column_iterator , c);
                                                value.insert(val_iterator , val);
						
//						std::cout << "values added" << std::endl;
                                                while(r <= (index_type) row.size()-1)
                                                {
                                                        row[r] += 1;
                                                        r++;
                                                }
//                                               std::cout << "Addition complete at last element in row" << std::endl;


					}
					else
					{
//						std::cout<< "Adding element to the middle of the column" <<  std::endl;
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
//                                                std::cout << "Addition complete at last element in row" << std::endl;
						
			
					}
				}
			}				
		}
//	std::cout << "--------------------------------------------------------------------------" << std::endl;
	}

	template <typename index_type , typename value_type>			
	index_type sparse_matrix <index_type, value_type> :: return_element_index(index_type r , index_type c)
	{
//		std::cout << "--------------------------------------------------------------------------" << std::endl;

//		std::cout << "Entered return_element_index to find element (" << r << " , " << c << " ) " << std::endl;
		if(r < (index_type) 1 || c < (index_type) 1)
		{
			generate_error(11);
		}
		if( (index_type) row.size()-1 < r )
		{
//			std::cout << "Exiting return_element_index as element (" << r << " , " << c << " ) as row is not found "<< std::endl;
			return -3; 
		}
		else
		{
			auto index = row[r-1];
			auto max_index = row[r]-1 ;
//			std::cout << "Index : " << index << " max_index : " << max_index << std::endl;	
			if((max_index - index) < 0)	
			{
					
//				std::cout << "Exiting return_element_index as element (" << r << " , " << c << " ) no element in row " << std::endl;       

				return -2;
			}
			else
			{
				if(c < col[index] || c > col[max_index])
				{
//					std::cout << "Exiting return_element_index as element (" << r << " , " << c << " ) not found with column range between  "<< col[index] << " to  " << col[max_index] << std::endl;       

					return -1;
				}
				if(c == col[index])
				{
					return index;
				}
				else if(c == col[max_index])
				{
					return max_index;
				}
				auto temp = (index_type) ((max_index - index) / 2);
				while( max_index > index )
				{
					if(c == col[index + temp])
					{
//						std::cout << "Exiting return_element_index as element (" << r << " , " << c << " ) found in index "<< index + temp << " with value " << value[temp+index] << std::endl;

						return index + temp;
					}
					else if(c > col[index + temp])
					{
						index = index + temp;
					}
					else
					{
						max_index = index + temp;
					}
					temp = (index_type) ((max_index - index) / 2);

				}
//				std::cout << "Exiting return_element_index as element (" << r << " , " << c << " ) as element is not found "<< std::endl;
				return -1;
			}
		}
	}
	
	template class sparse_matrix <int , double>;
	template class sparse_matrix <int , float>;	
	template class sparse_matrix <long int , double>;
	template class sparse_matrix <long int , float>;
}


