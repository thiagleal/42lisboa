/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:24:59 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/08/29 16:08:03 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int agrc, char **argv)
{
	printf("Contador; %d\nNome do arquivo: %s\nValor: %c\n", agrc, argv[0], argv[1][1]);
	return (0);
}