/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:09:39 by envyilma          #+#    #+#             */
/*   Updated: 2023/09/21 16:15:24 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	loop_control(t_philo *philo, t_table *table)
{
	int	i;

	i = -1;
	while (i++, i < table->number_of_p)
	{
		philo[i].time_without_eat++;
		if (philo[i].time_without_eat >= table->death_time)
		{
			ft_message("philo is dead\n", &philo[i]);
			table->break_eat = 1;
			return (0);
		}
		if (table->must_least_eat != -1 && table->total_meal
			/ table->number_of_p >= table->must_least_eat)
		{
			table->break_eat = 1;
			return (0);
		}
	}
	return (1);
}

void	*check_death(void *philos)
{
	t_philo	*philo;
	t_table	*table;

	philo = *(t_philo **)(philos);
	table = philo->table;
	table->start = get_time();
	while (1)
	{
		if (loop_control(philo, table) == 0)
			return (NULL);
		ft_usleep(1);
	}
}
