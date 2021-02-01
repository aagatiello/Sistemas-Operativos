#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pthread_t thread1, thread2, thmain;
pthread_attr_t attr;
pthread_mutex_t my_lock;

void *func1(void *arg)
{
    pthread_mutex_lock(&my_lock);

    char *msg1 = "Hola, soy thread 1.\n";
    while (strlen(msg1))
    {
        putchar(*msg1);
        msg1++;
        sched_yield();
    }

    pthread_mutex_unlock(&my_lock);
    pthread_exit(NULL);
}

void *func2(void *arg)
{
    pthread_mutex_lock(&my_lock);

    char *msg2 = "Hola, soy thread 2.\n";
    while (strlen(msg2))
    {
        putchar(*msg2);
        msg2++;
        sched_yield();
    }

    pthread_mutex_unlock(&my_lock);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    thmain = pthread_self();

    pthread_attr_init(&attr);
    pthread_mutex_init(&my_lock, NULL);

    pthread_create(&thread1, &attr, func1, NULL);
    pthread_create(&thread2, &attr, func2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&my_lock);
    pthread_exit(NULL);
}
