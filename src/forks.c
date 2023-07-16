void    pick_right_fork(t_philo *philo, int sit)
{
    printf("%d\n", philo->sit);
    printf("nbr_philo: %d\n", philo->program->nbr_philo);
    if (philo->sit == philo->program->nbr_philo)
    {
        pthread_mutex_lock(&philo->program->mutex_fork[sit]);
        pthread_mutex_lock(philo->program->time);
        printf("%lu, the philo n %d is picking fork right...\n", check_time(philo->program->start) , philo->sit);
        pthread_mutex_unlock(philo->program->time);
    }
    else
    {
        pthread_mutex_lock(&philo->program->mutex_fork[sit - 1]);
        pthread_mutex_lock(philo->program->time);
        printf("%lu, the philo n %d is picking fork left...\n", check_time(philo->program->start) , philo->sit);
        pthread_mutex_unlock(philo->program->time);
    }
}
void    pick_left_fork(t_philo *philo, int sit)
{
    if (sit != philo->program->nbr_philo)
    {
        pthread_mutex_lock(&philo->program->mutex_fork[sit - 1]);
        pthread_mutex_lock(philo->program->time);
        printf("%lu, the philo n %d is picking fork left...\n", check_time(philo->program->start) , philo->sit);
        pthread_mutex_lock(&philo->program->mutex_fork[sit]);

        printf("%lu, the philo n %d is picking fork right...\n", check_time(philo->program->start) , philo->sit);
        // pthread_mutex_unlock(&philo->program->write);
    }
}

void    left_fork(t_philo *philo, int sit)
{
        if (philo->sit == philo->program->nbr_philo && philo->program->nbr_philo % 2)
    {
        pthread_mutex_unlock(&philo->program->mutex_fork[0]);
        pthread_mutex_lock(philo->program->write);
        printf("%lu, the philo n %d is picking fork left...\n", check_time(philo->program->start) , philo->sit);
        pthread_mutex_unlock(philo->program->write);
        pthread_mutex_unlock(&philo->program->mutex_fork[philo->sit - 1]);
        pthread_mutex_lock(philo->program->write);
        printf("%lu, the philo n %d is picking fork right...\n", check_time(philo->program->start) , philo->sit);
        pthread_mutex_unlock(philo->program->write);
        return ;
    }
    pthread_mutex_unlock(&philo->program->mutex_fork[sit - 1]);
    printf("%lu, the philo n %d left fork left...\n", check_time(philo->program->start) , philo->sit);
    if (sit == philo->program->nbr_philo)
        pthread_mutex_unlock(&philo->program->mutex_fork[0]);
    else
        pthread_mutex_unlock(&philo->program->mutex_fork[sit]);
    pthread_mutex_lock(philo->program->write);
    printf("%lu, the philo n %d left fork right...\n", check_time(philo->program->start) , philo->sit);
    pthread_mutex_unlock(philo->program->write);
}