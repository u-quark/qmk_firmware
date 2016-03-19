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

// Lookup tables for the steno layer
const unsigned long PROGMEM left_hand_table[256] =
{
    0,                  // [0]
    0,                  // [1]
    0,                  // [2]
    0,                  // [3]
    0,                  // [4]
    0,                  // [5]
    0,                  // [6]
    0,                  // [7]
    0,                  // [8]
    0,                  // [9]
    0,                  // [10]
    0,                  // [11]
    0,                  // [12]
    0,                  // [13]
    0,                  // [14]
    0,                  // [15]
    0,                  // [16]
    0,                  // [17]
    0,                  // [18]
    0,                  // [19]
    0,                  // [20]
    0,                  // [21]
    0,                  // [22]
    0,                  // [23]
    0,                  // [24]
    0,                  // [25]
    0,                  // [26]
    0,                  // [27]
    0,                  // [28]
    0,                  // [29]
    0,                  // [30]
    0,                  // [31]
    0,                  // [32]
    0,                  // [33]
    0,                  // [34]
    0,                  // [35]
    0,                  // [36]
    0,                  // [37]
    0,                  // [38]
    0,                  // [39]
    0,                  // [40]
    0,                  // [41]
    0,                  // [42]
    0,                  // [43]
    0,                  // [44]
    0,                  // [45]
    0,                  // [46]
    0,                  // [47]
    0,                  // [48]
    0,                  // [49]
    0,                  // [50]
    0,                  // [51]
    0,                  // [52]
    0,                  // [53]
    0,                  // [54]
    0,                  // [55]
    0,                  // [56]
    0,                  // [57]
    0,                  // [58]
    0,                  // [59]
    0,                  // [60]
    0,                  // [61]
    0,                  // [62]
    0,                  // [63]
    0,                  // [64]
    0,                  // [65]
    0,                  // [66]
    0,                  // [67]
    0,                  // [68]
    0,                  // [69]
    0,                  // [70]
    0,                  // [71]
    0,                  // [72]
    0,                  // [73]
    0,                  // [74]
    0,                  // [75]
    0,                  // [76]
    0,                  // [77]
    0,                  // [78]
    0,                  // [79]
    0,                  // [80]
    0,                  // [81]
    0,                  // [82]
    0,                  // [83]
    0,                  // [84]
    0,                  // [85]
    0,                  // [86]
    0,                  // [87]
    0,                  // [88]
    0,                  // [89]
    0,                  // [90]
    0,                  // [91]
    0,                  // [92]
    0,                  // [93]
    0,                  // [94]
    0,                  // [95]
    0,                  // [96]
    0,                  // [97]
    0,                  // [98]
    0,                  // [99]
    0,                  // [100]
    0,                  // [101]
    0,                  // [102]
    0,                  // [103]
    0,                  // [104]
    0,                  // [105]
    0,                  // [106]
    0,                  // [107]
    0,                  // [108]
    0,                  // [109]
    0,                  // [110]
    0,                  // [111]
    0,                  // [112]
    0,                  // [113]
    0,                  // [114]
    0,                  // [115]
    0,                  // [116]
    0,                  // [117]
    0,                  // [118]
    0,                  // [119]
    0,                  // [120]
    0,                  // [121]
    0,                  // [122]
    0,                  // [123]
    0,                  // [124]
    0,                  // [125]
    0,                  // [126]
    0,                  // [127]
    0,                  // [128]
    0,                  // [129]
    0,                  // [130]
    0,                  // [131]
    0,                  // [132]
    0,                  // [133]
    0,                  // [134]
    0,                  // [135]
    0,                  // [136]
    0,                  // [137]
    0,                  // [138]
    0,                  // [139]
    0,                  // [140]
    0,                  // [141]
    0,                  // [142]
    0,                  // [143]
    0,                  // [144]
    0,                  // [145]
    0,                  // [146]
    0,                  // [147]
    0,                  // [148]
    0,                  // [149]
    0,                  // [150]
    0,                  // [151]
    0,                  // [152]
    0,                  // [153]
    0,                  // [154]
    0,                  // [155]
    0,                  // [156]
    0,                  // [157]
    0,                  // [158]
    0,                  // [159]
    0,                  // [160]
    0,                  // [161]
    0,                  // [162]
    0,                  // [163]
    0,                  // [164]
    0,                  // [165]
    0,                  // [166]
    0,                  // [167]
    0,                  // [168]
    0,                  // [169]
    0,                  // [170]
    0,                  // [171]
    0,                  // [172]
    0,                  // [173]
    0,                  // [174]
    0,                  // [175]
    0,                  // [176]
    0,                  // [177]
    0,                  // [178]
    0,                  // [179]
    0,                  // [180]
    0,                  // [181]
    0,                  // [182]
    0,                  // [183]
    0,                  // [184]
    0,                  // [185]
    0,                  // [186]
    0,                  // [187]
    0,                  // [188]
    0,                  // [189]
    0,                  // [190]
    0,                  // [191]
    0,                  // [192]
    0,                  // [193]
    0,                  // [194]
    0,                  // [195]
    0,                  // [196]
    0,                  // [197]
    0,                  // [198]
    0,                  // [199]
    0,                  // [200]
    0,                  // [201]
    0,                  // [202]
    0,                  // [203]
    0,                  // [204]
    0,                  // [205]
    0,                  // [206]
    0,                  // [207]
    0,                  // [208]
    0,                  // [209]
    0,                  // [210]
    0,                  // [211]
    0,                  // [212]
    0,                  // [213]
    0,                  // [214]
    0,                  // [215]
    0,                  // [216]
    0,                  // [217]
    0,                  // [218]
    0,                  // [219]
    0,                  // [220]
    0,                  // [221]
    0,                  // [222]
    0,                  // [223]
    0,                  // [224]
    0,                  // [225]
    0,                  // [226]
    0,                  // [227]
    0,                  // [228]
    0,                  // [229]
    0,                  // [230]
    0,                  // [231]
    0,                  // [232]
    0,                  // [233]
    0,                  // [234]
    0,                  // [235]
    0,                  // [236]
    0,                  // [237]
    0,                  // [238]
    0,                  // [239]
    0,                  // [240]
    0,                  // [241]
    0,                  // [242]
    0,                  // [243]
    0,                  // [244]
    0,                  // [245]
    0,                  // [246]
    0,                  // [247]
    0,                  // [248]
    0,                  // [249]
    0,                  // [250]
    0,                  // [251]
    0,                  // [252]
    0,                  // [253]
    0,                  // [254]
    0                   // [255]
};

