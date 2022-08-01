CC?=gcc
CFLAGS?=-O2 -Wall -Wextra -g -lm
DESTDIR?=$(HOME)/.local/bin

PROGRAMS=hello xor striputf8 utf8codepoints nomoji fantasynamegen decolor passwdgen

SUFFIXES: .sh .py .c

all: $(PROGRAMS)

install: $(PROGRAMS)
	find -maxdepth 1 -executable -type f | xargs -i{} cp {} $(DESTDIR)/{}
%:%.py
	cp $< $@
	chmod a+x $@

%:%.sh
	cp $< $@
	chmod a+x $@

%:%.c
	$(CC) $< -o $@ -std=gnu99 $(CFLAGS)

clean:
	rm $(PROGRAMS)
