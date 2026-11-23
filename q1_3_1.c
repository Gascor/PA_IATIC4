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

    unsigned int *tab_malloc = malloc(count * sizeof(unsigned int));
    if (tab_malloc == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }
    unsigned int *tab_calloc = calloc(count, sizeof(unsigned int));
    if (tab_calloc == NULL) {
        perror("calloc");
        free(tab_malloc);
        return EXIT_FAILURE;
    }

    /* Initialisation par arithmetique de pointeurs uniquement (pas de []) */
    for (unsigned int *p = tab_malloc; p < tab_malloc + count; p++)
        *p = (unsigned int)(p - tab_malloc);          /* 0, 1, 2, ... */
    for (unsigned int *p = tab_calloc; p < tab_calloc + count; p++)
        *p = (unsigned int)(p - tab_calloc) * 10;     /* 0, 10, 20, ... */

    printf("=== Tableau alloue avec malloc ===\n");
    for (size_t i = 0; i < count; i++)
        printf("tab_malloc[%zu] : adresse = %p, valeur = %u\n",
               i, (void *)(tab_malloc + i), *(tab_malloc + i));

    printf("\n=== Tableau alloue avec calloc ===\n");
    for (size_t i = 0; i < count; i++)
        printf("tab_calloc[%zu] : adresse = %p, valeur = %u\n",
               i, (void *)(tab_calloc + i), *(tab_calloc + i));

    free(tab_malloc);
    free(tab_calloc);
    return EXIT_SUCCESS;
}

/*
 * ==========================================================================
 *       EXPLICATION - Question 1.3.1 : parcours d'un tableau
 * ==========================================================================
 *
 * Compilation : gcc -Wall q1_3_1.c -o q1_3_1 && ./q1_3_1 5
 *
 * - tab_malloc pointe sur le 1er element ; tab_malloc + count pointe juste
 *   apres le dernier (adresse de fin, valide pour une comparaison).
 * - p++ avance le pointeur d'UN ELEMENT, c'est-a-dire de
 *   sizeof(unsigned int) = 4 octets, et non d'un octet : le compilateur
 *   multiplie automatiquement par la taille du type pointe.
 * - p - tab_malloc donne le nombre d'ELEMENTS entre les deux pointeurs
 *   (l'indice), pas le nombre d'octets.
 * - *(tab + i) est strictement equivalent a tab[i].
 * ==========================================================================
 */
