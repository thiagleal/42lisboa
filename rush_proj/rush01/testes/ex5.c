/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:33:25 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/08/25 15:51:29 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#define N 4

// Função para imprimir mensagem de erro
void imprimir_erro(void)
{
    write(1, "Error\n", 6);
}

// Função para imprimir a solução do tabuleiro
void imprimir_solucao(int tabuleiro[N][N])
{
    char c;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            c = tabuleiro[i][j] + '0';
            write(1, &c, 1);
            if (j < N - 1)
                write(1, " ", 1);
        }
        write(1, "\n", 1);
    }
}

// Função para validar a entrada
int validar_entrada(int argc, char **argv, int *entrada)
{
    if (argc != 2)
        return (0);

    int i = 0;
    int j = 0;

    // Verifica os 16 números
    for (i = 0; i < 16; i++)
    {
        // Cada número deve estar entre '1' e '4'
        if (argv[1][j] < '1' || argv[1][j] > '4')
            return (0);
        entrada[i] = argv[1][j] - '0';
        j++;
        
        // Verifica se deve haver um espaço após cada número, exceto o último
        if (i < 15)
        {
            if (argv[1][j] != ' ')
                return (0);
            j++;
        }
    }

    // Verifica se há mais caracteres após os 16 números e espaços
    while (argv[1][j] != '\0')
    {
        if (argv[1][j] != ' ')
            return (0);
        j++;
    }

    return (1);
}

// Função para checar a visibilidade da esquerda para a direita em uma linha
int checar_linha_esquerda(int tabuleiro[N][N], int linha, int esperado)
{
    int max_visto = 0;
    int qtd_vistos = 0;
    for (int i = 0; i < N; i++)
    {
        if (tabuleiro[linha][i] > max_visto)
        {
            max_visto = tabuleiro[linha][i];
            qtd_vistos++;
        }
    }
    return (qtd_vistos == esperado);
}

// Função para checar a visibilidade da direita para a esquerda em uma linha
int checar_linha_direita(int tabuleiro[N][N], int linha, int esperado)
{
    int max_visto = 0;
    int qtd_vistos = 0;
    for (int i = N - 1; i >= 0; i--)
    {
        if (tabuleiro[linha][i] > max_visto)
        {
            max_visto = tabuleiro[linha][i];
            qtd_vistos++;
        }
    }
    return (qtd_vistos == esperado);
}

// Função para checar a visibilidade de baixo para cima em uma coluna
int checar_coluna_cima(int tabuleiro[N][N], int coluna, int esperado)
{
    int max_visto = 0;
    int qtd_vistos = 0;
    for (int i = 0; i < N; i++)
    {
        if (tabuleiro[i][coluna] > max_visto)
        {
            max_visto = tabuleiro[i][coluna];
            qtd_vistos++;
        }
    }
    return (qtd_vistos == esperado);
}

// Função para checar a visibilidade de cima para baixo em uma coluna
int checar_coluna_baixo(int tabuleiro[N][N], int coluna, int esperado)
{
    int max_visto = 0;
    int qtd_vistos = 0;
    for (int i = N - 1; i >= 0; i--)
    {
        if (tabuleiro[i][coluna] > max_visto)
        {
            max_visto = tabuleiro[i][coluna];
            qtd_vistos++;
        }
    }
    return (qtd_vistos == esperado);
}

// Função para verificar se o tabuleiro está válido com base nas entradas
int esta_valido(int tabuleiro[N][N], int *entrada)
{
    for (int i = 0; i < N; i++)
    {
        if (!checar_coluna_cima(tabuleiro, i, entrada[i]))
            return (0);
        if (!checar_coluna_baixo(tabuleiro, i, entrada[i + 4]))
            return (0);
        if (!checar_linha_esquerda(tabuleiro, i, entrada[i + 8]))
            return (0);
        if (!checar_linha_direita(tabuleiro, i, entrada[i + 12]))
            return (0);
    }
    return (1);
}

// Função para verificar se um número pode ser colocado na posição especificada
int pode_colocar(int tabuleiro[N][N], int linha, int coluna, int num)
{
    for (int i = 0; i < N; i++)
    {
        if (tabuleiro[linha][i] == num || tabuleiro[i][coluna] == num)
            return (0);
    }
    return (1);
}

// Função para resolver o quebra-cabeça usando backtracking
int resolver(int tabuleiro[N][N], int *entrada, int linha, int coluna)
{
    if (linha == N)
    {
        if (esta_valido(tabuleiro, entrada))
        {
            imprimir_solucao(tabuleiro);
            return (1);
        }
        return (0);
    }

    int proxima_linha = (coluna == N - 1) ? linha + 1 : linha;
    int proxima_coluna = (coluna + 1) % N;

    for (int num = 1; num <= N; num++)
    {
        if (pode_colocar(tabuleiro, linha, coluna, num))
        {
            tabuleiro[linha][coluna] = num;
            if (resolver(tabuleiro, entrada, proxima_linha, proxima_coluna))
                return (1);
            tabuleiro[linha][coluna] = 0;
        }
    }
    return (0);
}

// Função principal
int main(int argc, char **argv)
{
    int entrada[16];
    int tabuleiro[N][N] = {0};

    if (!validar_entrada(argc, argv, entrada))
    {
        imprimir_erro();
        return (1);
    }

    if (!resolver(tabuleiro, entrada, 0, 0))
    {
        imprimir_erro();
        return (1);
    }

    return (0);
}§