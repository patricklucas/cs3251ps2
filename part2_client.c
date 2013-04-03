#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int part2_client(const char* addr, const int port) {
    int sock;
    struct sockaddr_in sa;

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        return -1;
    }

    memset(&sa, 0, sizeof(struct sockaddr_in));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(addr);
    sa.sin_port = htons(port);

    {
        char buf[9216];
        int count;

        while ((count = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
            sendto(sock, buf, count, 0, (struct sockaddr*)&sa, sizeof(struct sockaddr));
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

    return part2_client(addr, port);
}
