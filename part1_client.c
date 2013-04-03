#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int part1_client(const char* addr, const int port) {
    int sock;
    struct sockaddr_in sa;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("a\n");
        return -1;
    }

    memset(&sa, 0, sizeof(struct sockaddr_in));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(addr);
    sa.sin_port = htons(port);

    if ((connect(sock, (struct sockaddr *)&sa, sizeof(struct sockaddr_in))) == -1) {
        close(sock);
        printf("b\n");
        return -1;
    }

    {
        char buf[4096];
        int count;

        while ((count = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
            send(sock, buf, count, 0);
        }
    }

    close(sock);
    return 0;
}

int main(int argc, char *argv[]) {
    char *addr;
    int port;

    if (argc >= 3) {
        addr = argv[1];
        port = atoi(argv[2]);
    } else if (argc == 2) {
        addr = "0.0.0.0";
        port = atoi(argv[1]);
    } else {
        addr = "0.0.0.0";
        port = 1234;
    }

    return part1_client(addr, port);
}
