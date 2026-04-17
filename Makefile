# Компилятор и флаги
CC = gcc
CFLAGS = -g -Wall -Wextra -std=c11
AR = ar
ARFLAGS = rcs

# Автоматическое определение файлов
SRCS = $(wildcard *.c)
TEST_SRCS = $(wildcard *_test.c)
MAIN_SRCS = $(filter-out $(TEST_SRCS), $(SRCS))
TEST_TARGETS = $(TEST_SRCS:.c=)

# Если есть main.c, создаем исполняемый файл program
ifneq ($(filter main.c, $(MAIN_SRCS)),)
    MAIN_TARGET = program
else
    MAIN_TARGET =
endif

# Библиотека из всех не-тестовых файлов
LIBRARY = libproject.a
LIB_OBJS = $(MAIN_SRCS:.c=.o)

# Все исполняемые файлы (кроме тестов)
PROGRAMS = $(filter-out $(TEST_TARGETS), $(MAIN_SRCS:.c=))

.PHONY: all clean check_fmt fmt test build-all

# Основная цель - собирает библиотеку и все программы
all: $(LIBRARY) $(MAIN_TARGET) $(PROGRAMS)

# Сборка всех возможных исполняемых файлов
build-all: $(LIBRARY) $(PROGRAMS) $(TEST_TARGETS)

# Сборка библиотеки
$(LIBRARY): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^

# Правило для создания объектных файлов
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Сборка отдельных программ из соответствующих .c файлов
$(PROGRAMS): %: %.o $(LIBRARY)
	$(CC) $(CFLAGS) -o $@ $@.o -L. -lproject

# Специальное правило для program (если есть main.c)
ifneq ($(MAIN_TARGET),)
$(MAIN_TARGET): main.o $(LIBRARY)
	$(CC) $(CFLAGS) -o $@ main.o -L. -lproject
endif

# Очистка
clean:
	rm -rf *.o *.a program $(PROGRAMS) $(TEST_TARGETS)

# Проверка форматирования
check_fmt:
	@clang-format -style=LLVM --dry-run --Werror *.c *.h 2>/dev/null || true

# Форматирование
fmt:
	@clang-format -style=LLVM -i *.c *.h 2>/dev/null || true

# Запуск тестов
test: $(LIBRARY) $(TEST_TARGETS)
	@for test in $(TEST_TARGETS); do \
		echo "Running $$test..."; \
		./$$test || exit 1; \
	done

# Сборка тестовых программ
$(TEST_TARGETS): %: %.o $(LIBRARY)
	$(CC) $(CFLAGS) -o $@ $< -L. -lproject
