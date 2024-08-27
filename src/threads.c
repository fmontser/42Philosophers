/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 00:10:55 by fmontser          #+#    #+#             */
/*   Updated: 2024/01/29 19:05:15 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"
#include <unistd.h>

static void	*_run_monitor(void *philo)
{
	t_philo	*_philo;
	t_gen	is_stuffed;

	_philo = (t_philo *)philo;
	is_stuffed = NO;
	while (get(&_philo->data->sim_status) == STOPPED)
		;
	while (get(&_philo->data->sim_status) == ONGOING)
	{
		if (get(&_philo->die_time) < get_sys_time_ms())
		{
			print_status(philo, DEAD, get_rel_time_ms(_philo));
			break ;
		}
		if (is_stuffed == NO && get(&_philo->meals_left) < 1)
		{
			set_add(&_philo->data->stuffed_left, -1);
			is_stuffed = YES;
		}
		if (get(&_philo->data->stuffed_left) == NONE)
			break ;
		sleep_ms(1);
	}
	set(&_philo->data->sim_status, STOPPED);
	return (philo);
}

static void	*_run_philo(void *philo)
{
	t_philo	*_philo;
	int		first_run;

	first_run = 1;
	_philo = (t_philo *)philo;
	pthread_create(&_philo->monitor_thread, NULL, _run_monitor, _philo);
	while (get(&_philo->data->sim_status) == STOPPED)
		;
	reset_die_time(_philo->data, philo);
	if (ft_is_even(get(&_philo->id)))
		usleep(200);
	if (get(&_philo->data->n_philo) > 1)
	{
		while (get(&_philo->data->sim_status) == ONGOING)
		{
			act_think(philo);
			act_eat(philo);
			act_sleep(philo);
		}
	}
	else
		act_think(philo);
	pthread_join(_philo->monitor_thread, NULL);
	set_add(&_philo->data->ph_th_left, -1);
	return (philo);
}

void	start_threads(t_data *data)
{
	uint64_t	i;

	i = 0;
	while (i < data->n_philo.value)
	{
		pthread_create(&data->ph_lst->thread, NULL, _run_philo, data->ph_lst);
		pthread_detach(data->ph_lst->thread);
		if (data->n_philo.value > 1)
			data->ph_lst = data->ph_lst->next;
		i++;
	}
	set(&data->start_time, get_sys_time_ms());
	set(&data->sim_status, ONGOING);
}
