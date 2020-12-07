NAME := $(lastword $(subst /, ,$(dir $(realpath $(lastword $(MAKEFILE_LIST))))))
INCLUDES = ./
CC = gcc
OBJ_DIR = ../objs/

CFLAGS += -pthread
CFLAGS += -Wall
CFLAGS += -Wextra

ifneq ($(no_error), 1)
	CFLAGS += -Werror
endif

# CFLAGS += -fPIC

ifeq ($(debug), 1)
	CFLAGS += -g3
else ifeq ($(debug), 2)
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -g3
else ifeq ($(debug), 3)
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -g3
	CFLAGS += -Wpadded
else ifeq ($(debug), 4)
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -g3
	CFLAGS += -Wpadded
	ifneq ($(CC), gcc)
		CFLAGS += -Weverything
	endif
endif

ifeq ($(db), 1)
	CFLAGS += -g3
endif
ifeq ($(opti), 1)
	CFLAGS += -O3
endif

ifeq ($(debug_mode), 1)
	DEBUG_MODE = 1
else
	DEBUG_MODE = 0
endif

HEADER += $(INCLUDES)*.h

# SRCS += $(NAME).c
# SRCS += $(NAME)_utils.c
SRCS += $(wildcard *.c)

# vpath %.c ./

OBJS = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRCS))

all :
	$(MAKE) $(NAME)

$(OBJS): $(OBJ_DIR)%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $<  -I $(INCLUDES) -o $@

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I$(INCLUDES) -o $@
	@echo "\033[32m$@ is ready !\033[0m"

$(OBJ_DIR):
	mkdir $@

FORCE :

clean :
	$(RM) -R $(OBJ_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean
	$(MAKE)

f : all
	./$(NAME)

.PHONY: all clean fclean mclean re FORCE
#.SILENT:
