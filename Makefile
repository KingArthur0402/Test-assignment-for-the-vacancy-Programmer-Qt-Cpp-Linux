CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -std=c11
LDFLAGS = -lm

TARGET1 = build/task1
TARGET2 = build/task2

SRCS1 = task1/main.c \
		task1/cpu_info.c
OBJS1 = $(SRCS1:%.c=%.o)

SRCS2 = task2/main.c \
        task2/udp_client.c \
		task1/cpu_info.c
OBJS2 = $(SRCS2:%.c=%.o)

OBJS3 = task3/.qmake.stash \
		task3/*.o \
		task3/Makefile \
		task3/moc*

all: task1 task2 clean_objects

task1: $(TARGET1)

task2: $(TARGET2)

$(TARGET1): $(OBJS) $(OBJS1)
	@mkdir -p build
	$(CC) $(OBJS) $(OBJS1) -o $(TARGET1) $(LDFLAGS)
	@echo "Build complete: $(TARGET1)"

$(TARGET2): $(OBJS) $(OBJS2)
	@mkdir -p build
	$(CC) $(OBJS) $(OBJS2) -o $(TARGET2) $(LDFLAGS)
	@echo "Build complete: $(TARGET2)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: clean_objects
	rm -rf build
	@echo "Files cleaned"

clean_objects:
	rm -f $(OBJS) $(OBJS1) $(OBJS2) $(OBJS3)
	@echo "Object files cleaned"

rebuild: clean all

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem task1/*.c task2/*.c task3/cpu_graph.cpp task3/main.cpp

clang-formatn:
	clang-format -n task1/*.c task1/*.h task2/*.c task2/*.h task3/*.cpp task3/*.h

clang-formati:
	clang-format -i task1/*.c task1/*.h task2/*.c task2/*.h task3/*.cpp task3/*.h

help:
	@echo "Available targets:"
	@echo "  all                    - Build"
	@echo "  task1                  - Build task1"
	@echo "  task2                  - Build task2"
	@echo "  clean                  - Remove files"
	@echo "  rebuild                - Rebuild from scratch"
	@echo "  clean_objects          - Remove object files"
	@echo "  cppcheck               - Cppcheck files"
	@echo "  clang-formatn          - Clang-format -n"
	@echo "  clang-formati          - Clang-format -i"
	@echo "  help                   - Show this help"


.PHONY: all clean rebuild help clean_objects cppcheck clang-formatn clang-formati