#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <string.h>


#define BUFFER_SIZE 1024
#define NUM_MESSAGES 10

char buffer[BUFFER_SIZE];


int main() {
    int pipe_fd[2];
    if (pipe(pipe_fd) < 0) {
        printf("Got error while creating pipe!\n");
        exit(1);
    }

    sem_t* sem_p_w = sem_open("sem_parent_write", O_CREAT, 0644, 1);
    sem_t* sem_p_r = sem_open("sem_parent_read", O_CREAT, 0644, 0);
    sem_t* sem_c_r = sem_open("sem_child_read", O_CREAT, 0644, 0);
    if (sem_p_w == SEM_FAILED || sem_p_r == SEM_FAILED || sem_c_r == SEM_FAILED) {
        printf("Got error while creating semf's\n");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == 0) {
        for (int i = 0; i < NUM_MESSAGES; ++i) {
            sem_wait(sem_c_r);

            read(pipe_fd[0], buffer, BUFFER_SIZE);
            printf("Child received message: %s\n", buffer);

            sprintf(buffer, "Message %d from child to parent!", i);
            write(pipe_fd[1], buffer, BUFFER_SIZE);
            sem_post(sem_p_r);
        }
    } else {
        for (int i = 0; i < NUM_MESSAGES; ++i) {
            sprintf(buffer, "Message %d from parent to child!", i);
            write(pipe_fd[1], buffer, BUFFER_SIZE);

            sem_post(sem_c_r);
            sem_wait(sem_p_r);

            read(pipe_fd[0], buffer, BUFFER_SIZE);
            printf("Parent received message: %s\n", buffer);
        }
        wait(NULL);
    }

    sem_close(sem_p_r);
    sem_close(sem_p_w);
    sem_close(sem_c_r);
    sem_unlink("sem_parent_read");
    sem_unlink("sem_parent_write");
    sem_unlink("sem_child_read");
    return 0;
}
