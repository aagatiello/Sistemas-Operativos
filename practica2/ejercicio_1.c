#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_t thread1, thread2, thmain; /* Declaración de los threads */
pthread_attr_t attr;                /* Atributos de los threads */

void *func(void *arg)
{
    int factorial = 1;
    int input = atoi((char *)arg); /* String to int */
    for (int num = 1; num <= input; num++)
        factorial *= num;
    printf("El factorial de %d es %d\n", input, factorial);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    thmain = pthread_self();

    /* Inicialización de los parametros de los threads por defecto */
    pthread_attr_init(&attr);

    if (argc != 3)
    {
        perror("Indica dos numeros enteros.\n");
        exit(1);
    }

    pthread_create(&thread1, &attr, func, (void *)argv[1]);
    pthread_create(&thread2, &attr, func, (void *)argv[2]);

    /* Main espera a que los otros threads terminen */
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_exit(NULL);
}