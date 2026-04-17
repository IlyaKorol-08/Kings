CC ?= gcc
CFLAGS ?= -g -Wall -Wextra -std=c11
AR ?= ar
ARFLAGS ?= rcs
LDFLAGS ?=
LDLIBS ?= -lm
CLANG_FORMAT ?= clang-format
FORMAT_STYLE ?= LLVM

# Автопоиск исходников в корне репозитория.
SRCS := $(wildcard *.c)
TEST_SRCS := $(wildcard *_test.c)
MAIN_SRCS := $(filter-out $(TEST_SRCS),$(SRCS))

# Цели, которые собираем автоматически для любых веток/заданий.
LIBRARIES := $(MAIN_SRCS:.c=.a)
TEST_TARGETS := $(TEST_SRCS:.c=)
PROGRAMS := $(MAIN_SRCS:.c=.out)

.PHONY: all clean check_fmt fmt test programs

# Основная цель: собрать все библиотеки из не-тестовых исходников.
all:
	@if [ -z "$(MAIN_SRCS)" ]; then \
		echo "No main C sources found. Nothing to build."; \
	else \
		$(MAKE) --no-print-directory $(LIBRARIES); \
	fi

# Дополнительная цель (опционально): собрать исполняемые файлы.
programs:
	@if [ -z "$(MAIN_SRCS)" ]; then \
		echo "No main C sources found. Nothing to build."; \
	else \
		$(MAKE) --no-print-directory $(PROGRAMS); \
	fi

# Очистка рабочей директории от генерируемых файлов.
clean:
	rm -f *.o *.a *.out $(TEST_TARGETS)

# Проверка форматирования.
check_fmt:
	@set -- *.c *.h; \
	if [ "$$1" = "*.c" ] && [ "$$2" = "*.h" ]; then \
		echo "No C/H files to check."; \
	else \
		$(CLANG_FORMAT) -style=$(FORMAT_STYLE) --dry-run --Werror "$$@"; \
	fi

# Форматирование.
fmt:
	@set -- *.c *.h; \
	if [ "$$1" = "*.c" ] && [ "$$2" = "*.h" ]; then \
		echo "No C/H files to format."; \
	else \
		$(CLANG_FORMAT) -style=$(FORMAT_STYLE) -i "$$@"; \
	fi

# Запуск тестов (файлы с суффиксом _test.c).
test:
	@if [ -z "$(TEST_SRCS)" ]; then \
		echo "No test files found."; \
	else \
		$(MAKE) --no-print-directory $(TEST_TARGETS); \
		for test in $(TEST_TARGETS); do \
			echo "=== Running $$test ==="; \
			./$$test || exit 1; \
		done; \
	fi

# Объектные файлы.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Статические библиотеки.
%.a: %.o
	$(AR) $(ARFLAGS) $@ $<

# Тест: foo_test.c -> линкуется со всеми собранными библиотеками.
# Это делает правило независимым от соглашения об именовании тестов.
%_test: %_test.c $(LIBRARIES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBRARIES) $(LDLIBS)

# Исполняемый файл без линковки одноименной библиотеки.
%.out: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)
