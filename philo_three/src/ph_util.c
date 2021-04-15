/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolim <jolim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 17:15:46 by jolim             #+#    #+#             */
/*   Updated: 2021/04/15 15:02:31 by jolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\v' || c == '\t' || c == '\n' || \
	c == '\r')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int			p;
	long long	num;
	int			sign;

	if (*str == '\0')
		return (0);
	while (isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	else
		sign = 1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	p = 0;
	num = 0;
	while (*(str + p) <= '9' && *(str + p) >= '0')
		num = num * 10 + (*(str + p++) - '0') * sign;
	if (*(str + p) != '\0')
		return (-1);
	return (num);
}

void		*ft_calloc(size_t count, size_t size)
{
	char	*new;

	if (count == 0 || size == 0)
	{
		new = malloc(0);
		if (!new)
			return (NULL);
		return (new);
	}
	new = malloc(count * size);
	if (!new)
		return (NULL);
	memset(new, 0, count * size);
	return (new);
}

void		*free_null(void *ptr)
{
	free(ptr);
	return (NULL);
}

int			ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
