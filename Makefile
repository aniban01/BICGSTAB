

SOURCE = src/
OBJECT = obj/


#INC = -I inc/matrix  -I inc/program_utilization  -I inc/solver
INC = -Iinc/matrix  -Iinc/program_utilization  -Iinc/solver
FLAG =  -W -Wall -std=c++20
OPENMP = -fopenmp


LINEAR_CC = g++
PARALLEL_CC = mpicxx


COMMON_DEPENDENCIES = $(SOURCE)error_handling.h $(SOURCE)global_variables.h $(SOURCE)matrix_allocation.h

DEPENDENCIES_SERIAL = $(OBJECT)matrix_calculations.o $(OBJECT)BICGSTAB.o $(OBJECT)matrix_allocation.o $(OBJECT)initializers.o $(OBJECT)Main.o $(OBJECT)error_handling.o
DEPENDENCIES_PARALLEL = $(OBJECT)matrix_calculations_parallel.o $(OBJECT)BICGSTAB_parallel.o $(OBJECT)matrix_allocation.o $(OBJECT)initializers_parallel.o $(OBJECT)Main_parallel.o $(OBJECT)error_handling.o $(OBJECT)parallel_alg.o
SOURCE_LIST = $(wildcard $(SOURCE)*.cc)
OBJ_LIST = $(patsubst %.cc , $(OBJECT)%.o , $(SOURCE_LIST))
 

all : Final Final_parallel

Input : src/input.cc
	$(LINEAR_CC) -o $@  $^ $(FLAG) $(INC)

Final_parallel : $(DEPENDENCIES_PARALLEL)
	$(PARALLEL_CC) -o $@  $^ $(FLAG) $(OPENMP) $(INC)



$(OBJECT)Main_parallel.o : $(SOURCE)Main_parallel.cc
	$(PARALLEL_CC) -o $@ -c $< $(FLAG) $(OPENMP) $(INC)

$(OBJECT)BICGSTAB_parallel.o : $(SOURCE)BICGSTAB_parallel.cc
	$(PARALLEL_CC) -o $@ -c $< $(FLAG) $(OPENMP) $(INC)

$(OBJECT)parallel_alg.o : $(SOURCE)parallel_alg.cc
	$(PARALLEL_CC) -o $@ -c $< $(FLAG) $(OPENMP) $(INC)

$(OBJECT)matrix_calculations_parallel.o : $(SOURCE)matrix_calculations_parallel.cc
	$(LINEAR_CC) -o $@ -c $< $(FLAG) $(OPENMP) $(INC)

$(OBJECT)initializers_parallel.o : $(SOURCE)initializers_parallel.cc    
	$(LINEAR_CC) -o $@ -c $< $(FLAG) $(OPENMP) $(INC)



Final : $(DEPENDENCIES_SERIAL)
	$(LINEAR_CC) -o $@  $^ $(FLAG) $(OPENMP) $(INC)


$(OBJECT)matrix_allocation.o : $(SOURCE)matrix_allocation.cc    
	$(LINEAR_CC) -o $@ -c $< $(FLAG) $(OPENMP) $(INC)

$(OBJECT)initializers.o : $(SOURCE)initializers.cc    
	$(LINEAR_CC) -o $@ -c $< $(FLAG) $(OPENMP) $(INC)

$(OBJECT)error_handling.o : $(SOURCE)error_handling.cc    
	$(LINEAR_CC) -o $@ -c $< $(FLAG) $(OPENMP) $(INC)

$(OBJECT)matrix_calculations.o : $(SOURCE)matrix_calculations.cc    
	$(LINEAR_CC) -o $@ -c $< $(FLAG) $(OPENMP) $(INC)

$(OBJECT)BICGSTAB.o : $(SOURCE)BICGSTAB.cc 
	$(LINEAR_CC) -o $@ -c $< $(FLAG) $(OPENMP) $(INC)

$(OBJECT)Main.o : $(SOURCE)Main.cc 
	$(LINEAR_CC) -o $@ -c $< $(FLAG) $(OPENMP) $(INC)

run : Final_parallel
	mpirun --oversubscribe -n 6 Final_parallel

.PHONY : clean
clean : 
	rm -f Final $(OBJECT)*.o


