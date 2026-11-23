#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage : %s <nombre_elements>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *end;
    errno = 0;
    long n = strtol(argv[1], &end, 10);
    if (errno != 0 || *end != '\0' || n <= 0) {
        fprintf(stderr, "Erreur : '%s' n'est pas un entier strictement positif\n", argv[1]);
        return EXIT_FAILURE;
    }
    size_t count = (size_t)n;

    /* Tableaux declares comme pointeurs sur void */
    void *tab_malloc = malloc(count * sizeof(unsigned int));
    if (tab_malloc == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }
    void *tab_calloc = calloc(count, sizeof(unsigned int));
    if (tab_calloc == NULL) {
        perror("calloc");
        free(tab_malloc);
        return EXIT_FAILURE;
    }

    /* Initialisation commentee (Question 1.3.2)
    for (void *p = tab_malloc; p < tab_malloc + count; p++)
        *p = (unsigned int)(p - tab_malloc);
    for (void *p = tab_calloc; p < tab_calloc + count; p++)
        *p = (unsigned int)(p - tab_calloc) * 10;
    */

    /* Cast en int * pour pouvoir lire les valeurs */
    printf("=== Tableau alloue avec malloc ===\n");
    for (size_t i = 0; i < count; i++)
        printf("tab_malloc[%zu] : adresse = %p, valeur = %d\n",
               i, (void *)((int *)tab_malloc + i), *((int *)tab_malloc + i));

    printf("\n=== Tableau alloue avec calloc ===\n");
    for (size_t i = 0; i < count; i++)
        printf("tab_calloc[%zu] : adresse = %p, valeur = %d\n",
               i, (void *)((int *)tab_calloc + i), *((int *)tab_calloc + i));

    free(tab_malloc);
    free(tab_calloc);
    return EXIT_SUCCESS;
}

/*
 * ==========================================================================
 *                  EXPLICATION - Question 1.3.2 : void *
 * ==========================================================================
 *
 * Compilation : gcc -Wall q1_3_2.c -o q1_3_2 && ./q1_3_2 5
 *
 * - malloc et calloc renvoient deja un void * : on peut le stocker tel quel.
 * - Un void * est une adresse "generique" : il ne porte aucune information
 *   sur le type ni sur la taille de ce qui est pointe.
 * - On ne peut donc PAS le dereferencer directement (*tab_malloc n'a pas de
 *   sens : combien d'octets lire ? comment les interpreter ?).
 * - Il faut le caster : (int *)tab_malloc indique au compilateur qu'il pointe
 *   sur des int de 4 octets. Ensuite ((int *)tab_malloc + i) avance bien
 *   de i * 4 octets, et * lit un int.
 * ==========================================================================
 */
