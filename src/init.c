/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 23:03:14 by fmontser          #+#    #+#             */
/*   Updated: 2024/01/29 19:06:11 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

#define N_PHILO_IDX 1
#define TTD_IDX 2
#define TTE_IDX 3
#define TTS_IDX 4
#define N_MEALS_IDX 5
#define LIMITED_MODE 6

static t_philo	*_init_philo(t_data *data, uint64_t philo_id)
{
	t_philo	*philo;

	philo = ft_smalloc(data, sizeof(t_philo));
	setmutex(data, &philo->id, philo_id);
	setmutex(data, &philo->meals_left, data->max_meals.value);
	setmutex(data, &philo->die_time, UINT64_MAX);
	setmutex(data, &philo->r_fork, philo_id);
	philo->next = NULL;
	philo->data = data;
	return (philo);
}

static t_ret	_create_philos(t_data *data)
{
	uint64_t	id;
	t_philo		*_head;

	id = 1;
	data->ph_lst = _init_philo(data, id);
	if (!data->ph_lst)
		return (cleanxit(data, MEM_ERROR));
	if (data->n_philo.value == 1)
		return (SUCCESS);
	_head = data->ph_lst;
	while (++id <= data->n_philo.value)
	{
		data->ph_lst->next = _init_philo(data, id);
		if (!data->ph_lst->next)
			return (cleanxit(data, MEM_ERROR));
		data->ph_lst->next->l_fork = data->ph_lst->r_fork;
		data->ph_lst = data->ph_lst->next;
	}
	data->ph_lst->next = _head;
	_head->l_fork = data->ph_lst->r_fork;
	data->ph_lst = data->ph_lst ->next;
	return (SUCCESS);
}

t_ret	init_data(t_data *data, int argc, char *argv[])
{
	data->ph_lst = NULL;
	data->free_lst = NULL;
	data->free_head = NULL;
	if (argc == LIMITED_MODE)
	{
		setmutex(data, &data->max_meals, ft_atoi(argv[N_MEALS_IDX]));
		setmutex(data, &data->sim_mode, LIMITED);
	}
	else
	{
		setmutex(data, &data->max_meals, UINT64_MAX);
		setmutex(data, &data->sim_mode, UNLIMITED);
	}
	setmutex(data, &data->n_philo, ft_atoi(argv[N_PHILO_IDX]));
	setmutex(data, &data->ttd, ft_atoi(argv[TTD_IDX]));
	setmutex(data, &data->tte, ft_atoi(argv[TTE_IDX]));
	setmutex(data, &data->tts, ft_atoi(argv[TTS_IDX]));
	setmutex(data, &data->ph_th_left, data->n_philo.value);
	setmutex(data, &data->start_time, 0);
	setmutex(data, &data->stuffed_left, data->n_philo.value);
	setmutex(data, &data->sim_status, STOPPED);
	setmutex(data, &data->printer, NONE);
	if (_create_philos(data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
