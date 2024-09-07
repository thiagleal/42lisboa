/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:28:31 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/08/25 20:41:08 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define ALLOWED_ARGS	2
#define	GAME_SIZE		16
#define	ROWS			4
#define	COLS			4
#include <unistd.h>

extern int	g_borders[tam];
int			g_final_solution[lin][col];
int			g_found_final_solution = 0;

void	put_char(char c)
{
	write(1, &c, 1);
}

void	put_str(const char *str, int len)
{
	int		i;
	char	c;

	c = str[0];
	i = 1;
	while (c != '\0' && i <= len)
	{
		put_char(c);
		c = str[i];
		i++;
	}
}

void	put_num_as_char(int num)
{
	char	c;

	c = num + '0';
	put_char(c);
}

int		count_str_len(char *str)
{
	int		overflow;
	int		len;
	char	c;

	c = str[0];
	len = 1;
	overflow = 100;
	while (c != '\0' && len < overflow)
	{
		c = str[len];
		len++;
	}
	return (len);
}

int		show_error(void)
{
	write(1, "Error\n", 6);
	return (2);
}

int	does_not_satisfy_upper_border(int board[lin][col])
{
	int col;
	int box_count;
	int tallest_box;
	int border_idx;

	border_idx = 0;
	col = 0;
	while (border_idx < (tam - 12))
	{
		box_count = 0;
		tallest_box = 0;
		iterate_row_forw(board, col, &tallest_box, &box_count);
		if (box_count != g_borders[border_idx])
			return (1);
		border_idx++;
		col++;
	}
	return (0);
}

int	does_not_satisfy_lower_border(int board[lin][col])
{
	int col;
	int box_count;
	int tallest_box;
	int border_idx;

	border_idx = tam - 12;
	col = 0;
	while (border_idx < (tam - 8))
	{
		box_count = 0;
		tallest_box = 0;
		iterate_row_back(board, col, &tallest_box, &box_count);
		if (box_count != g_borders[border_idx])
			return (1);
		border_idx++;
		col++;
	}
	return (0);
}

int	does_not_satisfy_left_border(int board[lin][col])
{
	int row;
	int box_count;
	int tallest_box;
	int border_idx;

	border_idx = tam - 8;
	row = 0;
	while (border_idx < (tam - 4))
	{
		box_count = 0;
		tallest_box = 0;
		iterate_col_forw(board, row, &tallest_box, &box_count);
		if (box_count != g_borders[border_idx])
			return (1);
		border_idx++;
		row++;
	}
	return (0);
}

int	does_not_satisfy_right_border(int board[lin][col])
{
	int row;
	int box_count;
	int tallest_box;
	int border_idx;

	row = 0;
	border_idx = tam - 4;
	while (border_idx < tam)
	{
		box_count = 0;
		tallest_box = 0;
		iterate_col_back(board, row, &tallest_box, &box_count);
		if (box_count != g_borders[border_idx])
			return (1);
		border_idx++;
		row++;
	}
	return (0);
}

int			g_found_final_solution = 0;

int		should_stop_checking(int idx)
{
	return ((idx == tam) || g_found_final_solution);
}

void	handle_final_solution(int board[lin][col])
{
	g_found_final_solution = 1;
	copy_board(board, g_final_solution);
}

int		check_board(int board[lin][col], int i, int idx)
{
	int row_or_col;

	row_or_col = 0;
	while (row_or_col < idx / lin || row_or_col < idx % col)
	{
		if (i == board[row_or_col][idx % col] ||
			i == board[idx / lin][row_or_col])
			return (0);
		row_or_col++;
	}
	return (1);
}

void	modify_board(int board[lin][col], int idx)
{
	int test_board[lin][col];
	int is_valid;
	int i;

	if (should_stop_checking(idx))
	{
		if (ft_is_valid_solution(board))
			handle_final_solution(board);
		return ;
	}
	i = 1;

	while (i <= lin)
	{
		is_valid = 1;
		copy_board(board, test_board);
		is_valid = check_board(board, i, idx);
		if (is_valid)
		{
			test_board[idx / lin][idx % col] = i;
			modify_board(test_board, idx + 1);
			test_board[idx / lin][idx % col] = 0;
		}
		i++;
	}
}

