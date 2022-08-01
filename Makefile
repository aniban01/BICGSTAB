

SOURCE = src/
OBJECT = obj/


#INC = -I inc/matrix  -I inc/program_utilization  -I inc/solver
INC = -Iinc/matrix  -Iinc/program_utilization  -Iinc/solver
FLAG =  -W -Wall -std=c++20
OPENMP = -fopenmp





COMMON_DEPENDENCIES = $(SOURCE)error_handling.h $(SOURCE)global_variables.h $(SOURCE)matrix_allocation.h

DEPENDENCIES = $(OBJECT)matrix_calculations.o $(OBJECT)BICGSTAB.o $(OBJECT)matrix_allocation.o $(OBJECT)initializers.o $(OBJECT)Main.o $(OBJECT)error_handling.o
SOURCE_LIST = $(wildcard $(SOURCE)*.cc)
OBJ_LIST = $(patsubst %.cc , $(OBJECT)%.o , $(SOURCE_LIST))
 

all : Final


Final : $(DEPENDENCIES)
	g++ -o $@  $^ $(FLAG) $(OPENMP) $(INC)



$(OBJECT)matrix_allocation.o : $(SOURCE)matrix_allocation.cc    
	g++ -o $@ -c $< $(FLAG) $(OPENMP) $(INC)

$(OBJECT)initializers.o : $(SOURCE)initializers.cc    
	g++ -o $@ -c $< $(FLAG) $(OPENMP) $(INC)

$(OBJECT)error_handling.o : $(SOURCE)error_handling.cc    
	g++ -o $@ -c $< $(FLAG) $(OPENMP) $(INC)



$(OBJECT)matrix_calculations.o : $(SOURCE)matrix_calculations.cc    
	g++ -o $@ -c $< $(FLAG) $(OPENMP) $(INC)

$(OBJECT)BICGSTAB.o : $(SOURCE)BICGSTAB.cc 
	g++ -o $@ -c $< $(FLAG) $(OPENMP) $(INC)

$(OBJECT)Main.o : $(SOURCE)Main.cc 
	g++ -o $@ -c $< $(FLAG) $(OPENMP) $(INC)


.PHONY : clean
clean : 
	rm -f Final $(OBJECT)*.o


