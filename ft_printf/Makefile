
SRCS	= \
			t_unit.c \
			ft_utils.c \
			ft_parser.c \
			ft_printf.c \
			ft_print_c.c \
			ft_print_d.c \
			ft_print_p.c \
			ft_print_s.c \
			ft_print_u.c \
			ft_print_x.c \
			ft_processor.c \
			ft_dec_to_hex.c \
			ft_parser_utils.c \
			ft_print_percent.c

NAME		= libftprintf.a

LIBFT_PATH	= ../libft

HEADER		= ft_printf.h

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

# создаём скрытую директорию, в которой будут .o файлы
OBJS_DIR =		.obj/

# прописываем (добавляем) путь для каждого .o файла
OBJS	 = 		$(addprefix $(OBJS_DIR), $(patsubst %.c, %.o, $(SRCS)))

NORM 	= norminette

all:		make_lib $(NAME)

make_lib:
			@cp  $(LIBFT_PATH)/libft.a $(NAME)

$(NAME): 	$(OBJS)
			@ar rc $(NAME) $?
			@printf "$(GREEN)$(BOLD)ft_printf –– [Success compiling] $(NO_COLOR)\n"

$(OBJS_DIR)%.o:		%.c $(HEADER) $(LIBFT_PATH)/.obj/*
					@test -d $(OBJS_DIR) || mkdir $(OBJS_DIR)
					@printf "$(GREEN)$(BOLD)Compilation $(YELLOW)$(UNDER_LINE)$<$(NO_COLOR)  $(BOLD)–– $(RED)[KO]        $(NO_COLOR)\r"
					@$(CC) $(CFLAGS) -c $< -o $@
					@printf "$(GREEN)$(BOLD)Compilation $(YELLOW)$(UNDER_LINE)$<$(NO_COLOR)  $(BOLD)–– $(GREEN)[OK]$(NO_COLOR)\n"

clean:
			@rm -rf $(OBJS) $(BONUS_OBJS)
			@/bin/rm -rf $(OBJS_DIR)

fclean: 	clean
			@rm -rf $(NAME)
			@echo "$(RED)$(UNDER_LINE)$(NAME) deleted.$(NO_COLOR)"

re: 		fclean all

.PHONY: $(NAME)	all bonus clean fclean re
.PHONY: SRCS BONUS_SRCS LIBS LIBFT_PATH CC CFLAGS OBJS BONUS_OBJS OBJS_DIR CRT HEADER NORM


################
##   COLORS   ##
################

UNDER_LINE	= \033[4m
BOLD	 	= \033[1m
CLEAR		= \033[0;0m

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

run:		all
			@echo "$(YELLOW)gcc -Wall -Werror -Wextra -L. -lftprintf main.c && ./a.out$(NO_COLOR)"
			@gcc $(CFLAGS) -L. -lftprintf main.c && ./a.out
			@rm a.out

norm:		
			@$(NORM) $(SRCS) $(HEADER)
			@cd $(LIBFT_PATH) && make norm

.PHONY:
		run norm norm_lib
