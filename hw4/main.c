#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>


#define MAX_BUFFER_SIZE 1024

char* buffer[MAX_BUFFER_SIZE];


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Expected 2 argumets!\n");
        exit(1);
    }

    int file_read;
    file_read = open(argv[1], O_RDONLY);
    if (file_read < 0) {
        printf("Error while opening read file!\n");
        exit(1);
    }

    int file_write;
    file_write = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (file_write < 0) {
        printf("Error while opening write file!\n");
        close(file_read);
        exit(1);
    }

    int text_size = read(file_read, buffer, sizeof(buffer));
    if (text_size < 0) {
        printf("Error while reading file!\n");
        close(file_read);
        close(file_write);
        exit(1);
    }
    int write_flag = write(file_write, buffer, text_size);
    if (write_flag < 0) {
        printf("Error while writing file!\n");
        close(file_read);
        close(file_write);
        exit(1);
    }

    close(file_read);
    close(file_write);
    return 0;
}
