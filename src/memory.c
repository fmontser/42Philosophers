/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 23:15:19 by fmontser          #+#    #+#             */
/*   Updated: 2024/01/29 17:40:53 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "defs.h"

void	*ft_smalloc(t_data *data, uint64_t size)
{
	if (!data->free_lst)
	{
		data->free_lst = malloc(sizeof(t_free));
		data->free_head = data->free_lst;
	}
	else
	{
		data->free_lst->next = malloc(sizeof(t_free));
		data->free_lst = data->free_lst->next;
	}
	if (!data->free_lst)
		return (NULL);
	data->free_lst->ptr = malloc(size);
	if (!data->free_lst->ptr)
		return (NULL);
	return (data->free_lst->ptr);
}

void	ft_free(t_free *list_head)
{
	t_free	*head;
	t_free	*next;

	head = list_head;
	while (head)
	{
		free(head->ptr);
		head = head->next;
	}
	head = list_head;
	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}

t_ret	cleanxit(t_data *data, t_err error)
{
	if (error == MEM_ERROR)
		demutex(data);
	ft_free(data->free_lst);
	return (print_error(error));
}

t_ret	setmutex(t_data *data, t_mv *mv, uint64_t value)
{
	*mv = (t_mv){
		.value = value,
		.mutx = ft_smalloc(data, sizeof(pthread_mutex_t))
	};
	if (pthread_mutex_init(mv->mutx, NULL) != SUCCESS)
		return (cleanxit(NULL, MEM_ERROR));
	return (SUCCESS);
}

void	demutex(t_data *data)
{
	uint64_t	i;

	i = 0;
	pthread_mutex_destroy(data->max_meals.mutx);
	pthread_mutex_destroy(data->n_philo.mutx);
	pthread_mutex_destroy(data->ttd.mutx);
	pthread_mutex_destroy(data->tte.mutx);
	pthread_mutex_destroy(data->tts.mutx);
	pthread_mutex_destroy(data->start_time.mutx);
	pthread_mutex_destroy(data->stuffed_left.mutx);
	pthread_mutex_destroy(data->sim_status.mutx);
	pthread_mutex_destroy(data->printer.mutx);
	while (++i <= data->n_philo.value)
	{
		pthread_mutex_destroy(data->ph_lst->id.mutx);
		pthread_mutex_destroy(data->ph_lst->meals_left.mutx);
		pthread_mutex_destroy(data->ph_lst->die_time.mutx);
		pthread_mutex_destroy(data->ph_lst->r_fork.mutx);
		if (data->n_philo.value > 1)
			pthread_mutex_destroy(data->ph_lst->l_fork.mutx);
		data->ph_lst = data->ph_lst->next;
	}
}
