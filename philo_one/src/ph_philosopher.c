/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philosopher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 21:41:36 by jolim             #+#    #+#             */
/*   Updated: 2021/04/11 22:19:33 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*odd_philosopher(void *philo)
{
	while (1)
	{
		if (odd_philo_liftcycle(philo) == true)
			break;
	}
	return (NULL);
}

void	*even_philosopher(void *philo)
{
	while (1)
	{
		if (even_philo_liftcycle(philo) == true)
			break;
	}
	return (NULL);
}
