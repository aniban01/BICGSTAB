#include "matrix_calculations_parallel.h"

namespace matrix_calculations_parallel
{


		
	template class vector <int , double>;
        template class vector <int, float >;
        template class vector <long int , double>;
        template class vector <long int , float>;

	// Functions for class vector
	template <typename index_type , typename value_type>
	value_type vector<index_type , value_type> :: norm()
	{
 		
	       	value_type local_sum = (value_type) 0;
        	value_type global_sum;
		omp_set_num_threads(thread_num);
		#pragma omp parallel for simd reduction(+:local_sum) 
		for (index_type i  = 0 ; i < size ; i++)
		{
			local_sum += A[i]* A[i];
		}
		MPI_Datatype MPI_data_type  = MPI_Type(local_sum);					
		MPI_Allreduce(&local_sum,&global_sum,1,MPI_data_type,MPI_SUM,MPI_COMM_WORLD);	
		return std::sqrt(global_sum);
	}


	template <typename index_type , typename value_type>
        value_type vector<index_type , value_type> :: dot_product(matrix_calculations_parallel::vector <index_type , value_type> B )
        {
	       value_type sum = (value_type)0 ;
                if(size != B.return_size())
		{
			generate_error(22);
		}
		omp_set_num_threads(thread_num);
                #pragma omp parallel for simd reduction(+:sum) 
                for(index_type a = 0 ; a < size ; a++)
                {
                        sum += A[a] * B.value(a+lower);
                }
		value_type global_sum;
		MPI_Datatype MPI_data_type  = MPI_Type(sum);     
                MPI_Allreduce(&sum,&global_sum,1,MPI_data_type,MPI_SUM,MPI_COMM_WORLD);
                return global_sum;
        }

	template <typename index_type , typename value_type>
        value_type vector<index_type , value_type> :: local_dot_product(matrix_calculations_parallel::vector <index_type , value_type> B )
        {
	       value_type sum = (value_type)0 ;
                if(size != B.return_size())
		{
			generate_error(22);
		}
		omp_set_num_threads(thread_num);
                #pragma omp parallel for simd reduction(+:sum) 
                for(index_type a = 0 ; a < size ; a++)
                {
                        sum += A[a] * B.value(a+lower);
                }
                return sum;
        }

	template <typename index_type , typename value_type>
	void vector<index_type , value_type> :: display()
	{
		int myid, nprocs;
                MPI_Comm_rank(MPI_COMM_WORLD, &myid);
                MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
                MPI_Barrier(MPI_COMM_WORLD);
		for( auto k=0; k<nprocs; k++){
                   	if( k == myid )
			{
				for( auto i = 0 ; i < size; i++)
                                {
					std::cout << " " << A[i];	
				}
			}
			
			fflush(stdout);
                        sleep(1);
                        MPI_Barrier(MPI_COMM_WORLD);	
		}
		std::cout<< std::endl;
		
	}
	

	template <typename index_type , typename value_type>

	vector <index_type , value_type> vector<index_type , value_type>::operator + (value_type num)
        {
                vector<index_type, value_type> B{size , lower}; 
               	omp_set_num_threads(thread_num);
		#pragma omp parallel for 
		for( auto i = (index_type) 0 ; i < size ; i ++)
                {
                        B.update_value(i+lower  , A[i] + num );
                }
                return B;
        }
        template <typename index_type , typename value_type>
	vector <index_type , value_type> vector<index_type , value_type>::operator * (value_type num)
        {
                vector<index_type, value_type> B{size , lower}; 
       		omp_set_num_threads(thread_num);	
		#pragma omp parallel for  
		for( auto i = (index_type) 0 ; i < size ; i ++)
                {
                        B.update_value(i + lower  , A[i] * num );
                }
                return B;
        }
	template <typename index_type , typename value_type>
        vector <index_type , value_type> vector<index_type , value_type>::operator / (value_type num)
        {
                vector<index_type, value_type> B{size , lower}; 
        	omp_set_num_threads(thread_num);	
		#pragma omp parallel for  
	       for( auto i = (index_type) 0 ; i < size ; i ++)
                {
                        B.update_value(i + lower , A[i] / num );
                }
                return B;
        }
	template <typename index_type , typename value_type>
        vector <index_type , value_type> vector<index_type , value_type>::operator - (value_type num)
        {
                vector<index_type, value_type> B{size , lower};
        	
		omp_set_num_threads(thread_num);	
		#pragma omp parallel for  
	       for( auto i = (index_type) 0 ; i < size ; i ++)
                {
                        B.update_value(i + lower , A[i] - num );
                }
                return B;
        }
	
