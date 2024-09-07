/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 11:06:36 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/08/24 17:16:07 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

    #include <unistd.h>
    #include <stdlib.h>

#define GRID_SIZE 4

// Função para verificar se um número pode ser colocado em uma posição (sem repetir na linha/coluna)
int can_place(int grid[GRID_SIZE][GRID_SIZE], int row, int col, int num) {
    for (int i = 0; i < GRID_SIZE; i++) {
        if (grid[row][i] == num || grid[i][col] == num)
            return 0;
    }
    return 1;
}

// Função para verificar se a solução atual atende a todas as condições de visibilidade
int is_valid(int grid[GRID_SIZE][GRID_SIZE], int *input) {
    int visible, max, i, j;

    // Verifica colunas de cima para baixo
    for (i = 0; i < GRID_SIZE; i++) {
        visible = 0;
        max = 0;
        for (j = 0; j < GRID_SIZE; j++) {
            if (grid[j][i] > max) {
                max = grid[j][i];
                visible++;
            }
        }
        if (visible != input[i]) return 0;
    }

    // Verifica colunas de baixo para cima
    for (i = 0; i < GRID_SIZE; i++) {
        visible = 0;
        max = 0;
        for (j = GRID_SIZE - 1; j >= 0; j--) {
            if (grid[j][i] > max) {
                max = grid[j][i];
                visible++;
            }
        }
        if (visible != input[GRID_SIZE + i]) return 0;
    }

    // Verifica linhas da esquerda para a direita
    for (i = 0; i < GRID_SIZE; i++) {
        visible = 0;
        max = 0;
        for (j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] > max) {
                max = grid[i][j];
                visible++;
            }
        }
        if (visible != input[2 * GRID_SIZE + i]) return 0;
    }

    // Verifica linhas da direita para a esquerda
    for (i = 0; i < GRID_SIZE; i++) {
        visible = 0;
        max = 0;
        for (j = GRID_SIZE - 1; j >= 0; j--) {
            if (grid[i][j] > max) {
                max = grid[i][j];
                visible++;
            }
        }
        if (visible != input[3 * GRID_SIZE + i]) return 0;
    }

    return 1;
}

// Função recursiva para tentar preencher o grid
int solve(int grid[GRID_SIZE][GRID_SIZE], int *input, int row, int col) {
    if (row == GRID_SIZE) {
        return is_valid(grid, input);
    }

    if (col == GRID_SIZE) {
        return solve(grid, input, row + 1, 0);
    }

    for (int num = 1; num <= GRID_SIZE; num++) {
        if (can_place(grid, row, col, num)) {
            grid[row][col] = num;
            if (solve(grid, input, row, col + 1)) {
                return 1;
            }
            grid[row][col] = 0;
        }
    }

    return 0;
}

// Função para converter um inteiro para um caractere
void put_char(char c) {
    write(1, &c, 1);
}

// Função para imprimir o grid
void print_grid(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            put_char(grid[i][j] + '0');
            if (j < GRID_SIZE - 1)
                put_char(' ');
        }
        put_char('\n');
    }
}

// Função principal
int main(int argc, char **argv) {
    if (argc != 2) {
        write(1, "Error\n", 6);
        return 1;
    }

    int *input = (int *)malloc(16 * sizeof(int));
    for (int i = 0; i < 16; i++) {
        if (argv[1][i * 2] < '1' || argv[1][i * 2] > '4') {
            write(1, "Error\n", 6);
            free(input);
            return 1;
        }
        input[i] = argv[1][i * 2] - '0';
    }

    int grid[GRID_SIZE][GRID_SIZE] = {0};

    if (solve(grid, input, 0, 0)) {
        print_grid(grid);
    } else {
        write(1, "Error\n", 6);
    }

    free(input);
    return 0;
}