const unsigned long PROGMEM thumbs_table[16] =
{
    0,                  // [0]
    0,                  // [1]
    0,                  // [2]
    0,                  // [3]
    0,                  // [4]
    0,                  // [5]
    0,                  // [6]
    0,                  // [7]
    0,                  // [8]
    0,                  // [9]
    0,                  // [10]
    0,                  // [11]
    0,                  // [12]
    0,                  // [13]
    0,                  // [14]
    0                   // [15]
};

const unsigned long PROGMEM right_hand_table[256] =
{
    0,                  // [0]
    0,                  // [1]
    0,                  // [2]
    0,                  // [3]
    0,                  // [4]
    0,                  // [5]
    0,                  // [6]
    0,                  // [7]
    0,                  // [8]
    0,                  // [9]
    0,                  // [10]
    0,                  // [11]
    0,                  // [12]
    0,                  // [13]
    0,                  // [14]
    0,                  // [15]
    0,                  // [16]
    0,                  // [17]
    0,                  // [18]
    0,                  // [19]
    0,                  // [20]
    0,                  // [21]
    0,                  // [22]
    0,                  // [23]
    0,                  // [24]
    0,                  // [25]
    0,                  // [26]
    0,                  // [27]
    0,                  // [28]
    0,                  // [29]
    0,                  // [30]
    0,                  // [31]
    0,                  // [32]
    0,                  // [33]
    0,                  // [34]
    0,                  // [35]
    0,                  // [36]
    0,                  // [37]
    0,                  // [38]
    0,                  // [39]
    0,                  // [40]
    0,                  // [41]
    0,                  // [42]
    0,                  // [43]
    0,                  // [44]
    0,                  // [45]
    0,                  // [46]
    0,                  // [47]
    0,                  // [48]
    0,                  // [49]
    0,                  // [50]
    0,                  // [51]
    0,                  // [52]
    0,                  // [53]
    0,                  // [54]
    0,                  // [55]
    0,                  // [56]
    0,                  // [57]
    0,                  // [58]
    0,                  // [59]
    0,                  // [60]
    0,                  // [61]
    0,                  // [62]
    0,                  // [63]
    0,                  // [64]
    0,                  // [65]
    0,                  // [66]
    0,                  // [67]
    0,                  // [68]
    0,                  // [69]
    0,                  // [70]
    0,                  // [71]
    0,                  // [72]
    0,                  // [73]
    0,                  // [74]
    0,                  // [75]
    0,                  // [76]
    0,                  // [77]
    0,                  // [78]
    0,                  // [79]
    0,                  // [80]
    0,                  // [81]
    0,                  // [82]
    0,                  // [83]
    0,                  // [84]
    0,                  // [85]
    0,                  // [86]
    0,                  // [87]
    0,                  // [88]
    0,                  // [89]
    0,                  // [90]
    0,                  // [91]
    0,                  // [92]
    0,                  // [93]
    0,                  // [94]
    0,                  // [95]
    0,                  // [96]
    0,                  // [97]
    0,                  // [98]
    0,                  // [99]
    0,                  // [100]
    0,                  // [101]
    0,                  // [102]
    0,                  // [103]
    0,                  // [104]
    0,                  // [105]
    0,                  // [106]
    0,                  // [107]
    0,                  // [108]
    0,                  // [109]
    0,                  // [110]
    0,                  // [111]
    0,                  // [112]
    0,                  // [113]
    0,                  // [114]
    0,                  // [115]
    0,                  // [116]
    0,                  // [117]
    0,                  // [118]
    0,                  // [119]
    0,                  // [120]
    0,                  // [121]
    0,                  // [122]
    0,                  // [123]
    0,                  // [124]
    0,                  // [125]
    0,                  // [126]
    0,                  // [127]
    0,                  // [128]
    0,                  // [129]
    0,                  // [130]
    0,                  // [131]
    0,                  // [132]
    0,                  // [133]
    0,                  // [134]
    0,                  // [135]
    0,                  // [136]
    0,                  // [137]
    0,                  // [138]
    0,                  // [139]
    0,                  // [140]
    0,                  // [141]
    0,                  // [142]
    0,                  // [143]
    0,                  // [144]
    0,                  // [145]
    0,                  // [146]
    0,                  // [147]
    0,                  // [148]
    0,                  // [149]
    0,                  // [150]
    0,                  // [151]
    0,                  // [152]
    0,                  // [153]
    0,                  // [154]
    0,                  // [155]
    0,                  // [156]
    0,                  // [157]
    0,                  // [158]
    0,                  // [159]
    0,                  // [160]
    0,                  // [161]
    0,                  // [162]
    0,                  // [163]
    0,                  // [164]
    0,                  // [165]
    0,                  // [166]
    0,                  // [167]
    0,                  // [168]
    0,                  // [169]
    0,                  // [170]
    0,                  // [171]
    0,                  // [172]
    0,                  // [173]
    0,                  // [174]
    0,                  // [175]
    0,                  // [176]
    0,                  // [177]
    0,                  // [178]
    0,                  // [179]
    0,                  // [180]
    0,                  // [181]
    0,                  // [182]
    0,                  // [183]
    0,                  // [184]
    0,                  // [185]
    0,                  // [186]
    0,                  // [187]
    0,                  // [188]
    0,                  // [189]
    0,                  // [190]
    0,                  // [191]
    0,                  // [192]
    0,                  // [193]
    0,                  // [194]
    0,                  // [195]
    0,                  // [196]
    0,                  // [197]
    0,                  // [198]
    0,                  // [199]
    0,                  // [200]
    0,                  // [201]
    0,                  // [202]
    0,                  // [203]
    0,                  // [204]
    0,                  // [205]
    0,                  // [206]
    0,                  // [207]
    0,                  // [208]
    0,                  // [209]
    0,                  // [210]
    0,                  // [211]
    0,                  // [212]
    0,                  // [213]
    0,                  // [214]
    0,                  // [215]
    0,                  // [216]
    0,                  // [217]
    0,                  // [218]
    0,                  // [219]
    0,                  // [220]
    0,                  // [221]
    0,                  // [222]
    0,                  // [223]
    0,                  // [224]
    0,                  // [225]
    0,                  // [226]
    0,                  // [227]
    0,                  // [228]
    0,                  // [229]
    0,                  // [230]
    0,                  // [231]
    0,                  // [232]
    0,                  // [233]
    0,                  // [234]
    0,                  // [235]
    0,                  // [236]
    0,                  // [237]
    0,                  // [238]
    0,                  // [239]
    0,                  // [240]
    0,                  // [241]
    0,                  // [242]
    0,                  // [243]
    0,                  // [244]
    0,                  // [245]
    0,                  // [246]
    0,                  // [247]
    0,                  // [248]
    0,                  // [249]
    0,                  // [250]
    0,                  // [251]
    0,                  // [252]
    0,                  // [253]
    0,                  // [254]
    0                   // [255]
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

void stroke(void)
{
    const unsigned long left_letters = pgm_read_dword(&(left_hand_table[bits_left_hand]));
    const unsigned long thumbs_letters = pgm_read_dword(&(thumbs_table[bits_thumbs]));
    const unsigned long right_letters = pgm_read_dword(&(right_hand_table[bits_right_hand]));

    // TODO

    // Clear bits and keyboard
    bits_left_hand = 0;
    bits_thumbs = 0;
    bits_right_hand = 0;
    clear_keyboard_but_mods();
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

                // Stroke if all keys are released
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
