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

    /* Version decommentee telle quelle : NE COMPILE PAS
    for (void *p = tab_malloc; p < tab_malloc + count; p++)
        *p = (unsigned int)(p - tab_malloc);
    for (void *p = tab_calloc; p < tab_calloc + count; p++)
        *p = (unsigned int)(p - tab_calloc) * 10;
    */

    /* Version corrigee : on caste le void * en unsigned int * */
    for (unsigned int *p = (unsigned int *)tab_malloc;
         p < (unsigned int *)tab_malloc + count; p++)
        *p = (unsigned int)(p - (unsigned int *)tab_malloc);
    for (unsigned int *p = (unsigned int *)tab_calloc;
         p < (unsigned int *)tab_calloc + count; p++)
        *p = (unsigned int)(p - (unsigned int *)tab_calloc) * 10;

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
 *       EXPLICATION - Question 1.3.3 : arithmetique de pointeurs et void
 * ==========================================================================
 *
 * Compilation : gcc -Wall q1_3_3.c -o q1_3_3 && ./q1_3_3 5
 *
 * Ce que l'on remarque en decommentant l'initialisation d'origine :
 *
 * 1) *p = ... ne compile plus :
 *        error: invalid use of void expression
 *    (+ warning: dereferencing 'void *' pointer)
 *    On ne peut pas dereferencer un void * : le compilateur ne connait ni
 *    la taille ni le type de l'objet pointe, il ne sait donc pas quoi ecrire.
 *
 * 2) L'arithmetique p++ / tab + count sur un void * est INTERDITE en C
 *    standard (sizeof(void) n'existe pas). GCC l'accepte comme extension en
 *    considerant sizeof(void) = 1 (warning avec -Wpointer-arith ou
 *    -pedantic). Meme si ca compilait, p++ avancerait de 1 OCTET au lieu
 *    de 4 : on ne parcourrait que le premier quart du tableau, element par
 *    element mal aligne, et les indices calcules (p - tab) seraient faux.
 *
 * Ce qu'il faut changer :
 *    Redonner un type aux pointeurs en les castant en (unsigned int *) (ou
 *    utiliser une variable intermediaire unsigned int *). Le compilateur
 *    connait alors la taille d'un element (4 octets) : p++ avance d'un
 *    element, et *p ecrit un unsigned int. C'est la version utilisee
 *    ci-dessus.
 * ==========================================================================
 */
