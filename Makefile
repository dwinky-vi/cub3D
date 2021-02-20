


SRCS	= \
		main.c ft_some_utils.c ft_free.c ft_parser.c\
		ft_validator.c ft_2d.c

NAME		= cub3D

LIBFT_PATH		= ./libft

FT_PRINTF_PATH	= ./ft_printf

MINILIBX_PATH	= ./minilibx

HEADER		= ft_cub3d.h

CC		= gcc

CFLAGS	= -g

# создаём скрытую директорию, в которой будут .o файлы
OBJS_DIR =			.obj

# прописываем (добавляем) путь для каждого .o файла
OBJS	= 			$(addprefix $(OBJS_DIR)/, $(patsubst %.c, %.o, $(SRCS)))

NORM 	=			~/.scripts/colorised_norm.sh

all:		make_lib make_printf make_mlx $(NAME)

make_lib:
			@${MAKE} -C libft

make_printf:
			@${MAKE} -C ft_printf

make_mlx:
			@${MAKE} -C minilibx

$(NAME): 	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -I $(HEADER) -L./libft -lft -L./ft_printf -lftprintf $(MINILIBX_PATH)/libmlx.dylib -framework OpenGL -framework AppKit -o $(NAME)
			@printf "$(GREEN)$(BOLD)cub3D $(NO_COLOR)–– $(GREEN)$(BOLD)[Success compiling]        $(NO_COLOR)\n"

$(OBJS_DIR)/%.o:	%.c $(HEADER) libft/libft.a
					@test -d $(OBJS_DIR) || mkdir $(OBJS_DIR)
					@printf "$(GREEN)$(BOLD)Compilation $(UNDER_LINE)$(YELLOW)$<$(NO_COLOR)  $(BOLD)–– $(RED)[KO]        $(NO_COLOR)\r"
					@$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@
					@printf "$(GREEN)$(BOLD)Compilation $(UNDER_LINE)$(YELLOW)$<$(NO_COLOR)  $(BOLD)–– $(GREEN)[OK]$(NO_COLOR)\n"

clean:
			@rm -rf $(OBJS)
			@/bin/rm -rf $(OBJS_DIR)
			@cd $(LIBFT_PATH) && make clean
			@cd $(FT_PRINTF_PATH) && make clean
			@cd $(MINILIBX_PATH) && make clean

fclean: 	clean
			@rm -rf $(NAME)
			@cd $(LIBFT_PATH) && make fclean
			@cd $(FT_PRINTF_PATH) && make fclean
			@cd $(MINILIBX_PATH) && make fclean
			@printf "$(UNDER_LINE)$(BOLD)$(LIGHT_CYAN)$(NAME)$(NO_COLOR) $(RED)deleted$(NO_COLOR)\n"

re: 		fclean all

norm:
			@$(NORM) $(SRCS) $(HEADER)
			@cd $(LIBFT_PATH) && make norm
			@cd $(FT_PRINTF_PATH) && make norm

################
##   COLORS   ##
################

UNDER_LINE	= \033[4m
BOLD	 	= \033[1m

NO_COLOR 	= \033[0m
BLACK	 	= \033[0;30m
RED 	 	= \033[0;31m
GREEN 	 	= \033[0;32m
BROWN 	 	= \033[0;33m
BLUE 		= \033[0;34m
PURPLE 	 	= \033[0;35m
CYAN 	 	= \033[0;36m
LIGHT_GRAY	= \033[0;37m

DARK_GRAY	= \033[1;30m
LIGHT_RED	= \033[1;31m
LIGHT_GREEN	= \033[1;32m
YELLOW 		= \033[1;33m
LIGHT_BLUE	= \033[1;34m
LIGHT_PURPLE= \033[1;35m
LIGHT_CYAN	= \033[1;36m
WHITE 		= \033[1;37m

.PHONY:	all clean fclean re 
.PHONY: make_lib make_printf make_mlx norm
.PHONY: SRCS NAME LIBFT_PATH FT_PRINTF_PATH MINILIBX_PATH HEADER CC CFLAGS OBJS_DIR OBJS NORM
.PHONY: UNDER_LINE BOLD NO_COLOR BLACK RED GREEN BROWN BLUE PURPLE CYAN LIGHT_GRAY DARK_GRAY LIGHT_RED LIGHT_GREEN YELLOW LIGTH_BLUE LIGHT_PURPLE LIGHT_CYAN WHITE
