#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXLON 1000

pthread_t thread, thmain;
pthread_attr_t attr;

void *cuenta(void *arg)
{
    int pos, cont = 0, leidos;
    char cadena[MAXLON];
    int fd;
    char *nombre = (char *)arg;

    fd = open(nombre, O_RDONLY);
    while ((leidos = read(fd, cadena, MAXLON)) != 0)
        for (pos = 0; pos < leidos; pos++)
            if ((cadena[pos] == 'a') || (cadena[pos] == 'A'))
                cont++;
    printf("Fichero %s: %d caracteres 'a' o 'A' encontrados\n", nombre, cont);
    close(fd);

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    thmain = pthread_self();

    /* Inicialización de los parametros de los threads por defecto */
    pthread_attr_init(&attr);

    if (argc != 2)
    {
        printf("Indica el nombre de un fichero.\n");
        exit(0);
    }

    pthread_create(&thread, &attr, cuenta, (void *)argv[1]);
    pthread_join(thread, NULL);

    pthread_exit(NULL);
}