
NAME = pipex

SRCS = srcs/pipex.c 

OBJS = $(SRCS:.c=.o)

HEADERS = includes

CC = clang

CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C ./libft/
	$(CC) -o $(NAME) $(OBJS) ./libft/libft.a

%.o : %.c
	$(CC) ${CFLAGS} -I ${HEADERS} -o $@ -c $<

clean :
	$(MAKE) clean -C ./libft
	rm -f $(OBJS)

fclean : clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME)

re : fclean all
