# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/08 13:18:47 by mmisumi           #+#    #+#              #
#    Updated: 2025/05/16 14:54:27 by mmisumi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fractol

SRCDIR := src
OBJDIR := obj

SRCS:= $(SRCDIR)/main.c \
		$(RSCDIR)/validate.c \
		$(RSCDIR)/fractol.c \
		$(RSCDIR)/hooks.c \
		$(RSCDIR)/pixelstuff.c \
		$(SRCDIR)/utils.c

OBJS := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

LIBFT := libft/libft.a

FT_PRINTF := ft_printf/libftprintf.a

MLX = mlx_linux

CC := cc
CFLAGS := -g -I. -Ilibft -Ift_printf -Wall -Werror -Wextra

RM := rm -f 

all: minilibx $(LIBFT) $(FT_PRINTF) $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	make -C libft

$(FT_PRINTF):
	make -C ft_printf

minilibx:
	@[ -f "$(MLX)/libmlx.a" ] || (cd $(MLX) && make)

$(NAME): $(OBJS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJS) -o $(NAME) -Llibft -lft -Lft_printf -lftprintf -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -I/opt/X11/include

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I/usr/include -Imlx_linux -O3

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJDIR)
	make -C libft clean
	make -C ft_printf clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean
	make -C ft_printf fclean

re: fclean all

.PHONY: all clean fclean re