#ifndef ENCODE_H
#define ENCODE_H

#define ENCODING_SIZE 5
#define ENCODE1(c1) c1
#define ENCODE2(c1, c2) c1 | (c2 << 5)
#define ENCODE3(c1, c2, c3) c1 | (c2 << ENCODING_SIZE) | (c3 << 2*ENCODING_SIZE)
#define ENCODE4(c1, c2, c3, c4) c1 | (c2 << ENCODING_SIZE) | (c3 << 2*ENCODING_SIZE) | (c4 << 3*ENCODING_SIZE)
#define ENCODE5(c1, c2, c3, c4, c5) c1 | (c2 << ENCODING_SIZE) | (c3 << 2*ENCODING_SIZE) | (c4 << 3*ENCODING_SIZE) | ((uint32_t)(c5) << 4*ENCODING_SIZE)
#define ENCODE6(c1, c2, c3, c4, c5, c6) c1 | (c2 << ENCODING_SIZE) | (c3 << 2*ENCODING_SIZE) | (c4 << 3*ENCODING_SIZE) | ((uint32_t)(c5) << 4*ENCODING_SIZE) | ((uint32_t)(c6) << 5*ENCODING_SIZE)

#define DECODING_MASK 0x1F
#define DECODE1(encoded) ((encoded >> 0*ENCODING_SIZE) & DECODING_MASK)
#define DECODE2(encoded) ((encoded >> 1*ENCODING_SIZE) & DECODING_MASK)
#define DECODE3(encoded) ((encoded >> 2*ENCODING_SIZE) & DECODING_MASK)
#define DECODE4(encoded) ((encoded >> 3*ENCODING_SIZE) & DECODING_MASK)
#define DECODE5(encoded) ((encoded >> 4*ENCODING_SIZE) & DECODING_MASK)
#define DECODE6(encoded) ((encoded >> 5*ENCODING_SIZE) & DECODING_MASK)

#ifdef AZERTY

#define _A      KC_Q
#define _M      KC_SCLN
#define _Q      KC_A
#define _W      KC_Z
#define _Z      KC_W

#else

#define _A      KC_A
#define _Q      KC_Q
#define _W      KC_W
#define _Z      KC_Z
#define _M      KC_M

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
