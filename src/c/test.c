#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction qui insère les données dans la page HTML
void insertData(char* question, char* answer) {
    // Ouverture du fichier HTML en mode écriture
    FILE *fp = fopen("../html/faq.html", "w");

    // Vérification que l'ouverture du fichier s'est bien passée
    if (fp == NULL) {
        //printf("Erreur : Impossible d'ouvrir le fichier\n");
        exit(1);
    }

    // Écriture du code HTML
    fprintf(fp, "<html>\n");
    fprintf(fp, "<head>\n");
    fprintf(fp, "<title>FAQ</title>\n");
    fprintf(fp, "</head>\n");
    fprintf(fp, "<body>\n");
    fprintf(fp, "<h1>FAQ</h1>\n");
    fprintf(fp, "<div>\n");
    fprintf(fp, "<h2>%s</h2>\n", question);
    fprintf(fp, "<p>%s</p>\n", answer);
    fprintf(fp, "</div>\n");
    fprintf(fp, "</body>\n");
    fprintf(fp, "</html>\n");

    // Fermeture du fichier
    fclose(fp);
}

int main() {
    // Exemple de données récupérées depuis une base de données
    char* question = "Comment utiliser CGI ?";
    char* answer = "Il faut écrire un programme CGI qui génère du code HTML.";

    printf("Content-Type:text/html;charset=utf-8\n\n");  // En-tête HTTP

    // Début du corps de la page
    printf("<!DOCTYPE html>\n");
    printf("<html>\n");
    printf("<head>\n");
    printf("<meta charset=\"UTF-8\">\n");
    printf("<title>Page HTML générée en C</title>\n");
    printf("<style>\n");
    printf("body { font-family: Arial, sans-serif; }\n");
    printf("h1 { color: #333; }\n");
    printf("p { font-size: 1.2em; }\n");
    printf("</style>\n");
    printf("</head>\n");
    printf("<body>\n");
    printf("<header>\n");
    printf("<h1>Bienvenue sur ma page générée en C !</h1>\n");
    printf("</header>\n");
    printf("<main>\n");
    printf("<p>Ceci est une page HTML générée en C, avec du style CSS intégré.</p>\n");
    printf("<p>Je suis un paragraphe de texte.</p>\n");
    printf("</main>\n");
    printf("<footer>\n");
    printf("<p>&copy; 2023 Mon site web</p>\n");
    printf("</footer>\n");
    printf("</body>\n");
    printf("</html>\n");

    // Insertion des données dans la page HTML
    //insertData(question, answer);

    return 0;
}
