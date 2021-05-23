DIR := /home/dan/.local/share/heb12/
CC := tcc
CFLAGS := -Wall -Wextra -Wpedantic -O2

# Add include directory for BibleSearch
CFLAGS += -I.

FILES := biblec/biblec.c fbrp/fbrp.c biblesearch/bsearch.c libheb12/*.c main.c

default: compile
demo: compile test

msdos: msdosconfig compile
msdosconfig:
	@i586-pc-msdosdjgpp-gcc $(CFLAGS) -O3 $(FILES)
	
help:
	@echo "For now, default settings are compiled with the program."
	@echo "make				Default, compile heb12cli"
	@echo "make demo		Runs John 3 16"
	@echo "make setup		Install bibles"
	@echo "make path		Add heb12 to ~/.bashrc"

compile:
	$(CC) $(CFLAGS) $(FILES) -o heb12

test:
	@./heb12 -l -r "John 3 16"

setup:
	@wget http://api.heb12.com/translations/biblec/web.i -P $(DIR)
	@wget http://api.heb12.com/translations/biblec/web.t -P $(DIR)

path:
	@echo "export PATH=\\$PATH:$(PWD)" >> ~/.bashrc
