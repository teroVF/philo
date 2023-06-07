#include <pthread.h>
#include <stdio.h>

typedef struct queijo
{
  int n;
  pthread_mutex_t mtx_queijo;  
}                t_queijo;


void * pega3(t_queijo *x)
{
    printf("tentei pegar 3\n");
    pthread_mutex_lock(&x->mtx_queijo);
    if (x->n < 3)
        return NULL;
    x->n -= 3;
    pthread_mutex_unlock(&x->mtx_queijo);
    printf("comi 3\n");
    printf("sobram %d\n", x->n);
    sleep(rand() % 3 + 1);
    return (NULL);
}

void * pega1(t_queijo *x)
{
    printf("tentei pegar 1\n");
    pthread_mutex_lock(&x->mtx_queijo);

    if (x->n < 1)
        return NULL;
    x->n -= 1;
    pthread_mutex_unlock(&x->mtx_queijo);
    printf("peguei 1\n");
    printf("sobram %d\n", x->n);
    sleep(rand() % 3 + 1);
    return (NULL);
}

int main(void)
{
    t_queijo *x;
    pthread_t a;
    pthread_t b;

    x->n = 100;
    pthread_mutex_init(&x->mtx_queijo, NULL);

    pthread_create(&a, NULL, pega3, x);
    pthread_create(&b, NULL, pega1, x);
    printf("aqui %p\n", a);
    printf("aqui %p\n", b);
    while (1)
    {
        pthread_join(b, NULL);
        pthread_join(a, NULL);
        if (x->n == 0)
            break;
    }
    printf("acabou\n");
    pthread_mutex_destroy(&x->mtx_queijo);
    return (0);
}