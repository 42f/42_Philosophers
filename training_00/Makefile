NAME := $(lastword $(subst /, ,$(dir $(realpath $(lastword $(MAKEFILE_LIST))))))

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pthread
CFLAGS += -fPIC
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

ifeq ($(err), 0)
	CFLAGS += -g3
else
	CFLAGS += -Werror
endif
ifneq ($(opti), 0)
	CFLAGS += -O3
endif

ifeq ($(debug_mode), 1)
	DEBUG_MODE = 1
else
	DEBUG_MODE = 0
endif

CC = gcc

INCLUDES = ./

HEADER += $(INCLUDES)*.h

# SRCS += $(NAME).c
# SRCS += $(NAME)_utils.c

SRCS += ./*.c

OBJ_DIR = ../objs/

vpath %.c ./

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
