CC = gcc

INCLUDES = -I include

CFLAGS = $(INCLUDES) -g
# -Wunused-function -Wall -Wextra

SRC = main.c \
      $(wildcard src/*.c) \
      $(wildcard src/compiler/*.c) \
      $(wildcard src/core/*.c) \
      $(wildcard src/lexer/*.c) \
      $(wildcard src/parser/*.c)

# Object directory
OBJDIR = obj

# Convert source files to object files inside obj/
OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

# Final executable name
TARGET = ex-t

# Default target
all: $(TARGET)

# Link all object files
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Compile each .c into .o inside obj/
ifeq ($(OS),Windows_NT)
    MKDIR = if not exist "$(subst /,\,$(dir $@))" mkdir "$(subst /,\,$(dir $@))"
    RM = rmdir /S /Q
    EXE = .exe
else
    MKDIR = mkdir -p $(dir $@)
    RM = rm -rf
    EXE =
endif

$(OBJDIR)/%.o: %.c
	@$(MKDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
ifeq ($(OS),Windows_NT)
    RM = rmdir /S /Q
    EXE = .exe
else
    RM = rm -rf
    EXE =
endif

clean:
	$(RM) $(OBJDIR)

.PHONY: all clean