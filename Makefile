# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/08 13:18:47 by mmisumi           #+#    #+#              #
#    Updated: 2025/05/15 13:18:25 by mmisumi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fractol

SRCDIR := src
OBJDIR := obj

SRCS:= $(SRCDIR)/main.c \
		$(RSCDIR)/fractol.c \
		$(RSCDIR)/validate.c \
		$(RSCDIR)/pixelstuff.c \
		$(RSCDIR)/hooks.c

OBJS := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

LIBFT := libft/libft.a

FT_PRINTF := ft_printf/libftprintf.a

CC := cc
CFLAGS = -g -I. -Ilibft -Ift_printf
# CFLAGS += -Wall -Werror -Wextra

RM := rm -f 

all: $(OBJDIR) $(LIBFT) $(FT_PRINTF) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	make -C libft

$(FT_PRINTF):
	make -C ft_printf

# -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -I/opt/X11/include
$(NAME): $(OBJS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -Llibft -lft -Lft_printf -lftprintf -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -I/opt/X11/include


# -I/usr/include -Imlx_linux -O3
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