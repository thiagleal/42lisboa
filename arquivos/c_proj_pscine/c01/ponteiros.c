/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ponteiros.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:28:27 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/08/22 22:04:04 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	int	teste;
	int *point;
	
	teste = 42;
	// *point = 42; //posso declarar o valor, vai direto para o int teste
	point = &teste;

	printf("Conteudo de teste = %d\n", teste);
	printf("Endereco de teste = %p\n", &teste); //saber endereco no printf %p e & antes na variavel normal
	printf("Conteudo de point = %d\n", *point);
	printf("Endereco de pount = %p\n", point);	 //saber endereco no printf %p no ponteiro
	return (0);
}