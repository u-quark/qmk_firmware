#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "keymap_extras/keymap_french.h"
#include "led.h"

#define LAYER_COLEMAK 0
#define LAYER_STENO 1
#define LAYER_SHIFT_COLEMAK 2
#define LAYER_FN 3

#define SFT_CMAK 0
#define USFT_CMAK 1
#define STENO 2

// 8 bits for the left hand
#define OFFSET_LEFT_HAND 0
#define L_A (1L << 0)
#define L_S (1L << 1)
#define L_C (1L << 2)
#define L_T (1L << 3)
#define L_W (1L << 4)
#define L_H (1L << 5)
#define L_N (1L << 6)
#define L_R (1L << 7)

// 4 bits for the thumbs
#define OFFSET_THUMBS 8
#define T_A (1L << 0)
#define T_O (1L << 1)
#define T_E (1L << 2)
#define T_U (1L << 3)

// 8 bits for the right hand
#define OFFSET_RIGHT_HAND 12
#define R_R (1L << 0)
#define R_N (1L << 1)
#define R_L (1L << 2)
#define R_G (1L << 3)
#define R_C (1L << 4)
#define R_H (1L << 5)
#define R_T (1L << 6)
#define R_S (1L << 7)

// Global vars for the steno layer
uint32_t bits_keys_pressed = 0;
uint8_t bits_left_hand = 0;
uint8_t bits_thumbs = 0;
uint8_t bits_right_hand = 0;

// Utility functions for the steno layer
void add_left_hand(uint8_t bit)        { bits_keys_pressed |= (bit << OFFSET_LEFT_HAND); bits_left_hand |= bit; }
void del_left_hand(uint8_t bit)        { bits_keys_pressed &= ~(bit << OFFSET_LEFT_HAND); }
void add_thumb(uint8_t bit)            { bits_keys_pressed |= (bit << OFFSET_THUMBS); bits_thumbs |= bit; }
void del_thumb(uint8_t bit)            { bits_keys_pressed &= ~(bit << OFFSET_THUMBS); }
void add_right_hand(uint8_t bit)       { bits_keys_pressed |= (bit << OFFSET_RIGHT_HAND); bits_right_hand |= bit; }
void del_right_hand(uint8_t bit)       { bits_keys_pressed &= ~(bit << OFFSET_RIGHT_HAND); }

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

