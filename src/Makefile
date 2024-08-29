CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

SOURCES = s21_arithmetic.c s21_comparisons.c s21_convertors.c s21_other_functions.c s21_service_functions.c
OBJECTS = $(SOURCES:.c=.o)
LIBRARY = s21_decimal.a

TEST_DIR = tests
TEST_SUITE_SOURCES = $(wildcard $(TEST_DIR)/*_suite.c)
TEST_SUITE_OBJECTS = $(patsubst %.c,%.o,$(TEST_SUITE_SOURCES))
TEST_SOURCES = $(wildcard $(TEST_DIR)/*_tests.c)
TEST_OBJECTS = $(patsubst %.c,%.o,$(TEST_SOURCES))
TEST_EXECUTABLES = $(patsubst %.c,%,$(TEST_SUITE_SOURCES))

ALL_SRC = $(wildcard *.c */*.c *.h */*.h)

ifeq ($(shell uname), Linux)
	LDLIBS = -lcheck -lm -lsubunit -lrt 
else
	LDLIBS = -lcheck -lm -lpthread
endif

all: $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	ar rcs $@ $^
	ranlib $@

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) -c $^

test: $(LIBRARY) $(TEST_EXECUTABLES)
	for test in $(TEST_EXECUTABLES); do ./$$test; done

$(TEST_EXECUTABLES): %: $(TEST_SUITE_OBJECTS) $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(TEST_SUITE_OBJECTS) $(TEST_OBJECTS) $(LIBRARY) $(LDLIBS)

$(TEST_SUITE_OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(LIBRARY) $(TEST_EXECUTABLES) *.o */*.o
	rm -f *.gcno *.gcda *.gcov **/*.gcno **/*.gcda **/*.gcov coverage.info
	rm -rf coverage_report

rebuild: clean test

clang:
	cp ../materials/linters/.clang-format ./
	clang-format -i $(ALL_SRC)

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(ALL_SRC)

gcov_report: CFLAGS += -coverage
gcov_report: clean test
	gcov $(SOURCES)
	mkdir coverage_report
	lcov --directory . --capture --output-file coverage.info
	genhtml coverage.info --output-directory coverage_report
	open ./coverage_report/index.html