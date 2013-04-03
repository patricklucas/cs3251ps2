.PHONY: all
all: part1 part2 part3

.PHONY: part1
part1: part1_server part1_client

part1_server: part1_server.c
	gcc -o $@ $^

part1_client: part1_client.c
	gcc -o $@ $^

.PHONY: part2
part2: part2_server part2_client

part2_server: part2_server.c
	gcc -o $@ $^

part2_client: part2_client.c
	gcc -o $@ $^

.PHONY: part3
part3: part3_server

part3_server: part3_server.c
	gcc -o $@ $^

.PHONY: clean
clean:
	rm -rf part1_server part1_client
	rm -rf part2_server part2_client
	rm -rf part3_server
