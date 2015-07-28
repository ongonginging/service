
.PHONY: client server

client:
	make -f client/Makefile

server:
	make -f server/Makefile

