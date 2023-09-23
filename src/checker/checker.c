/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: envyilma <envyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:40:53 by envyilma          #+#    #+#             */
/*   Updated: 2023/09/21 16:55:07 by envyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_number(char *s)
{
	int	i;

	i = -1;
	while (i++, s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (-1);
	}
	return (1);
}

int	checker(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (-1);
	i = 0;
	while (i++, av[i])
	{
		if (is_number(av[i]) == -1)
			return (-1);
	}
	return (1);
}
