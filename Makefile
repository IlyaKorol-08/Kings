SRCS = $(wildcard *.c)
TEST_SRCS = $(wildcard *_test.c)
MAIN_SRCS = $(filter-out $(TEST_SRCS), $(SRCS))
TEST_TARGETS = $(TEST_SRCS:.c=)
LIBRARY = project.a
LIB_OBJS = $(MAIN_SRCS:.c=.o)
PROGRAMS = $(MAIN_SRCS:.c=)

.PHONY: all clean check_fmt fmt test

all: $(LIBRARY) $(PROGRAMS)

clean:
	rm -rf *.o *.a $(PROGRAMS) $(TEST_TARGETS)

check_fmt:
	clang-format -style=LLVM --dry-run --Werror *.c *.h || true

fmt:
	clang-format -style=LLVM -i *.c *.h

# --- library
$(LIBRARY): $(LIB_OBJS)
	ar rc $@ $^

%.o: %.c
	gcc -g -c $< -o $@

# --- programs
$(PROGRAMS): %: %.o $(LIBRARY)
	gcc -g -o $@ $< -L. -lproject

# --- tests
test: $(TEST_TARGETS)
	@for test in $(TEST_TARGETS); do ./$$test; done

$(TEST_TARGETS): %: %.o $(LIBRARY)
	gcc -g -static -o $@ $< $(LIBRARY)
