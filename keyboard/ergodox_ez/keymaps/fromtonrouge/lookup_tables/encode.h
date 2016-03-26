#ifndef ENCODE_H
#define ENCODE_H

#define MAX_LETTERS 5
#define NO_ENTRY {0}
#define _1(c1) {c1, 0, 0, 0, 0}
#define _2(c1, c2) {c1, c2, 0, 0, 0}
#define _3(c1, c2, c3) {c1, c2, c3, 0, 0}
#define _4(c1, c2, c3, c4) {c1, c2, c3, c4, 0}
#define _5(c1, c2, c3, c4, c5) {c1, c2, c3, c4, c5}

#define MAX_SYMBOLS 3
#define _S1(c1) {c1, 0, 0}
#define _S2(c1, c2) {c1, c2, 0}
#define _S3(c1, c2, c3) {c1, c2, c3}

#ifdef AZERTY

#include "keymap_extras/keymap_french.h"

#define _A      FR_A
#define _M      FR_M
#define _Q      FR_Q
#define _W      FR_W
#define _Z      FR_Z
#define _SCLN   FR_SCLN
#define _COMM   FR_COMM
#define _DOT    FR_DOT
#define _COLN   FR_COLN
#define _UNDS   FR_UNDS

#else

#define _A      KC_A
#define _Q      KC_Q
#define _W      KC_W
#define _Z      KC_Z
#define _M      KC_M
#define _SCLN   KC_SCLN
#define _COMM   KC_COMM
#define _DOT    KC_DOT
#define _COLN   KC_COLN
#define _UNDS   KC_UNDS

#endif

#define _B      KC_B
#define _C      KC_C
#define _D      KC_D
#define _E      KC_E
#define _F      KC_F
#define _G      KC_G
#define _H      KC_H
#define _I      KC_I
#define _J      KC_J
#define _K      KC_K
#define _L      KC_L
#define _N      KC_N
#define _O      KC_O
#define _P      KC_P
#define _R      KC_R
#define _S      KC_S
#define _T      KC_T
#define _U      KC_U
#define _V      KC_V
#define _X      KC_X
#define _Y      KC_Y

#endif
