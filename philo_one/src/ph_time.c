/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 21:45:01 by jolim             #+#    #+#             */
/*   Updated: 2021/04/11 17:36:35 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ph_get_duration(struct timeval last, struct timeval now)
{
	int				duration;

	if (last.tv_sec == now.tv_sec)
		return (now.tv_usec - last.tv_usec);
	duration = 1000000 * (now.tv_sec - last.tv_sec - 1) + \
	1000000 - last.tv_usec + now.tv_usec;
	return (duration);
}
