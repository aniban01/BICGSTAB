#ifndef parallel_2022
#define parallel_2022



#include <mpi.h>
#include <typeinfo>


template <typename index_type>
void generate_vals_1d(  int& nbrbottom , int& nbrtop , index_type& top ,index_type&  bottom,  index_type row_num , MPI_Comm comm );

template <typename index_type>
void decomp_1d(index_type row_num , int size_row, int row_rank ,  index_type &s, index_type &e );

template <typename value_type>
MPI_Datatype MPI_Type(value_type A);

#endif
