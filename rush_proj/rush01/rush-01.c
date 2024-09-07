/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:51:34 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/08/25 14:10:30 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#define N 4

/*
> ./rush-01 "col1up col2up col3up col4up col1down col2down col3down col4down row1left row2left
row3left row4left row1right row2right row3right row4right"

*/

void    print_error(void)
{
    write(1, "Error\n", 6);
}

int validate_input(int argc, char **argv, int *input)
{
    if (argc != 2)
        return (0);
	if (*input / N == 4)

    for (int i = 0; i < 16; i++)
    {
        if (argv[1][i * 2] < '1' || argv[1][i * 2] > '4')
            return (0);
        input[i] = argv[1][i * 2] - '0';
        if (i < 15 && argv[1][i * 2 + 1] != ' ')
            return (0);
    }
    return (1);
}

int	main(int argc, char **argv)
{	
    int input[16];
    //int board[N][N] = {0};

    if (!validate_input(argc, argv, input))
    {
        print_error();
        return (1);
    }
	/*
    if (!solve(board, input, 0, 0))
    {
        print_error();
        return (1);
    }

    return (0);
	*/
}