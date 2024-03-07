#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    int num;

    // Crea el socket del servidor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Configurar opciones del socket
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Vincular el socket al puerto 8080 y a la dirección 127.0.0.1
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Escucha para nuevos datos 
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Acepta la nueva conexion, si es mayor que 0
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Procesamiento de la conexión
    while (1) {
        valread = read(new_socket, &num, sizeof(int));
        if (valread < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        if (num == 0) {
//si el numero es 0 sale del bucle
            printf("Cliente ha enviado 0, terminando...\n");
            break;
        }
        //valor de num incrementado mas 1 	
        num++;
        printf("Cliente ha enviado: %d, servidor responde: %d\n", num - 1, num);
        if (send(new_socket, &num, sizeof(int), 0) != sizeof(int)) {
            perror("send");
            exit(EXIT_FAILURE);
        }
    }

    // Se cierra el socket
    close(new_socket);
    close(server_fd);
    return 0;
}
