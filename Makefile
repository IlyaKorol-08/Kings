clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

quadratic_solver.o: quadratic_solver.h quadratic_solver.c
	gcc -g -c quadratic_solver.c -o quadratic_solver.o

quadratic_solver.a: quadratic_solver.o
	ar rc quadratic_solver.a quadratic_solver.o

quadratic_test.o: quadratic_test.c quadratic_solver.h
	gcc -g -c quadratic_test.c -o quadratic_test.o

quadratic_test: quadratic_test.o quadratic_solver.a
	gcc -g -static -o quadratic_test quadratic_test.o -L. -l:quadratic_solver.a -lm

test: quadratic_test
	./quadratic_test
