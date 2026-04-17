SRCS = $(wildcard *.c)
TEST_SRCS = $(wildcard *_test.c)
MAIN_SRCS = $(filter-out $(TEST_SRCS), $(SRCS))
TEST_TARGETS = $(TEST_SRCS:.c=)
PROGRAMS = $(addsuffix .out, $(basename $(MAIN_SRCS)))
LIBRARY = libproject.a
LIB_OBJS = $(MAIN_SRCS:.c=.o)

.PHONY: all clean check_fmt fmt test

all: $(PROGRAMS)

clean:
	rm -rf *.o *.a $(PROGRAMS) $(TEST_TARGETS)

check_fmt:
	clang-format -style=LLVM --dry-run --Werror *.c *.h

fmt:
	clang-format -style=LLVM -i *.c *.h

# --- library
$(LIBRARY): $(LIB_OBJS)
	ar rc $@ $^

# --- object files
%.o: %.c
	gcc -g -c $< -o $@

# --- programs
%.out: %.c $(LIBRARY)
	gcc -g -o $@ $< -L. -lproject -lm

# --- tests
test: $(TEST_TARGETS)
	@for test in $(TEST_TARGETS); do ./$$test; done

$(TEST_TARGETS): %: %.o $(LIBRARY)
	gcc -g -static -o $@ $< $(LIBRARY) -lm
