

SOURCE = src/
OBJECT = obj/
TEST_DIR = test_case/code/
TEST_OBJ = test_case/object/

INC = -Iinc/matrix  -Iinc/program_utilization  -Iinc/solver
FLAG =  -W -Wall -std=c++20
OPENMP = -fopenmp


LINEAR_CC = g++
PARALLEL_CC = mpicxx


COMMON_DEPENDENCIES = $(SOURCE)error_handling.h $(SOURCE)global_variables.h $(SOURCE)matrix_allocation.h

DEPENDENCIES_SERIAL = $(OBJECT)matrix_calculations.o $(OBJECT)BICGSTAB.o $(OBJECT)matrix_allocation.o $(OBJECT)initializers.o $(OBJECT)Main.o $(OBJECT)error_handling.o
DEPENDENCIES_PARALLEL = $(OBJECT)matrix_calculations_parallel.o $(OBJECT)BICGSTAB_parallel.o $(OBJECT)matrix_allocation.o $(OBJECT)initializers_parallel.o $(OBJECT)Main_parallel.o $(OBJECT)error_handling.o $(OBJECT)parallel_alg.o
 

USE_SERIAL_DEP = $(OBJECT)matrix_calculations.o $(OBJECT)BICGSTAB.o $(OBJECT)matrix_allocation.o $(OBJECT)initializers.o  $(OBJECT)error_handling.o
USE_PARALLEL_DEP = $(OBJECT)matrix_calculations_parallel.o $(OBJECT)BICGSTAB_parallel.o $(OBJECT)matrix_allocation.o $(OBJECT)initializers_parallel.o  $(OBJECT)error_handling.o $(OBJECT)parallel_alg.o

TEST = vector_linear vector_parallel matrix_linear matrix_parallel Solver_linear Solver_parallel 

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
	$(PARALLEL_CC) -o $@ -c $< $(FLAG) $(OPENMP) $(INC)

$(OBJECT)initializers_parallel.o : $(SOURCE)initializers_parallel.cc    
	$(LINEAR_CC) -o $@ -c $< $(FLAG) $(OPENMP) $(INC)



Final : $(DEPENDENCIES_SERIAL)
	$(LINEAR_CC) -o $@  $^ $(FLAG) $(OPENMP) $(INC)


$(OBJECT)matrix_allocation.o : $(SOURCE)matrix_allocation.cc    
	$(LINEAR_CC) -o $@ -c $< $(FLAG) -O3  $(INC) 

$(OBJECT)initializers.o : $(SOURCE)initializers.cc    
	$(LINEAR_CC) -o $@ -c $< $(FLAG) -O3  $(INC)

$(OBJECT)error_handling.o : $(SOURCE)error_handling.cc    
	$(LINEAR_CC) -o $@ -c $< $(FLAG)  -O3 $(INC)

$(OBJECT)matrix_calculations.o : $(SOURCE)matrix_calculations.cc    
	$(LINEAR_CC) -o $@ -c $< $(FLAG) -O3  $(INC)

$(OBJECT)BICGSTAB.o : $(SOURCE)BICGSTAB.cc 
	$(LINEAR_CC) -o $@ -c $< $(FLAG)  -O3 $(INC)

$(OBJECT)Main.o : $(SOURCE)Main.cc 
	$(LINEAR_CC) -o $@ -c $< $(FLAG)  -O3 $(INC)

run : Final_parallel
	mpirun --oversubscribe -n 4 Final_parallel


