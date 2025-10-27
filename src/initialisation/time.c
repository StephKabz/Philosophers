/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stkabang <stkabang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:36:57 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/27 15:25:22 by stkabang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_timestamp(void)
{
	struct timeval		tv;
	static long long	fallback_time;

	fallback_time = 0;
	if (gettimeofday(&tv, NULL) != 0)
	{
		fallback_time += 1;
		return (fallback_time);
	}
	return ((long long)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_sleep(t_program *prog, int milliseconds)
{
	long long	start;

	start = get_timestamp();
	while ((get_timestamp() - start < milliseconds))
	{
		if (!is_simulation_running(prog))
			break ;
		usleep(50);
	}
}
