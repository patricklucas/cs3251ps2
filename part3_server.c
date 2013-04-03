#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int part1_server(const char* addr, const int port) {
    int sock;
    const int opt = 1;
    struct sockaddr_in sa;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        return -1;
    }

    if ((setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) == -1) {
        close(sock);
        return -1;
    }

    memset(&sa, 0, sizeof(struct sockaddr_in));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(addr);
    sa.sin_port = htons(port);

    if (bind(sock, (struct sockaddr *)&sa, sizeof(struct sockaddr_in)) == -1) {
        close(sock);
        return -1;
    }

    if ((listen(sock, 1)) == -1) {
        close(sock);
        return -1;
    }

    {
        int client;
        char buf[4096];
        int count;

        if ((client = accept(sock, (struct sockaddr*)NULL, NULL)) == -1) {
            close(sock);
            return -1;
        }

        while ((count = read(client, buf, sizeof(buf) - 1)) > 0) {
            write(STDOUT_FILENO, buf, count);
        }

        close(client);
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

    return part1_server(addr, port);
}
