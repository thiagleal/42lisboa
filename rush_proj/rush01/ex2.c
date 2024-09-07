/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:33:06 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/08/24 17:39:36 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#define SIZE 4

// Função para escrever um único caractere na saída
void ft_putchar(char c) {
    write(1, &c, 1);
}

// Função para escrever uma string na saída
void ft_putstr(char *str) {
    while (*str)
        ft_putchar(*str++);
}

// Função para converter um número em caractere e escrevê-lo na saída
void ft_putnbr(int n) {
    ft_putchar(n + '0');
}

// Função para imprimir a matriz
void print_grid(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            ft_putnbr(grid[i][j]);
            if (j < SIZE - 1)
                ft_putchar(' ');
        }
        ft_putchar('\n');
    }
}

// Função para validar a entrada
int is_valid_input(char *input) {
    int i = 0;

    while (input[i] != '\0') {
        if ((i % 2 == 0 && (input[i] < '1' || input[i] > '4')) || (i % 2 == 1 && input[i] != ' '))
            return 0;
        i++;
    }

    return (i == 31);  // A entrada válida deve ter 31 caracteres
}

// Função para inicializar a matriz
void init_grid(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = 0;
        }
    }
}

// Função para checar se o valor pode ser inserido na posição sem quebrar as regras
int can_place(int grid[SIZE][SIZE], int row, int col, int num) {
    for (int i = 0; i < SIZE; i++) {
        if (grid[row][i] == num || grid[i][col] == num)
            return 0;
    }
    return 1;
}

// Função para verificar se as pistas laterais estão satisfeitas
int check_clues(int grid[SIZE][SIZE], int *clues) {
    int i, j, max, visible;

    // Verificação das pistas de cima
    for (i = 0; i < SIZE; i++) {
        max = 0;
        visible = 0;
        for (j = 0; j < SIZE; j++) {
            if (grid[j][i] > max) {
                max = grid[j][i];
                visible++;
            }
        }
        if (visible != clues[i])
            return 0;
    }

    // Verificação das pistas de baixo
    for (i = 0; i < SIZE; i++) {
        max = 0;
        visible = 0;
        for (j = SIZE - 1; j >= 0; j--) {
            if (grid[j][i] > max) {
                max = grid[j][i];
                visible++;
            }
        }
        if (visible != clues[i + 4])
            return 0;
    }

    // Verificação das pistas da esquerda
    for (i = 0; i < SIZE; i++) {
        max = 0;
        visible = 0;
        for (j = 0; j < SIZE; j++) {
            if (grid[i][j] > max) {
                max = grid[i][j];
                visible++;
            }
        }
        if (visible != clues[i + 8])
            return 0;
    }

    // Verificação das pistas da direita
    for (i = 0; i < SIZE; i++) {
        max = 0;
        visible = 0;
        for (j = SIZE - 1; j >= 0; j--) {
            if (grid[i][j] > max) {
                max = grid[i][j];
                visible++;
            }
        }
        if (visible != clues[i + 12])
            return 0;
    }

    return 1;
}

// Função para resolver o puzzle
int solve(int grid[SIZE][SIZE], int *clues, int row, int col) {
    if (row == SIZE)
        return check_clues(grid, clues);

    if (col == SIZE)
        return solve(grid, clues, row + 1, 0);

    for (int num = 1; num <= 4; num++) {
        if (can_place(grid, row, col, num)) {
            grid[row][col] = num;
            if (solve(grid, clues, row, col + 1))
                return 1;
            grid[row][col] = 0;
        }
    }

    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2 || !is_valid_input(argv[1])) {
        ft_putstr("Error\n");
        return 1;
    }

    int clues[16];
    for (int i = 0; i < 16; i++) {
        clues[i] = argv[1][2 * i] - '0';
    }

    int grid[SIZE][SIZE];
    init_grid(grid);

    if (solve(grid, clues, 0, 0)) {
        print_grid(grid);
    } else {
        ft_putstr("Error\n");
    }

    return 0;
}

