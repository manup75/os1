#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/utsname.h>

void process_system_calls();
void file_system_calls();
void communication_system_calls();
void information_system_calls();

int main() {
    int choice;

    while (1) {
        printf("\n--- System Call Menu ---\n");
        printf("1. Process Related\n");
        printf("2. File Related\n");
        printf("3. Communication Related\n");
        printf("4. Information Related\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: process_system_calls(); break;
            case 2: file_system_calls(); break;
            case 3: communication_system_calls(); break;
            case 4: information_system_calls(); break;
            case 5: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

void process_system_calls() {
    int choice;
    pid_t pid;

    printf("\n--- Process Related Calls ---\n");
    printf("1. Fork\n2. Exit\n3. Wait\n4. Kill\n5. Exec\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            pid = fork();
            if (pid == 0) printf("Child PID: %d\n", getpid());
            else { printf("Parent PID: %d\n", getpid()); wait(NULL); }
            break;
        case 2:
            printf("Process will exit now.\n");
            exit(0);
            break;
        case 3:
            pid = fork();
            if (pid == 0) { sleep(2); exit(0); }
            else { printf("Waiting for child...\n"); wait(NULL); }
            break;
        case 4:
            pid = fork();
            if (pid == 0) while (1); // Infinite loop
            else { sleep(1); printf("Killing child process...\n"); kill(pid, SIGKILL); wait(NULL); }
            break;
        case 5:
            if (fork() == 0) execl("/bin/ls", "ls", NULL);
            else wait(NULL);
            break;
        default: printf("Invalid choice!\n");
    }
}

void file_system_calls() {
    int choice;
    int fd;
    char buffer[100];

    printf("\n--- File Related Calls ---\n");
    printf("1. Open/Read/Write/Close\n2. Link/Unlink\n3. Stat\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fd = open("testfile.txt", O_CREAT | O_RDWR, 0644);
            if (fd == -1) { perror("Error opening file"); return; }
            write(fd, "Hello, World!\n", 14);
            lseek(fd, 0, SEEK_SET);
            read(fd, buffer, sizeof(buffer));
            printf("File content: %s\n", buffer);
            close(fd);
            break;
        case 2:
            link("testfile.txt", "testfile_link.txt");
            printf("Link created.\n");
            unlink("testfile_link.txt");
            printf("Link removed.\n");
            break;
        case 3: {
            struct stat fileStat;
            if (stat("testfile.txt", &fileStat) < 0) { perror("Error getting stats"); return; }
            printf("File Size: %ld bytes\n", fileStat.st_size);
            printf("File Permissions: %o\n", fileStat.st_mode & 0777);
            break;
        }
        default: printf("Invalid choice!\n");
    }
}

void communication_system_calls() {
    int choice;
    printf("1. Pipe\n2. FIFO\nChoose an option: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        int fd[2];
        pid_t pid;
        char buffer[100];

        if (pipe(fd) == -1) {
            perror("Pipe failed");
            return;
        }

        pid = fork();
        if (pid == 0) {
            close(fd[0]); 
            write(fd[1], "Message via Pipe", 16);
            close(fd[1]);
            exit(0);
        } else {
            close(fd[1]); 
            int bytesRead = read(fd[0], buffer, sizeof(buffer));
            buffer[bytesRead] = '\0'; 
            printf("Received: %s\n", buffer);
            close(fd[0]);
            wait(NULL);
        }
    } else if (choice == 2) {
        char *fifo = "/tmp/myfifo";
        mkfifo(fifo, 0666);

        if (fork() == 0) {
            int fd = open(fifo, O_WRONLY);
            write(fd, "Message via FIFO", 16);
            close(fd);
            exit(0);
        } else {
            char buffer[100];
            int fd = open(fifo, O_RDONLY);
            int bytesRead = read(fd, buffer, sizeof(buffer));
            buffer[bytesRead] = '\0'; 
            printf("Received: %s\n", buffer);
            close(fd);
            wait(NULL);
        }

        unlink(fifo);
    } else {
        printf("Invalid option!\n");
    }
}

void information_system_calls() {
    int choice;
    struct utsname buffer;

    printf("\n--- Information Related Calls ---\n");
    printf("1. Get PID\n2. Get PPID\n3. Uname\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: printf("PID: %d\n", getpid()); break;
        case 2: printf("PPID: %d\n", getppid()); break;
        case 3:
            if (uname(&buffer) < 0) { perror("Uname failed"); return; }
            printf("System: %s\nNode: %s\nRelease: %s\nVersion: %s\nMachine: %s\n",
                   buffer.sysname, buffer.nodename, buffer.release, buffer.version, buffer.machine);
            break;
        default: printf("Invalid choice!\n");
    }
}
