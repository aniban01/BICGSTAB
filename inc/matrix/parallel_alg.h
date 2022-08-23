#ifndef parallel_2022
#define parallel_2022



#include <mpi.h>

template <typename index_type>
void decomp_2d(index_type row_num , index_type col_num , int size_row, int size_col , int row_rank , int col_rank, index_type &s, index_type &e , index_type &top , index_type &bottom );

template <typename index_type>
void generate_vals( int& nbrleft , int& nbrright , int& nbrbottom , int& nbrtop , index_type& s , index_type& e ,index_type& top ,index_type&  bottom,  index_type col_num , index_type row_num , MPI_Comm comm = MPI_COMM_WORLD);



#endif
