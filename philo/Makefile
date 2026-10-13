CC = cc -Wall -Wextra -Werror

SRC_MAIN = $(wildcard main.c)
SRC = $(wildcard philo/*.c)
OBJ = $(patsubst %.c, obj/%.o, $(SRC) $(SRC_MAIN))

all: out/main.out

out/main.out: obj/main.o lib/philo.a
	@mkdir -p $(@D)
	$(CC) -o $@ $^ -L. lib/philo.a

lib/philo.a: $(OBJ)
	@mkdir -p $(@D)
	ar rcs $@ $^

obj/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $< -o $@

fclean: clean
	rm -r -f out/

clean:
	rm -r -f lib/
	rm -r -f obj/

re: fclean
	make all

.PHONY: all clean fclean re

