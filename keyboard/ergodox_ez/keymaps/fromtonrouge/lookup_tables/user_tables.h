#ifndef USER_TABLES_H
#define USER_TABLES_H

#include "encode.h"

// User symbols lookup tables for the steno layer
const uint16_t PROGMEM g_left_user_symbols_table[64][MAX_SYMBOLS] =
{
    NO_ENTRY,                               // [0]
    _S1(KC_ESC),                            // [1]      USRL_0
    _S1(_UNDS),                             // [2]      USRL_1
    _S2(KC_ESC, _COLN),                     // [3]      USRL_0|USRL_1
    _S1(_EXLM),                             // [4]      USRL_2
    NO_ENTRY,                               // [5]
    _S1(_PLUS),                             // [6]      USRL_1|USRL_2
    NO_ENTRY,                               // [7]
    _S1(_LCBR),                             // [8]      USRL_3
    NO_ENTRY,                               // [9]
    _S1(_MINS),                             // [10]     USRL_1|USRL_3
    NO_ENTRY,                               // [11]
    _S1(_LESS),                             // [12]     USRL_2|USRL_3
    NO_ENTRY,                               // [13]
    _S2(_PLUS, _PLUS),                      // [14]     USRL_1|USRL_2|USRL_3
    NO_ENTRY,                               // [15]
    _S1(_LPRN),                             // [16]     USRL_4
    NO_ENTRY,                               // [17]
    NO_ENTRY,                               // [18]
    NO_ENTRY,                               // [19]
    NO_ENTRY,                               // [20]
    NO_ENTRY,                               // [21]
    NO_ENTRY,                               // [22]
    NO_ENTRY,                               // [23]
    _S1(_LBRC),                             // [24]     USRL_3|USRL_4
    NO_ENTRY,                               // [25]
    _S2(_MINS, _MINS),                      // [26]     USRL_1|USRL_3|USRL_4
    NO_ENTRY,                               // [27]
    _S2(_LESS, _LESS),                      // [28]     USRL_2|USRL_3|USRL_4
    NO_ENTRY,                               // [29]
    NO_ENTRY,                               // [30]
    NO_ENTRY,                               // [31]
    _S1(_ASTR),                             // [32]     USRL_5
    NO_ENTRY,                               // [33]
    NO_ENTRY,                               // [34]
    NO_ENTRY,                               // [35]
    NO_ENTRY,                               // [36]
    NO_ENTRY,                               // [37]
    NO_ENTRY,                               // [38]
    NO_ENTRY,                               // [39]
    NO_ENTRY,                               // [40]
    NO_ENTRY,                               // [41]
    NO_ENTRY,                               // [42]
    NO_ENTRY,                               // [43]
    NO_ENTRY,                               // [44]
    NO_ENTRY,                               // [45]
    NO_ENTRY,                               // [46]
    NO_ENTRY,                               // [47]
    NO_ENTRY,                               // [48]
    NO_ENTRY,                               // [49]
    NO_ENTRY,                               // [50]
    NO_ENTRY,                               // [51]
    NO_ENTRY,                               // [52]
    NO_ENTRY,                               // [53]
    NO_ENTRY,                               // [54]
    NO_ENTRY,                               // [55]
    NO_ENTRY,                               // [56]
    NO_ENTRY,                               // [57]
    NO_ENTRY,                               // [58]
    NO_ENTRY,                               // [59]
    NO_ENTRY,                               // [60]
    NO_ENTRY,                               // [61]
    NO_ENTRY,                               // [62]
    NO_ENTRY                                // [63]
};

const uint16_t PROGMEM g_right_user_symbols_table[64][MAX_SYMBOLS] =
{
    NO_ENTRY,                               // [0]
    _S1(_AMP),                              // [1]      USRR_0
    _S1(_RPRN),                             // [2]      USRR_1
    NO_ENTRY,                               // [3]
    _S1(_RCBR),                             // [4]      USRR_2
    NO_ENTRY,                               // [5]
    _S1(_RBRC),                             // [6]      USRR_1|USRR_2
    NO_ENTRY,                               // [7]
    _S1(_COMM),                             // [8]      USRR_3
    NO_ENTRY,                               // [9]
    NO_ENTRY,                               // [10]
    NO_ENTRY,                               // [11]
    _S1(_GRTR),                             // [12]     USRR_2|USRR_3
    NO_ENTRY,                               // [13]
    _S2(_MINS, _GRTR),                      // [14]     USRR_1|USRR_2|USRR_3
    NO_ENTRY,                               // [15]
    _S1(_DOT),                              // [16]     USRR_4
    NO_ENTRY,                               // [17]
    NO_ENTRY,                               // [18]
    NO_ENTRY,                               // [19]
    NO_ENTRY,                               // [20]
    NO_ENTRY,                               // [21]
    NO_ENTRY,                               // [22]
    NO_ENTRY,                               // [23]
    NO_ENTRY,                               // [24]
    NO_ENTRY,                               // [25]
    NO_ENTRY,                               // [26]
    NO_ENTRY,                               // [27]
    _S2(_GRTR, _GRTR),                      // [28]     USRR_2|USRR_3|USRR_4
    NO_ENTRY,                               // [29]
    NO_ENTRY,                               // [30]
    NO_ENTRY,                               // [31]
    _S1(_SCLN),                             // [32]     USRR_5
    NO_ENTRY,                               // [33]
    _S2(_RPRN, _SCLN),                      // [34]     USRR_1|USRR_5
    NO_ENTRY,                               // [35]
    _S2(_RCBR, _SCLN),                      // [36]     USRR_2|USRR_5
    NO_ENTRY,                               // [37]
    _S2(_RBRC, _SCLN),                      // [38]     USRR_1|USRR_2|USRR_5
    NO_ENTRY,                               // [39]
    NO_ENTRY,                               // [40]
    NO_ENTRY,                               // [41]
    NO_ENTRY,                               // [42]
    NO_ENTRY,                               // [43]
    NO_ENTRY,                               // [44]
    NO_ENTRY,                               // [45]
    NO_ENTRY,                               // [46]
    NO_ENTRY,                               // [47]
    _S1(_COLN),                             // [48]     USRR_4|USRR_5
    NO_ENTRY,                               // [49]
    NO_ENTRY,                               // [50]
    NO_ENTRY,                               // [51]
    NO_ENTRY,                               // [52]
    NO_ENTRY,                               // [53]
    NO_ENTRY,                               // [54]
    NO_ENTRY,                               // [55]
    _S2(_COLN, _COLN),                      // [56]     USRR_3|USRR_4|USRR_5
    NO_ENTRY,                               // [57]
    NO_ENTRY,                               // [58]
    NO_ENTRY,                               // [59]
    NO_ENTRY,                               // [60]
    NO_ENTRY,                               // [61]
    NO_ENTRY,                               // [62]
    NO_ENTRY                                // [63]
};

#endif
