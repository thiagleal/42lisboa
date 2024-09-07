/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 20:38:48 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/09/01 16:59:48 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "functions.h"

/*
char *find(char *dict, char *nb)
{
	char *result;

	result = nb + *dict;
	
	return (result);
}
*/

void	print(char *dict, char *nb)
{
	int	nbint;

	nbint = ft_strlen(nb);
	char *result = (char *)malloc(nbint * sizeof(char) + 1);
	if (result == NULL)
	{
		printf("Error\n");
		return;
	}
	*result = '0'; //find(dict, nb);
	if (dict < 0) //Apenas para copilar
	{
		free(result);
		return;
	}
	if (result) 
	{
		ft_putstr(result);
		ft_putstr("\n");
		free(result);
	}
	else
	{
		ft_putstr("Dict Error\n");
		free(result);
	}
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (ft_valid_number(argv[1]))
		{
			print("numbers.dict", argv[1]);
		}
		else
			ft_putstr("Error\n");
	}
	else if (argc == 3)
	{
		if (ft_valid_number(argv[2]))
		{
			print(argv[1], argv[2]);
		}
		else
			ft_putstr("Error\n");
	}
	else
		ft_putstr("Error\n");
	return (0);
}

/*

//para testar = printf("Teste de =   = %d\n", );

9 , 8 and 7 - 6 , 5 and 4 - 3 , 234567887697654

Nine sextillion, eight hundred and seventy-six quintillion, five hundred and 
forty-three quadrillion, two hundred and thirty-four trillion, five hundred and 
sixty-seven billion, eight hundred and eighty-seven million, six hundred and 
ninety-seven thousand, six hundred and fifty-four


98765434567

Ninety-eight billion, seven hundred and sixty-five million, four hundred and 
thirty-four thousand, five hundred and sixty-seven


*/