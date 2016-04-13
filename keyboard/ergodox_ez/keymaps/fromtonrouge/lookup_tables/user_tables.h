#ifndef USER_TABLES_H
#define USER_TABLES_H

#include "encode.h"

// User symbols lookup tables for the steno layer
const uint16_t PROGMEM g_left_user_symbols_table[64][MAX_SYMBOLS] =
{
    NO_ENTRY,                               // [0]
    _S1(KC_ESC),                            // [1]      0
    _S1(_EXLM),                             // [2]      1
    _S2(KC_ESC, _COLN),                     // [3]      0|1
    _S1(_UNDS),                             // [4]      2
    _S1(_APOS),                             // [5]      0|2
    _S1(_PLUS),                             // [6]      1|2
    NO_ENTRY,                               // [7]
    _S1(_LCBR),                             // [8]      3
    NO_ENTRY,                               // [9]
    _S1(_MINS),                             // [10]     1|3
    NO_ENTRY,                               // [11]
    _S1(_LESS),                             // [12]     2|3
    _S1(_QUOT),                             // [13]     0|2|3
    _S2(_PLUS, _PLUS),                      // [14]     1|2|3
    NO_ENTRY,                               // [15]
    _S1(_LPRN),                             // [16]     4
    NO_ENTRY,                               // [17]
    _S2(_EXLM, _LPRN),                      // [18]     1|4
    NO_ENTRY,                               // [19]
    NO_ENTRY,                               // [20]
    NO_ENTRY,                               // [21]
    NO_ENTRY,                               // [22]
    NO_ENTRY,                               // [23]
    _S1(_LBRC),                             // [24]     3|4
    NO_ENTRY,                               // [25]
    _S2(_MINS, _MINS),                      // [26]     1|3|4
    NO_ENTRY,                               // [27]
    _S2(_LESS, _LESS),                      // [28]     2|3|4
    NO_ENTRY,                               // [29]
    NO_ENTRY,                               // [30]
    NO_ENTRY,                               // [31]
    _S1(_ASTR),                             // [32]     5
    _S1(_SLSH),                             // [33]     0|5
    NO_ENTRY,                               // [34]
    _S2(_SLSH, _ASTR),                      // [35]     0|1|5
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
    _S2(_SLSH, _SLSH),                      // [49]     0|4|5
    NO_ENTRY,                               // [50]
    NO_ENTRY,                               // [51]
    NO_ENTRY,                               // [52]
    NO_ENTRY,                               // [53]
    NO_ENTRY,                               // [54]
    NO_ENTRY,                               // [55]
    NO_ENTRY,                               // [56]
    _S3(_SLSH, _SLSH, _SLSH),               // [57]     0|3|4|5
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
    _S1(_SCLN),                             // [1]      0
    _S1(_DOT),                              // [2]      1
    _S1(_COLN),                             // [3]      0|1
    _S1(_COMM),                             // [4]      2
    _S1(_APOS),                             // [5]      0|2
    _S1(_PLUS),                             // [6]      1|2
    _S2(_COLN, _COLN),                      // [7]      0|1|2
    _S1(_RCBR),                             // [8]      3
    _S2(_RCBR, _SCLN),                      // [9]      0|3
    _S1(_MINS),                             // [10]     1|3
    NO_ENTRY,                               // [11]
    _S1(_GRTR),                             // [12]     2|3
    _S1(_QUOT),                             // [13]     0|2|3
    _S2(_PLUS, _PLUS),                      // [14]     1|2|3
    NO_ENTRY,                               // [15]
    _S1(_RPRN),                             // [16]     4
    _S2(_RPRN, _SCLN),                      // [17]     0|4
    NO_ENTRY,                               // [18]
    NO_ENTRY,                               // [19]
    _S2(_MINS, _GRTR),                      // [20]     2|4
    NO_ENTRY,                               // [21]
    NO_ENTRY,                               // [22]
    NO_ENTRY,                               // [23]
    _S1(_RBRC),                             // [24]     3|4
    _S2(_RBRC, _SCLN),                      // [25]     0|3|4
    _S2(_MINS, _MINS),                      // [26]     1|3|4
    NO_ENTRY,                               // [27]
    _S2(_GRTR, _GRTR),                      // [28]     2|3|4
    NO_ENTRY,                               // [29]
    NO_ENTRY,                               // [30]
    NO_ENTRY,                               // [31]
    _S1(_AMP),                              // [32]     5
    _S1(_BSLS),                             // [33]     0|5
    NO_ENTRY,                               // [34]
    _S2(_ASTR, _SLSH),                      // [35]     0|1|5
    NO_ENTRY,                               // [36]
    NO_ENTRY,                               // [37]
    NO_ENTRY,                               // [38]
    NO_ENTRY,                               // [39]
    _S1(_EQL),                              // [40]     3|5
    NO_ENTRY,                               // [41]
    NO_ENTRY,                               // [42]
    NO_ENTRY,                               // [43]
    _S2(_EQL, _EQL),                        // [44]     2|3|5
    NO_ENTRY,                               // [45]
    NO_ENTRY,                               // [46]
    NO_ENTRY,                               // [47]
    _S1(_QUES),                             // [48]     4|5
    NO_ENTRY,                               // [49]
    NO_ENTRY,                               // [50]
    NO_ENTRY,                               // [51]
    NO_ENTRY,                               // [52]
    NO_ENTRY,                               // [53]
    NO_ENTRY,                               // [54]
    NO_ENTRY,                               // [55]
    _S1(_EXLM),                             // [56]     3|4|5
    NO_ENTRY,                               // [57]
    NO_ENTRY,                               // [58]
    NO_ENTRY,                               // [59]
    NO_ENTRY,                               // [60]
    NO_ENTRY,                               // [61]
    NO_ENTRY,                               // [62]
    NO_ENTRY                                // [63]
};

#endif
