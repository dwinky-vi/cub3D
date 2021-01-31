
SRCS	= \
		main.c ft_some_utils.c\

NAME		= cub3D

LIBFT_PATH	= ./libft

FT_PRINTF_PATH = ./ft_printf

HEADER		= ft_cub3d.h

CC		= gcc

CFLAGS	= 

# создаём скрытую директорию, в которой будут .o файлы
OBJS_DIR =			.obj

# прописываем (добавляем) путь для каждого .o файла
OBJS	= 			$(addprefix $(OBJS_DIR)/, $(patsubst %.c, %.o, $(SRCS)))

NORM 	=			~/.scripts/colorised_norm.sh

all:		make_lib make_ft_printf $(NAME)

make_lib:
			@cd $(LIBFT_PATH) && make 

make_ft_printf:
			@cd $(FT_PRINTF_PATH) && make 

$(NAME): 	$(OBJS)
			@$(CC) $(CFLAGS) -L./libft -lft -L./ft_printf -lftprintf ./minilibx_opengl_20191021/libmlx.a -framework OpenGL -framework AppKit $? -o $(NAME)
			@printf "$(GREEN)$(BOLD)cub3D –– [Success compiling]        $(NO_COLOR)\n"

$(OBJS_DIR)/%.o:	%.c $(HEADER) libft/.obj/* ft_printf/.obj/*
					@test -d $(OBJS_DIR) || mkdir $(OBJS_DIR)
					@printf "$(GREEN)$(BOLD)Compilation $(YELLOW)$(UNDER_LINE)$<$(NO_COLOR)  $(BOLD)–– $(RED)[KO]        $(NO_COLOR)\r"
					@$(CC) $(CFLAGS) -c $< -o $@
					@printf "$(GREEN)$(BOLD)Compilation $(YELLOW)$(UNDER_LINE)$<$(NO_COLOR)  $(BOLD)–– $(GREEN)[OK]$(NO_COLOR)\n"

clean:
			@rm -rf $(OBJS)
			@/bin/rm -rf $(OBJS_DIR)
			@cd $(LIBFT_PATH) && make clean
			@cd $(FT_PRINTF_PATH) && make clean

fclean: 	clean
			@rm -rf $(NAME)
			@cd $(LIBFT_PATH) && make fclean
			@cd $(FT_PRINTF_PATH) && make fclean
			@printf "$(UNDER_LINE)$(NAME) $(RED)deleted$(NO_COLOR)\n"

norm:		
			@$(NORM) $(SRCS) $(HEADER)
			@cd $(LIBFT_PATH) && make norm
			@cd $(FT_PRINTF_PATH) && make norm

re: 		fclean all

.PHONY:	all clean fclean re norm
.PHONY: SRCS SRCS CC CFLAGS OBJS OBJS_DIR HEADER NORM


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
