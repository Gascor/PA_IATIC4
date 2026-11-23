#include <stdio.h>

void storageClassesTest() {
    // static_val is static (scope: within block, life: till end of program)
    static int static_val = 1;
    // register_val is a register variable (scope: within block, life: till end of block)
    register int register_val = 1;

    // incrementing variables
    static_val++;
    register_val++;

    printf("Static value: %d \n", static_val);
    printf("Register value: %d \n", register_val);
}

int main(void) {
    storageClassesTest();
    storageClassesTest();
    return 0;
}

/*
 * ==========================================================================
 *                 EXPLICATION - Question 1.1.1 : static et register
 * ==========================================================================
 *
 * Sortie du programme :
 *     Static value: 2
 *     Register value: 2
 *     Static value: 3
 *     Register value: 2
 *
 * - static_val : portee locale a la fonction, mais duree de vie egale a
 *   celle du programme. Elle est stockee dans le segment de donnees (pas sur
 *   la pile) et n'est initialisee qu'UNE seule fois. Sa valeur est donc
 *   conservee entre les appels : 1 -> 2 au 1er appel, puis 2 -> 3 au 2e.
 *
 * - register_val : variable automatique (portee et duree de vie limitees
 *   au bloc). Elle est recreee et reinitialisee a 1 a chaque appel, puis
 *   detruite a la sortie de la fonction : elle vaut donc toujours 2.
 *
 * Role de "register" : c'est une suggestion faite au compilateur de ranger
 * la variable dans un registre du processeur plutot qu'en memoire, pour
 * y acceder plus vite. Le compilateur est libre de l'ignorer (les
 * compilateurs modernes optimisent eux-memes l'allocation des registres).
 * Consequence : on ne peut PAS prendre l'adresse d'une variable register
 * (&register_val provoque une erreur). Pour le reste, elle se comporte
 * comme une variable auto.
 * ==========================================================================
 */
