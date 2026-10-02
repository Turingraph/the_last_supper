CC = cc -Wall -Wextra -Werror

SRC_roulette = $(wildcard roulette/*.c)
OBJ_roulette = $(patsubst %.c, obj/%.o, $(SRC_roulette))
OUT_roulette = $(patsubst %.c, out/%.out, $(SRC_roulette))

SRC_duel = $(wildcard duel/*.c)
OBJ_duel = $(patsubst %.c, obj/%.o, $(SRC_duel))
OUT_duel = $(patsubst %.c, out/%.out, $(SRC_duel))

SRC_vacation = $(wildcard vacation/*.c)
OBJ_vacation = $(patsubst %.c, obj/%.o, $(SRC_vacation))
OUT_vacation = $(patsubst %.c, out/%.out, $(SRC_vacation))

all: $(OUT_roulette) $(OUT_duel) $(OUT_vacation)

out/%.out: obj/%.o
	@mkdir -p $(@D)
	$(CC) -o $@ $^ -L. ../src/lib/utils.a

# *** create object files. ***
# https://stackoverflow.com/questions/1950926/create-directories-using-make-file
obj/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $< -o $@

clean:
	rm -r -f out/
	rm -r -f obj/

re: clean
	make all

.PHONY: all clean re
