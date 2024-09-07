
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct  s_dict
{
    char        *number;
    char        *word;
    struct s_dict *next;
}               t_dict;

// Function Prototypes
t_dict  *parse_dict(char *dict_path);
void    free_dict(t_dict *dict);
char    *get_word_from_dict(t_dict *dict, char *number);
int     is_valid_number(char *str);
void    print_error(char *error_message);
void    convert_number(t_dict *dict, char *number);
void    print_word(char *word);

// Main function
int main(int argc, char **argv)
{
    t_dict *dictionary;
    char   *dict_path;
    char   *number_to_convert;

    if (argc == 2)
    {
        dict_path = "numbers.dict"; // Default dictionary
        number_to_convert = argv[1];
    }
    else if (argc == 3)
    {
        dict_path = argv[1];
        number_to_convert = argv[2];
    }
    else
    {
        print_error("Error\n");
        return (1);
    }

    // Validate the number
    if (!is_valid_number(number_to_convert))
    {
        print_error("Error\n");
        return (1);
    }

    // Parse the dictionary
    dictionary = parse_dict(dict_path);
    if (!dictionary)
    {
        print_error("Dict Error\n");
        return (1);
    }

    // Convert the number to its word form
    convert_number(dictionary, number_to_convert);

    // Free the dictionary
    free_dict(dictionary);
    return (0);
}

// Function to print errors
void print_error(char *error_message)
{
    write(1, error_message, strlen(error_message));
}

// Function to validate if a string is a valid number
int is_valid_number(char *str)
{
    int i = 0;
    if (str[i] == '-' || str[i] == '+') i++;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

// Function to parse the dictionary file
t_dict *parse_dict(char *dict_path)
{
    int fd;
    char buffer[BUFFER_SIZE + 1];
    int bytes_read;
    t_dict *dict = NULL;
    t_dict *current = NULL;
    
    fd = open(dict_path, O_RDONLY);
    if (fd < 0)
        return (NULL);
    
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        char *line = strtok(buffer, "\n");
        while (line != NULL)
        {
            t_dict *new_entry = (t_dict *)malloc(sizeof(t_dict));
            if (!new_entry)
            {
                free_dict(dict);
                close(fd);
                return (NULL);
            }

            char *colon = strchr(line, ':');
            if (colon)
            {
                *colon = '\0';
                new_entry->number = strdup(line);
                new_entry->word = strdup(colon + 1);

                // Trim spaces using malloced memory
                char *trimmed_number = strtok(new_entry->number, " ");
                char *trimmed_word = strtok(new_entry->word, " ");
                new_entry->number = strdup(trimmed_number);
                new_entry->word = strdup(trimmed_word);

                new_entry->next = NULL;

                if (!dict)
                    dict = new_entry;
                else
                    current->next = new_entry;
                current = new_entry;
            }
            else
            {
                free(new_entry);
                free_dict(dict);
                close(fd);
                return (NULL);
            }
            line = strtok(NULL, "\n");
        }
    }
    close(fd);
    return (dict);
}

// Function to get word from dictionary
char *get_word_from_dict(t_dict *dict, char *number)
{
    while (dict)
    {
        if (strcmp(dict->number, number) == 0)
            return (dict->word);
        dict = dict->next;
    }
    return (NULL);
}

// Function to convert number to word
void convert_number(t_dict *dict, char *number)
{
    char *word = get_word_from_dict(dict, number);
    if (word)
        print_word(word);
    else
        print_error("Dict Error\n");
}

// Function to print the word
void print_word(char *word)
{
    write(1, word, strlen(word));
    write(1, "\n", 1);
}

// Function to free the dictionary
void free_dict(t_dict *dict)
{
    t_dict *tmp;

    while (dict)
    {
        tmp = dict;
        dict = dict->next;
        free(tmp->number);
        free(tmp->word);
        free(tmp);
    }
}