// Lookup tables for the steno layer
const unsigned long PROGMEM left_hand_table[256] =
{
    0,                                      // [0]
    ENCODE1(FR_A),                          // [1]
    ENCODE1(KC_S),                          // [2]
    ENCODE2(FR_A, KC_S),                    // [3]
    ENCODE1(KC_C),                          // [4]
    ENCODE2(FR_A, KC_C),                    // [5]
    ENCODE2(KC_S, KC_C),                    // [6]
    ENCODE3(FR_A, KC_S, KC_C),              // [7]
    ENCODE1(KC_T),                          // [8]
    ENCODE2(FR_A, KC_T),                    // [9]
    ENCODE2(KC_S, KC_T),                    // [10]
    ENCODE3(FR_A, KC_S, KC_T),              // [11]
    ENCODE1(KC_D),                          // [12]
    ENCODE2(FR_A, KC_D),                    // [13]
    ENCODE1(KC_G),                          // [14]
    ENCODE2(FR_A, KC_G),                    // [15]
    ENCODE1(FR_W),                          // [16]
    ENCODE2(FR_A, FR_W),                    // [17]
    ENCODE2(KC_S, FR_W),                    // [18]
    0,                                      // [19]
    ENCODE1(KC_P),                          // [20]
    ENCODE2(FR_A, KC_P),                    // [21]
    ENCODE2(KC_S, KC_P),                    // [22]
    ENCODE3(FR_A, KC_S, KC_P),              // [23]
    ENCODE2(KC_T, FR_W),                    // [24]
    ENCODE3(FR_A, KC_T, KC_T),              // [25]
    ENCODE1(KC_X),                          // [26]
    ENCODE2(FR_A, KC_X),                    // [27]
    ENCODE2(KC_D, FR_W),                    // [28]
    ENCODE3(FR_A, KC_D, KC_D),              // [29]
    ENCODE2(KC_G, FR_W),                    // [30]
    ENCODE3(FR_A, KC_G, KC_G),              // [31]
    ENCODE1(KC_H),                          // [32]
    ENCODE2(FR_A, KC_H),                    // [33]
    ENCODE2(KC_S, KC_H),                    // [34]
    ENCODE3(FR_A, KC_S, KC_H),              // [35]
    ENCODE2(KC_C, KC_H),                    // [36]
    ENCODE3(FR_A, KC_C, KC_H),              // [37]
    ENCODE3(KC_S, KC_C, KC_H),              // [38]
    0,                                      // [39]
    ENCODE2(KC_T, KC_H),                    // [40]
    ENCODE3(FR_A, KC_T, KC_H),              // [41]
    0,                                      // [42]
    ENCODE4(FR_A, KC_S, KC_T, KC_H),        // [43]
    ENCODE1(KC_F),                          // [44]
    ENCODE2(FR_A, KC_F),                    // [45]
    ENCODE2(KC_G, KC_H),                    // [46]
    ENCODE3(FR_A, KC_G, KC_H),              // [47]
    ENCODE2(FR_W, KC_H),                    // [48]
    ENCODE3(FR_A, FR_W, KC_H),              // [49]
    0,                                      // [50]
    0,                                      // [51]
    ENCODE2(KC_P, KC_H),                    // [52]
    ENCODE3(FR_A, KC_P, KC_H),              // [53]
    ENCODE3(KC_S, KC_P, KC_H),              // [54]
    ENCODE4(FR_A, KC_S, KC_P, KC_H),        // [55]
    ENCODE1(KC_K),                          // [56]
    ENCODE2(FR_A, KC_K),                    // [57]
    ENCODE2(KC_S, KC_K),                    // [58]
    ENCODE3(FR_A, KC_S, KC_K),              // [59]
    ENCODE1(KC_B),                          // [60]
    ENCODE2(FR_A, KC_B),                    // [61]
    0,                                      // [62]
    ENCODE3(FR_A, KC_B, KC_B),              // [63]
    ENCODE1(KC_N),                          // [64]
    ENCODE2(FR_A, KC_N),                    // [65]
    ENCODE2(KC_S, KC_N),                    // [66]
    ENCODE3(FR_A, KC_N, KC_N),              // [67]
    ENCODE1(FR_Z),                          // [68]
    ENCODE2(FR_A, FR_Z),                    // [69]
    ENCODE2(KC_S, KC_S),                    // [70]
    ENCODE3(FR_A, KC_S, KC_S),              // [71]
    ENCODE1(KC_V),                          // [72]
    ENCODE2(FR_A, KC_V),                    // [73]
    ENCODE2(KC_S, KC_V),                    // [74]
    0,                                      // [75]
    ENCODE3(KC_D, KC_E, KC_V),              // [76]
    ENCODE3(FR_A, KC_D, KC_V),              // [77]
    ENCODE2(KC_G, KC_N),                    // [78]
    ENCODE3(FR_A, KC_G, KC_N),              // [79]
    ENCODE1(FR_M),                          // [80]
    ENCODE2(FR_A, FR_M),                    // [81]
    ENCODE2(KC_S, FR_M),                    // [82]
    ENCODE3(FR_A, KC_S, FR_M),              // [83]
    ENCODE2(KC_P, KC_N),                    // [84]
    ENCODE3(FR_A, FR_M, FR_M),              // [85]
    0,                                      // [86]
    ENCODE3(FR_A, KC_P, KC_P),              // [87]
    ENCODE1(KC_J),                          // [88]
    ENCODE2(FR_A, KC_J),                    // [89]
    0,                                      // [90]
    0,                                      // [91]
    ENCODE3(KC_D, KC_E, FR_M),              // [92]
    ENCODE3(FR_A, KC_D, FR_M),              // [93]
    0,                                      // [94]
    ENCODE3(FR_A, KC_D, KC_J),              // [95]
    ENCODE1(KC_Y),                          // [96]
    ENCODE2(FR_A, KC_Y),                    // [97]
    ENCODE2(KC_S, KC_Y),                    // [98]
    ENCODE3(FR_A, KC_S, KC_Y),              // [99]
    ENCODE2(KC_C, KC_Y),                    // [100]
    ENCODE3(FR_A, KC_C, KC_C),              // [101]
    0,                                      // [102]
    0,                                      // [103]
    ENCODE2(KC_T, KC_Y),                    // [104]
    0,                                      // [105]
    ENCODE3(KC_S, KC_T, KC_Y),              // [106]
    0,                                      // [107]
    ENCODE2(KC_D, KC_Y),                    // [108]
    ENCODE3(FR_A, KC_F, KC_F),              // [109]
    ENCODE2(KC_G, KC_Y),                    // [110]
    ENCODE3(FR_A, KC_F, KC_T),              // [111]
    ENCODE2(FR_M, KC_Y),                    // [112]
    0,                                      // [113]
    0,                                      // [114]
    0,                                      // [115]
    ENCODE2(KC_P, KC_Y),                    // [116]
    0,                                      // [117]
    ENCODE3(KC_S, KC_P, KC_Y),              // [118]
    ENCODE5(FR_A, KC_S, KC_P, KC_H, KC_Y),  // [119]
    ENCODE2(KC_K, KC_N),                    // [120]
    ENCODE4(FR_A, KC_C, KC_K, KC_N),        // [121]
    ENCODE2(KC_X, KC_Y),                    // [122]
    0,                                      // [123]
    ENCODE2(KC_B, KC_Y),                    // [124]
    ENCODE3(FR_A, KC_B, KC_Y),              // [125]
    0,                                      // [126]
    0,                                      // [127]
    ENCODE1(KC_R),                          // [128]
    ENCODE2(FR_A, KC_R),                    // [129]
    ENCODE3(KC_S, KC_E, KC_R),              // [130]
    ENCODE3(FR_A, KC_R, KC_R),              // [131]
    ENCODE2(KC_C, KC_R),                    // [132]
    ENCODE3(FR_A, KC_C, KC_R),              // [133]
    ENCODE3(KC_S, KC_C, KC_R),              // [134]
    ENCODE4(FR_A, KC_S, KC_C, KC_R),        // [135]
    ENCODE2(KC_T, KC_R),                    // [136]
    ENCODE3(FR_A, KC_T, KC_R),              // [137]
    ENCODE3(KC_S, KC_T, KC_R),              // [138]
    0,                                      // [139]
    ENCODE2(KC_D, KC_R),                    // [140]
    ENCODE3(FR_A, KC_D, KC_R),              // [141]
    ENCODE2(KC_G, KC_R),                    // [142]
    ENCODE3(FR_A, KC_G, KC_R),              // [143]
    ENCODE2(FR_W, KC_R),                    // [144]
    0,                                      // [145]
    0,                                      // [146]
    0,                                      // [147]
    ENCODE2(KC_P, KC_R),                    // [148]
    ENCODE3(FR_A, KC_P, KC_R),              // [149]
    ENCODE3(KC_S, KC_P, KC_R),              // [150]
    ENCODE4(FR_A, KC_P, KC_P, KC_R),        // [151]
    0,                                      // [152]
    ENCODE4(FR_A, KC_T, KC_T, KC_R),        // [153]
    ENCODE2(KC_X, KC_R),                    // [154]
    0,                                      // [155]
    ENCODE3(KC_D, KC_E, KC_R),              // [156]
    ENCODE4(FR_A, KC_D, KC_D, KC_R),        // [157]
    0,                                      // [158]
    ENCODE4(FR_A, KC_G, KC_G, KC_R),        // [159]
    ENCODE2(KC_R, KC_H),                    // [160]
    0,                                      // [161]
    ENCODE3(KC_S, KC_H, KC_R),              // [162]
    0,                                      // [163]
    ENCODE3(KC_C, KC_H, KC_R),              // [164]
    ENCODE4(FR_A, KC_C, KC_C, KC_R),        // [165]
    0,                                      // [166]
    0,                                      // [167]
    ENCODE3(KC_T, KC_H, KC_R),              // [168]
    ENCODE4(FR_A, KC_T, KC_H, KC_L),        // [169]
    0,                                      // [170]
    0,                                      // [171]
    ENCODE2(KC_F, KC_R),                    // [172]
    ENCODE3(FR_A, KC_F, KC_R),              // [173]
    0,                                      // [174]
    ENCODE4(FR_A, KC_F, KC_F, KC_R),        // [175]
    0,                                      // [176]
    0,                                      // [177]
    0,                                      // [178]
    0,                                      // [179]
    ENCODE3(KC_P, KC_H, KC_R),              // [180]
    ENCODE4(FR_A, KC_P, KC_H, KC_R),        // [181]
    0,                                      // [182]
    0,                                      // [183]
    ENCODE2(KC_K, KC_R),                    // [184]
    0,                                      // [185]
    0,                                      // [186]
    0,                                      // [187]
    ENCODE2(KC_B, KC_R),                    // [188]
    ENCODE3(FR_A, KC_B, KC_R),              // [189]
    0,                                      // [190]
    ENCODE4(FR_A, KC_B, KC_B, KC_R),        // [191]
    ENCODE1(KC_L),                          // [192]
    ENCODE2(FR_A, KC_L),                    // [193]
    ENCODE2(KC_S, KC_L),                    // [194]
    ENCODE3(FR_A, KC_S, KC_L),              // [195]
    ENCODE2(KC_C, KC_L),                    // [196]
    0,                                      // [197]
    0,                                      // [198]
    0,                                      // [199]
    ENCODE1(FR_Q),                          // [200]
    ENCODE2(FR_A, FR_Q),                    // [201]
    ENCODE2(KC_S, FR_Q),                    // [202]
    ENCODE3(FR_A, KC_S, FR_Q),              // [203]
    ENCODE3(KC_D, KC_E, KC_L),              // [204]
    ENCODE3(FR_A, KC_C, FR_Q),              // [205]
    ENCODE2(KC_G, KC_L),                    // [206]
    ENCODE3(FR_A, KC_G, KC_L),              // [207]
    ENCODE2(FR_M, KC_R),                    // [208]
    ENCODE3(FR_A, KC_L, KC_L),              // [209]
    0,                                      // [210]
    0,                                      // [211]
    ENCODE2(KC_P, KC_L),                    // [212]
    ENCODE3(FR_A, KC_P, KC_L),              // [213]
    ENCODE3(KC_S, KC_P, KC_L),              // [214]
    ENCODE4(FR_A, KC_P, KC_P, KC_L),        // [215]
    ENCODE3(KC_J, KC_E, KC_R),              // [216]
    0,                                      // [217]
    ENCODE4(KC_S, KC_E, KC_R, KC_V),        // [218]
    0,                                      // [219]
    0,                                      // [220]
    ENCODE4(FR_A, KC_D, KC_D, KC_L),        // [221]
    0,                                      // [222]
    ENCODE4(FR_A, KC_G, KC_G, KC_L),        // [223]
    ENCODE2(KC_L, KC_Y),                    // [224]
    0,                                      // [225]
    ENCODE3(KC_S, KC_L, KC_Y),              // [226]
    0,                                      // [227]
    ENCODE3(KC_C, KC_R, KC_Y),              // [228]
    ENCODE4(FR_A, KC_C, KC_C, KC_L),        // [229]
    0,                                      // [230]
    0,                                      // [231]
    ENCODE3(KC_T, KC_R, KC_Y),              // [232]
    0,                                      // [233]
    ENCODE4(KC_S, KC_T, KC_R, KC_Y),        // [234]
    0,                                      // [235]
    ENCODE2(KC_F, KC_L),                    // [236]
    ENCODE3(FR_A, KC_F, KC_L),              // [237]
    0,                                      // [238]
    ENCODE4(FR_A, KC_F, KC_F, KC_L),        // [239]
    0,                                      // [240]
    0,                                      // [241]
    0,                                      // [242]
    0,                                      // [243]
    ENCODE3(KC_P, KC_H, KC_L),              // [244]
    0,                                      // [245]
    0,                                      // [246]
    0,                                      // [247]
    ENCODE2(KC_K, KC_L),                    // [248]
    0,                                      // [249]
    0,                                      // [250]
    0,                                      // [251]
    ENCODE2(KC_B, KC_L),                    // [252]
    ENCODE3(FR_A, KC_B, KC_L),              // [253]
    0,                                      // [254]
    0                                       // [255]
};

