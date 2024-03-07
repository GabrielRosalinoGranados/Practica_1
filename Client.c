#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PUERTO 12345
#define TAM_BUFFER 1024

int main() {
    int sockfd; // Descriptor del socket
    struct sockaddr_in servidor; // Estructura para almacenar la dirección del servidor
    char mensaje[TAM_BUFFER]; // Buffer para mensajes definiendo el tamaño como 1024

    // Creacion del socket y comprobacion
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    // Especifica la dirección del servidor
    servidor.sin_family = AF_INET;
    servidor.sin_addr.s_addr = inet_addr("127.0.0.1"); // Dirección IP del servidor (localhost)
    servidor.sin_port = htons(PUERTO); // Puerto del servidor

    // Conecta al servidor
    if (connect(sockfd, (struct sockaddr *)&servidor, sizeof(servidor)) != 0) {
        perror("Error al conectar al servidor");
        exit(EXIT_FAILURE);
    }

    // Envia mensaje Hola al servidor, comprueba si ha sido enviado el mensaje
    strcpy(mensaje, "Hola");
    if (send(sockfd, mensaje, strlen(mensaje), 0) == -1) {
        perror("Error al enviar mensaje al servidor");
        exit(EXIT_FAILURE);
    }

    // Recibir respuesta del servidor
    if (recv(sockfd, mensaje, TAM_BUFFER, 0) == -1) {
        perror("Error al recibir respuesta del servidor");
        exit(EXIT_FAILURE);
    }
    printf("Respuesta del servidor: %s\n", mensaje);

    // Cerrar el socket
    close(sockfd);

    return 0;
}