	template <typename index_type , typename value_type>
	vector <index_type , value_type> vector<index_type , value_type>::operator + (vector<index_type , value_type > num)
        {
                
		vector<index_type, value_type> B{size , lower};
        	omp_set_num_threads(thread_num);	
		#pragma omp parallel for  
	       for( auto i = (index_type) 0 ; i < size ; i ++)
                {
                        B.update_value(i + lower , A[i] + num.value(i+ lower) );
                }
                return B;
        }
        template <typename index_type , typename value_type>
	vector <index_type , value_type> vector<index_type , value_type>::operator * (vector<index_type , value_type > num)
        {

		vector<index_type, value_type> B{size , lower};
        	omp_set_num_threads(thread_num);	
		#pragma omp parallel for  
	       for( auto i = (index_type) 0 ; i < size ; i ++)
                {
                        B.update_value(i+ lower  , A[i] * num.value(i+ lower) );
                }
                return B;
        }

        template <typename index_type , typename value_type>
	vector <index_type , value_type> vector<index_type , value_type>::operator / (vector<index_type , value_type > num)
        {

		vector<index_type, value_type> B{size , lower};
        	omp_set_num_threads(thread_num);	
		#pragma omp parallel for  
	       for( auto i = (index_type) 0 ; i < size ; i ++)
                {
                        B.update_value(i + lower , A[i] / num.value(i+ lower) );
                }
                return B;
        }

        template <typename index_type , typename value_type>
	vector <index_type , value_type> vector<index_type , value_type>::operator - (vector<index_type , value_type >  num)
        {

		vector<index_type, value_type> B{size , lower};
        	omp_set_num_threads(thread_num);	
		#pragma omp parallel for  
	       for( auto i = (index_type) 0 ; i < size ; i ++)
                {
                        B.update_value(i+ lower  , A[i] - num.value(i+ lower) );
                }
                return B;
        }
	

	
	template class sparse_matrix_operations <int , double>;
        template class sparse_matrix_operations <int, float >;
        template class sparse_matrix_operations <long int , double>;
        template class sparse_matrix_operations <long int , float>;




// Function definitions for class sparse_matrix_operations
	template <typename index_type , typename value_type>
	value_type sparse_matrix_operations<index_type , value_type> :: norm()
	{
        	value_type sum_mat = 0;
		for (value_type element : A.value)
		{
			sum_mat += element * element;
		}
		return std::sqrt(sum_mat);
	}