const unsigned long PROGMEM thumbs_table[16] =
{
    0,                                      // [0]
    ENCODE1(FR_A),                          // [1]
    ENCODE1(KC_O),                          // [2]
    ENCODE2(KC_I, KC_O),                    // [3]
    ENCODE1(KC_E),                          // [4]
    ENCODE2(KC_E, FR_A),                    // [5]
    ENCODE2(KC_I, KC_E),                    // [6]
    ENCODE2(KC_E, KC_E),                    // [7]
    ENCODE1(KC_U),                          // [8]
    0,                                      // [9]
    ENCODE2(KC_O, KC_U),                    // [10]
    ENCODE2(KC_O, KC_O),                    // [11]
    ENCODE1(KC_I),                          // [12]
    0,                                      // [13]
    ENCODE2(KC_O, KC_I),                    // [14]
    0                                       // [15]
};

const unsigned long PROGMEM right_hand_table[256] =
{
    0,                                      // [0]
    ENCODE1(KC_R),                          // [1]
    ENCODE1(KC_N),                          // [2]
    ENCODE2(KC_R, KC_N),                    // [3]
    ENCODE1(KC_L),                          // [4]
    ENCODE2(KC_R, KC_L),                    // [5]
    ENCODE1(KC_S),                          // [6]
    ENCODE2(KC_L, KC_L),                    // [7]
    ENCODE1(KC_G),                          // [8]
    ENCODE2(KC_R, KC_G),                    // [9]
    ENCODE2(KC_N, KC_G),                    // [10]
    ENCODE2(KC_G, KC_N),                    // [11]
    ENCODE2(KC_L, KC_G),                    // [12]
    0,                                      // [13]
    ENCODE1(KC_D),                          // [14]
    ENCODE2(KC_D, KC_L),                    // [15]
    ENCODE1(KC_C),                          // [16]
    ENCODE2(KC_R, KC_C),                    // [17]
    ENCODE2(KC_N, KC_C),                    // [18]
    0,                                      // [19]
    ENCODE1(KC_P),                          // [20]
    ENCODE2(KC_R, KC_P),                    // [21]
    ENCODE2(KC_S, KC_P),                    // [22]
    ENCODE2(KC_P, KC_L),                    // [23]
    ENCODE1(KC_B),                          // [24]
    ENCODE2(KC_R, KC_B),                    // [25]
    ENCODE2(KC_G, KC_G),                    // [26]
    0,                                      // [27]
    ENCODE2(KC_B, KC_L),                    // [28]
    0,                                      // [29]
    0,                                      // [30]
    ENCODE2(KC_L, KC_B),                    // [31]
    ENCODE1(KC_H),                          // [32]
    ENCODE1(FR_W),                          // [33]
    ENCODE1(KC_V),                          // [34]
    ENCODE2(FR_W, KC_N),                    // [35]
    ENCODE1(FR_Z),                          // [36]
    ENCODE2(FR_W, KC_L),                    // [37]
    ENCODE2(KC_S, KC_H),                    // [38]
    ENCODE2(KC_L, KC_V),                    // [39]
    ENCODE2(KC_G, KC_H),                    // [40]
    ENCODE3(KC_R, KC_G, KC_H),              // [41]
    ENCODE1(FR_M),                          // [42]
    ENCODE2(KC_R, FR_M),                    // [43]
    ENCODE1(KC_X),                          // [44]
    0,                                      // [45]
    ENCODE2(KC_S, FR_M),                    // [46]
    ENCODE2(KC_L, FR_M),                    // [47]
    ENCODE2(KC_C, KC_H),                    // [48]
    ENCODE3(KC_R, KC_C, KC_H),              // [49]
    ENCODE3(KC_N, KC_C, KC_H),              // [50]
    ENCODE2(KC_R, KC_V),                    // [51]
    ENCODE2(KC_P, KC_H),                    // [52]
    0,                                      // [53]
    0,                                      // [54]
    ENCODE3(KC_L, KC_C, KC_H),              // [55]
    ENCODE1(KC_F),                          // [56]
    ENCODE2(KC_R, KC_F),                    // [57]
    ENCODE2(FR_M, KC_B),                    // [58]
    0,                                      // [59]
    ENCODE2(KC_L, KC_F),                    // [60]
    0,                                      // [61]
    ENCODE2(FR_M, KC_P),                    // [62]
    0,                                      // [63]
    ENCODE1(KC_T),                          // [64]
    ENCODE2(KC_R, KC_T),                    // [65]
    ENCODE2(KC_N, KC_T),                    // [66]
    ENCODE3(KC_R, KC_N, KC_T),              // [67]
    ENCODE2(KC_L, KC_T),                    // [68]
    0,                                      // [69]
    ENCODE2(KC_S, KC_T),                    // [70]
    ENCODE3(KC_R, KC_S, KC_T),              // [71]
    ENCODE1(KC_K),                          // [72]
    ENCODE2(KC_R, KC_K),                    // [73]
    ENCODE2(KC_N, KC_K),                    // [74]
    0,                                      // [75]
    ENCODE2(KC_K, KC_L),                    // [76]
    0,                                      // [77]
    ENCODE2(KC_S, KC_K),                    // [78]
    ENCODE2(KC_L, KC_K),                    // [79]
    ENCODE2(KC_C, KC_T),                    // [80]
    0,                                      // [81]
    ENCODE4(KC_T, KC_I, KC_O, KC_N),        // [82]
    0,                                      // [83]
    ENCODE2(KC_P, KC_T),                    // [84]
    0,                                      // [85]
    ENCODE3(KC_N, KC_S, KC_T),              // [86]
    ENCODE2(KC_L, KC_P),                    // [87]
    ENCODE2(KC_C, KC_K),                    // [88]
    0,                                      // [89]
    ENCODE2(KC_B, KC_T),                    // [90]
    0,                                      // [91]
    ENCODE3(KC_C, KC_K, KC_L),              // [92]
    0,                                      // [93]
    0,                                      // [94]
    0,                                      // [95]
    ENCODE2(KC_T, KC_H),                    // [96]
    ENCODE3(KC_R, KC_T, KC_H),              // [97]
    ENCODE3(KC_N, KC_T, KC_H),              // [98]
    ENCODE3(FR_W, KC_T, KC_H),              // [99]
    ENCODE3(KC_L, KC_T, KC_H),              // [100]
    0,                                      // [101]
    0,                                      // [102]
    0,                                      // [103]
    ENCODE3(KC_G, KC_H, KC_T),              // [104]
    ENCODE2(FR_W, KC_K),                    // [105]
    ENCODE4(KC_N, KC_G, KC_T, KC_H),        // [106]
    0,                                      // [107]
    ENCODE2(KC_X, KC_T),                    // [108]
    0,                                      // [109]
    ENCODE3(KC_D, KC_T, KC_H),              // [110]
    0,                                      // [111]
    ENCODE3(KC_T, KC_C, KC_H),              // [112]
    0,                                      // [113]
    0,                                      // [114]
    0,                                      // [115]
    ENCODE3(KC_P, KC_T, KC_H),              // [116]
    0,                                      // [117]
    0,                                      // [118]
    0,                                      // [119]
    ENCODE2(KC_F, KC_T),                    // [120]
    0,                                      // [121]
    0,                                      // [122]
    0,                                      // [123]
    0,                                      // [124]
    0,                                      // [125]
    ENCODE3(FR_M, KC_P, KC_T),              // [126]
    0,                                      // [127]
    ENCODE1(KC_S),                          // [128]
    ENCODE2(KC_R, KC_S),                    // [129]
    ENCODE2(KC_N, KC_S),                    // [130]
    ENCODE3(KC_R, KC_N, KC_S),              // [131]
    ENCODE2(KC_L, KC_S),                    // [132]
    ENCODE3(KC_R, KC_L, KC_S),              // [133]
    ENCODE2(KC_S, KC_S),                    // [134]
    ENCODE3(KC_L, KC_L, KC_S),              // [135]
    ENCODE2(KC_G, KC_S),                    // [136]
    ENCODE3(KC_R, KC_G, KC_S),              // [137]
    ENCODE3(KC_N, KC_G, KC_S),              // [138]
    ENCODE3(KC_G, KC_N, KC_S),              // [139]
    0,                                      // [140]
    0,                                      // [141]
    ENCODE2(KC_D, KC_S),                    // [142]
    0,                                      // [143]
    ENCODE2(KC_C, KC_S),                    // [144]
    ENCODE3(KC_R, KC_C, KC_S),              // [145]
    ENCODE4(KC_N, KC_C, KC_E, KC_S),        // [146]
    0,                                      // [147]
    ENCODE2(KC_P, KC_S),                    // [148]
    ENCODE3(KC_R, KC_P, KC_S),              // [149]
    ENCODE3(KC_S, KC_P, KC_S),              // [150]
    ENCODE4(KC_P, KC_L, KC_E, KC_S),        // [151]
    ENCODE2(KC_B, KC_S),                    // [152]
    ENCODE3(KC_R, KC_B, KC_S),              // [153]
    ENCODE3(KC_G, KC_G, KC_S),              // [154]
    0,                                      // [155]
    ENCODE4(KC_B, KC_L, KC_E, KC_S),        // [156]
    0,                                      // [157]
    0,                                      // [158]
    ENCODE3(KC_L, KC_B, KC_S),              // [159]
    ENCODE2(KC_H, KC_S),                    // [160]
    ENCODE2(FR_W, KC_S),                    // [161]
    ENCODE3(KC_V, KC_E, KC_S),              // [162]
    ENCODE3(FR_W, KC_N, KC_S),              // [163]
    ENCODE3(FR_Z, KC_E, KC_S),              // [164]
    ENCODE3(FR_W, KC_L, KC_S),              // [165]
    ENCODE4(KC_S, KC_H, KC_E, KC_S),        // [166]
    ENCODE4(KC_L, KC_V, KC_E, KC_S),        // [167]
    ENCODE3(KC_G, KC_H, KC_S),              // [168]
    0,                                      // [169]
    ENCODE2(FR_M, KC_S),                    // [170]
    ENCODE3(KC_R, FR_M, KC_S),              // [171]
    ENCODE3(KC_X, KC_E, KC_S),              // [172]
    ENCODE3(KC_R, KC_L, KC_D),              // [173]
    ENCODE3(KC_S, FR_M, KC_S),              // [174]
    ENCODE3(KC_L, FR_M, KC_S),              // [175]
    ENCODE1(KC_D),                          // [176]
    ENCODE2(KC_R, KC_D),                    // [177]
    ENCODE2(KC_N, KC_D),                    // [178]
    ENCODE2(FR_W, KC_D),                    // [179]
    ENCODE3(KC_P, KC_H, KC_S),              // [180]
    0,                                      // [181]
    0,                                      // [182]
    0,                                      // [183]
    ENCODE2(KC_D, KC_G),                    // [184]
    0,                                      // [185]
    ENCODE3(FR_M, KC_B, KC_S),              // [186]
    0,                                      // [187]
    0,                                      // [188]
    0,                                      // [189]
    ENCODE3(FR_M, KC_P, KC_S),              // [190]
    0,                                      // [191]
    ENCODE2(KC_T, KC_S),                    // [192]
    ENCODE3(KC_R, KC_T, KC_S),              // [193]
    ENCODE3(KC_N, KC_T, KC_S),              // [194]
    0,                                      // [195]
    ENCODE3(KC_L, KC_T, KC_S),              // [196]
    0,                                      // [197]
    ENCODE3(KC_S, KC_T, KC_S),              // [198]
    ENCODE4(KC_R, KC_S, KC_T, KC_S),        // [199]
    ENCODE2(KC_K, KC_S),                    // [200]
    ENCODE3(KC_R, KC_K, KC_S),              // [201]
    ENCODE3(KC_N, KC_K, KC_S),              // [202]
    0,                                      // [203]
    0,                                      // [204]
    0,                                      // [205]
    ENCODE3(KC_S, KC_K, KC_S),              // [206]
    ENCODE3(KC_L, KC_K, KC_S),              // [207]
    ENCODE3(KC_C, KC_T, KC_S),              // [208]
    0,                                      // [209]
    0,                                      // [210]
    0,                                      // [211]
    0,                                      // [212]
    0,                                      // [213]
    0,                                      // [214]
    ENCODE3(KC_L, KC_P, KC_S),              // [215]
    ENCODE3(KC_C, KC_K, KC_S),              // [216]
    0,                                      // [217]
    ENCODE3(KC_B, KC_T, KC_S),              // [218]
    0,                                      // [219]
    ENCODE5(KC_C, KC_K, KC_L, KC_E, KC_S),  // [220]
    0,                                      // [221]
    0,                                      // [222]
    0,                                      // [223]
    ENCODE3(KC_T, KC_H, KC_S),              // [224]
    ENCODE4(KC_R, KC_T, KC_H, KC_S),        // [225]
    ENCODE4(KC_N, KC_T, KC_H, KC_S),        // [226]
    ENCODE4(FR_W, KC_T, KC_H, KC_S),        // [227]
    0,                                      // [228]
    0,                                      // [229]
    0,                                      // [230]
    0,                                      // [231]
    ENCODE4(KC_G, KC_H, KC_T, KC_S),        // [232]
    ENCODE3(FR_W, KC_K, KC_S),              // [233]
    ENCODE5(KC_N, KC_G, KC_T, KC_H, KC_S),  // [234]
    0,                                      // [235]
    0,                                      // [236]
    0,                                      // [237]
    ENCODE4(KC_D, KC_T, KC_H, KC_S),        // [238]
    0,                                      // [239]
    ENCODE2(KC_D, KC_S),                    // [240]
    ENCODE3(KC_R, KC_D, KC_S),              // [241]
    ENCODE3(KC_N, KC_D, KC_S),              // [242]
    ENCODE3(FR_W, KC_D, KC_S),              // [243]
    ENCODE4(KC_P, KC_T, KC_H, KC_S),        // [244]
    ENCODE4(KC_R, KC_L, KC_D, KC_S),        // [245]
    0,                                      // [246]
    ENCODE3(KC_L, KC_D, KC_S),              // [247]
    0,                                      // [248]
    0,                                      // [249]
    0,                                      // [250]
    0,                                      // [251]
    0,                                      // [252]
    0,                                      // [253]
    ENCODE4(FR_M, KC_P, KC_T, KC_S),        // [254]
    0                                       // [255]
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
// COLEMAK
[LAYER_COLEMAK] = KEYMAP(
        // left hand
        FR_AMP,         FR_LBRC,    FR_LCBR,    FR_RCBR,    FR_LPRN,    FR_EQL,         KC_INS,
        FR_DLR,         FR_Q,       FR_W,       KC_F,       KC_P,       KC_G,           KC_BSPC,
        KC_TAB,         FR_A,       KC_R,       KC_S,       KC_T,       KC_D,
        M(SFT_CMAK),    FR_Z,       KC_X,       KC_C,       KC_V,       KC_B,           KC_ESC,
        KC_LCTL,        FR_AMP,     KC_LALT,    KC_UP,      KC_DOWN,
                                                                                    MO(LAYER_FN),       TG(LAYER_FN),
                                                                                                        KC_PSCR,
                                                                            KC_ENT, KC_BSPC,            KC_LGUI,
        // right hand
                    KC_CAPS,        FR_ASTR,    FR_RPRN,    FR_PLUS,    FR_RBRC,    FR_EXLM,    FR_HASH,
                    KC_BSPC,        KC_J,       KC_L,       KC_U,       KC_Y,       FR_SCLN,    FR_SLSH,
                                    KC_H,       KC_N ,      KC_E,       KC_I,       KC_O,       FR_MINS,
                    KC_ENT,         KC_K,       FR_M,       FR_COMM,    FR_DOT,     FR_APOS,    M(SFT_CMAK),
                                                KC_LEFT,    KC_RIGHT,   FR_BSLS,    FR_AT,      KC_RCTL,
        TG(LAYER_FN),     MO(LAYER_FN),
        TG(LAYER_STENO),
        KC_NO,      KC_DEL,     KC_SPC
),

// STENO LAYER
[LAYER_STENO] = KEYMAP(
        // left hand
        KC_NO,        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,        KC_NO,
        KC_NO,        KC_1,       KC_2,       KC_3,       KC_4,       KC_5,         KC_TRNS,
        KC_NO,        M(STENO),   M(STENO),   M(STENO),   M(STENO),   M(STENO),
        KC_LSFT,      M(STENO),   M(STENO),   M(STENO),   M(STENO),   M(STENO),     KC_TRNS,
        KC_NO,        KC_NO,      KC_NO,      KC_TRNS,    KC_TRNS,
                                                                                        KC_TRNS,    KC_TRNS,
                                                                                                    KC_TRNS,
                                                                            M(STENO),   M(STENO),   KC_TRNS,
        // right hand
                    KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                    KC_TRNS,        KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_NO,
                                    M(STENO),   M(STENO),   M(STENO),   M(STENO),   M(STENO),   M(STENO),
                    KC_TRNS,        M(STENO),   M(STENO),   M(STENO),   M(STENO),   M(STENO),   M(STENO),
                                                KC_TRNS,    KC_TRNS,    KC_NO,      KC_NO,      KC_NO,
        KC_TRNS,    KC_TRNS,
        KC_TRNS,
        KC_TRNS,    M(STENO),    M(STENO)
),

// SHIFTED LAYER
[LAYER_SHIFT_COLEMAK] = KEYMAP(
        FR_UGRV,        KC_7,       KC_5,       KC_3,       KC_1,       KC_9,           KC_TRNS,
        M(USFT_CMAK),   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,
        KC_TRNS,        FR_UGRV,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                                                        KC_TRNS,    KC_TRNS,
                                                                                                    KC_TRNS,
                                                                            KC_TRNS,    KC_TRNS,    KC_TRNS,
    // right hand
                    KC_TRNS,        KC_0,       KC_2,       KC_4,           KC_6,           KC_8,           M(USFT_CMAK),
                    KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,        M(USFT_CMAK),   FR_COMM,
                                    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_TRNS,        M(USFT_CMAK),
                    KC_TRNS,        KC_TRNS,    KC_TRNS,    M(USFT_CMAK),   M(USFT_CMAK),   M(USFT_CMAK),   KC_TRNS,
                                                KC_TRNS,    KC_TRNS,        M(USFT_CMAK),   M(USFT_CMAK),   KC_TRNS,
        KC_TRNS,    KC_TRNS,
        KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS
),

// F1-F12 Layer
[LAYER_FN] = KEYMAP(
       // left hand
        KC_TRNS,        KC_F1,      KC_F2,      KC_F3,      KC_F4,          KC_F5,          KC_F6,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,
        KC_LSFT,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_PGDN,    KC_PGUP,
                                                                                        KC_TRNS,    KC_TRNS,
                                                                                                    KC_TRNS,
                                                                            KC_TRNS,    KC_TRNS,    KC_TRNS,
       // right hand
                    KC_F7,          KC_F8,      KC_F9,      KC_F10,     KC_F11,         KC_F12,     KC_TRNS,
                    KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,    KC_TRNS,
                                    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,    KC_TRNS,
                    KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,    KC_RSFT,
                                                KC_HOME,    KC_END,     KC_TRNS,        KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,
        KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS
),

};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(LAYER_FN)                // FN1 - Momentary Layer 1 (Symbols)
};

