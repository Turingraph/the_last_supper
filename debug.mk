
all:
	$(MAKE) -C src -f debug.mk
	$(MAKE) -C unit_test -f Makefile

clean:
	$(MAKE) -C src -f debug.mk clean
	$(MAKE) -C unit_test -f Makefile clean

re:
	make -f debug.mk clean
	make -f debug.mk all

.PHONY: all clean re

