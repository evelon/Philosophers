/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 21:45:01 by jolim             #+#    #+#             */
/*   Updated: 2021/04/14 12:55:21 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

unsigned long	ph_get_duration(struct timeval last, struct timeval now)
{
	unsigned long	duration;

	duration = (now.tv_sec - last.tv_sec - 1) * 1000 + \
	(unsigned long)(1000000 + now.tv_usec - last.tv_usec) / 1000;
	return (duration);
}

void	ph_sleep_precise(int ms)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(100);
		gettimeofday(&now, NULL);
		if (ph_get_duration(start, now) >= (unsigned int)ms)
			return ;
	}
}
