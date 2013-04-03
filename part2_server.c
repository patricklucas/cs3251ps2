#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int part2_server(const char* addr, const int port) {
    int sock;
    const int opt = 1;
    struct sockaddr_in sa;
    int client;

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
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

    {
        char buf[9216];
        int count;

        while ((count = recv(sock, buf, sizeof(buf), 0)) > 0) {
            write(STDOUT_FILENO, buf, count);
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

    return part2_server(addr, port);
}
