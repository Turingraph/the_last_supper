
#-----------------------------------------------------------------------------------------------
# *** command ***

CC = cc -Wall -Wextra -Werror

#-----------------------------------------------------------------------------------------------
# https://stackoverflow.com/questions/9488256/use-directory-path-of-target-in-list-of-prerequisites-in-makefile
# https://www.gnu.org/software/make/manual/make.html#Secondary-Expansion
.SECONDEXPANSION:

# *** library ***
LIBRARY = $(patsubst %, lib/%.a, utils)

# *** atom src ***
SRC_utils = $(wildcard utils/*.c)

#-----------------------------------------------------------------------------------------------

# *** elementary obj ***
OBJ_utils = $(patsubst %.c, obj/%.o, $(SRC_utils))

#-----------------------------------------------------------------------------------------------
# *** create library ***

all: $(LIBRARY)

# ChatGPT recommended me this solution.
# The takes away is reading the functions for files name section of Makefile manual first
# (a.k.a. https://ftp.gnu.org/old-gnu/Manuals/make-3.79.1/html_node/make_79.html )
# if you have to manipulating the string of the files/folders name according to correct 
# format like this, for example you might want to split string as arrays of string,
# with `,` or `/` as the separators.
lib/%.a: $$(OBJ_$$(notdir $$(basename $$@)))
	@mkdir -p $(@D)
	ar rcs $@ $^

# *** create object files. ***
# https://stackoverflow.com/questions/1950926/create-directories-using-make-file
obj/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $< -o $@

#-----------------------------------------------------------------------------------------------
# *** clean ***
# https://askubuntu.com/questions/802996/how-to-remove-directory-with-all-of-its-contents
clean:
	rm -r -f lib/
	rm -r -f obj/

# Lol, both Makefile tutorial and Suisei already cover .PHONY
# https://youtu.be/N029UUlH1Dc?si=8PragRfDm3MzFOBc
.PHONY: all clean