/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:24:43 by envyilma          #+#    #+#             */
/*   Updated: 2023/09/23 13:12:54 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <stdio.h>

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
	free_everything(philos);
}
