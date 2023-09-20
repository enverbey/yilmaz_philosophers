/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:24:43 by envyilma          #+#    #+#             */
/*   Updated: 2023/09/20 20:26:13 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_table
{
	pthread_t		check_dead;
	pthread_mutex_t	*forks;
	u_int64_t		start;
	int				number_of_p;
	int				time_eat;
	int				time_sleep;
	int				death_time;
	int				break_eat;
}	t_table;

typedef struct s_philo
{
	pthread_t		philo_id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				number;
	int				time_without_eat;
	t_table			*table;
}	t_philo;

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		exit(0);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void	set_table(t_table *table, char **av)
{
	int	i;

	i = -1;
	table->number_of_p = ft_atoi(av[1]);
	table->death_time = ft_atoi(av[2]);
	table->time_eat = ft_atoi(av[3]);
	table->time_sleep = ft_atoi(av[4]);
	table->break_eat = 0;
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->number_of_p);
	while (i++, i < table->number_of_p)
		pthread_mutex_init(&table->forks[i], NULL);
}

void	set_philos(t_table *table, t_philo **philos)
{
	int	i;

	i = 0;
	(*philos) = (t_philo *)malloc(sizeof(t_philo) * table->number_of_p);
	while (i < table->number_of_p)
	{
		(*philos)[i].left_fork = &table->forks[i];
		(*philos)[i].right_fork = &table->forks[(i + 1) % table->number_of_p];
		(*philos)[i].number = i + 1;
		(*philos)[i].time_without_eat = 0;
		(*philos)[i].table = table;
		i++;
	}
}

void	*check_death(void *philos)
{
	t_philo	*philo;
	t_table	*table;
	int		i;

	philo = *(t_philo **)(philos);
	table = philo->table;
	table->start = get_time();
	while (1)
	{
		i = -1;
		while (i++, i < table->number_of_p)
		{
			printf("%d idli filo girdi %d\n", philo[i].number, philo[i].time_without_eat);
			philo[i].time_without_eat++;
			if (philo[i].time_without_eat >= table->death_time)
			{
				table->break_eat = 1;
				return (NULL);
			}
		}
		ft_usleep(1);
	}
}

void	*eat(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	while (table->break_eat != 1)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%llu %d. philo has taken a fork\n",
			get_time() - table->start, philo->number);
		pthread_mutex_lock(philo->right_fork);
		printf("%llu %d. philo has taken a fork\n",
			get_time() - table->start, philo->number);
		philo->time_without_eat = 0;
		printf("%llu %d. philo is eating\n",
			get_time() - table->start, philo->number);
		ft_usleep(table->time_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("%llu %d. philo is sleeping\n",
			get_time() - table->start, philo->number);
		ft_usleep(table->time_sleep);
		printf("%llu %d. philo is thinking\n",
			get_time() - table->start, philo->number);
	}
	return (NULL);
}

void	start_philo(t_table *table, t_philo **philolar)
{
	t_philo	*philos;
	int		i;

	philos = (*philolar);
	i = -1;
	pthread_create(&table->check_dead, NULL, check_death, (void *)(&philos));
	while (i++, i < table->number_of_p)
		pthread_create(&philos[i].philo_id, NULL, eat, (void *)&philos[i]);
	i = -1;
	pthread_join(table->check_dead, NULL);
	while (i++, i < table->number_of_p)
		pthread_join(philos[i].philo_id, NULL);
}

int	main(int ac, char **av)
{
	t_philo		*philos;
	t_table		table;

	philos = NULL;
	if (checker(ac, av) == -1)
		return (printf("Error\n"), 0);
	set_table(&table, av);
	set_philos(&table, &philos);
	start_philo(&table, &philos);
}
