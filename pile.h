/*!\file pile.h
2 * \brief Biblioth`eque de gestion de (une) pile de taille fixe
3 * \author Far`es Belhadj amsi@up8.edu
4 * \date September 27, 2019
5 */
#include "ratio.h"
#ifndef _PILE_H
#define _PILE_H
/*!\brief taille de la pile (statique) */
#define PILE_MAX 256

#ifdef __cplusplus
extern "C" {
#endif

extern void push(int v);
extern void pushR(ratio_t* v);
extern int pop(void);
extern ratio_t* popR(void);
extern int empty(void);

#ifdef __cplusplus
}
#endif

#endif