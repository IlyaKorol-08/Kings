SRCS = $(wildcard *.c)
TEST_SRCS = $(wildcard *_test.c)
MAIN_SRCS = $(filter-out $(TEST_SRCS), $(SRCS))
TEST_TARGETS = $(TEST_SRCS:.c=)
LIBRARY = project.a
LIB_OBJS = $(MAIN_SRCS:.c=.o)
PROGRAMS = $(MAIN_SRCS:.c=)

.PHONY: all clean check_fmt fmt test

all: $(LIBRARY)
	@for src in $(MAIN_SRCS); do \
		prog=$${src%.c}; \
		gcc -g -o $$prog $$src -L. -lproject; \
	done

clean:
	rm -rf *.o *.a $(PROGRAMS) $(TEST_TARGETS)

check_fmt:
	clang-format -style=LLVM --dry-run --Werror *.c *.h

fmt:
	clang-format -style=LLVM -i *.c *.h

# --- library
$(LIBRARY): $(LIB_OBJS)
	ar rc $@ $^

%.o: %.c
	gcc -g -c $< -o $@

# --- tests
test: $(LIBRARY) $(TEST_TARGETS)
	@for test in $(TEST_TARGETS); do ./$$test; done

$(TEST_TARGETS): %: %.o $(LIBRARY)
	gcc -g -static -o $@ $< $(LIBRARY)