test: $(TEST)
	./vector_linear > test_case/output_dir/vector_linear_8.txt 
	mpirun --oversubscribe -n 2 vector_parallel > test_case/output_dir/vector_parallel_8_2.txt 
	mpirun --oversubscribe -n 4 vector_parallel > test_case/output_dir/vector_parallel_8_4.txt 
	mpirun --oversubscribe -n 6 vector_parallel > test_case/output_dir/vector_parallel_8_6.txt 
	mpirun --oversubscribe -n 8 vector_parallel > test_case/output_dir/vector_parallel_8_8.txt 
	./matrix_linear > test_case/output_dir/matrix_linear_8.txt
	mpirun --oversubscribe -n 2 matrix_parallel > test_case/output_dir/matrix_parallel_8_2.txt 
	mpirun --oversubscribe -n 4 matrix_parallel > test_case/output_dir/matrix_parallel_8_4.txt 
	mpirun --oversubscribe -n 6 matrix_parallel > test_case/output_dir/matrix_parallel_8_6.txt 
	mpirun --oversubscribe -n 8 matrix_parallel > test_case/output_dir/matrix_parallel_8_8.txt 
	
	./Solver_linear > test_case/output_dir/solver_linear_8.txt 
	mpirun --oversubscribe -n 2 Solver_parallel > test_case/output_dir/solver_parallel_8_2.txt 
	mpirun --oversubscribe -n 4 Solver_parallel > test_case/output_dir/solver_parallel_8_4.txt 
	mpirun --oversubscribe -n 6 Solver_parallel > test_case/output_dir/solver_parallel_8_6.txt 
	mpirun --oversubscribe -n 8 Solver_parallel > test_case/output_dir/solver_parallel_8_8.txt 



vector_linear: $(TEST_OBJ)vector_linear.o $(USE_SERIAL_DEP)
	$(LINEAR_CC) -o $@  $^ $(FLAG)  $(INC)  

$(TEST_OBJ)vector_linear.o: $(TEST_DIR)vector_linear.cc
	$(LINEAR_CC) -o $@ -c $< $(FLAG)  $(INC)

vector_parallel: $(TEST_OBJ)vector_parallel.o $(USE_PARALLEL_DEP)
	$(PARALLEL_CC) -o $@ $^ $(FLAG) $(OPENMP) $(INC)

$(TEST_OBJ)vector_parallel.o: $(TEST_DIR)vector_parallel.cc
	$(PARALLEL_CC) -o $@ -c $< $(FLAG) $(OPENMP) $(INC)

matrix_linear: $(TEST_OBJ)matrix_linear.o $(USE_SERIAL_DEP)
	$(LINEAR_CC) -o $@  $^ $(FLAG)  $(INC)  

$(TEST_OBJ)matrix_linear.o: $(TEST_DIR)matrix_linear.cc
	$(LINEAR_CC) -o $@ -c $< $(FLAG)  $(INC)

matrix_parallel: $(TEST_OBJ)matrix_parallel.o $(USE_PARALLEL_DEP)
	$(PARALLEL_CC) -o $@ $^ $(FLAG) $(OPENMP) $(INC)

$(TEST_OBJ)matrix_parallel.o: $(TEST_DIR)matrix_parallel.cc
	$(PARALLEL_CC) -o $@ -c $< $(FLAG) $(OPENMP) $(INC)

Solver_linear: $(TEST_OBJ)Solver_linear.o $(USE_SERIAL_DEP)
	$(LINEAR_CC) -o $@  $^ $(FLAG)  $(INC)  

$(TEST_OBJ)Solver_linear.o: $(TEST_DIR)Solver_linear.cc
	$(LINEAR_CC) -o $@ -c $< $(FLAG)  $(INC)

Solver_parallel: $(TEST_OBJ)Solver_parallel.o $(USE_PARALLEL_DEP)
	$(PARALLEL_CC) -o $@ $^ $(FLAG) $(OPENMP) $(INC)

$(TEST_OBJ)Solver_parallel.o: $(TEST_DIR)Solver_parallel.cc
	$(PARALLEL_CC) -o $@ -c $< $(FLAG) $(OPENMP) $(INC)

.PHONY : clean
clean : 
	rm -f Final Final_parallel  $(OBJECT)*.o $(TEST) *.txt test_case/output_dir/*.txt $(TEST_OBJ)*.o $(TEST_DIR)*.o 


