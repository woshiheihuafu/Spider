.PHONY:Spider clean distclean install

CC=gcc
INCLUDE_PATH=../include/
LIBRARY_PATH=../library/
INSTALL_PATH=/usr/bin/
LDFLAGS=-lssl -lcrypto
CFLAGS=-I$(INCLUDE_PATH) -g -Wall -c
CPPFLAGS=
SFILE=$(wildcard *.c)
DFILE=$(patsubst %.c,%.o,$(SFILE))
TARGET=Spider
$(TARGET):$(DFILE)
	$(CC) $^ $(LDFLAGS) -o $@

%.o:%.c
	$(CC) $(CFLAGS) $<

clean:
	rm $(DFILE) -rf
	rm $(TARGET) -rf
