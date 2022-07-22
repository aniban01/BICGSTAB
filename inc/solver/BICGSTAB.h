#include "matrix_calculations.h"
namespace solver
{
	template <typename index_type , typename value_type>
	
	class BICGSTAB
	{
		//Elements in the equation Ax = B 
		matrix_calculations::sparse_matrix_operations<index_type , value_type> A;
		matrix_calculations::vector<index_type , value_type> b;
		matrix_calculations::vector<index_type, value_type> x;
		
		//BICGSTAB variables
		double tolerance_level = 0.000001;
		


		value_type Matrix_initializer(index_type r , index_type c)
		{
			if(r == c)
			{
				return 2;
			}	
			else if(r == c-1 || c == r-1)
			{
				return 1;
			}
			else 
			{
				return 0;
			}
		}

		value_type Vector_constant_initializer(index_type r , value_type val = (value_type)2)
		{

			return A.row_sum(r) * val;
		}

		public:
		
		BICGSTAB(index_type r , index_type c , value_type val = (value_type)2) : A(r,c, &(Matrix_initializer)) , x(c,0) , b(c, val , &(Vector_constant_initializer)){}; 
		
		void display();
	
		
		
	};

}
