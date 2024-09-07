/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testeredu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:37:06 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/08/25 21:40:39 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#define TAMANHO_JOGO 16
#define LINHAS 4
#define COLUNAS 4

int bordas[TAMANHO_JOGO];
int solucao_final[LINHAS][COLUNAS];
int solucao_encontrada = 0;

void	put_char(char c) 
{ 
	write(1, &c, 1); 
}

void	put_str(const char *str) 
{ 
	while (*str) 
	{ 
		put_char(*str++); 
	} 
}

void	transf(int num) 
{ 
	put_char(num + '0'); 
}

void	error() 
{ 
	put_str("Error\n"); 
}

int	validar_linha(int tabuleiro[LINHAS][COLUNAS], int coluna, int *borda, int reverso) 
{
	int	caixa_mais_alta = 0;
	int	contagem_caixas = 0;

	for (int linha = 0; linha < LINHAS; linha++) 
	{
		int	atual = reverso ? tabuleiro[LINHAS - linha - 1][coluna] : tabuleiro[linha][coluna];
		if (atual > caixa_mais_alta) 
		{
			caixa_mais_alta = atual;
			contagem_caixas++;
		}
	}
	return (contagem_caixas == *borda);
}

int	validar_coluna(int tabuleiro[LINHAS][COLUNAS], int linha, int *borda, int reverso) 
{
	int	caixa_mais_alta = 0;
	int	contagem_caixas = 0;

	for (int coluna = 0; coluna < COLUNAS; coluna++) 
	{
		int	atual = reverso ? tabuleiro[linha][COLUNAS - coluna - 1] : tabuleiro[linha][coluna];
		if (atual > caixa_mais_alta) 
		{
			caixa_mais_alta = atual;
			contagem_caixas++;
		}
	}
	return (contagem_caixas == *borda);
}

int	solucao_valida(int tabuleiro[LINHAS][COLUNAS]) 
{
	for (int i = 0; i < COLUNAS; i++) 
	{
		if (!validar_linha(tabuleiro, i, &bordas[i], 0) ||
			!validar_linha(tabuleiro, i, &bordas[i + COLUNAS], 1) ||
			!validar_coluna(tabuleiro, i, &bordas[i + 2 * COLUNAS], 0) ||
			!validar_coluna(tabuleiro, i, &bordas[i + 3 * COLUNAS], 1)) 
		{
			return (0);
		}
	}
	return (1);
}

void	tratar_solucao_final(int tabuleiro[LINHAS][COLUNAS]) 
{
	solucao_encontrada = 1;
	for (int i = 0; i < LINHAS; i++) 
	{
		for (int j = 0; j < COLUNAS; j++) 
		{
			solucao_final[i][j] = tabuleiro[i][j];
		}
	}
}

void	modificar_tabuleiro(int tabuleiro[LINHAS][COLUNAS], int indice) 
{
	if (indice == TAMANHO_JOGO || solucao_encontrada) 
	{
		if (solucao_valida(tabuleiro)) 
		{
			tratar_solucao_final(tabuleiro);
		}
		return;
	}

	int	linha = indice / COLUNAS;
	int	coluna = indice % COLUNAS;

	int	i = 1;
	while (i <= LINHAS) 
	{
		int	valido = 1;
		int	j = 0;

		while (j < LINHAS) 
		{
			if (tabuleiro[linha][j] == i || tabuleiro[j][coluna] == i) 
			{
				valido = 0;
				j = LINHAS;
			}
			else
			{
				j++;
			}
		}

		if (valido) 
		{
			tabuleiro[linha][coluna] = i;
			modificar_tabuleiro(tabuleiro, indice + 1);
			tabuleiro[linha][coluna] = 0;
		}

		i++;
	}
}

void	mostrar_tabuleiro(int tabuleiro[LINHAS][COLUNAS]) 
{
	for (int i = 0; i < LINHAS; i++) 
	{
		for (int j = 0; j < COLUNAS; j++) 
		{
			transf(tabuleiro[i][j]);
			if (j != COLUNAS - 1) 
			{
				put_char(' ');
			}
		}
		put_char('\n');
	}
}

void	analisar_argumentos(const char *str) 
{
	int	j = 0;
	int	i = 0;

	// Verifica o comprimento da string manualmente
	while (str[i] != '\0') 
	{
		if (i >= 31) 
		{
			error();
			return;
		}
		i++;
	}

	// Verifica se a string possui exatamente 16 caracteres (para os valores esperados)
	if (i != TAMANHO_JOGO) 
	{
		error();
		return;
	}

	i = 0;
	while (str[i] != '\0') 
	{
		if (str[i] >= '1' && str[i] <= '4') 
		{
			bordas[j++] = str[i] - '0';
		}
		else
		{
			// Se encontrar caracteres inválidos
			error();
			return;
		}
		i++;
	}

	if (j != TAMANHO_JOGO) 
	{
		error();
	}
}

int	main(int argc, char **argv) 
{
	if (argc != 2) 
	{
		error();
		return (1);
	}

	analisar_argumentos(argv[1]);

	int	tabuleiro[LINHAS][COLUNAS] = {0};
	modificar_tabuleiro(tabuleiro, 0);

	if (!solucao_encontrada) 
	{
		error();
		return (1);
	}

	mostrar_tabuleiro(solucao_final);
	return (0);
}
