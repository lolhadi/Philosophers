
CC = cc
CFLAGS = -Wall -Wextra -Werror -g 

OBJS_DIR = objs
SRCS_FILES = main utils init thread action action2

OBJS = $(addprefix $(OBJS_DIR)/, $(addsuffix .o, $(SRCS_FILES)))

NAME = philo

all : $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@ -lpthread

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -rf $(OBJS_DIR) $(NAME)

re: fclean all

.PHONY: all clean fclean re