int		solve_board(void)
{
	int	start_idx;
	int	board[lin][col];

	start_idx = 0;
	create_board(board);
	modify_board(board, start_idx);
	if (!g_found_final_solution)
		return (show_error());
	show_board(g_final_solution);
	return (0);
}

int		ft_is_space(char c)
{
	return (c == ' ');
}

int		ft_is_valid_num(char c)
{
	return (c >= '1' && c <= '4');
}

int		ft_is_valid_format(char *str)
{
	char	c;
	int		valid_n_count;
	int		i;

	i = 0;
	valid_n_count = 0;
	c = str[i];
	while (c != '\0' && i < (tam * 2 - 1))
	{
		if (i % 2 == 0)
		{
			if (ft_is_valid_num(c))
				valid_n_count++;
			else
				return (0);
		}
		else if (!ft_is_space(c))
			return (0);
		i++;
		c = str[i];
	}
	if (valid_n_count != tam)
		return (0);
	return (1);
}

int		ft_is_valid_argument(char *str)
{
	const int	expected_len = tam * 2;
	int			is_valid_len;

	is_valid_len = count_str_len(str) == expected_len;
	return (is_valid_len && ft_is_valid_format(str));
}

int		ft_is_valid_solution(int board[lin][col])
{
	if (does_not_satisfy_upper_border(board) ||
		does_not_satisfy_lower_border(board) ||
		does_not_satisfy_left_border(board) ||
		does_not_satisfy_right_border(board))
		return (0);
	return (1);
}

void	show_board(int board[lin][col])
{
	int	row;
	int	col;

	row = 0;
	while (row < lin)
	{
		col = 0;
		while (col < col)
		{
			put_num_as_char(board[row][col]);
			if (col != col - 1)
				put_char(' ');
			col++;
		}
		put_char('\n');
		row++;
	}
}

void	create_board(int board[lin][col])
{
	int	row;
	int	col;

	row = 0;
	while (row < lin)
	{
		col = 0;
		while (col < col)
		{
			board[row][col] = 0;
			col++;
		}
		row++;
	}
}

void	copy_board(int board[lin][col], int copy[lin][col])
{
	int row;
	int col;

	row = 0;
	while (row < lin)
	{
		col = 0;
		while (col < col)
		{
			copy[row][col] = board[row][col];
			col++;
		}
		row++;
	}
}

void	iterate_row_forw(int board[lin][col], int col,
	int *tallest_box, int *box_count)
{
	int row;

	row = 0;
	while (row < lin)
	{
		if (board[row][col] > *tallest_box)
		{
			*tallest_box = board[row][col];
			*box_count = *box_count + 1;
		}
		row++;
	}
}

void	iterate_row_back(int board[lin][col], int col,
	int *tallest_box, int *box_count)
{
	int row;

	row = 3;
	while (row >= 0)
	{
		if (board[row][col] > *tallest_box)
		{
			*tallest_box = board[row][col];
			*box_count = *box_count + 1;
		}
		row--;
	}
}

void	iterate_col_forw(int board[lin][col], int row,
	int *tallest_box, int *box_count)
{
	int col;

	col = 0;
	while (col < col)
	{
		if (board[row][col] > *tallest_box)
		{
			*tallest_box = board[row][col];
			*box_count = *box_count + 1;
		}
		col++;
	}
}

void	iterate_col_back(int board[lin][col], int row,
	int *tallest_box, int *box_count)
{
	int col;

	col = 3;
	while (col >= 0)
	{
		if (board[row][col] > *tallest_box)
		{
			*tallest_box = board[row][col];
			*box_count = *box_count + 1;
		}
		col--;
	}
}

char	*filter_args(char **args)
{
	args++;
	return (*args);
}

void	parse_arguments(char *str)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	c = str[i];
	while (c != '\0' && i < (tam * 2 - 1))
	{
		if (ft_is_valid_num(c))
		{
			g_borders[j] = c - '0';
			j++;
		}
		i++;
		c = str[i];
	}
}

int		main(int argc, char **argv)
{
	char	*filtered_args;

	if (argc != ALLOWED_ARGS)
		return (show_error());
	filtered_args = filter_args(argv);
	if (!ft_is_valid_argument(filtered_args))
		return (show_error());
	parse_arguments(filtered_args);
	return (solve_board());
}