	template <typename index_type , typename value_type>
	matrix_calculations_parallel::vector<index_type , value_type>  sparse_matrix_operations<index_type , value_type> :: SPMM(matrix_calculations_parallel::vector <index_type , value_type> B ) 
	{
		matrix_calculations_parallel::vector <index_type , value_type> product(B.return_size() , B.return_lower());
		index_type row_index = low_row , col_index = 0;
		
		if(recv_details.size() == 0 && send_details.size() == 0)
                {
			
			value_type temp_sum = 0;
         		
			for(;col_index < (index_type)A.col.size() && row_index < (index_type)A.row.size();)
                                {
                                        
	
                                        temp_sum += A.value[col_index] * B.value(A.col[col_index]);
                                	col_index++;
					if(A.row[row_index] <= col_index)
                                        {
                                                product.update_value(row_index, temp_sum);
						while(row_index < (index_type)A.row.size() && A.row[row_index] == A.row[row_index+1] )
                                                {
                                                        row_index++;
                                                        product.update_value(row_index,0);
						}
                                                row_index++;
						temp_sum = 0;
                                        }

				}
			
			
                }
		else
		{
			std::map <index_type , std::vector<value_type>> matrix_mult_results;
			std::map <index_type , std::vector<index_type>> matrix_out_bound; 
			
			int myid , nprocs;
                	MPI_Comm_rank(comm, &myid);
                	MPI_Comm_size(comm, &nprocs);
		

		

			std::vector<value_type> send_buffer ,  recieve_buffer;
			for(auto i : send_index_buffer)
			{
				send_buffer.push_back(B.value(i));
			} 

		

			recieve_buffer.resize(num_element_recv);		
			MPI_Datatype MPI_data_type  = MPI_Type(send_buffer[0]);
		
			MPI_Win win;
               	 	MPI_Win_create(&send_buffer[0], sizeof(send_buffer[0])*send_buffer.size(), sizeof(send_buffer[0]), MPI_INFO_NULL, MPI_COMM_WORLD, &win);
                
			MPI_Win_fence(MPI_MODE_NOPRECEDE , win);
				for(auto i : recv_details)
				{
                         		MPI_Get(&recieve_buffer[i.start_index], i.num_element  , MPI_data_type , i.rank , i.dest_index , i.dest_num_element , MPI_data_type , win);
                		}
				omp_set_num_threads(thread_num);	
				for(;col_index < (index_type)A.col.size() && row_index < (index_type)A.row.size(); col_index++)
				{
					if(A.row[row_index] <= col_index)
					{
						row_index++;
					} 
					if(A.col[col_index] < low_row || A.col[col_index] > high_row)
					{
						matrix_out_bound[row_index].push_back(col_index);
					}
					else
					{
						matrix_mult_results[row_index].push_back(A.value[col_index] * B.value(A.col[col_index]));	
					}
				}
			
			
			MPI_Win_fence(MPI_MODE_NOSUCCEED , win);
			MPI_Win_free(&win);
			
			for(auto i = low_row ; i <= high_row ; i++)
			{	
				omp_set_num_threads(thread_num);
				for(auto k : matrix_out_bound[i])
				{ 
					auto temp_index = std::distance(recv_index_buffer.begin() , std::find(recv_index_buffer.begin(), recv_index_buffer.end(), A.col[k]));
					matrix_mult_results[i].push_back(recieve_buffer[temp_index] * A.value[k]);
				}
				value_type row_sum= 0;
					
                                #pragma omp parallel for reduction(+:row_sum) 
				for(auto k : matrix_mult_results[i])
                        	{
                        		row_sum +=  k;
				}
				product.update_value(i, row_sum);
			} 
		}
		return product;
	}

