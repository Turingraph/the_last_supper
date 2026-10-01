CC = cc -Wall -Wextra -Werror
SRC_roulette = $(wildcard roulette/*.c)

OBJ_roulette = $(patsubst %.c, obj/%.o, $(SRC_roulette))
OUT_roulette = $(patsubst %.c, out/%.out, $(SRC_roulette))

all: $(OUT_roulette)

$(OUT_roulette): out/%.out: obj/%.o
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
