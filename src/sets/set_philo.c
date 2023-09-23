/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:57:19 by envyilma          #+#    #+#             */
/*   Updated: 2023/09/23 11:20:35 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <stdlib.h>

void	set_philos(t_table *table, t_philo **philos)
{
	int	i;

	i = 0;
	(*philos) = (t_philo *)malloc(sizeof(t_philo) * table->number_of_p);
	while (i < table->number_of_p)
	{
		pthread_mutex_init(&(*philos)[i].mutex_w_eat, NULL);
		(*philos)[i].left_fork = &table->forks[i];
		(*philos)[i].right_fork = &table->forks[(i + 1) % table->number_of_p];
		(*philos)[i].number = i + 1;
		(*philos)[i].time_without_eat = 0;
		(*philos)[i].table = table;
		i++;
	}
}
