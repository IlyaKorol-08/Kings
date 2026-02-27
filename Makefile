clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

# --- add

add.o: add.h add.c
	gcc -g -c add.c -o add.o

add.a: add.o
	ar rc add.a add.o

add_test.o: add_test.c
	gcc -g -c add_test.c -o add_test.o

add_test: add_test.o add.a
	gcc -g -static -o add_test add_test.o add.a

# ---

test: add_test
	./add_test