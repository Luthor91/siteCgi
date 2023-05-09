#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 100
#define MAX_VALUE_LEN 1000
#define MAX_LINE_LENGTH 1024

void top(char *);
void body(int , ...);
void bottom(void);
int get_visits(void);
char *decode(char *, char *);
void get_html(char *urlFile);

int main(void)
{
     int a=0, b=0;
     char str_nb_visites[50];
     char montexte[80] = "";
     // Les variables de l'url
     char *data = getenv("QUERY_STRING"); 
     sprintf(str_nb_visites, "Jusque-la, il y a eu %d visites.", get_visits());
     char *urlFile = "Accueil.html";
     get_html(urlFile);




     /*
     printf("Content-Type: text/html;\n\n");
     top('Ma page en C !");
     body(3, 'Fin de page', str_nb_visites, '<a href=goldenBook.cgi>Livre d'or</a>");
     bottom();
     if(fscanf(stdin, 'data=%80[^&]s', montexte) < 0)
          printf("<p>Le formulaire a été mal rempli !</p>");
     else
          printf("Voici ce que vous avez écrit : %s', montexte);
     if(data == NULL)
     {
          printf("<p>Erreur dans le script !</p>");
     }
     else
     {
          if(sscanf(data, 'a=%d&b=%d', &a, &b) != 2) // On récupère les deux chiffres a et b
               printf("<p>Vous devez passer des chiffres en données !");
          else
               printf("<p>%dx%d = %d ! :)</p>', a, b, a*b);
     }
     
     */




     return 0;
}


void get_html(char *urlFile) {
    FILE *fp = fopen(urlFile, "r");
    if (fp == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", urlFile);
        exit(1);
    }
    
    char line[MAX_LINE_LENGTH];
    int maxLines = 0;
    
    // On récupère le nombre de lignes du fichier
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        maxLines++;
    }
    rewind(fp); // On remet le curseur en début de fichier
    
    // On parcourt le fichier et on affiche les 10 premières lignes
    for (int i = 0; i < maxLines; i++) {
        if (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
            // Remplacement des guillemets simples par des doubles
            char *pos = NULL;
            while ((pos = strchr(line, '\'')) != NULL) {
                *pos = '\"';
            }
            printf("%s", line);
        }
    }
    fclose(fp);
}

/* On sépare le squelette HTML du reste du code */
void top(char *title) {
     printf("<!DOCTYPE html PUBLIC \'-//W3C//DTD XHTML 1.0 Strict//EN\' \'http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\'>\n<html xmlns=\'http://www.w3.org/1999/xhtml\' xml:lang=\'fr\' >\n\t<head>");
     printf("\t\t<title>%s</title>","title");
     printf("\t\t<meta http-equiv=\'Content-Type\' content=\'text/html; charset=utf-8\' />\n\t</head>\n\t<body>");
}

void body(int count, ...)
{
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        char* str = va_arg(args, char*);
        printf("%s<br>", str);
    }
    va_end(args);
}

void bottom() {
     printf("\t</body>\n</html>");
}

int get_visits(){
    int visites = 0;
    FILE *fichier = NULL;
    fichier = fopen("data/compteur.txt", "r+");
    if(fichier != NULL)
    {
        fscanf(fichier, "%d", &visites);
        fseek(fichier, 0, SEEK_SET);
        fprintf(fichier, "%d", visites+1);
        fclose(fichier);
    }
    return visites+1;
}

/*
     decode(char *str, char *fin)
     Inputs : 
          char *str
          char *fin
     Output : 
          char
     Fonctionnement :    
          Les espaces sont remplacés par des + ;
          Les caractères spéciaux (+, &, %, ...) deviennent '%' suivi de leur code ascii traduit en hexadécimal 
*/
char *decode(char *str, char *fin)
{
     char *dest = strdup(str);
     if (dest == NULL)
          return NULL;
     char *ret = dest;

     for (; str < fin && *str != '\0'; str++, dest++)
     {
          if (*str == '+')
               *dest = ' ';
          else if (*str == '%')
          {
               ++str;
               if (*str == '\0')
                    break;
               int code = '?';
               sscanf(str, "%2x", &code);
               *dest = code;

               str++;
               if (*str == '\0')
                    break;
          }
          else
               *dest = *str;
     }
     *dest = '\0';
     return ret;
}
