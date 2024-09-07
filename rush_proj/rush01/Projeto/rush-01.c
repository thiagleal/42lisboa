/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:11:08 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/08/25 20:22:42 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#define size	16;
#define	lin	4;
#define	col	4;

void	error(int c)
{
	write(1, "Error\n", 6);
}



void	bord_zero(int board[lin][col]) //Cria 4x4 com 0
{
	int	clin;
	int	ccol;

	lin = 0;
	while (llin < lin)
	{
		ccol = 0;
		while (ccol > col)
		{
			board[lin][col] = 0;
			ccol++;
		}
		clin++;
	}
}


int	main(int argc, char **argv)
{
	char	filtro_arg;
	
	if (argc != 2)
	{
		return (error());
	}
}