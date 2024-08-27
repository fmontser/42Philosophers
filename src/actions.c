/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 21:47:49 by fmontser          #+#    #+#             */
/*   Updated: 2024/01/29 17:42:16 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

void	act_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork.mutx);
	print_status(philo, FORKING, get_rel_time_ms(philo));
	pthread_mutex_lock(philo->l_fork.mutx);
	print_status(philo, FORKING, get_rel_time_ms(philo));
	print_status(philo, EATING, get_rel_time_ms(philo));
	if (get(&philo->data->sim_mode) == LIMITED && get(&philo->meals_left) > 0)
		set_add(&philo->meals_left, -1);
	reset_die_time(philo->data, philo);
	sleep_ms(get(&philo->data->tte));
	pthread_mutex_unlock(philo->l_fork.mutx);
	pthread_mutex_unlock(philo->r_fork.mutx);
}

void	act_sleep(t_philo *philo)
{
	print_status(philo, SLEEPING, get_rel_time_ms(philo));
	sleep_ms(get(&philo->data->tts));
}

void	act_think(t_philo *philo)
{
	print_status(philo, THINKING, get_rel_time_ms(philo));
}
