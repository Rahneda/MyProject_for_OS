#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "../include/comm_lib.h"

#define FIFO_SERVER "/tmp/myserver.fifo"

typedef struct {
    char key[256];
    char value[256];
} KeyValue;

KeyValue kv_store[100];
int kv_count = 0;

void handle_signal(int sig) {
    unlink(FIFO_SERVER);
    exit(0);
}

void set_value(const char *key, const char *value) {
    for (int i = 0; i < kv_count; i++) {
        if (strcmp(kv_store[i].key, key) == 0) {
            strcpy(kv_store[i].value, value);
            return;
        }
    }
    strcpy(kv_store[kv_count].key, key);
    strcpy(kv_store[kv_count].value, value);
    kv_count++;
}

char* get_value(const char *key) {
    for (int i = 0; i < kv_count; i++) {
        if (strcmp(kv_store[i].key, key) == 0) {
            return kv_store[i].value;
        }
    }
    return NULL;
}

int main() {
    int server_fd, client_fd;
    char buffer[1024];

    signal(SIGTERM, handle_signal);

    server_fd = server_connect(FIFO_SERVER);
    if (server_fd == -1) {
        exit(EXIT_FAILURE);
    }

    while (1) {
        if (receive_message(server_fd, buffer, sizeof(buffer)) == -1) {
            continue;
        }

        char command[16], key[256], value[256];
        sscanf(buffer, "%s %s %s", command, key, value);

        if (strcmp(command, "set") == 0) {
            set_value(key, value);
        } else if (strcmp(command, "get") == 0) {
            char *result = get_value(key);
            if (result != NULL) {
                client_fd = open(key, O_WRONLY);
                if (client_fd != -1) {
                    send_message(client_fd, result);
                    close_connection(client_fd);
                }
            }
        }
    }

    close_connection(server_fd);
    return 0;
}
