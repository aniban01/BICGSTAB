#ifndef BICGSTAB_2022
#define BICGSTAB_2022


#include "matrix_calculations.h"
#include "initializers.h"

namespace solver
{
	template <typename index_type , typename value_type>
	
	class BICGSTAB
	{
		//Elements in the equation Ax = b 
		matrix_calculations::sparse_matrix_operations<index_type , value_type> A;
		matrix_calculations::vector<index_type, value_type> x;
		matrix_calculations::vector<index_type , value_type> b;
		
		//BICGSTAB variables
		double tolerance_level = 0.000001;

		public:
		
		BICGSTAB(index_type r , index_type c ,  value_type val_1 = (value_type)0 ,  value_type val_2 = (value_type)2) : A(r,c) , x(c,val_1) , b(c, val_2){};

		BICGSTAB(index_type r , index_type c ,  std::function<value_type (index_type , index_type)> init , value_type val_1 = (value_type)0 ,  value_type val_2 = (value_type)2) : A(r,c, init) , x(c,val_1) , b(c, val_2){}; 
		
		BICGSTAB(index_type r , index_type c ,  std::function<value_type (index_type , index_type)> init , std::function<value_type (index_type ,  std::vector<value_type>)> init_v , std::vector<value_type> init_v_values , value_type val_1 = (value_type)0  ) : A(r,c, init) , x(c,val_1) , b(c, init_v , init_v_values){}; 
	
		BICGSTAB( index_type c ,  std::string path , value_type val_1 = (value_type)0 ,  value_type val_2 = (value_type)2) : A(path) , x(c,val_1) , b(c, val_2){};
		
		 BICGSTAB(index_type c ,  std::string path , std::function<value_type (index_type ,  std::vector<value_type>)> init_v , std::vector<value_type> init_v_values , value_type val_1 = (value_type)0  ) : A(path) , x(c,val_1) , b(c, init_v , init_v_values){};


		value_type solve( value_type tolerance , unsigned long int max_sim);
		void display();
	
		
		
	};

}

#endif
