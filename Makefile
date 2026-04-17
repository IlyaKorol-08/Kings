SRCS = $(wildcard *.c)
TEST_SRCS = $(wildcard *_test.c)
MAIN_SRCS = $(filter-out $(TEST_SRCS), $(SRCS))
TEST_TARGETS = $(TEST_SRCS:.c=)
LIBRARY = libproject.a
LIB_OBJS = $(MAIN_SRCS:.c=.o)

.PHONY: all clean check_fmt fmt test

all: $(LIBRARY)
	@for src in $(MAIN_SRCS); do \
		prog=$${src%.c}; \
		gcc -g -o $$prog $$src -L. -lproject; \
	done

clean:
	rm -rf *.o *.a $(TEST_TARGETS) $(MAIN_SRCS:.c=)

check_fmt:
	clang-format -style=LLVM --dry-run --Werror *.c *.h || true

fmt:
	clang-format -style=LLVM -i *.c *.h

# --- library
$(LIBRARY): $(LIB_OBJS)
	ar rc $@ $^

%.o: %.c
	gcc -g -c $< -o $@

# --- tests
test: $(TEST_TARGETS)
	@for test in $(TEST_TARGETS); do ./$$test; done

$(TEST_TARGETS): %: %.o $(LIBRARY)
	gcc -g -static -o $@ $< $(LIBRARY)
