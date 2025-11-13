CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -std=c11
LDFLAGS = -lm

TARGET1 = build/task1
TARGET2 = build/task2

SRCS = task1/cpu_info.c
OBJS = $(SRCS:%.c=%.o)

SRCS1 = task1/main.c
OBJS1 = $(SRCS1:%.c=%.o)

SRCS2 = task2/main.c \
        task2/upd_client.c
OBJS2 = $(SRCS2:%.c=%.o)

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

clean:
	rm -f $(OBJS) $(OBJS1) $(OBJS2) $(TARGET1) $(TARGET2)
	@echo "Files cleaned"

clean_objects:
	rm -f $(OBJS) $(OBJS1) $(OBJS2)
	@echo "Object files cleaned"

rebuild: clean all

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem task1/*.c task2/*.c

clang-formatn:
	clang-format -n task1/*.c task1/*.h task2/*.c task2/*.h

clang-formati:
	clang-format -i task1/*.c task1/*.h task2/*.c task2/*.h

help:
	@echo "Available targets:"
	@echo "  all                    - Build"
	@echo "  task1                  - Build task1"
	@echo "  task2                  - Build task2"
	@echo "  clean                  - Remove object files and graph"
	@echo "  rebuild                - Rebuild from scratch"
	@echo "  clean_objects          - Remove object files"
	@echo "  cppcheck               - Cppcheck files"
	@echo "  clang-formatn          - Clang-format -n"
	@echo "  clang-formati          - Clang-format -i"
	@echo "  leaks                  - Leaks"
	@echo "  help                   - Show this help"


.PHONY: all clean rebuild help clean_objects cppcheck clang-formatn clang-formati