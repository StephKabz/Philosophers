/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stkabang <stkabang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 00:55:09 by kingstephan       #+#    #+#             */
/*   Updated: 2025/10/27 15:22:54 by stkabang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_program	prog;

	if (parse_arguments(&prog, argc, argv) != 0)
		return (1);
	if (init_program(&prog) != 0)
		return (1);
	start_simulation(&prog);
	cleanup_program(&prog);
	return (0);
}
