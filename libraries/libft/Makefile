# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykiso <ykiso@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 14:48:07 by aaleksee          #+#    #+#              #
#    Updated: 2024/08/31 19:07:01 by ykiso            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCFLAGS = -I../../includes

PRINTF_DIR = printf/
GNL_DIR = GNL/

SRCS =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_lstnew.c ft_lstadd_back.c ft_lstclear.c

PRINTF_SRCS =	$(PRINTF_DIR)ft_printf.c \
				$(PRINTF_DIR)ft_printf_utils_str_nbr.c \
				$(PRINTF_DIR)ft_printf_utils_p_x.c \
				$(PRINTF_DIR)ft_printf_utils_flags.c

GNL_SRCS =		$(GNL_DIR)get_next_line.c \
				$(GNL_DIR)get_next_line_utils.c

OBJS =			$(SRCS:.c=.o)
PRINTF_OBJS =	$(PRINTF_SRCS:.c=.o)
GNL_OBJS =		$(GNL_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF_OBJS) $(GNL_OBJS)
	@ar -rc $@ $?

%.o: %.c
	@$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

bonus: $(OSRC) $(OBSRC)
	@ar -rc $(NAME) $?

clean:
	@rm -f $(OBJS) $(PRINTF_OBJS) $(GNL_OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re