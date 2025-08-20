# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdurand <vdurand@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 23:20:17 by val               #+#    #+#              #
#    Updated: 2025/06/23 15:11:08 by vdurand          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	ANSI TEXT COLORS
BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m

#	ANSI BACKGROUND COLORS
BG_BLACK = \033[40m
BG_RED = \033[41m
BG_GREEN = \033[42m
BG_YELLOW = \033[43m
BG_BLUE = \033[44m
BG_MAGENTA = \033[45m
BG_CYAN = \033[46m
BG_WHITE = \033[47m

#	STYLES
BOLD = \033[1m
DIM = \033[2m
ITALIC = \033[3m
UNDERLINE = \033[4m
BLINK = \033[5m
REVERSE = \033[7m
HIDDEN = \033[8m

RESET = \033[0m
##################

DEBUG_VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=all --track-origins=yes -s

NAME = libcrazypng.a

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = libft

VERBOSE = 0

ifeq ($(VERBOSE),1)
    SILENT =
else
    SILENT = @
endif

ifeq ($(VERBOSE),1)
    DUMP_OUT =
else
    DUMP_OUT = > /dev/null 2>&1
endif


SRC_FILES = \
	utils/file.c \
	utils/file_fread.c \
	utils/swaps.c \
	utils/buffer_utils.c \
	bitstream/bitstream_utils.c \
	bitstream/bitstream_reads.c \
	bitstream/bitstream_misc.c \
	png/png_managing.c \
	png/png_parsing.c \
	png/png_chunk_parsing.c \
	png/png_utils.c \
	png/png_chunk_IHDR.c \
	png/png_chunk_PLTE.c \
	png/png_decompress.c \
	png/png_unfilter.c \
	png/png_unfilter_algos.c \
	png/png_pixel_unpacking.c \
	deflate/inflate.c \
	deflate/lz77.c \
	deflate/inflate_decode.c \
	deflate/inflate_decode_huffman.c \
	deflate/inflate_huffman_assign.c \
	deflate/inflate_read_dynamic.c \
	deflate/inflate_read_lengths.c \
	huffman/huffman_decode.c \
	huffman/huffman_deflate.c \
	huffman/huffman_managing.c

SRC = $(patsubst %.c, $(SRC_DIR)/%.c, $(SRC_FILES))
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
DEP = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.d, $(SRC))

LIBFT_DIR = libft

CC = cc
OPTIFLAGS = -O3
CFLAGS = $(OPTIFLAGS) -Werror -Wextra -Wall
LDFLAGS = -$(FTFLAGS)
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)

all: makelibft $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a
	@cp $(LIBFT_DIR)/libft.a $@
	$(SILENT) $(AR) rcs $@ $(OBJ) $(DUMP_OUT)
#	$(SILENT) $(AR) rcs $@ $^ $(DUMP_OUT)
	@echo "$(BG_GREEN)>>> Library $@ built$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile $(INC_DIR)/*.h | $(OBJ_DIR)
	$(SILENT) mkdir -p $(dir $@)
	@echo "$(BLUE)>>> Compiling $<...$(RESET)"
	$(SILENT)$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

makelibft:
	@echo "$(BLUE)>>> Compiling Libft...$(RESET)"
	$(SILENT)$(MAKE) -C $(LIBFT_DIR) $(DUMP_OUT)
	$(SILENT)$(MAKE) bonus -C $(LIBFT_DIR) $(DUMP_OUT)
	@echo "$(GREEN)>>> Compilation achieved!$(RESET)"

$(OBJ_DIR):
	@echo "$(YELLOW)>>> Directory '$(OBJ_DIR)' created!$(RESET)"
	$(SILENT)mkdir -p $(OBJ_DIR)

cleanlibs:
	@echo "$(YELLOW)>>> Cleaning libs...$(RESET)"
	@$(MAKE) fclean -C $(LIBFT_DIR) > /dev/null 2>&1

clean:
	@echo "$(YELLOW)>>> Cleaning objects$(RESET)"
	rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(YELLOW)>>> Cleaning library$(RESET)"
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

debug: all
	$(DEBUG_VALGRIND) ./$(NAME)

debug_env: all
	env -i $(DEBUG_VALGRIND) ./$(NAME)

debug_trueclean: all
	$(DEBUG_VALGRIND) env -i ./$(NAME)

-include $(DEP)

.PHONY: all cleanlibs clean fclean re makelibft makeminilibx debug debug_env debug_trueclean