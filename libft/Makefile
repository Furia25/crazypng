# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 21:41:19 by val               #+#    #+#              #
#    Updated: 2025/06/23 15:12:51 by vdurand          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDE_DIR = ./
CFLAGS = -Wall -Wextra -Werror -fPIC -I$(INCLUDE_DIR)  -O3 -Wno-unused-result
CC = cc
NAME = libft.a

BASE_SRC = checks/ft_isalpha.c \
		checks/ft_isdigit.c \
		checks/ft_isalnum.c \
		checks/ft_isascii.c \
		checks/ft_isprint.c \
		checks/ft_toupper.c \
		checks/ft_tolower.c \
		checks/ft_isbigendian.c \
		memory/ft_memset.c \
		memory/ft_bzero.c \
		memory/ft_memcpy.c \
		memory/ft_memmove.c \
		memory/ft_memchr.c \
		memory/ft_memcmp.c \
		memory/ft_calloc.c \
		strings/ft_strlen.c \
		strings/ft_strlcpy.c \
		strings/ft_strlcat.c \
		strings/ft_strcpy.c \
		strings/ft_strcat.c \
		strings/ft_strchr.c \
		strings/ft_strrchr.c \
		strings/ft_strncmp.c \
		strings/ft_strcmp.c \
		strings/ft_strnstr.c \
		strings/ft_strdup.c \
		strings/ft_substr.c \
		strings/ft_strjoin.c \
		strings/ft_strtrim.c \
		strings/ft_split.c \
		strings/ft_strmapi.c \
		strings/ft_striteri.c \
		strings/ft_strend.c \
		conversions/ft_atoi.c \
		conversions/ft_itoa.c \
		files_managing/ft_putchar_fd.c \
		files_managing/ft_putstr_fd.c \
		files_managing/ft_putendl_fd.c \
		files_managing/ft_putnbr_fd.c \
		files_managing/ft_putptr_fd.c \
		files_managing/ft_putnbr_base_fd.c \
		files_managing/get_next_line.c \
		ft_printf.c \

BONUS_SRC = chained_lists/ft_lstadd_back_bonus.c \
			chained_lists/ft_lstadd_front_bonus.c \
			chained_lists/ft_lstclear_bonus.c \
			chained_lists/ft_lstdelone_bonus.c \
			chained_lists/ft_lstiter_bonus.c \
			chained_lists/ft_lstlast_bonus.c \
			chained_lists/ft_lstmap_bonus.c \
			chained_lists/ft_lstnew_bonus.c \
			chained_lists/ft_lstsize_bonus.c

BASE_OBJS = $(BASE_SRC:.c=.o)
BONUS_OBJS = $(BONUS_SRC:.c=.o)
ALL_OBJS = $(BASE_OBJS) $(BONUS_OBJS)

all: $(NAME)

bonus: .bonus

.bonus : $(ALL_OBJS)
	ar rcs $(NAME) $(ALL_OBJS)
	@touch .bonus

$(NAME): $(BASE_OBJS)
	ar rcs $(NAME) $(BASE_OBJS)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(BONUS_OBJS) $(BASE_OBJS)
	@rm -rf .bonus

fclean: clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus
