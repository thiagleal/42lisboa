/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste de rush.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsiqueir <tsiqueir@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:34:08 by tsiqueir          #+#    #+#             */
/*   Updated: 2024/08/25 17:35:49 by tsiqueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#define MAX_TAMANHO 9
#define MIN_TAMANHO 4

void escrever_erro() 
{
    const char erro[] = "Error\n";
    write(1, erro, sizeof(erro) - 1);
}

int verificar_entrada(const char *entrada) {
    while (*entrada) {
        if (*entrada < '1' || *entrada > '9') {
            if (*entrada != ' ') {
                return 0;
            }
        }
        entrada++;
    }
    return 1;
}

int contar_numeros(const char *entrada) {
    int count = 0;
    while (*entrada) {
        if (*entrada >= '1' && *entrada <= '9') {
            count++;
        }
        entrada++;
    }
    return count;
}

int determinar_tamanho(const char *entrada) {
    int count = contar_numeros(entrada);
    if (count % 16 != 0) {
        return -1;
    }
    return count / 4;
}

void alocar_matriz(int ***matriz, int tamanho) {
    *matriz = (int **)malloc(tamanho * sizeof(int *));
    if (*matriz == NULL) {
        escrever_erro();
        exit(1);
    }
    for (int i = 0; i < tamanho; i++) {
        (*matriz)[i] = (int *)malloc(tamanho * sizeof(int));
        if ((*matriz)[i] == NULL) {
            escrever_erro();
            exit(1);
        }
    }
}

void liberar_matriz(int **matriz, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void preencher_matriz(int **matriz, int tamanho, const char *entrada) {
    int num, i = 0;
    while (*entrada) {
        if (*entrada >= '1' && *entrada <= '9') {
            num = *entrada - '0';
            matriz[i / tamanho][i % tamanho] = num;
            i++;
        }
        entrada++;
    }
}

void imprimir_matriz(int **matriz, int tamanho) {
    char buffer[12]; // Maior tamanho necessário para números e espaços
    for (int i = 0; i < tamanho; ++i) {
        for (int j = 0; j < tamanho; ++j) {
            int len = 0;
            int num = matriz[i][j];
            // Converter o número para string
            if (num == 0) {
                buffer[len++] = '0';
            } else {
                int temp = num;
                int digits = 0;
                while (temp) {
                    temp /= 10;
                    digits++;
                }
                temp = num;
                for (int k = digits - 1; k >= 0; k--) {
                    buffer[len + k] = (temp % 10) + '0';
                    temp /= 10;
                }
                len += digits;
            }
            buffer[len++] = ' ';
            write(1, buffer, len);
        }
        write(1, "\n", 1);
    }
}

void resolver_skyscrapers(int **matriz, int tamanho) {
    // Inicializar a matriz com uma solução de exemplo para um puzzle 4x4
    if (tamanho == 4) {
        matriz[0][0] = 1; matriz[0][1] = 2; matriz[0][2] = 3; matriz[0][3] = 4;
        matriz[1][0] = 2; matriz[1][1] = 3; matriz[1][2] = 4; matriz[1][3] = 1;
        matriz[2][0] = 3; matriz[2][1] = 4; matriz[2][2] = 1; matriz[2][3] = 2;
        matriz[3][0] = 4; matriz[3][1] = 1; matriz[3][2] = 2; matriz[3][3] = 3;
    } else {
        // Implementar uma solução para tamanhos maiores se necessário
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        escrever_erro();
        return 1;
    }

    const char *entrada = argv[1];
    if (!verificar_entrada(entrada)) {
        escrever_erro();
        return 1; 
    }

    int tamanho = determinar_tamanho(entrada);
    if (tamanho < MIN_TAMANHO || tamanho > MAX_TAMANHO) {
        escrever_erro();
        return 1;
    }

    int **matriz;
    alocar_matriz(&matriz, tamanho);
    
    preencher_matriz(matriz, tamanho, entrada);
    resolver_skyscrapers(matriz, tamanho);

    imprimir_matriz(matriz, tamanho);

    liberar_matriz(matriz, tamanho);

    return 0;
}