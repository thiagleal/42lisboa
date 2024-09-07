/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 20:38:48 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/09/01 15:05:28 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//para testar = printf("Teste de =   = %d\n", );

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "functions.h"


char *find(char *dict, char *nb)
{
	int		contnb;
	int		bytes_read;
	int		open_dict;
	char	*result;
	
	
	contnb = ft_strlen(nb);
	*result = NULL;
	open_dict = open(dict, O_RDONLY); //Abrir o dicionario, fechar depois
	if (open_dict == -1)
	{
		ft_putstr("Dict Error\n");
		close(open_dict);
		return NULL;
	}

	char *buffer[1024] = (char *)malloc(sizeof(buffer) + 1); //Malloc, fechar depois
	if (open_dict == NULL)
	{
		ft_putstr("Error\n");
		close(buffer);
		return NULL;
	}

		bytes_read = read(open_dict, buffer, sizeof(buffer) - 1);

	if (nb >= 0 && nb <= 20)
	{
		
		free(open_dict);
		close(open_dict);
		return (buffer);
	}
	else if (contnb == 2)
	{
		
		return (buffer);
	}
	else if (contnb == 3)
	{
		
		return (buffer);
	}
	else if (contnb > 3)
	{
		
	}



	free(open_dict);
	close(open_dict);
	close(buffer);
}


void	print(char *dict, char *nb)
{
	int	nbint;
	//char *result;

	nbint = ft_atoi(nb);

	
	char *result = (char *)malloc(ft_strlen(nb) * sizeof(char) + 1);
	if (result == NULL)
	{
		ft_putstr("Error\n");
		return;
	}
	
	printf("Alocaçao de %d bytes da memoria\n", ft_strlen(nb) * sizeof(char)); //Teste para verificar a qtd de memoria alocada
	
	*result = find(dict, nbint);

	printf("Teste de =nb= %s\n", nb); //Teste
	printf("Teste de =nbint= %d\n", nbint); //Teste
	printf("Teste de =tamanho nb= %d\n", ft_strlen(nb)); //Teste
	printf("Teste de =result= %s\n", result); //Teste
	printf("Teste de =dict= %s\n", dict); //Teste
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
			//ft_putstr("Deu certo\n"); //Teste
		}
		else
		ft_putstr("Error\n");
	}
	else if (argc == 3)
	{
		if (ft_valid_number(argv[2]))
		{
			print(argv[1], argv[2]);
			//ft_putstr("Deu certo\n"); //Teste
		}
		else
		ft_putstr("Error\n");
	}
	else
		ft_putstr("Error\n");
	return (0);
}

/*


9 , 8 and 7 - 6 , 5 and 4 - 3 , 234567887697654

Nine sextillion, eight hundred and seventy-six quintillion, five hundred and 
forty-three quadrillion, two hundred and thirty-four trillion, five hundred and 
sixty-seven billion, eight hundred and eighty-seven million, six hundred and 
ninety-seven thousand, six hundred and fifty-four


98765434567

Ninety-eight billion, seven hundred and sixty-five million, four hundred and 
thirty-four thousand, five hundred and sixty-seven


*/


/*
	int	dici;
	char	*result;
	char	*line;
	char	*key;
	char	*value;
	char	buffer;
	int	bytes_read;
	
	dici = (int *)malloc(1 * sizeof(int)); //Malloc, fechar depois
	if (dici == NULL)
	{
		printf("Error\n");
		return NULL;
	}
	
	dici = open("numbers.dict", O_RDONLY); //Abrir o dicionario
	if (dici == -1)
	{
		printf("Dict Error\n");
		return NULL;
	}

	// Read the contents of the file
	char buffer[256];
	ssize_t bytesRead = read(dici, buffer, sizeof(buffer) - 1);
	if (bytesRead == -1)
	{
		printf("Error reading dictionary file\n");
		close(dici);
		return NULL;
	}
	buffer[bytesRead] = '\0';

	// Search for the number in the dictionary
	char *token = strtok(buffer, ":");
	while (token != NULL)
	{
		if (strcmp(token, nb) == 0)
		{
			char *result = strtok(NULL, ":");
			close(dici);
			return result;
		}
		token = strtok(NULL, ":");
	}

	close(dici);
	return NULL;
*/