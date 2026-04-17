# Общий Makefile для проекта
# Группа: [номер группы]
# Участники: [список участников]

CC = gcc
CFLAGS = -g -Wall -Wextra -std=c11
AR = ar
ARFLAGS = rcs

# Автоматический поиск файлов
SRCS = $(wildcard *.c)
TEST_SRCS = $(wildcard *_test.c)
MAIN_SRCS = $(filter-out $(TEST_SRCS), $(SRCS))
TEST_TARGETS = $(TEST_SRCS:.c=)
LIBRARIES = $(MAIN_SRCS:.c=.a)
PROGRAMS = $(MAIN_SRCS:.c=.out)

.PHONY: all clean check_fmt fmt test

# Основная цель - сборка всех библиотек
all: $(LIBRARIES)

# Очистка рабочей директории от генерируемых файлов
clean:
	rm -rf *.o *.a *.out $(TEST_TARGETS)

# Проверка форматирования
check_fmt:
	@if ls *.c *.h 1>/dev/null 2>&1; then \
		clang-format -style=LLVM --dry-run --Werror *.c *.h; \
	else \
		echo "No C/H files to check."; \
	fi

# Форматирование
fmt:
	@if ls *.c *.h 1>/dev/null 2>&1; then \
		clang-format -style=LLVM -i *.c *.h; \
	else \
		echo "No C/H files to format."; \
	fi

# Запуск тестов (любые файлы с суффиксом _test)
test: $(TEST_TARGETS)
	@if [ -z "$(TEST_TARGETS)" ]; then \
		echo "No test files found."; \
	else \
		for test in $(TEST_TARGETS); do \
			echo "=== Running $$test ==="; \
			./$$test || exit 1; \
		done; \
	fi

# Правило для создания объектных файлов
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Правило для создания статических библиотек
%.a: %.o
	$(AR) $(ARFLAGS) $@ $^

# Правило для создания тестов
%_test: %_test.c %.a
	$(CC) $(CFLAGS) -o $@ $< -L. -l$(basename $@)

# Сборка исполняемых программ (если нужны)
%.out: %.c %.a
	$(CC) $(CFLAGS) -o $@ $< -L. -l$(basename $@)
