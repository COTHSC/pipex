
NAME = pipex

SRCS = srcs/pipex.c \
	  srcs/pipex_utils.c \
	  srcs/pipes_and_redirects.c 

OBJS = $(SRCS:.c=.o)

HEADERS = includes

CC = clang

CFLAGS = -Wall -Wextra -Werror -g

all : $(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C ./libft/
	$(CC) -o $(NAME) $(OBJS) ./libft/libft.a

%.o : %.c
	$(CC) $(CFLAGS) -g  -I ${HEADERS} -o $@ -c $<

clean :
	$(MAKE) clean -C ./libft
	rm -f $(OBJS)

fclean : clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME)

re : fclean all
