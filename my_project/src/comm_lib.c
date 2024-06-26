#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "../include/comm_lib.h"

int server_connect(const char *fifo_path) {
    if (mkfifo(fifo_path, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return -1;
    }
    int fd = open(fifo_path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    return fd;
}

int client_connect(const char *server_fifo, const char *client_fifo) {
    if (mkfifo(client_fifo, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return -1;
    }
    int fd = open(server_fifo, O_WRONLY);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    return fd;
}

int send_message(int fd, const char *message) {
    if (write(fd, message, strlen(message) + 1) == -1) {
        perror("write");
        return -1;
    }
    return 0;
}

int receive_message(int fd, char *buffer, size_t buffer_size) {
    if (read(fd, buffer, buffer_size) == -1) {
        perror("read");
        return -1;
    }
    return 0;
}

void close_connection(int fd) {
    close(fd);
}
