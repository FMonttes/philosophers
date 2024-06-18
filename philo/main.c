/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felipe <felipe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:07:03 by felipe            #+#    #+#             */
/*   Updated: 2024/06/14 10:46:43 by felipe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_data data;
    if (ac == 5 || ac == 6)
    {
        get_data_from_input(&data, av);
        start_data(&data);
        philho_start(&data);
    }
    else
        printf(RED"Error: Wrong number of arguments\n"RST);
    return 0;
}

