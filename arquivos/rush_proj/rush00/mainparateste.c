/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:09:15 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/08/18 18:26:02 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	rush(int x, int y);

int	main(void)
{
	rush(5, 3);
	printf("\n");
	rush(5, 1);
	printf("\n");
	rush(1, 1);
	printf("\n");
	rush(1, 5),
	printf("\n");
	rush(4, 4);
	printf("\n");
	rush(15, 15);
	rush(20, 20);
	printf("\n");
	return (0);
}
