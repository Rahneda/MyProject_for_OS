#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../include/comm_lib.h"

#define FIFO_SERVER "/tmp/myserver.fifo"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <client_fifo>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *client_fifo = argv[1];
    int server_fd = client_connect(FIFO_SERVER, client_fifo);
    if (server_fd == -1) {
        exit(EXIT_FAILURE);
    }

    char command[256];
    while (fgets(command, sizeof(command), stdin) != NULL) {
        send_message(server_fd, command);

        char buffer[1024];
        int client_fd = open(client_fifo, O_RDONLY);
        if (client_fd != -1) {
            receive_message(client_fd, buffer, sizeof(buffer));
            printf("Response: %s\n", buffer);
            close_connection(client_fd);
        }
    }

    close_connection(server_fd);
    unlink(client_fifo);

    return 0;
}
