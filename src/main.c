/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontser <fmontser@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:46:34 by fmontser          #+#    #+#             */
/*   Updated: 2024/01/29 17:38:23 by fmontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

static void	_wait_threads(t_data *data)
{
	while (get(&data->ph_th_left))
		sleep_ms(1000);
}

static t_ret	_args_check(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (FAILURE);
	else if (argc == 5 || argc == 6)
	{
		while (--argc)
		{
			if (ft_atoi(argv[argc]) < 1)
				return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (_args_check(argc, argv) == FAILURE)
		return (cleanxit(&data, ARG_ERROR));
	init_data(&data, argc, argv);
	start_threads(&data);
	_wait_threads(&data);
	demutex(&data);
	ft_free(data.free_head);
	return (SUCCESS);
}
