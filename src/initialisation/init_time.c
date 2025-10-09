/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kingstephane <kingstephane@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:36:57 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/10 00:22:57 by kingstephan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_timestamp(void)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	time_diff(long start, long current)
{
	if (start < 0 || current < 0)
		return (-1);
	if (start > current)
		return (-1);
	return (current - start);
}

void	sleep_time(int milliseconde)
{
	long	microsecondes;

	if (milliseconde <= 0)
		return ;
	microsecondes = milliseconde * 1000;
	if (usleep(microsecondes) != 0)
		return ;
}
