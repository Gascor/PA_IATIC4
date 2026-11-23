#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage : %s <nombre_elements>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Conversion et verification du parametre */
    char *end;
    errno = 0;
    long n = strtol(argv[1], &end, 10);
    if (errno != 0 || *end != '\0' || n <= 0) {
        fprintf(stderr, "Erreur : '%s' n'est pas un entier strictement positif\n", argv[1]);
        return EXIT_FAILURE;
    }
    size_t count = (size_t)n;

    /* Allocation avec malloc : count * taille d'un unsigned int, NON initialise */
    unsigned int *tab_malloc = malloc(count * sizeof(unsigned int));
    if (tab_malloc == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    /* Allocation avec calloc : count elements de taille sizeof(unsigned int),
     * memoire mise a zero par calloc */
    unsigned int *tab_calloc = calloc(count, sizeof(unsigned int));
    if (tab_calloc == NULL) {
        perror("calloc");
        free(tab_malloc);
        return EXIT_FAILURE;
    }

    /* Aucune initialisation volontaire des tableaux */

    printf("=== Tableau alloue avec malloc ===\n");
    for (size_t i = 0; i < count; i++)
        printf("tab_malloc[%zu] : adresse = %p, valeur = %u\n",
               i, (void *)&tab_malloc[i], tab_malloc[i]);

    printf("\n=== Tableau alloue avec calloc ===\n");
    for (size_t i = 0; i < count; i++)
        printf("tab_calloc[%zu] : adresse = %p, valeur = %u\n",
               i, (void *)&tab_calloc[i], tab_calloc[i]);

    free(tab_malloc);
    free(tab_calloc);
    return EXIT_SUCCESS;
}

/*
 * ==========================================================================
 *              EXPLICATION - Question 1.2.1 : malloc et calloc
 * ==========================================================================
 *
 * Compilation / execution :
 *     gcc -Wall q1_2_1.c -o q1_2_1
 *     ./q1_2_1 42
 *
 * void *malloc(size_t size);
 *   - alloue "size" octets sur le TAS (heap) ;
 *   - la memoire n'est PAS initialisee : elle contient ce qui s'y trouvait
 *     avant (valeurs "aleatoires", souvent 0 sur une memoire neuve fournie
 *     par le systeme, mais rien ne le garantit) ;
 *   - renvoie NULL en cas d'echec.
 *
 * void *calloc(size_t nmemb, size_t size);
 *   - alloue un tableau de "nmemb" elements de "size" octets chacun ;
 *   - la memoire est INITIALISEE A ZERO : toutes les valeurs affichees
 *     valent donc 0 ;
 *   - verifie le depassement de nmemb * size (plus sur que malloc(n*size)) ;
 *   - renvoie NULL en cas d'echec.
 *
 * Observations :
 *   - Les adresses de chaque tableau sont consecutives et espacees de
 *     sizeof(unsigned int) = 4 octets (ex : ...2a0, ...2a4, ...2a8).
 *   - Les deux tableaux sont dans le tas, a des adresses differentes ;
 *     un petit ecart supplementaire separe les deux blocs (en-tete de
 *     gestion de l'allocateur).
 *   - Les valeurs du tableau malloc sont indeterminees (lire une valeur non
 *     initialisee est un comportement indefini en C : on le fait ici
 *     uniquement pour l'exercice). Celles du tableau calloc valent 0.
 *
 * Dans les deux cas, la memoire doit etre liberee avec free().
 * ==========================================================================
 */
