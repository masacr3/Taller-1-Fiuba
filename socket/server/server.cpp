#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    // Crear un socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    if (serverSocket == -1) {
        std::cerr << "Error al crear el socket" << std::endl;
        return -1;
    }

    // Configurar la dirección del servidor
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Vincular el socket a la dirección
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error al vincular el socket a la dirección" << std::endl;
        close(serverSocket);
        return -1;
    }

    // Escuchar por conexiones entrantes
    if (listen(serverSocket, 10) == -1) {
        std::cerr << "Error al intentar escuchar por conexiones entrantes" << std::endl;
        close(serverSocket);
        return -1;
    }

    std::cout << "Servidor esperando conexiones en el puerto 8080..." << std::endl;

    // Aceptar una conexión entrante
    int clientSocket = accept(serverSocket, NULL, NULL);
    
    if (clientSocket == -1) {
        std::cerr << "Error al aceptar la conexión" << std::endl;
        close(serverSocket);
        return -1;
    }

    // Leer datos del cliente
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    recv(clientSocket, buffer, sizeof(buffer), 0);

    std::cout << "Mensaje del cliente: " << buffer << std::endl;

    // Cerrar los sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}
