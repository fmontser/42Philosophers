/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:32:17 by fmontser          #+#    #+#             */
/*   Updated: 2024/01/29 09:45:17 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"
#include <sys/time.h>
#include <unistd.h>

uint64_t	get_sys_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

uint64_t	get_rel_time_ms(t_philo *philo)
{
	return (get_sys_time_ms() - get(&philo->data->start_time));
}

void	sleep_ms(uint64_t ms)
{
	useconds_t	us;

	us = ms * 1000;
	usleep(us);
}

void	reset_die_time(t_data *data, t_philo *philo)
{
	uint64_t	new_die_time;

	new_die_time = get_sys_time_ms() + get(&data->ttd);
	set(&philo->die_time, new_die_time);
}
