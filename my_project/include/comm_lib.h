#ifndef COMM_LIB_H
#define COMM_LIB_H

int server_connect(const char *fifo_path);
int client_connect(const char *server_fifo, const char *client_fifo);
int send_message(int fd, const char *message);
int receive_message(int fd, char *buffer, size_t buffer_size);
void close_connection(int fd);

#endif
