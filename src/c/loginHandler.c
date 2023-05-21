#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include "utils/cJSON.h"

#define USERS_FILE "users.json"
#define MAX_SIZE_ARG 50

typedef struct {
    char* key;
    char** value_ptr;
} Argument;

char *readcontent(const char *);
void get_post_args(Argument* arg_list, ...);
void free_post_args(void);

int main() {
    printf("Content-type:text/html\n\n");
    printf("<html>\n<head>\n<title>CGI Login Form</title>\n</head>\n<body>\n");
    //char username[21];
    //char password[21];
    bool username_found = false;
    bool password_match = false;

    // Définir les arguments attendus
    char* username = malloc(MAX_SIZE_ARG * sizeof(char));
    char* password = malloc(MAX_SIZE_ARG * sizeof(char));

    // Créer les structures d'argument
    Argument args[] = {
        { "username", &username },
        { "password", &password },
        { NULL, NULL } // Terminateur
    };

    // Appeler la fonction get_post_args avec les arguments
    get_post_args(args, &args[0], &args[1], NULL);
    //get_post_args("username", &username, "password", &password, NULL);
    free_post_args();

    if (username != NULL && *username != '\0') {
        printf("<br>username = %s<BR>", username);
    }
    if (password != NULL && *password != '\0') {
        printf("<br>password = %s<BR>", password);
    }

    if(strcmp(username, "user") && strcmp(password, "password")) {
        username_found = true;
        password_match = true;

    }

    //printf("Content-Type: text/html\n");

    if (username_found && password_match) {
        printf("Location: ../html/index.html\n\n");
    } else {
        printf("Location: ../html/error.html\n\n");
    }

    printf("</body>\n</html>\n");
    return 0;
}


char *readcontent(const char *filename)
{
    char *fcontent = NULL;
    int fsize = 0;
    FILE *fp;

    fp = fopen(filename, "r");
    if(fp) {
        fseek(fp, 0, SEEK_END);
        fsize = ftell(fp);
        rewind(fp);

        fcontent = (char*) malloc(sizeof(char) * fsize);
        fread(fcontent, 1, fsize, fp);

        fclose(fp);
    }
    return fcontent;
}

void get_post_args(Argument* args, ...)
{
    char* data = NULL;
    char* token = NULL;
    char* key = NULL;
    char* value = NULL;
    size_t len = 0;
    size_t read = 0;
    // Récupération de la méthode HTTP et du contenu de la requête
    char* request_method = getenv("REQUEST_METHOD");

    // Requête vide ou ne contient aucune information
    if (request_method == NULL || strcmp(request_method, "POST") != 0) {
        printf("<br>Status: 400 Bad Request");
        printf("<br>Erreur : requête non valide");
        return;
    }

    // Récupération de la taille des données POST
    char* content_length_str = getenv("CONTENT_LENGTH");
    // Arguments vide 
    if (content_length_str == NULL) {
        printf("<br>Status: 400 Bad Request\r\n\r\n");
        printf("<br>Erreur : taille des données POST non spécifiée\n");
        return;
    }
    // string to int conversion
    int content_length = atoi(content_length_str);
    // Allocation de mémoire pour les données POST
    data = (char*)malloc(content_length + 1); // +1

    if (data == NULL) {
        printf("<br>Status: 500 Internal Server Error\r\n\r\n");
        printf("<br>Erreur : mémoire insuffisante\n");
        free(data);
        return;
    }

    // Lecture des données POST à partir de stdin
    read = fread(data, 1, content_length, stdin);
    printf("<br><br>Contenu de la requete POST : %s ; Longueur : %d<br><br>", data, content_length);

    if (read != content_length) {
        printf("<br>Status: 400 Bad Request\r\n\r\n");
        printf("<br>Erreur : taille des données POST invalide\n");
        free(data);
        return;
    }
    data[read] = '\0';

    // Traitement des données POST
    token = strtok(data, "&");
    va_list ap;
    va_start(ap, args);

    while (token != NULL) {
        key = strtok(token, "=");
        value = strtok(NULL, "=");
        if (key == NULL || value == NULL) {
            printf("skipped");
            continue;
        }
        printf("token = %s ; key : %s ; value : %s<br>", token, key, value);

        Argument* arg = args;

        while (arg->key != NULL) {
            if (strcmp(key, arg->key) == 0) {
                if (strlen(value) > MAX_SIZE_ARG - 1) {
                    printf("<br>Status: 400 Bad Request\r\n\r\n");
                    printf("<br>Erreur : la valeur de l'argument dépasse la taille maximale autorisée\n");
                    free(data);
                    va_end(ap);
                    return;
                }
                *(arg->value_ptr) = value;
                break;
            }
            arg++;
        }

        token = strtok(NULL, "&");
    }
    va_end(ap);
    free(data);
}




void free_post_args() {
    // Recuperation de la methode HTTP et du contenu de la requete
    char *request_method = getenv("REQUEST_METHOD");
    if (request_method == NULL || strcmp(request_method, "POST") != 0) {
        // La requete n'est pas de type POST, il n'y a rien a liberer
        return;
    }

    // Recuperation de la taille des donnees POST
    char *content_length_str = getenv("CONTENT_LENGTH");
    if (content_length_str == NULL) {
        // La taille des donnees POST n'a pas ete specifiee, il n'y a rien a liberer
        return;
    }
    int content_length = atoi(content_length_str);

    // Liberation de l'espace memoire alloue pour les donnees POST
    char *data = (char *) malloc(content_length + 1);
    if (data == NULL) {
        // Impossible de liberer l'espace memoire, il y a une erreur
        printf("<br>Status: 500 Internal Server Error\r\n\r\n");
        printf("<br>Erreur : memoire insuffisante\n");
        exit(EXIT_FAILURE);
    }

    // Liberation de l'espace memoire alloue pour les donnees POST
    free(data);
}
