#include "pile.h"
#include "ratio.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

/*
 * Converti une chaine infix en postfix
 */
static void infix2postfix(char * s, char * d) 
{
    while(*s) {
        if(*s >= '0' && *s <= '9') {
            do {
                *d++ = *s++;
            } while( *s >= '0' && *s <= '9');

            if(*s == '.') *d++ = '.';
            else *d++ = ' ';
            if(!*s) break;
        }
        if((*s == ')') && !empty()) { *d++ = (char)pop(); *d++ = ' '; }
        else if(*s == '+') push((int) *s);
        else if(*s == '*') push((int) *s);
        else if(*s == '-') push((int) *s);
        else if(*s == '/') push((int) *s);
        s++;
    }
    while(!empty()) {*d++ = (char)pop(); *d++ = ' '; }
    *d = '\0';
}

/*
 * Affiche les float dans un char
 */
void afficher_nb(char d[BUFSIZ << 1])
{
    char * ptr;
    ptr = d;

    while(*ptr)
    {
        if (isdigit(*ptr) || *ptr == '.') {

            long val = strtol(ptr, &ptr, 10);
            printf("%ld", val);

            if (*ptr == '.')
            {
                printf(".");
                ptr++;
            } else { printf("\n"); }
        }
        else { ptr++; }
    }
}

/*
 * Retourne le nombre de float dans un char
 */
int nb_numbers(char d[BUFSIZ << 1])
{
    int r = 0;
    char * ptr;
    ptr = d;

    while(*ptr)
    {
        if (isdigit(*ptr) || *ptr == '.') { strtol(ptr, &ptr, 10);
            if (*ptr == '.') { ptr++; }  else { r++; }
        } else { ptr++; }
    } return r;
}

/*
 * Retourne un type float d'un float dans un char
 */
float get_double(const char *str)
{
    while (*str && !(isdigit(*str) || ((*str == '-' || *str == '+' || *str == '*' || *str == '/') && isdigit(*(str + 1)))))
        str++;
        
    return strtod(str, NULL);
}

/*
 * Type d'opération
 */
int getType(char token)
{
    if (token == '+') return 1;     if (token == '-') return 2;
    if (token == '*') return 3;     if (token == '/') return 4;
    return 0;
}

/*
 * Converti des float en nombres rationnel puis
 * effectue des opérations binaires et affiche le
 * résultat
 */
void nb_float(char d[BUFSIZ << 1])
{
    const char * separators = " ";

    ratio_t * a, * b, * c, * result;
    float resultFinal;

    char * strToken = strtok(d, separators);
    while (strToken != NULL) // parcours du char
    {
        if (!getType(*strToken)) //float
        {
            a = malloc(sizeof * a);
            a = ratio_new(get_double(strToken) * 1000, 1000);
            pushR(a);
        }
        else
        {
            if(getType(*strToken) == 1) /* + */
            {
                b = popR(); c = popR();     // Dépile
                result = ratio_plus(b, c);  // Calcul
                pushR(result);              // Empile
            }
            if(getType(*strToken) == 2) /* - */
            {
                b = popR(); c = popR();
                result = ratio_moins(b, c);
                pushR(result);
            }
            if(getType(*strToken) == 3) /* x */
            {
                b = popR(); c = popR();
                result = ratio_mul(b, c);
                pushR(result);
            }
            if(getType(*strToken) == 4) /* / */
            {
                b = popR(); c = popR();
                result = ratio_div(c, b);
                pushR(result);
            }
        }
        strToken = strtok (NULL, separators); //token suivant
    }

    printf("%d / %d = ", ratio_num(result), ratio_denom(result));
    
    resultFinal = (float)ratio_num(result) / (float)ratio_denom(result);
    printf("%.3f", resultFinal);
}

int main(int argc, char ** argv) 
{
    char source[BUFSIZ], destination[BUFSIZ << 1];
    do {
        if(!fgets(source, BUFSIZ, stdin)) break;
            infix2postfix(source, destination);
            printf("%s\n", destination);
            nb_float(destination);
        } while(1);
        
    return 0;
}