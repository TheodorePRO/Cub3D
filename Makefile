# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjudlin <tjudlin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/11 10:55:33 by tjudlin           #+#    #+#              #
#    Updated: 2022/03/10 10:58:35 by tjudlin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

# --   Directory   -- #
OBJ_DIR = objs

INC = ./mlx_linux/*.a
LIB			=	-L -lft -L ./mlx_linux -lmlx -lXext -lX11 -lm -lbsd
MLX			=	mlx_linux/Makefile.gen

# --  Search All files in SRCS  -- #
SRC_DIR    = $(shell find srcs -type d)
vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)
SRCS = $(foreach dir, $(SRC_DIR), $(foreach file, $(wildcard $(dir)/*.c), $(notdir $(file))))

# --  Redirection in OBJS  -- #
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

# --   Compilation flags  -- #
CC            =    gcc
CFLAGS      =   -Wall -Wextra -Werror

all :
		mkdir -p $(OBJ_DIR)
		make $(MLX) $(NAME) --no-print-directory

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INC) $(LIB)

$(OBJ_DIR)/%.o: %.c
		$(CC) $(CFLAGS) -o $@ -c $<

clean:
		rm -rf $(OBJ_DIR)
		@echo "object files removed."
# make clean -C $(LIB_DIR) --no-print-directory

fclean:	clean
		rm -f $(NAME)
		@echo "binary file removed."

# make fclean -C $(LIB_DIR) --no-print-directory
# make fclean -C $(CHECK_DIR) --no-print-directory
# rm -f checker

re:		fclean all

.PHONY: all clean flcean re
