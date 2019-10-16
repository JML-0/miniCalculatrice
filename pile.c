/*!\file pile.c
2 * \brief Biblioth`eque de gestion de (une) pile de taille fixe
3 * \author Far`es Belhadj amsi@up8.edu
4 * \date September 27, 2019
5 */
#include "pile.h"
#include <stdlib.h>
#include <assert.h>

/*! \brief indice indiquant le haut de la pile. */
static int _haut = -1;
static int _hautR = -1;
/*! \brief tableau static utilis´e pour le stockage de la pile. */
static int _pile[PILE_MAX];
static ratio_t* _pileR[PILE_MAX];

/*!\brief Empiler la valeur \a v dans la pile.
* \param v la valeur `a empiler */
void push(int v) {
    _pile[++_haut] = v;
}

void pushR(ratio_t* v) {
    _pileR[++_hautR] = v;
}

/*!\brief d´epiler et renvoyer la valeur de l’´el´ement en haut de la pile.
* \return la valeur en haut de la pile. */
int pop(void) {
    return _pile[_haut--];
}

ratio_t* popR(void) {
    return _pileR[_hautR--];
}
/*!\brief Indique si la pile est vide.
* \return vrai si la pile est vide, faux sinon. */
int empty(void) {
    return _haut < 0;
}