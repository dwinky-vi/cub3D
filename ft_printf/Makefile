
SRCS	= \
			ft_utils.c \
			ft_parser.c \
			ft_printf.c  \
			ft_print_c.c \
			ft_print_d.c \
			ft_print_p.c \
			ft_print_s.c \
			ft_print_u.c \
			ft_print_x.c \
			ft_processor.c \
			ft_dec_to_hex.c \
			ft_parser_utils.c \
			ft_print_percent.c \
			ft_creat_new_unit.c \

NAME		= libftprintf.a

LIBFT_PATH	= ./libft

HEADER		= ft_printf.h

CC			= gcc

CFLAGS		= -Wall -Werror -Wextra

OBJS_DIR =		.obj/

OBJS	 = 		$(addprefix $(OBJS_DIR), $(patsubst %.c, %.o, $(SRCS)))

NORM 	= norminette

all:		make_lib $(NAME)

make_lib:
			@$(MAKE) -C $(LIBFT_PATH)
			@cp libft/libft.a $(NAME)

$(NAME): 	$(OBJS)
			@ar rc $(NAME) $?
			@printf "$(GREEN)$(BOLD)$(LIGHT_PURPLE)ft_printf –– [Success compiling]        $(NO_COLOR)\n"

$(OBJS_DIR)%.o:		%.c $(HEADER) libft/.obj/*
					@test -d $(OBJS_DIR) || mkdir $(OBJS_DIR)
					@printf "$(GREEN)$(BOLD)Compilation $(UNDER_LINE)$(YELLOW)$<$(NO_COLOR)  $(BOLD)–– $(RED)[KO]        $(NO_COLOR)\r"
					@$(CC) $(CFLAGS) -c $< -o $@
					@printf "$(GREEN)$(BOLD)Compilation $(UNDER_LINE)$(YELLOW)$<$(NO_COLOR)  $(BOLD)–– $(GREEN)[OK]$(NO_COLOR)\n"

clean:
			@rm -rf $(OBJS) $(BONUS_OBJS)
			@/bin/rm -rf $(OBJS_DIR)
			@cd $(LIBFT_PATH) && make clean

fclean: 	clean
			@rm -rf $(NAME)
			@cd $(LIBFT_PATH) && make fclean
			@printf "$(UNDER_LINE)$(BOLD)$(NAME)$(NO_COLOR)$(LIGHT_RED) deleted$(NO_COLOR)\n"

re: 		fclean all
norm:		
			@$(NORM) $(SRCS) $(HEADER)
			@cd $(LIBFT_PATH) && make norm

.PHONY:	all clean fclean re norm norm_lib
.PHONY: NAME SRCS LIBS LIBFT_PATH CC CFLAGS OBJS OBJS_DIR HEADER NORM
.PHONY: UNDER_LINE BOLD NO_COLOR RED GREEN LIGHT_RED YELLOW LIGHT_PURPLE WHITE

################
##   COLORS   ##
################

UNDER_LINE	= \033[4m
BOLD	 	= \033[1m
NO_COLOR 	= \033[0m
RED 	 	= \033[0;31m
GREEN 	 	= \033[0;32m
LIGHT_RED	= \033[1;31m
YELLOW 		= \033[1;33m
LIGHT_PURPLE= \033[1;35m
WHITE 		= \033[1;37m

# gcc -L. -lftprintf main.c && ./a.out