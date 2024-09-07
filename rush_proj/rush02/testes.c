/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:26:15 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/09/01 15:25:28 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 256
#define MAX_MSG_LENGTH 512

// Função para ler o conteúdo do arquivo numbers.dict
char *read_file(const char *filename, size_t *size) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        const char *error_msg = "Erro ao abrir o arquivo\n";
        write(2, error_msg, 25);
        return NULL;
    }

    off_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size < 0) {
        const char *error_msg = "Erro ao obter o tamanho do arquivo\n";
        write(2, error_msg, 36);
        close(fd);
        return NULL;
    }
    lseek(fd, 0, SEEK_SET);

    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        const char *error_msg = "Erro ao alocar memória\n";
        write(2, error_msg, 23);
        close(fd);
        return NULL;
    }

    ssize_t bytes_read = read(fd, buffer, file_size);
    if (bytes_read < 0) {
        const char *error_msg = "Erro ao ler o arquivo\n";
        write(2, error_msg, 22);
        free(buffer);
        close(fd);
        return NULL;
    }

    buffer[file_size] = '\0'; // Adiciona o terminador nulo
    close(fd);
    
    if (size) {
        *size = file_size;
    }

    return buffer;
}

// Função para calcular o comprimento de uma string
size_t my_strlen(const char *str) {
    size_t length = 0;
    while (*str++) {
        length++;
    }
    return length;
}

// Função para copiar uma string
char *my_strcpy(char *dest, const char *src) {
    char *orig_dest = dest;
    while ((*dest++ = *src++)) {
        ;
    }
    return orig_dest;
}

// Função para converter um número inteiro para string
int my_itoa(int num, char *str, int base) {
    char *p = str;
    char *p1, *p2;
    int digits = 0;
    int temp_num;
    
    if (num == 0) {
        *p++ = '0';
        *p = '\0';
        return 1;
    }
    
    temp_num = num;
    while (temp_num) {
        temp_num /= base;
        digits++;
    }

    p += digits;
    *p = '\0';

    while (num) {
        *--p = "0123456789"[num % base];
        num /= base;
    }

    return digits;
}

// Função para encontrar a representação em inglês do número
char *find_number_in_dict(const char *dict, size_t dict_size, int number) {
    const char *ptr = dict;
    const char *end = dict + dict_size;

    while (ptr < end) {
        int dict_number;
        char dict_word[MAX_WORD_LENGTH];
        char *word_ptr = dict_word;

        // Lê o número da linha
        while (ptr < end && *ptr >= '0' && *ptr <= '9') {
            *word_ptr++ = *ptr++;
        }
        *word_ptr = '\0';

        if (*ptr == ' ') ptr++;
        
        // Lê a palavra da linha
        word_ptr = dict_word;
        while (ptr < end && *ptr != '\n') {
            *word_ptr++ = *ptr++;
        }
        *word_ptr = '\0';

        // Converte a string do número em um inteiro
        dict_number = 0;
        word_ptr = dict_word;
        while (*word_ptr) {
            dict_number = dict_number * 10 + (*word_ptr - '0');
            word_ptr++;
        }

        if (dict_number == number) {
            char *result = (char *)malloc(my_strlen(dict_word) + 1);
            if (result == NULL) {
                const char *error_msg = "Erro ao alocar memória\n";
                write(2, error_msg, 23);
                return NULL;
            }
            my_strcpy(result, dict_word);
            return result;
        }
        
        // Pular o caractere '\n'
        if (ptr < end && *ptr == '\n') {
            ptr++;
        }
    }

    return NULL; // Número não encontrado
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        const char *usage_msg = "Uso: ./programa <número>\n";
        write(2, usage_msg, 25);
        return 1;
    }

    // Converte o argumento para inteiro
    int number = 0;
    char *arg = argv[1];
    while (*arg) {
        if (*arg >= '0' && *arg <= '9') {
            number = number * 10 + (*arg - '0');
        } else {
            const char *error_msg = "Entrada inválida\n";
            write(2, error_msg, 18);
            return 1;
        }
        arg++;
    }

    size_t dict_size;
    char *dict_content = read_file("numbers.dict", &dict_size);
    if (dict_content == NULL) {
        return 1;
    }

    char result_str[MAX_MSG_LENGTH];
    char number_str[20];
    char *msg_ptr = result_str;

    // Converte o número para string
    my_itoa(number, number_str, 10);

    // Cria a mensagem
    msg_ptr = my_strcpy(msg_ptr, "Número ");
    msg_ptr = my_strcpy(msg_ptr, number_str);
    msg_ptr = my_strcpy(msg_ptr, " em inglês é: ");

    char *result = find_number_in_dict(dict_content, dict_size, number);
    if (result != NULL) {
        msg_ptr = my_strcpy(msg_ptr, result);
        free(result);
    } else {
        msg_ptr = my_strcpy(msg_ptr, "Número não encontrado no dicionário\n");
    }

    // Adiciona o terminador de linha
    *msg_ptr++ = '\n';
    *msg_ptr = '\0';

    write(1, result_str, my_strlen(result_str));

    free(dict_content);
    return 0;
}



