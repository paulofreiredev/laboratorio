#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

int main() {
    int serial_port = open("/dev/ttyUSB0", O_RDONLY);

    if (serial_port < 0) {
        perror("Erro ao abrir porta");
        return 1;
    }

    struct termios tty;

    tcgetattr(serial_port, &tty);

    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);

    tcsetattr(serial_port, TCSANOW, &tty);

    char buffer[256];

    while (1) {
        int n = read(serial_port, buffer, sizeof(buffer)-1);

        if (n > 0) {
            buffer[n] = '\0';
            printf("Recebido: %s", buffer);
        }
    }

    close(serial_port);

    return 0;
}