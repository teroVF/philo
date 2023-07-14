#include "../includes/philo.h"

void stop_threads(t_philo **philo)
{
	int i;

	i = 0;
	while (i < philo[0]->program->nbr_philo)
	{
		pthread_detach(*philo[i]->tid);
		i++;
	}
}

static int check_death(t_philo **philo, int i)
{
	__uint64_t limite;
	__uint64_t time;

	limite = philo[i]->last_meal + philo[i]->program->time_die;
	pthread_mutex_lock(philo[i]->program->time);
	time = check_time(philo[0]->program->start);
	pthread_mutex_unlock(philo[i]->program->time);
	if (time > limite + 10)
	{
		pthread_mutex_lock(philo[i]->program->dead);
		philo[i]->program->someone_dead = 1;
		pthread_mutex_unlock(philo[i]->program->dead);
		pthread_mutex_lock(philo[i]->program->write);
		printf("%lu %d died\n", time - 10, philo[i]->sit);
		pthread_mutex_unlock(philo[i]->program->write);
		return (1);
	}
	return (0);
}

static int check_is_full(t_philo **philo, int i)
{
	static int count = 0;
	
	if (philo[i]->numb_meals == philo[0]->program->meals 
		&& philo[i]->is_full == 0)
	{
		pthread_mutex_lock(philo[i]->program->write);
		printf("%lu %d is full\n", check_time(philo[0]->program->start),
			philo[i]->sit);
		pthread_mutex_unlock(philo[i]->program->write);
		count++;
		philo[i]->is_full = 1;
		if (count == philo[0]->program->nbr_philo)
			return (1);
	}
	return (0);
}

void wait_and_check(t_philo **philo)
{
	int i;
	
	i = 0;
	while (1)
	{
		if  (philo[0]->program->meals != -1 && check_is_full(philo, i) == 1)
			break ;
		if(check_death(philo, i) == 1)
			break ;
		i++;
		if (i == philo[0]->program->nbr_philo)
			i = 0;
	}
}