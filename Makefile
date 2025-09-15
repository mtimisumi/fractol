# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/08 13:18:47 by mmisumi           #+#    #+#              #
#    Updated: 2025/09/15 14:56:58 by mmisumi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fractol

SRCS:= src/main.c src/validate.c src/fractol.c src/hooks.c src/pixelstuff.c src/utils.c

OBJS := $(patsubst src/%.c, obj/%.o, $(SRCS))


LIBFT = libft/libft.a

PRINTF = ft_print/libftprintf.a

CC := cc -Wall -Werror -Wextra -g -I. -Ilibft -Ift_printf -Imlx_linux  -O3

RM := rm -f 

all: minilibx $(LIBFT) $(PRINTF) obj $(NAME)

obj:
	mkdir -p obj

$(LIBFT):
	make -C libft

$(PRINTF):
	make -C ft_printf

minilibx:
	@[ -f "mlx_linux/libmlx.a" ] || (cd mlx_linux && make)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(OBJS) -Llibft -lft -Lft_printf -lftprintf -Lmlx_linux -lmlx -lXext -lX11 -lm -lz -o $(NAME)

obj/%.o: src/%.c
	$(CC) -Imlx_linux -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) -r obj
	make -C libft clean
	make -C ft_printf clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean
	make -C ft_printf fclean

re: fclean all

.PHONY: all clean fclean re