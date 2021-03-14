

NAME	= libmlx.a

SRC	= \
	mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m \
	mlx_xpm.c mlx_int_str_to_wordtab.c

SRC	+= mlx_png.c mlx_mouse.m

OBJ1	= $(SRC:.c=.o)

OBJ		= $(OBJ1:.m=.o)

CFLAGS	+= -O2

# add to match string put with X11 in size and position
CFLAGS	+= -DSTRINGPUTX11

all: $(NAME)

$(NAME):	$(OBJ)
		@ar -r $(NAME) $(OBJ)
		@ranlib $(NAME)
		@printf "$(LIGHT_PURPLE)$(BOLD)$(NAME) –– [Success compiling] $(NO_COLOR)\n\n"

clean:
		@rm -f $(OBJ) *~
		@rm -f mlx_app

fclean: clean
		@rm -f $(NAME)
		@printf "$(UNDER_LINE)$(BOLD)$(NAME)$(NO_COLOR)  $(LIGHT_RED)deleted$(NO_COLOR)\n"

re: fclean all

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