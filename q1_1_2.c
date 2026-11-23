#include <stdio.h>

char * obi() {
    return "Hello";
}

/* Version d'origine (signalee par le compilateur) :
 *
 * char * one() {
 *     char str[] = "there";
 *     return str;
 * }
 *
 * Version corrigee : tableau declare static.
 */
char * one() {
    static char str[] = "there";
    return str;
}

int main(void) {
    printf("%s %s\n", obi(), one());
    return 0;
}

/*
 * ==========================================================================
 *   EXPLICATION - Question 1.1.2 : chaines et classe de stockage automatique
 * ==========================================================================
 *
 * obi() : "Hello" est un litteral de chaine. Il est stocke dans une zone
 * statique en lecture seule (.rodata) et existe pendant toute l'execution
 * du programme. Renvoyer son adresse est donc VALIDE (mais il ne faut pas
 * modifier la chaine).
 *
 * one() (version d'origine) : il y a deux elements distincts.
 *   - le litteral "there" : classe statique, en lecture seule ; il sert
 *     uniquement de valeur d'initialisation ;
 *   - le tableau str[] : variable locale de classe AUTOMATIQUE, allouee
 *     sur la PILE. Les caracteres du litteral y sont copies.
 * "return str;" renvoie l'adresse de ce tableau local. A la sortie de la
 * fonction, le cadre de pile est libere : le pointeur renvoye pointe vers
 * une zone qui n'existe plus (dangling pointer). L'utiliser est un
 * comportement indefini. C'est pourquoi gcc signale :
 *     warning: function returns address of local variable
 * (ce warning devient une erreur avec -Werror).
 *
 * Recapitulatif :
 *   "Hello" (obi)   -> statique    -> .rodata -> tout le programme
 *   "there" (one)   -> statique    -> .rodata -> tout le programme
 *   str[]   (one)   -> automatique -> pile    -> fin de one()
 *
 * Corrections possibles :
 *   1) static char str[] = "there";   (choisie ci-dessus)
 *   2) allocation dynamique avec malloc + strcpy (l'appelant fait free)
 *   3) const char * one() { return "there"; }
 * ==========================================================================
 */
