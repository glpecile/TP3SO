/**
    Fuente: https://www.geeksforgeeks.org/socket-programming-cc/
*/
#include "networking.h"
#define SA struct sockaddr
#define MAX_BUFFER 200

int main(int argc, char const *argv[])
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    //char buffer[MAX_BUFFER] = {0};
    // memset(buffer, 0, MAX_BUFFER);
    //char *buffer = calloc(MAX_BUFFER, sizeof(char) * MAX_BUFFER);
    char *buffer = NULL;

    // Se crea el fd del socket.
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        HANDLE_ERROR("Error in socket");
    }

    // Se conecta el socket al puerto 8080.
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    {
        HANDLE_ERROR("Error in setsockopt");
    }

    // Se inicializa el server address.
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    //Se conecta el socket al puerto 8080.
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        HANDLE_ERROR("Error in bind");
    }

    // Habilita la escucha del cliente.
    if (listen(server_fd, 1) < 0)
    {
        HANDLE_ERROR("Error in listen");
    }

    // Se acepta la informacion del cliente para lectura.
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        HANDLE_ERROR("Error in accept");
    }

    FILE *fp;
    fp = fdopen(new_socket, "r");
    if (fp == NULL)
    {
        HANDLE_ERROR("Error in fdopen.");
    }
    initGame(fp);
    int flag = 1;
    size_t size = 0;
    while (flag)
    {
        flag = challenge(1);
        // if (getline(&buffer, &size, fp) > 0)
        //     printf("%s", buffer);
    }
    // if (getline(&buffer, &size, fp) > 0)
    //     printf("%s", buffer);
    printf("Felicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto\n\n");
    
    // Liberamos los recursos utilizados.
    free(buffer);
    close(server_fd);
    return EXIT_SUCCESS;
}
