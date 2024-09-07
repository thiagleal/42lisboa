/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-02gpt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:13:15 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/09/01 14:50:29 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void ft_putstr(char *str) { //ok
    while (*str)
        write(1, str++, 1);
}

int is_valid_number(char *str) { //ok
    for (int i = 0; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

char *strip_spaces(char *str) { // ok
    while (*str == ' ') str++;  // Remove espaços no início
    char *end = str + strlen(str) - 1;
    while (end > str && *end == ' ') end--;  // Remove espaços no final
    *(end + 1) = '\0';
    return str;
}

char *find_in_dict(char *dict, char *number) {
    int fd = open(dict, O_RDONLY);
    if (fd == -1) {
        return NULL;
    }
    char buffer[1024];
    char *result = NULL;
    int bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        char *line = strtok(buffer, "\n");
        while (line) {
            char *key = strtok(line, ":");
            char *value = strtok(NULL, ":");
            if (key && value) {
                key = strip_spaces(key);
                value = strip_spaces(value);
                if (strcmp(key, number) == 0) {
                    result = strdup(value);
                    break;
                }
            }
            line = strtok(NULL, "\n");
        }
        if (result) break;
    }
    close(fd);
    return result;
}

void print_number(char *dict, char *number) { //ok
    char *result = find_in_dict(dict, number);
    if (result) {
        ft_putstr(result);
        ft_putstr("\n");
        free(result);
    } else {
        ft_putstr("Dict Error\n");
    }
}

int main(int argc, char **argv) {
    if (argc == 2) {
        if (is_valid_number(argv[1])) {
            print_number("dict.dict", argv[1]);
        } else {
            ft_putstr("Error\n");
        }
    } else if (argc == 3) {
        if (is_valid_number(argv[2])) {
            print_number(argv[1], argv[2]);
        } else {
            ft_putstr("Error\n");
        }
    } else {
        ft_putstr("Error\n");
    }
    return 0;
}


/*

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void ft_putstr(char *str) {
    while (*str)
        write(1, str++, 1);
}

int is_valid_number(char *str) {
    while (*str) {
        if (*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

char *strip_spaces(char *str) {
    // Remove espaços no início
    while (*str == ' ') str++;
    // Remove espaços no final
    char *end = str;
    while (*end) end++;
    end--;
    while (end > str && *end == ' ') end--;
    *(end + 1) = '\0';
    return str;
}

char *find_in_dict(char *dict, char *number) {
    int fd = open(dict, O_RDONLY);
    if (fd == -1) {
        return NULL;
    }
    
    char buffer[1024];
    char *result = NULL;
    int bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';

        char *ptr = buffer;
        char *line_start = ptr;
        
        while (*ptr) {
            if (*ptr == '\n' || *(ptr + 1) == '\0') {
                char *line_end = ptr;
                *line_end = '\0';  // Terminar a linha

                char *key_end = line_start;
                while (*key_end && *key_end != ':') key_end++;
                if (*key_end == ':') {
                    *key_end = '\0';  // Terminar a chave
                    key_end++;
                    char *value_start = key_end;
                    char *value_end = line_end;

                    *value_end = '\0';  // Terminar o valor

                    // Strip spaces
                    key_start = strip_spaces(line_start);
                    value_start = strip_spaces(value_start);

                    // Compare key with number
                    char *key_ptr = key_start;
                    char *num_ptr = number;
                    int match = 1;
                    while (*num_ptr) {
                        if (*key_ptr != *num_ptr) {
                            match = 0;
                            break;
                        }
                        key_ptr++;
                        num_ptr++;
                    }
                    if (*num_ptr != '\0') match = 0;

                    if (match && !*key_ptr) {
                        result = malloc(value_end - value_start + 1);
                        if (result) {
                            char *res_ptr = result;
                            while (value_start <= value_end) {
                                *res_ptr++ = *value_start++;
                            }
                            *res_ptr = '\0';
                        }
                        break;
                    }
                }

                line_start = ptr + 1;
            }
            ptr++;
        }

        if (result) break;
    }
    close(fd);
    return result;
}

void print_number(char *dict, char *number) {
    char *result = find_in_dict(dict, number);
    if (result) {
        ft_putstr(result);
        ft_putstr("\n");
        free(result);
    } else {
        ft_putstr("Dict Error\n");
    }
}

int main(int argc, char **argv) {
    if (argc == 2) {
        if (is_valid_number(argv[1])) {
            print_number("dict.dict", argv[1]);
        } else {
            ft_putstr("Error\n");
        }
    } else if (argc == 3) {
        if (is_valid_number(argv[2])) {
            print_number(argv[1], argv[2]);
        } else {
            ft_putstr("Error\n");
        }
    } else {
        ft_putstr("Error\n");
    }
    return 0;
}





*/