void send_letters(uint32_t encoded)
{
#define SEND(c) if (c) { register_code(c); unregister_code(c);} else { return;}

    const uint8_t c1 = DECODE1(encoded);
    SEND(c1);

    const uint8_t c2 = DECODE2(encoded);
    SEND(c2);

    const uint8_t c3 = DECODE3(encoded);
    SEND(c3);

    const uint8_t c4 = DECODE4(encoded);
    SEND(c4);

    const uint8_t c5 = DECODE5(encoded);
    SEND(c5);

    const uint8_t c6 = DECODE6(encoded);
    SEND(c6);
}

void stroke(void)
{
    // Send letters of the left hand
    const uint32_t left_letters = pgm_read_dword(&(left_hand_table[bits_left_hand]));
    send_letters(left_letters);

    // Send letters of the thumb cluster
    const uint32_t thumbs_letters = pgm_read_dword(&(thumbs_table[bits_thumbs]));
    send_letters(thumbs_letters);

    // Send letters of the right hand
    const uint32_t right_letters = pgm_read_dword(&(right_hand_table[bits_right_hand]));
    send_letters(right_letters);

    // Clear bits
    bits_left_hand = 0;
    bits_thumbs = 0;
    bits_right_hand = 0;
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t macroId, uint8_t opt)
{
    switch (macroId)
    {
    case STENO:
        {
            const int physical_row = record->event.key.col;
            const int physical_col = record->event.key.row;
            if (record->event.pressed)
            {
                switch (physical_row)
                {
                case 2:
                    {
                        switch (physical_col)
                        {
                        case 1: // Left hand
                            {
                                add_left_hand(L_A);
                                break;
                            }
                        case 2:
                            {
                                add_left_hand(L_C);
                                break;
                            }
                        case 3:
                            {
                                add_left_hand(L_W);
                                break;
                            }
                        case 4:
                            {
                                add_left_hand(L_N);
                                break;
                            }
                        case 5:
                            {
                                break;
                            }
                        case 8: // Right hand
                            {
                                break;
                            }
                        case 9:
                            {
                                add_right_hand(R_R);
                                break;
                            }
                        case 10:
                            {
                                add_right_hand(R_L);
                                break;
                            }
                        case 11:
                            {
                                add_right_hand(R_C);
                                break;
                            }
                        case 12:
                            {
                                add_right_hand(R_T);
                                break;
                            }
                        case 13:
                            {
                                break;
                            }
                        }
                        break;
                    }
                case 3:
                    {
                        switch (physical_col)
                        {
                        case 1: // Left hand
                            {
                                add_left_hand(L_S);
                                break;
                            }
                        case 2:
                            {
                                add_left_hand(L_T);
                                break;
                            }
                        case 3:
                            {
                                add_left_hand(L_H);
                                break;
                            }
                        case 4:
                            {
                                add_left_hand(L_R);
                                break;
                            }
                        case 5:
                            {
                                break;
                            }
                        case 8: // Right hand
                            {
                                break;
                            }
                        case 9:
                            {
                                add_right_hand(R_N);
                                break;
                            }
                        case 10:
                            {
                                add_right_hand(R_G);
                                break;
                            }
                        case 11:
                            {
                                add_right_hand(R_H);
                                break;
                            }
                        case 12:
                            {
                                add_right_hand(R_S);
                                break;
                            }
                        case 13:
                            {
                                break;
                            }
                        }
                        break;
                    }
                case 5: // Thumb
                    {
                        switch (physical_col)
                        {
                        case 3:
                            {
                                add_thumb(T_A);
                                break;
                            }
                        case 2:
                            {
                                add_thumb(T_O);
                                break;
                            }
                        case 11:
                            {
                                add_thumb(T_E);
                                break;
                            }
                        case 10:
                            {
                                add_thumb(T_U);
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            else
            {
                switch (physical_row)
                {
                case 2:
                    {
                        switch (physical_col)
                        {
                        case 1: // Left hand
                            {
                                del_left_hand(L_A);
                                break;
                            }
                        case 2:
                            {
                                del_left_hand(L_C);
                                break;
                            }
                        case 3:
                            {
                                del_left_hand(L_W);
                                break;
                            }
                        case 4:
                            {
                                del_left_hand(L_N);
                                break;
                            }
                        case 5:
                            {
                                break;
                            }
                        case 8: // Right hand
                            {
                                break;
                            }
                        case 9:
                            {
                                del_right_hand(R_R);
                                break;
                            }
                        case 10:
                            {
                                del_right_hand(R_L);
                                break;
                            }
                        case 11:
                            {
                                del_right_hand(R_C);
                                break;
                            }
                        case 12:
                            {
                                del_right_hand(R_T);
                                break;
                            }
                        case 13:
                            {
                                break;
                            }
                        }
                        break;
                    }
                case 3:
                    {
                        switch (physical_col)
                        {
                        case 1: // Left hand
                            {
                                del_left_hand(L_S);
                                break;
                            }
                        case 2:
                            {
                                del_left_hand(L_T);
                                break;
                            }
                        case 3:
                            {
                                del_left_hand(L_H);
                                break;
                            }
                        case 4:
                            {
                                del_left_hand(L_R);
                                break;
                            }
                        case 5:
                            {
                                break;
                            }
                        case 8: // Right hand
                            {
                                break;
                            }
                        case 9:
                            {
                                del_right_hand(R_N);
                                break;
                            }
                        case 10:
                            {
                                del_right_hand(R_G);
                                break;
                            }
                        case 11:
                            {
                                del_right_hand(R_H);
                                break;
                            }
                        case 12:
                            {
                                del_right_hand(R_S);
                                break;
                            }
                        case 13:
                            {
                                break;
                            }
                        }
                        break;
                    }
                case 5: // Thumb
                    {
                        switch (physical_col)
                        {
                        case 3:
                            {
                                del_thumb(T_A);
                                break;
                            }
                        case 2:
                            {
                                del_thumb(T_O);
                                break;
                            }
                        case 11:
                            {
                                del_thumb(T_E);
                                break;
                            }
                        case 10:
                            {
                                del_thumb(T_U);
                                break;
                            }
                        }
                        break;
                    }
                }

                // Stroke if all steno keys are released
                if (bits_keys_pressed == 0)
                {
                    stroke();
                }
            }
            break;
        }
    case SFT_CMAK: // Apply SHIFT and go to LAYER_SHIFT_COLEMAK
        {
            if (record->event.pressed)
            {
                register_code(KC_LSFT);
                layer_on(LAYER_SHIFT_COLEMAK);
            }
            else
            {
                unregister_code(KC_LSFT);
                layer_off(LAYER_SHIFT_COLEMAK);
            }
            break;
        }
    case USFT_CMAK: // Unapply SHIFT and register keycode on press
        {
            uint16_t keycode = keymap_key_to_keycode(LAYER_COLEMAK, record->event.key);
            if (record->event.pressed)
            {
                unregister_code(KC_LSFT);
                switch (keycode)
                {
                case FR_APOS:
                    {
                        register_code(FR_QUOT);
                        break;
                    }
                case FR_DLR:
                    {
                        register_code(KC_RALT);
                        register_code(FR_TILD);
                        break;
                    }
                case FR_SCLN:
                    {
                        register_code(FR_COLN);
                        break;
                    }
                case FR_COMM:
                    {
                        register_code(FR_LESS);
                        break;
                    }
                case FR_DOT:
                    {
                        register_code(KC_LSFT);
                        register_code(FR_GRTR);
                        break;
                    }
                case FR_HASH:
                    {
                        register_code(KC_RALT);
                        register_code(FR_GRV);
                        break;
                    }
                case FR_MINS:
                    {
                        register_code(FR_UNDS);
                        break;
                    }
                case FR_AT:
                    {
                        register_code(KC_RALT);
                        register_code(FR_CIRC);
                        break;
                    }
                case FR_BSLS:
                    {
                        register_code(KC_RALT);
                        register_code(FR_PIPE);
                        break;
                    }
                }
            }
            else
            {
                switch (keycode)
                {
                case FR_APOS:
                    {
                        unregister_code(FR_QUOT);
                        break;
                    }
                case FR_DLR:
                    {
                        unregister_code(KC_RALT);
                        unregister_code(FR_TILD);
                        break;
                    }
                case FR_SCLN:
                    {
                        unregister_code(FR_COLN);
                        break;
                    }
                case FR_COMM:
                    {
                        unregister_code(FR_LESS);
                        break;
                    }
                case FR_DOT:
                    {
                        unregister_code(KC_LSFT);
                        unregister_code(FR_GRTR);
                        break;
                    }
                case FR_HASH:
                    {
                        unregister_code(KC_RALT);
                        unregister_code(FR_GRV);
                        break;
                    }
                case FR_MINS:
                    {
                        unregister_code(FR_UNDS);
                        break;
                    }
                case FR_AT:
                    {
                        unregister_code(KC_RALT);
                        unregister_code(FR_CIRC);
                        break;
                    }
                case FR_BSLS:
                    {
                        unregister_code(KC_RALT);
                        unregister_code(FR_PIPE);
                        break;
                    }
                }
                register_code(KC_LSFT);
            }
            break;
        }
    }
    return MACRO_NONE;
}

// Runs just one time when the keyboard initializes.
void * matrix_init_user(void) {}

// Runs constantly in the background, in a loop.
void * matrix_scan_user(void)
{
    uint8_t layer = biton32(layer_state);

    ergodox_board_led_on();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK))
    {
        ergodox_right_led_1_on();
    }

    switch (layer)
    {
    case LAYER_FN:
        ergodox_right_led_2_on();
        break;
    case LAYER_STENO:
        ergodox_right_led_3_on();
        break;
    default:
        break;
    }

    if (bits_left_hand || bits_thumbs || bits_right_hand)
    {
        ergodox_right_led_2_on();
    }
}
