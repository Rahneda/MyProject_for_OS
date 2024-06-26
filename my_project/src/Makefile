CC = gcc
CFLAGS = -I../include -fPIC
LDFLAGS = -shared

all: libcomm.so server client

libcomm.so: comm_lib.o
    $(CC) $(LDFLAGS) -o libcomm.so comm_lib.o

comm_lib.o: comm_lib.c
    $(CC) $(CFLAGS) -c comm_lib.c

server: server.o libcomm.so
    $(CC) -o server server.o -L. -lcomm

server.o: server.c
    $(CC) $(CFLAGS) -c server.c

client: client.o libcomm.so
    $(CC) -o client client.o -L. -lcomm

client.o: client.c
    $(CC) $(CFLAGS) -c client.c

clean:
    rm -f *.o server client libcomm.so
    rm -f /tmp/myserver.fifo /tmp/myclient.fifo
