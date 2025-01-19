NAME = pipex

CC = gcc -g
CFLAGS = -Wall -Wextra -Werror
REMOVE = rm -rf

OBJ_PATH = obj
SRC_PATH = src
INC_PATH = include

LIBFT_PATH = assets/libft
LIBFT_LIB_PATH = assets/libft/libft.a

HEADERS	= -I $(LIBFT_PATH)/include/ -I ./include

SRC_FILES = pipex.c pipex_utils.c
BONUS_SRC_FILES = pipex_bonus.c pipex_bonus_utils.c pipex_utils.c

SRC := $(addprefix $(SRC_PATH)/, $(SRC_FILES))
BONUS_SRC := $(addprefix $(SRC_PATH)/, $(BONUS_SRC_FILES))
OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
OBJ_BONUS = $(BONUS_SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)

ORANGE = \033[1;38;5;208m
RESET = \033[0m
U_LINE = \033[4m
YELLOW = \033[1;38;5;226m

all: $(LIBFT_LIB_PATH) $(NAME)
	@if test -f bonus; then \
		rm pipex; \
		rm bonus; \
		$(MAKE) all; \
	fi

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LIBFT_LIB_PATH) $(HEADERS) -o $@
	@echo "\n$(ORANGE)$(U_LINE)$(NAME): Mandatory Compiled$(RESET) \n"

$(LIBFT_LIB_PATH):
	@$(MAKE) -C $(LIBFT_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@echo "$(YELLOW)$(NAME) Compiling:$(RESET) $(notdir $<)"

clean:
	@$(REMOVE) $(OBJ_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	@$(REMOVE) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

bonus: $(LIBFT_LIB_PATH) $(OBJ_BONUS)
	@$(CC) $(OBJ_BONUS) $(LIBFT_LIB_PATH) $(HEADERS) -o $(NAME)
	@echo ¨last compilation bonus¨ > bonus
	@echo "\n$(ORANGE)$(U_LINE)$(NAME): Bonus Compiled$(RESET) \n"

.PHONY: all clean fclean re $(LIBFT_LIB_PATH) bonus