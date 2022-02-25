.PHONY: all
all: client server

client: client.c
	gcc -o $@ $^

srever: server.c
	gcc -o $@ $^
.PHONY: clean
clean:
	rm -f client server
