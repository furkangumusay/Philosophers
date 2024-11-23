#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void    deneme(void *arg)
{
    int i = -1;

    pthread_mutex_lock(&mutex);
    printf("%s\n", arg);
    while (i < 100000)
    {
        i++;
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{
    pthread_t thread1;
    pthread_t thread2;
    char str[] = "furkan";

    pthread_create(&thread1, NULL, deneme, str);
    pthread_create(&thread2, NULL, deneme, str);

    return (0);
}