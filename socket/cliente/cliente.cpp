#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // Crear un socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    if (clientSocket == -1) {
        std::cerr << "Error al crear el socket" << std::endl;
        return -1;
    }

    // Configurar la dirección del servidor al que nos conectaremos
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // Cambia esto a la IP del servidor

    // Conectarse al servidor
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error al intentar conectarse al servidor" << std::endl;
        close(clientSocket);
        return -1;
    }

    // Enviar datos al servidor
    const char* message = "Hola, servidor!";
    send(clientSocket, message, strlen(message), 0);

    // Cerrar el socket
    close(clientSocket);

    return 0;
}
