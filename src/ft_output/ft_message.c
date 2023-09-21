/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_message.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:07:13 by envyilma          #+#    #+#             */
/*   Updated: 2023/09/21 16:09:00 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#include <stdio.h>

void	ft_message(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	if (philo->table->break_eat != 1)
		printf("%llu %d. %s",
			get_time() - philo->table->start, philo->number, str);
	pthread_mutex_unlock(&philo->table->print);
}
