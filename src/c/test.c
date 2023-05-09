#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *query = getenv("QUERY_STRING");
    char *name = "inconnu";
    
    if (query != NULL) {
        char *name_start = strstr(query, "name=");
        if (name_start != NULL) {
            name_start += strlen("name=");
            char *name_end = strstr(name_start, "&");
            if (name_end == NULL) {
                name_end = query + strlen(query);
            }
            int name_len = name_end - name_start;
            name = malloc(name_len + 1);
            strncpy(name, name_start, name_len);
            name[name_len] = '\0';
        }
    }
    
    printf("Content-type:text/html\r\n\r\n");
    printf("<html>\n");
    printf("<head>\n");
    printf("<title>Bienvenue sur notre site web</title>\n");
    printf("</head>\n");
    printf("<body>\n");
    printf("<h1>Bonjour %s!</h1>\n", name);
    printf("<p>Merci d'avoir visité notre site web.</p>\n");
    printf("</body>\n");
    printf("</html>\n");

    free(name);
    return 0;
}
