SRCS = $(wildcard *.c)
TEST_SRCS = $(wildcard *_test.c)
MAIN_SRCS = $(filter-out $(TEST_SRCS), $(SRCS))
TEST_TARGETS = $(TEST_SRCS:.c=)
LIBRARY = libproject.a
LIB_OBJS = $(MAIN_SRCS:.c=.o)

.PHONY: all clean check_fmt fmt test

all: $(LIBRARY)
	@if [ -n "$(MAIN_SRCS)" ]; then \
		gcc -g -o program $(MAIN_SRCS); \
	fi

$(LIBRARY): $(LIB_OBJS)
	ar rc $@ $^

%.o: %.c
	gcc -g -c $< -o $@

clean:
	rm -rf *.o *.a program $(TEST_TARGETS)

check_fmt:
	clang-format -style=LLVM --dry-run --Werror *.c *.h || true

fmt:
	clang-format -style=LLVM -i *.c *.h

test: $(LIBRARY) $(TEST_TARGETS)
	@for test in $(TEST_TARGETS); do ./$$test; done

$(TEST_TARGETS): %: %.o $(LIBRARY)
	gcc -g -static -o $@ $< $(LIBRARY)