	template <typename index_type , typename value_type>
	void  sparse_matrix_operations<index_type , value_type> :: allocate_grid() 
	{
		int myid , nprocs;
		MPI_Comm_rank(comm, &myid);
 	        MPI_Comm_size(comm, &nprocs);
		int split_elements[nprocs];
			
		if(recv_index_buffer.empty())
		{
			for(auto i = 0 ; i < nprocs ; i++)
			{
				split_elements[i] = 0 ;
			}
		}
		else
		{
			std::sort(recv_index_buffer.begin() , recv_index_buffer.end());
			recv_index_buffer.erase(std::unique(recv_index_buffer.begin(), recv_index_buffer.end() ), recv_index_buffer.end());
			std::map <int , std::vector<int>> communicator_col_split;	
			
			int myid , nprocs;
			MPI_Comm_rank(comm, &myid);
 	               	MPI_Comm_size(comm, &nprocs);
			
			index_type iterate = 0;
			if(recv_index_buffer[iterate] < low_row)
			{
				for(int index = 0 ; index < myid && iterate < (index_type)recv_index_buffer.size() ; index++)
				{
					index_type low , high;
					decomp_1d(row_size, nprocs, index ,   low ,  high );

					while(iterate < (index_type) recv_index_buffer.size() && recv_index_buffer[iterate] >= low &&  recv_index_buffer[iterate] <= high)
					{
						communicator_col_split[index].push_back(recv_index_buffer[iterate]);
						iterate++; 						
					}	
				}
			}
			if(iterate < (index_type) recv_index_buffer.size() &&  recv_index_buffer[iterate] > high_row )
			{
				for(int index = myid+1 ; index < nprocs && iterate < (index_type) recv_index_buffer.size() ; index++)
				{
					index_type low , high;
					decomp_1d(row_size, nprocs, index ,  low , high );
                                        
					while(iterate < (index_type) recv_index_buffer.size() && recv_index_buffer[iterate] >= low &&  recv_index_buffer[iterate] <= high)
					{
						communicator_col_split[index].push_back(recv_index_buffer[iterate]);
						iterate++; 						
					}	
				}
			}

			num_element_recv = 0;
			for(auto i = (index_type) 0 ; i < nprocs ; i++)
                        {
				if(communicator_col_split[i].empty())
                       		{
                         		split_elements[i] = 0;
                        	}
                       		else
                       		{
                      			split_elements[i] = (int)communicator_col_split[i].size();
                        		
					communicator_info new_element;
                                	new_element.rank = i;
                                	new_element.num_element = split_elements[i];
                                	new_element.start_index = num_element_recv;
					num_element_recv += split_elements[i];
                                	recv_details.push_back(new_element);
		
				}
			}
		
	  	     	sleep(1);
                        MPI_Barrier(comm);
		}	
		int other_proc_element[nprocs] {};
		MPI_Alltoall(split_elements, 1, MPI_INT,other_proc_element , 1 , MPI_INT , comm);
		num_element_send = 0;
		for(auto i = 0 ; i < nprocs; i++)
		{
			if(other_proc_element[i] > 0)
			{
				communicator_info new_element;
				new_element.rank = i;
				new_element.num_element = other_proc_element[i];
				new_element.start_index = num_element_send; 
				num_element_send += other_proc_element[i];
				send_details.push_back(new_element);
			} 
		}
	}	
	
	template <typename index_type , typename value_type>
	void sparse_matrix_operations<index_type , value_type> :: setup_communication()
	{
		if(recv_details.size() == 0 && send_details.size() == 0)
		{
			return;
		}
		int myid , nprocs;
                MPI_Comm_rank(comm, &myid);
                MPI_Comm_size(comm, &nprocs);
		int send_counter = 0;	
		send_index_buffer.resize(num_element_send);	
		for(auto i = 0; i < nprocs ; i++)
		{
			if(i == myid)
			{
				for(auto k = 0 ; k < (int)recv_details.size() ; k++)
				{
					std::vector<int> temp;
					temp.resize(2);
					MPI_Sendrecv(&recv_index_buffer[recv_details[k].start_index], recv_details[k].num_element, MPI_INT, recv_details[k].rank , 10+recv_details[k].rank, &temp[0] , 2, MPI_INT, recv_details[k].rank , 100+i, comm, MPI_STATUS_IGNORE);
					recv_details[k].dest_index = temp[0];
					recv_details[k].dest_num_element = temp[1];
				}
			
			}
			else
			{
				if(send_counter < (int)send_details.size() &&  send_details[send_counter].rank == i)
				{
					std::vector<int> temp;
					temp.push_back(send_details[send_counter].start_index);
					temp.push_back(num_element_send);

					MPI_Sendrecv(&temp[0] , 2, MPI_INT, send_details[send_counter].rank  , 100+i,&send_index_buffer[send_details[send_counter].start_index], send_details[send_counter].num_element, MPI_INT, i , 10+myid, comm,  MPI_STATUS_IGNORE);		
					send_counter++;
				}		
				
			}
			MPI_Barrier(comm);
		} 		
	}

}




