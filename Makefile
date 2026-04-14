clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

# --- add

integral_solver.o: integral_solver.h integral_solver.c
	gcc -g -c integral_solver.c -o integral_solver.o

integral_solver.a: integral_solver.o
	ar rc integral_solver.a integral_solver.o

integral_test.o: integral_test.c
	gcc -g -c integral_test.c -o integral_test.o

integral_test: integral_test.o integral_solver.a
	gcc -g -static -o integral_test integral_test.o -L. -l:integral_solver.a -lm

# ---

test: integral_test
	./integral_test
	