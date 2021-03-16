

SRCS	= \
		main.c ft_free.c \
		ft_parser1.c    ft_parser2.c ft_parser3.c ft_parser4.c\
		ft_validator1.c ft_validator2.c \
		ft_raycast1.c   ft_raycast2.c ft_raycast3.c \
		ft_some_utils.c\
		ft_spritecast1.c ft_spritecast2.c \
		ft_steps1.c ft_steps2.c \
		ft_hooks.c ft_my_mlx.c ft_sort.c\

NAME		= cub3D

LIBFT_PATH		= ./libft

FT_PRINTF_PATH	= ./ft_printf

MINILIBX_C_PATH	= ./minilibx_c

MINILIBX_SWIFT_PATH	= ./minilibx_swift

HEADER		= head_cub3d.h

CC		= gcc

CFLAGS	= -g

# создаём скрытую директорию, в которой будут .o файлы
OBJS_DIR =			.obj

# VPATH = *перечесление папок*





# прописываем (добавляем) путь для каждого .o файла
OBJS	= 			$(addprefix $(OBJS_DIR)/, $(patsubst %.c, %.o, $(SRCS)))

NORM 	=			~/.scripts/colorised_norm.sh

all:		make_mlx_c make_lib make_printf $(NAME)

make_lib:
			@${MAKE} -C libft

make_printf:
			@${MAKE} -C ft_printf

make_mlx_c:
			@${MAKE} -C minilibx_c
			@${MAKE} -C minilibx_swift

$(NAME): 	$(OBJS)
			@cp ./minilibx_swift/libmlx.dylib .
			@$(CC) $(CFLAGS) $(OBJS) -I $(HEADER) -L./libft -lft -L./ft_printf -lftprintf $(MINILIBX_C_PATH)/libmlx.a libmlx.dylib -framework OpenGL -framework AppKit -o $(NAME)
			@printf "$(LIGHT_PURPLE)$(BOLD)cub3D $(NO_COLOR)–– $(LIGHT_PURPLE)$(BOLD)[Success compiling]        $(NO_COLOR)\n"

$(OBJS_DIR)/%.o:	%.c $(HEADER) head_structs.h head_parser.h libft/libft.a
					@test -d $(OBJS_DIR) || mkdir $(OBJS_DIR)
					@printf "$(GREEN)$(BOLD)Compilation $(UNDER_LINE)$(YELLOW)$<$(NO_COLOR)  $(BOLD)–– $(RED)[KO]        $(NO_COLOR)\r"
					@$(CC) $(CFLAGS) -I $(HEADER) -I head_structs.h -I head_parser.h -I $(MINILIBX_C_PATH)/mlx.h -I $(MINILIBX_SWIFT_PATH)/mlx.h -c $< -o $@
					@printf "$(GREEN)$(BOLD)Compilation $(UNDER_LINE)$(YELLOW)$<$(NO_COLOR)  $(BOLD)–– $(GREEN)[OK]$(NO_COLOR)\n"

clean:
			@rm -rf $(OBJS)
			@/bin/rm -rf $(OBJS_DIR)
			@cd $(LIBFT_PATH) && make clean
			@cd $(FT_PRINTF_PATH) && make clean
			@cd $(MINILIBX_C_PATH) && make clean
			@cd $(MINILIBX_SWIFT_PATH) && make clean

fclean: 	clean
			@rm -rf $(NAME)
			@rm -rf libmlx.dylib
#			@rm -rf libmlx.a
			@cd $(LIBFT_PATH) && make fclean
			@cd $(FT_PRINTF_PATH) && make fclean
			@cd $(MINILIBX_C_PATH) && make fclean
			@cd $(MINILIBX_SWIFT_PATH) && make fclean
			@printf "$(UNDER_LINE)$(BOLD)$(NAME)$(NO_COLOR) $(LIGHT_RED)deleted$(NO_COLOR)\n"

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
.PHONY: make_lib make_printf make_mlx_c norm
.PHONY: SRCS NAME LIBFT_PATH FT_PRINTF_PATH MINILIBX_C_PATH MINILIBX_SWIFT_PATH HEADER CC CFLAGS OBJS_DIR OBJS NORM
.PHONY: UNDER_LINE BOLD NO_COLOR BLACK RED GREEN BROWN BLUE PURPLE CYAN LIGHT_GRAY DARK_GRAY LIGHT_RED LIGHT_GREEN YELLOW LIGTH_BLUE LIGHT_PURPLE LIGHT_CYAN WHITE
