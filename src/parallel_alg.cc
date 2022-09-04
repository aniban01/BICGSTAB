#include "parallel_alg.h"

template <typename index_type>
void decomp_1d(index_type row_num , int size_row, int row_rank ,  index_type &s, index_type &e )
{
	index_type  nlocal_row , deficit ;
        nlocal_row = row_num / size_row;
        
        s      = row_rank * nlocal_row + 1;
        deficit = row_num % size_row;
        s      = s + ((row_rank < deficit) ? row_rank : deficit);
        
        if (row_rank < deficit) 
	{
		nlocal_row++;
        }
	e  = s + nlocal_row - 1;
        
	if (e > row_num || row_rank == size_row-1) 
	{
		e = row_num;
	}
}

template void decomp_1d<int>(int row_num , int size_row, int row_rank , int &s, int &e );
template void decomp_1d<long int> ( long int row_num ,  int size_row, int row_rank , long int &s, long int &e );



template <typename index_type>
void generate_vals_1d(  int& nbrbottom , int& nbrtop , index_type& top ,index_type&  bottom,  index_type row_num , MPI_Comm comm )
{ 
	int myid, nprocs;


        MPI_Comm_rank(comm, &myid);
        MPI_Comm_size(comm, &nprocs);
	
	if(myid == 0)
	{
		nbrtop = -2;
		nbrbottom = myid+1;
	}
	else if(myid == nprocs -1)
	{
		nbrtop = myid -1;
		nbrbottom = -1;
	}
	else
	{
		nbrtop = myid-1;
		nbrbottom = myid+1;
	}		
        decomp_1d(row_num , nprocs, myid, top , bottom );
}

template void generate_vals_1d<int> (  int& nbrbottom , int& nbrtop, int& top ,int&  bottom, int row_num, MPI_Comm comm );
template void generate_vals_1d<long int> (   int& nbrbottom , int& nbrtop ,  long int& top , long int&  bottom, long int row_num , MPI_Comm comm );


template <typename value_type>
MPI_Datatype MPI_Type(value_type A)
{
	char temp = typeid(A).name()[0];
	switch (temp) {
		case 'i' : return MPI_INT;
				break;
		case 'f' : return MPI_FLOAT;
				break;
		case 'd' : return MPI_DOUBLE;
				break;
		case 'l' : return MPI_LONG;	
				break;	
	}
	return MPI_INT;
}
template MPI_Datatype MPI_Type<int> (int A);
template MPI_Datatype MPI_Type<long int> (long int A);
template MPI_Datatype MPI_Type<float> (float A);
template MPI_Datatype MPI_Type<double> (double A);

