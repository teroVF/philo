# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include "error_msg.h"

void	*error_msg(char *error_msg)
{
	ft_putendl_fd(error_msg, STDERR_FILENO);
	//free
	exit(EXIT_FAILURE);
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t			thread;
    pthread_t			thread1;

    pthread_create(&thread, NULL, error_msg, NULL);
    pthread_create(&thread1, NULL, error_msg, NULL);

    printf("%p\n", (void*) thread);
    printf("%p\n", (void*) thread1);

    return 0;
}
