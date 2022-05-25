#pragma once
NAME = find

CC = g++

CFLAGS = -Wall -Wextra -Werror -std=c++11

SRCS_DIRS = ./srcs

HDRS_DIRS = ./hdrs

OBJS_DIR = ./objs

SRCS = $(wildcard $(addsuffix /*.cpp, $(SRCS_DIRS)))

HDRS = $(wildcard $(addsuffix /*.hpp, $(HDRS_DIRS)))

OBJS = $(addprefix objs/, $(notdir $(patsubst %.cpp, %.o, $(SRCS))))

VPATH = $(SRCS_DIRS)

$(OBJS_DIR)/%.o: %.cpp $(HDRS)
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
