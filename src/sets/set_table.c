/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:54:52 by envyilma          #+#    #+#             */
/*   Updated: 2023/09/23 12:34:57 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <stdlib.h>

void	set_table(t_table *table, char **av)
{
	int	i;

	i = -1;
	table->number_of_p = ft_atoi(av[1]);
	table->death_time = ft_atoi(av[2]);
	table->time_eat = ft_atoi(av[3]);
	table->time_sleep = ft_atoi(av[4]);
	pthread_mutex_init(&table->mutex_break_eat, NULL);
	pthread_mutex_init(&table->mutex_total_meal, NULL);
	if (av[5])
		table->must_least_eat = ft_atoi(av[5]);
	else
		table->must_least_eat = -1;
	table->break_eat = 0;
	table->total_meal = 0;
	pthread_mutex_init(&table->print, NULL);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->number_of_p);
	while (i++, i < table->number_of_p)
		pthread_mutex_init(&table->forks[i], NULL);
}
