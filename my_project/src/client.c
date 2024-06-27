#include <stdio.h>
#include <string.h>
#include <unistd.h> // для `write` и `perror`

// Пример функции send_message
ssize_t send_message(int fd, const char *message, size_t length) {
    return write(fd, message, length);
}

int main() {
    int fd = 1; // Файловый дескриптор для вывода в stdout
    char message[256] = "Hello, server!";
    
    if (send_message(fd, message, strlen(message)) == -1) {
        perror("send_message");
    } else {
        printf("Message sent: %s\n", message);
    }

    return 0;
}
