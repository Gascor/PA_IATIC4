#include <stdio.h>
#include "answer.h"

int main(void) {
    printf("Why do computer scientists get confused between Halloween and Christmas ?\n");
    printf(answer, 8*sizeof(int) - 1, 8*(sizeof(short) + sizeof(char)) + 1);
    return 0;
}

/*
 * ==========================================================================
 *                 EXPLICATION - Question 1.1.3 : extern
 * ==========================================================================
 *
 * Compilation :
 *     gcc -Wall answer.c joke.c -o joke && ./joke
 *
 * Sortie :
 *     Why do computer scientists get confused between Halloween and Christmas ?
 *     Because Oct 31 = Dec 25
 *
 * --- La classe de stockage extern ---
 * - answer.h DECLARE la variable avec "extern" : on indique qu'elle existe
 *   quelque part dans le programme, sans reserver de memoire.
 * - answer.c DEFINIT la variable : la memoire est allouee ici (segment de
 *   donnees, duree de vie = tout le programme, liaison externe).
 * - joke.c inclut answer.h et peut donc utiliser "answer" alors qu'elle est
 *   definie dans un autre fichier. C'est l'editeur de liens (linker) qui
 *   relie l'utilisation dans joke.o a la definition dans answer.o.
 *   Si on oublie answer.c a la compilation : "undefined reference to answer".
 *
 * --- Bonus : l'explication de la blague ---
 * Avec sizeof(int) = 4, sizeof(short) = 2, sizeof(char) = 1 :
 *     8*sizeof(int) - 1                    = 8*4 - 1     = 31
 *     8*(sizeof(short) + sizeof(char)) + 1 = 8*(2+1) + 1 = 25
 * => "Oct 31 = Dec 25"
 *
 * Oct 31 = Halloween (31 octobre), Dec 25 = Noel (25 decembre).
 * Mais en informatique, "Oct" = octal (base 8) et "Dec" = decimal (base 10) :
 *     31 en octal = 3*8 + 1 = 25 en decimal.
 * Donc Oct 31 == Dec 25 est vrai : les informaticiens confondent
 * Halloween et Noel !
 * ==========================================================================
 */
