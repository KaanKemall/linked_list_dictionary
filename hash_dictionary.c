#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char *key;
    char *value;
    struct node *next;
} node;

typedef struct dictionary
{
    node *table[10];
    int length;
} dictionary;

int hash_function(char *key)
{
    int count = 0;
    int length = strlen(key);
    for (int i = 0; i < length; i++)
    {
        count += key[i];
    }
    return count % 10;
}

void dictionary_create(dictionary *dict)
{
    for (int i = 0; i < 10; i++)
    {
        dict->table[i] = NULL;
    }

    dict->length = 0;
}

void dictionary_add(dictionary *dict, char *key, char *value)
{
    int hash_value = hash_function(key);

    node *new_node = malloc(sizeof(node));
    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = NULL;

    if (dict->table[hash_value] == NULL)
    {
        dict->table[hash_value] = new_node;
    }
    else
    {
        node *temp = dict->table[hash_value];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    dict->length++;
}

void dictionary_print(dictionary *dict)
{
    for (int i = 0; i < 10; i++)
    {
        node *temp = dict->table[i];
        while (temp != NULL)
        {
            printf("%s -> %s\n", temp->key, temp->value);
            temp = temp->next;
        }
    }
    printf("%d\n", dict->length);
}

char *dictionary_get_value(dictionary *dict, char *key)
{
    int hash_value = hash_function(key);
    node *temp = dict->table[hash_value];

    while (temp != NULL)
    {
        if (strcmp(temp->key, key) == 0)
        {
            return temp->value;
        }
        temp = temp->next;
    }
    printf("\nNo key\n");
}

void dictionary_remove(dictionary *dict, char *key)
{
    int hash_value = hash_function(key);
    node *temp = dict->table[hash_value];

    if (temp != NULL && strcmp(temp->key, key) == 0)
    {
        dict->table[hash_value] = temp->next;
        free(temp);
        dict->length--;
        return;
    }
    
    while (temp != NULL)
    {
        if (temp->next != NULL && strcmp(temp->next->key, key) == 0)
        {
            node *temp2 = temp->next->next;
            free(temp->next);
            temp->next = temp2;
            dict->length--;
            return;
        }
        temp = temp->next;
    }
    printf("\nCant remove\n");
}

int main()
{
    dictionary dict;
    dictionary_create(&dict);

    dictionary_add(&dict, "bir", "one");
    dictionary_add(&dict, "iki", "two");
    dictionary_add(&dict, "uc", "three");
    dictionary_add(&dict, "dort", "four");
    dictionary_add(&dict, "bes", "five");
    dictionary_add(&dict, "alti", "six");
    dictionary_add(&dict, "yedi", "seven");
    dictionary_add(&dict, "sekiz", "eight");
    dictionary_add(&dict, "dokuz", "nine");
    dictionary_add(&dict, "on", "ten");
    dictionary_add(&dict, "on bir", "eleven");
    dictionary_add(&dict, "on iki", "twelve");

    dictionary_print(&dict);

    printf(dictionary_get_value(&dict, "dort"));
    dictionary_get_value(&dict, "on bes");

    dictionary_remove(&dict, "bes");
    dictionary_remove(&dict, "yirmi");

    dictionary_print(&dict);
}