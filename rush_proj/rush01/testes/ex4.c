/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex4.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:17:25 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/08/25 10:24:08 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int g[4][4], v[16];

void put_char(char c) { write(1, &c, 1); }

int	check_valid(int row, int col) {
	int i, max, visible;
	
	// Verificar a linha
	for (i = 0, max = 0, visible = 0; i < 4; i++)
		if (g[row][i] > max) {
			max = g[row][i];
			visible++;
		}
	if (visible != v[row + 8])
		return (0);
	
	for (i = 3, max = 0, visible = 0; i >= 0; i--)
		if (g[row][i] > max) {
			max = g[row][i];
			visible++;
		}
	if (visible != v[row + 12])
		return (0);

	// Verificar a coluna
	for (i = 0, max = 0, visible = 0; i < 4; i++)
		if (g[i][col] > max) {
			max = g[i][col];
			visible++;
		}
	if (visible != v[col])
		return (0);
	
	for (i = 3, max = 0, visible = 0; i >= 0; i--)
		if (g[i][col] > max) {
			max = g[i][col];
			visible++;
		}
	if (visible != v[col + 4])
		return (0);

	return (1);
}

int solve(int row, int col) {
	int num;

	if (row == 4)
		return (1);
	if (col == 4)
		return (solve(row + 1, 0));
	for (num = 1; num <= 4; num++) {
		int i, valid = 1;
		for (i = 0; i < row; i++)
			if (g[i][col] == num)
				valid = 0;
		for (i = 0; i < col; i++)
			if (g[row][i] == num)
				valid = 0;
		if (valid) {
			g[row][col] = num;
			if (check_valid(row, col) && solve(row, col + 1))
				return (1);
			g[row][col] = 0;
		}
	}
	return (0);
}

int main(int argc, char **argv) {
	int i, j;

	if (argc != 2)
		return (write(1, "Error\n", 6), 1);
	for (i = 0; i < 16; i++)
		v[i] = argv[1][i * 2] - '0';
	if (solve(0, 0))
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				put_char(g[i][j] + '0');
				put_char(j == 3 ? '\n' : ' ');
			}
		} else
		write(1, "Error\n", 6);
	return (0);
}