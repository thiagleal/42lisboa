/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:33:06 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/08/24 22:44:12 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 9

void ft_putchar(char c) {
    write(1, &c, 1);
}

void ft_putstr(char *str) {
    while (*str)
        ft_putchar(*str++);
}

// Função corrigida para números inteiros de qualquer tamanho
void ft_putnbr(int n) {
    if (n >= 10)
        ft_putnbr(n / 10);
    ft_putchar(n % 10 + '0');
}

// Função para imprimir a matriz
void print_grid(int grid[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            ft_putnbr(grid[i][j]);
            if (j < size - 1)
                ft_putchar(' ');
        }
        ft_putchar('\n');
    }
}

// Função para validar a entrada e determinar o tamanho da grid
int is_valid_input(char *input, int *size) {
    int i = 0;
    int count = 0;

    while (input[i] != '\0') {
        if ((i % 2 == 0 && (input[i] < '1' || input[i] > '9')) || (i % 2 == 1 && input[i] != ' '))
            return 0;
        if (i % 2 == 0)
            count++;
        i++;
    }

    *size = count / 4;
    return (count % 4 == 0) && (*size >= 4 && *size <= 9) && (i == count * 2 - 1);
}

// Função para inicializar a matriz
void init_grid(int grid[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j] = 0;
        }
    }
}

// Função para checar se o valor pode ser inserido na posição sem quebrar as regras
int can_place(int grid[MAX_SIZE][MAX_SIZE], int size, int row, int col, int num) {
    for (int i = 0; i < size; i++) {
        if (grid[row][i] == num || grid[i][col] == num)
            return 0;
    }
    return 1;
}

// Função para verificar se as pistas laterais estão satisfeitas
int check_clues(int grid[MAX_SIZE][MAX_SIZE], int size, int *clues) {
    int i, j, max, visible;

    // Verificação das pistas de cima
    for (i = 0; i < size; i++) {
        max = 0;
        visible = 0;
        for (j = 0; j < size; j++) {
            if (grid[j][i] > max) {
                max = grid[j][i];
                visible++;
            }
        }
        if (visible != clues[i])
            return 0;
    }

    // Verificação das pistas de baixo
    for (i = 0; i < size; i++) {
        max = 0;
        visible = 0;
        for (j = size - 1; j >= 0; j--) {
            if (grid[j][i] > max) {
                max = grid[j][i];
                visible++;
            }
        }
        if (visible != clues[i + size])
            return 0;
    }

    // Verificação das pistas da esquerda
    for (i = 0; i < size; i++) {
        max = 0;
        visible = 0;
        for (j = 0; j < size; j++) {
            if (grid[i][j] > max) {
                max = grid[i][j];
                visible++;
            }
        }
        if (visible != clues[i + 2 * size])
            return 0;
    }

    // Verificação das pistas da direita
    for (i = 0; i < size; i++) {
        max = 0;
        visible = 0;
        for (j = size - 1; j >= 0; j--) {
            if (grid[i][j] > max) {
                max = grid[i][j];
                visible++;
            }
        }
        if (visible != clues[i + 3 * size])
            return 0;
    }

    return 1;
}

// Função para encontrar a melhor célula vazia (heurística de menor domínio)
int find_best_empty_cell(int grid[MAX_SIZE][MAX_SIZE], int size, int *row, int *col) {
    int min_options = size + 1;
    int best_row = -1, best_col = -1;

    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (grid[r][c] == 0) {
                int options = 0;
                for (int num = 1; num <= size; num++) {
                    if (can_place(grid, size, r, c, num)) {
                        options++;
                    }
                }
                if (options < min_options) {
                    min_options = options;
                    best_row = r;
                    best_col = c;
                }
            }
        }
    }

    *row = best_row;
    *col = best_col;
    return (best_row != -1);
}

// Função de verificação das condições (Forward Checking)
int forward_checking(int grid[MAX_SIZE][MAX_SIZE], int size, int row, int col, int num) {
    grid[row][col] = num;
    for (int i = 0; i < size; i++) {
        if ((grid[row][i] == num && i != col) || (grid[i][col] == num && i != row)) {
            grid[row][col] = 0;
            return 0;
        }
    }
    return 1;
}

// Função para resolver o puzzle com heurística de escolha de células e forward checking
int solve(int grid[MAX_SIZE][MAX_SIZE], int size, int *clues, int row, int col) {
    if (row == size) {
        return check_clues(grid, size, clues);
    }

    if (!find_best_empty_cell(grid, size, &row, &col)) {
        return check_clues(grid, size, clues);
    }

    for (int num = 1; num <= size; num++) {
        if (can_place(grid, size, row, col, num) && forward_checking(grid, size, row, col, num)) {
            grid[row][col] = num;
            if (solve(grid, size, clues, 0, 0)) {
                return 1;
            }
            grid[row][col] = 0;
        }
    }

    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        ft_putstr("Error\n");
        return 1;
    }

    int size;
    if (!is_valid_input(argv[1], &size)) {
        ft_putstr("Error\n");
        return 1;
    }

    int clues[4 * MAX_SIZE];
    for (int i = 0; i < 4 * size; i++) {
        clues[i] = argv[1][2 * i] - '0';
    }

    int grid[MAX_SIZE][MAX_SIZE];
    init_grid(grid, size);

    if (solve(grid, size, clues, 0, 0)) {
        print_grid(grid, size);
    } else {
        ft_putstr("Error\n");
    }

    return 0;
}
