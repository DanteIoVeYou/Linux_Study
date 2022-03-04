CC=gcc
all: server client
server: server.c
	$(CC) -o $@ $^
client: client.c
	$(CC) -o $@ $^
.PHONY: clean
clean: 
	rm -f server client
