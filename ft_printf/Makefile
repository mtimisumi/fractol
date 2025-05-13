# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/08 13:04:30 by mmisumi           #+#    #+#              #
#    Updated: 2025/05/08 13:31:05 by mmisumi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libftprintf.a

SRCDIR := src
OBJDIR := obj

SRCS := $(SRCDIR)/ft_printf.c \
		$(SRCDIR)/det_type.c \
		$(SRCDIR)/low_hexa.c \
		$(SRCDIR)/print_adres.c \
		$(SRCDIR)/print_char.c \
		$(SRCDIR)/print_nbr.c \
		$(SRCDIR)/print_str.c \
		$(SRCDIR)/put_u.c \
		$(SRCDIR)/upp_hexa.c


OBJS := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

CC := cc
CFLAGS := -Wall -Werror -Wextra -I.

RM := rm -f 

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJS) $(RM) -r $(OBJDIR)

fclean: clean 
	$(RM) $(NAME)


re: fclean all

.PHONY: all clean fclean re