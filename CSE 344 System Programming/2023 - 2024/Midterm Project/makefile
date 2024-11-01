all: server client

server: server_side/neHosServer.c
	@gcc $^ -o server_side/neHosServer.out -lrt

client: client_side/neHosClient.c
	@gcc $^ -o client_side/neHosClient.out -lrt
