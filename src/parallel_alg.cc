#include "parallel_alg.h"



template <typename index_type>
void decomp_2d(index_type row_num , index_type col_num , int size_row, int size_col , int row_rank , int col_rank, index_type &s, index_type &e , index_type &top , index_type &bottom )
{
	index_type nlocal_col , nlocal_row , deficit ;
        
        nlocal_col = col_num / size_col;
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
        
        top    = col_rank * nlocal_col+ 1;
        deficit = col_num % size_col;
        top    = top + ((col_rank < deficit) ? col_rank : deficit);
        
	if (col_rank < deficit) nlocal_col++;
        {
		bottom  = top + nlocal_col - 1;
        }
	if (bottom > col_num || col_rank == size_col-1) 
	{
		bottom = col_num;
        }
}

template void decomp_2d<int>(int row_num , int col_num, int size_row, int size_col , int row_rank , int col_rank, int &s, int &e , int &top , int &bottom );
template void decomp_2d<long int> ( long int row_num , long int col_num, int size_row, int size_col , int row_rank ,int col_rank, long int &s, long int &e , long int &top , long int &bottom );


template <typename index_type>
//void generate_vals( index_type* nbrleft , index_type* nbrright , index_type* nbrbottom , index_type* nbrtop , index_type* s , index_type* e ,index_type* top ,index_type*  bottom,  index_type col_num , index_type row_num , MPI_Comm comm = MPI_COMM_WORLD)
void generate_vals( int& nbrleft , int& nbrright , int& nbrbottom , int& nbrtop , index_type& s , index_type& e ,index_type& top ,index_type&  bottom,  index_type col_num , index_type row_num , MPI_Comm comm )
{ 
	int myid, nprocs;


        MPI_Comm_rank(MPI_COMM_WORLD, &myid);
        MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	
	//size_t nbrl{0} , nbrr {0}, nbrt {0}, nbrb {0};
	MPI_Comm Communicator_2d;
        
	int periodic[2] = {0, 0};
        int proc_grid[2] = {0,0};
        int reorder = 0;
        int rank_coord[2] = {0,0};
        /*
	index_type periodic[2] = {0, 0};
        index_type proc_grid[2] = {0,0};
        index_type reorder = 0;
        index_type rank_coord[2] = {0,0};
	*/

	MPI_Dims_create(nprocs, 2, proc_grid);

        MPI_Cart_create(comm, 2 , proc_grid , periodic , reorder, &Communicator_2d);
        MPI_Cart_shift(Communicator_2d , 0 , 1 , &nbrleft , &nbrright);
        MPI_Cart_shift(Communicator_2d , 1 , 1 , &nbrtop , &nbrbottom);
        //MPI_Cart_shift(Communicator_2d , 0 , 1 , &nbrl , &nbrr);
        //MPI_Cart_shift(Communicator_2d , 1 , 1 , &nbrt , &nbrb);
        MPI_Cart_coords(Communicator_2d , myid , 2 , rank_coord);
        decomp_2d(row_num , col_num, proc_grid[1] , proc_grid[0], rank_coord[1] , rank_coord[0],  s, e , top , bottom );
}

template void generate_vals<int> ( int& nbrleft , int& nbrright , int& nbrbottom , int& nbrtop , int& s , int& e ,int& top ,int&  bottom, int col_num , int row_num, MPI_Comm comm );
template void generate_vals<long int> (  int& nbrleft , int& nbrright , int& nbrbottom , int& nbrtop , long int& s , long int& e , long int& top , long int&  bottom, long int col_num , long int row_num , MPI_Comm comm );
