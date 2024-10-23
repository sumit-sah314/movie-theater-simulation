grading.out: movie_simulation_grading_driver.o movie_simulation_program_3_functions.o
	g++ movie_simulation_grading_driver.o movie_simulation_program_3_functions.o -o grading.out

program3.out: movie_simulation_program_3.o movie_simulation_program_3_functions.o
	g++ movie_simulation_program_3.o movie_simulation_program_3_functions.o -o program3.out

movie_simulation_program_3_functions.o: movie_simulation_program_3_functions.cpp movie_simulation_program_3.h
	g++ -c movie_simulation_program_3_functions.cpp

movie_simulation_grading_driver.o: movie_simulation_grading_driver.cpp movie_simulation_program_3.h
	g++ -c movie_simulation_grading_driver.cpp

movie_simulation_program_3.o: movie_simulation_program_3.cpp movie_simulation_program_3.h
	g++ -c movie_simulation_program_3.cpp

run:
	clear; ./program3.out

grade:
	clear; ./grading.out

clean:
	rm *.o

