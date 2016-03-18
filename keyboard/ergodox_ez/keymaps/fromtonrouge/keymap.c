#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "keymap_extras/keymap_french.h"
#include "led.h"

#define LAYER_DVORAK 0      // default layer
#define LAYER_COLEMAK 1     // Colemak layer
#define LAYER_JACKDAW 2     // Jackdaw layer
#define LAYER_SHIFT_DVORAK 3       // Shifted Layer
#define LAYER_SHIFT_COLEMAK 4      // Shifted Layer
#define LAYER_FN 5          // Fn Layer

#define SFT_DVORAK 0
#define UNAPPLY_SFT_DVORAK 1
#define SFT_COLEMAK 2
#define UNAPPLY_SFT_COLEMAK 3
#define STENO 4

uint32_t bitsKeys = 0;
uint32_t bitsLeftHand = 0;
uint32_t bitsRightHand = 0;
uint32_t bitsThumbs = 0;

#define L_A (1L << 0)
#define L_C (1L << 1)
#define L_W (1L << 2)
#define L_N (1L << 3)
#define L_S (1L << 4)
#define L_T (1L << 5)
#define L_H (1L << 6)
#define L_R (1L << 7)

#define T_A (1L << 8)
#define T_O (1L << 9)
#define T_E (1L << 10)
#define T_U (1L << 11)

#define R_R (1L << 12)
#define R_L (1L << 13)
#define R_C (1L << 14)
#define R_T (1L << 15)
#define R_E (1L << 16)
#define R_N (1L << 17)
#define R_G (1L << 18)
#define R_H (1L << 19)
#define R_S (1L << 20)
#define R_Y (1L << 21)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[LAYER_DVORAK] = KEYMAP(  // layer 0 : default
        // left hand
        FR_AMP,         FR_LBRC,    FR_LCBR,    FR_RCBR,    FR_LPRN,    FR_EQL,     KC_INS,
        FR_DLR,         FR_SCLN,    FR_COMM,    FR_DOT,     KC_P,       KC_Y,       KC_BSPC,
        KC_TAB,         FR_A,       KC_O,       KC_E,       KC_U,       KC_I,
        M(SFT_DVORAK),  FR_APOS,    FR_Q,       KC_J,       KC_K,       KC_X,       KC_ESC,
        KC_LCTL,        FR_AMP,     KC_LALT,    KC_UP,      KC_DOWN,
                                                                                    MO(LAYER_FN),       TG(LAYER_FN),
                                                                                                        KC_PSCR,
                                                                            KC_ENT, KC_BSPC,            KC_LGUI,
        // right hand
                    KC_CAPS,        FR_ASTR,    FR_RPRN,    FR_PLUS,    FR_RBRC,    FR_EXLM,    FR_HASH,
                    KC_BSPC,        KC_F,       KC_G,       KC_C,       KC_R,       KC_L,       FR_SLSH,
                                    KC_D,       KC_H,       KC_T,       KC_N,       KC_S,       FR_MINS,
                    KC_ENT,         KC_B,       FR_M,       FR_W,       KC_V,       FR_Z,       M(SFT_DVORAK),
                                                KC_LEFT,    KC_RIGHT,   FR_BSLS,    FR_AT,      KC_RCTL,
        TG(LAYER_FN),     MO(LAYER_FN),
        TG(LAYER_JACKDAW),
        TG(LAYER_COLEMAK),   KC_DEL, KC_SPC
    ),

// COLEMAK
[LAYER_COLEMAK] = KEYMAP(
        // left hand
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,
        FR_DLR,         FR_Q,       FR_W,       KC_F,       KC_P,       KC_G,           KC_TRNS,
        KC_TRNS,        FR_A,       KC_R,       KC_S,       KC_T,       KC_D,
        M(SFT_COLEMAK), FR_Z,       KC_X,       KC_C,       KC_V,       KC_B,           KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                                                        KC_TRNS,    KC_TRNS,
                                                                                                    KC_TRNS,
                                                                            KC_TRNS,    KC_TRNS,    KC_TRNS,
        // right hand
                    KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    FR_HASH,
                    KC_TRNS,        KC_J,       KC_L,       KC_U,       KC_Y,       FR_SCLN,    FR_SLSH,
                                    KC_H,       KC_N ,      KC_E,       KC_I,       KC_O,       FR_MINS,
                    KC_TRNS,        KC_K,       FR_M,       FR_COMM,    FR_DOT,     FR_APOS,    M(SFT_COLEMAK),
                                                KC_TRNS,    KC_TRNS,    FR_BSLS,    FR_AT,      KC_TRNS,
        KC_TRNS,    KC_TRNS,
        KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS
),

// JACKDAW LAYER
[LAYER_JACKDAW] = KEYMAP(
        // left hand
        KC_NO,        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,        KC_NO,
        KC_NO,        KC_1,       KC_2,       KC_3,       KC_4,       KC_5,         KC_TRNS,
        KC_NO,        M(4),       M(4),       M(4),       M(4),       M(4),
        KC_NO,        M(4),       M(4),       M(4),       M(4),       M(4),         KC_TRNS,
        KC_NO,        KC_NO,      KC_NO,      KC_TRNS,    KC_TRNS,
                                                                                        KC_TRNS,    KC_TRNS,
                                                                                                    KC_TRNS,
                                                                            M(4),       M(4),       KC_TRNS,
        // right hand
                    KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                    KC_TRNS,        KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_NO,
                                    M(4),       M(4),       M(4),       M(4),       M(4),       M(4),
                    KC_TRNS,        M(4),       M(4),       M(4),       M(4),       M(4),       M(4),
                                                KC_TRNS,    KC_TRNS,    KC_NO,      KC_NO,      KC_NO,
        KC_TRNS,    KC_TRNS,
        KC_TRNS,
        KC_TRNS,    M(4),    M(4)
),

// SHIFTED LAYER
[LAYER_SHIFT_DVORAK] = KEYMAP(
        FR_UGRV,        KC_7,       KC_5,       KC_3,       KC_1,       KC_9,           KC_TRNS,
        M(1),           M(1),       M(1),       M(1),       KC_TRNS,    KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,        M(1),       KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,
        KC_TRNS,        FR_UGRV,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                                                        KC_TRNS,    KC_TRNS,
                                                                                                    KC_TRNS,
                                                                            KC_TRNS,    KC_TRNS,    KC_TRNS,
    // right hand
                    KC_TRNS,        KC_0,       KC_2,       KC_4,       KC_6,       KC_8,       M(1),
                    KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    FR_COMM,
                                    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    M(1),
                    KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                KC_TRNS,    KC_TRNS,    M(1),       M(1),       KC_TRNS,
        KC_TRNS,    KC_TRNS,
        KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS
),

// SHIFTED LAYER
[LAYER_SHIFT_COLEMAK] = KEYMAP(
        FR_UGRV,        KC_7,       KC_5,       KC_3,       KC_1,       KC_9,           KC_TRNS,
        M(3),           KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,
        KC_TRNS,        FR_UGRV,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                                                        KC_TRNS,    KC_TRNS,
                                                                                                    KC_TRNS,
                                                                            KC_TRNS,    KC_TRNS,    KC_TRNS,
    // right hand
                    KC_TRNS,        KC_0,       KC_2,       KC_4,       KC_6,       KC_8,       M(3),
                    KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    M(3),       FR_COMM,
                                    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    M(3),
                    KC_TRNS,        KC_TRNS,    KC_TRNS,    M(3),       M(3),       M(3),       KC_TRNS,
                                                KC_TRNS,    KC_TRNS,    M(3),       M(3),       KC_TRNS,
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
                                                                                                    LCTL(KC_INS),
                                                                            KC_TRNS,    KC_TRNS,    LSFT(KC_INS),
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

void reg(uint8_t code)
{
    register_code(code);
}

void double_reg(uint8_t code)
{
    register_code(code);
    unregister_code(code);
    register_code(code);
}

void stroke(void)
{
    // Left hand lookup table
    switch (bitsLeftHand)
    {
    case L_A:                                           { reg(FR_A); break; }
    case L_S:                                           { reg(KC_S); break; }
    case L_C:                                           { reg(KC_C); break; }
    case L_T:                                           { reg(KC_T); break; }
    case L_W:                                           { reg(FR_W); break; }
    case L_H:                                           { reg(KC_H); break; }
    case L_N:                                           { reg(KC_N); break; }
    case L_R:                                           { reg(KC_R); break; }
    case L_S|L_C:                                       { reg(KC_S); reg(KC_C); break; }
    case L_S|L_T:                                       { reg(KC_S); reg(KC_T); break; }
    case L_S|L_W:                                       { reg(KC_S); reg(FR_W); break; }
    case L_S|L_H:                                       { reg(KC_S); reg(KC_H); break; }
    case L_S|L_N:                                       { reg(KC_S); reg(KC_N); break; }
    case L_S|L_R:                                       { reg(KC_S); reg(KC_E); reg(KC_R); break; }
    case L_C|L_T:                                       { reg(KC_D); break; }
    case L_C|L_W:                                       { reg(KC_P); break; }
    case L_C|L_H:                                       { reg(KC_C); reg(KC_H); break; }
    case L_C|L_N:                                       { reg(FR_Z); break; }
    case L_C|L_R:                                       { reg(KC_C); reg(KC_R); break; }
    case L_T|L_W:                                       { reg(KC_T); reg(FR_W); break; }
    case L_T|L_H:                                       { reg(KC_T); reg(KC_H); break; }
    case L_T|L_N:                                       { reg(KC_V); break; }
    case L_T|L_R:                                       { reg(KC_T); reg(KC_R); break; }
    case L_W|L_H:                                       { reg(FR_W); reg(KC_H); break; }
    case L_W|L_N:                                       { reg(FR_M); break; }
    case L_W|L_R:                                       { reg(FR_W); reg(KC_R); break; }
    case L_H|L_N:                                       { reg(KC_Y); break; }
    case L_H|L_R:                                       { reg(KC_R); reg(KC_H); break; }
    case L_N|L_R:                                       { reg(KC_L); break; }
    case L_S|L_C|L_T:                                   { reg(KC_G); break; }
    case L_S|L_C|L_W:                                   { reg(KC_S); reg(KC_P); break; }
    case L_S|L_C|L_H:                                   { reg(KC_S); reg(KC_C); reg(KC_H); break; }
    case L_S|L_C|L_N:                                   { double_reg(KC_S); break; }
    case L_S|L_C|L_R:                                   { reg(KC_S); reg(KC_C); reg(KC_R); break; }
    case L_S|L_T|L_W:                                   { reg(KC_X); break; }
    case L_S|L_T|L_N:                                   { reg(KC_S); reg(KC_V); break; }
    case L_S|L_T|L_R:                                   { reg(KC_S); reg(KC_T); reg(KC_R); break; }
    case L_S|L_W|L_N:                                   { reg(KC_S); reg(FR_M); break; }
    }

    // Thumb lookup table
    switch (bitsThumbs)
    {
    case T_A:                                           { reg(FR_A); break; }
    case T_O:                                           { reg(KC_O); break; }
    case T_E:                                           { reg(KC_E); break; }
    case T_U:                                           { reg(KC_U); break; }
    case T_A|T_O:                                       { reg(KC_I); reg(KC_O); break; }
    case T_A|T_E:                                       { reg(KC_E); reg(FR_A); break; }
    case T_O|T_E:                                       { reg(KC_I); reg(KC_E); break; }
    case T_O|T_U:                                       { reg(KC_O); reg(KC_U); break; }
    case T_E|T_U:                                       { reg(KC_I); break; }
    case T_A|T_O|T_E:                                   { double_reg(KC_E); break; }
    case T_O|T_E|T_U:                                   { reg(KC_O); reg(KC_I); break; }
    case T_A|T_O|T_U:                                   { double_reg(KC_O); break; }
    }

    // Right hand lookup table
    switch (bitsRightHand)
    {
    case R_R:                                           { reg(KC_R); break; }
    case R_N:                                           { reg(KC_N); break; }
    case R_L:                                           { reg(KC_L); break; }
    case R_G:                                           { reg(KC_G); break; }
    case R_C:                                           { reg(KC_C); break; }
    case R_H:                                           { reg(KC_H); break; }
    case R_T:                                           { reg(KC_T); break; }
    case R_S:                                           { reg(KC_S); break; }
    case R_E:                                           { reg(KC_E); break; }
    case R_Y:                                           { reg(KC_Y); break; }
    case R_R|R_N:                                       { reg(KC_R); reg(KC_N); break; }
    }

    // Clear bits and keyboard
    bitsLeftHand = 0;
    bitsRightHand = 0;
    bitsThumbs = 0;
    clear_keyboard_but_mods();
}

void registerLeftHand(uint32_t bit)
{
    bitsKeys |= bit;
    bitsLeftHand |= bit;
}

void unregisterLeftHand(uint32_t bit)
{
    bitsKeys &= ~bit;
}

void registerRightHand(uint32_t bit)
{
    bitsKeys |= bit;
    bitsRightHand |= bit;
}

void unregisterRightHand(uint32_t bit)
{
    bitsKeys &= ~bit;
}

void registerThumb(uint32_t bit)
{
    bitsKeys |= bit;
    bitsThumbs |= bit;
}

void unregisterThumb(uint32_t bit)
{
    bitsKeys &= ~bit;
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t macroId, uint8_t opt)
{
    switch (macroId)
    {
    case STENO:
        {
            const int nPhysicalRow = record->event.key.col;
            const int nPhysicalCol = record->event.key.row;
            if (record->event.pressed)
            {
                switch (nPhysicalRow)
                {
                case 2:
                    {
                        switch (nPhysicalCol)
                        {
                        case 1: // Left hand
                            {
                                registerLeftHand(L_A);
                                break;
                            }
                        case 2:
                            {
                                registerLeftHand(L_C);
                                break;
                            }
                        case 3:
                            {
                                registerLeftHand(L_W);
                                break;
                            }
                        case 4:
                            {
                                registerLeftHand(L_N);
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
                                registerRightHand(R_R);
                                break;
                            }
                        case 10:
                            {
                                registerRightHand(R_L);
                                break;
                            }
                        case 11:
                            {
                                registerRightHand(R_C);
                                break;
                            }
                        case 12:
                            {
                                registerRightHand(R_T);
                                break;
                            }
                        case 13:
                            {
                                registerRightHand(R_E);
                                break;
                            }
                        }
                        break;
                    }
                case 3:
                    {
                        switch (nPhysicalCol)
                        {
                        case 1: // Left hand
                            {
                                registerLeftHand(L_S);
                                break;
                            }
                        case 2:
                            {
                                registerLeftHand(L_T);
                                break;
                            }
                        case 3:
                            {
                                registerLeftHand(L_H);
                                break;
                            }
                        case 4:
                            {
                                registerLeftHand(L_R);
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
                                registerRightHand(R_N);
                                break;
                            }
                        case 10:
                            {
                                registerRightHand(R_G);
                                break;
                            }
                        case 11:
                            {
                                registerRightHand(R_H);
                                break;
                            }
                        case 12:
                            {
                                registerRightHand(R_S);
                                break;
                            }
                        case 13:
                            {
                                registerRightHand(R_Y);
                                break;
                            }
                        }
                        break;
                    }
                case 5: // Thumb
                    {
                        switch (nPhysicalCol)
                        {
                        case 3:
                            {
                                registerThumb(T_A);
                                break;
                            }
                        case 2:
                            {
                                registerThumb(T_O);
                                break;
                            }
                        case 11:
                            {
                                registerThumb(T_E);
                                break;
                            }
                        case 10:
                            {
                                registerThumb(T_U);
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            else
            {
                switch (nPhysicalRow)
                {
                case 2:
                    {
                        switch (nPhysicalCol)
                        {
                        case 1: // Left hand
                            {
                                unregisterLeftHand(L_A);
                                break;
                            }
                        case 2:
                            {
                                unregisterLeftHand(L_C);
                                break;
                            }
                        case 3:
                            {
                                unregisterLeftHand(L_W);
                                break;
                            }
                        case 4:
                            {
                                unregisterLeftHand(L_N);
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
                                unregisterRightHand(R_R);
                                break;
                            }
                        case 10:
                            {
                                unregisterRightHand(R_L);
                                break;
                            }
                        case 11:
                            {
                                unregisterRightHand(R_C);
                                break;
                            }
                        case 12:
                            {
                                unregisterRightHand(R_T);
                                break;
                            }
                        case 13:
                            {
                                unregisterRightHand(R_E);
                                break;
                            }
                        }
                        break;
                    }
                case 3:
                    {
                        switch (nPhysicalCol)
                        {
                        case 1: // Left hand
                            {
                                unregisterLeftHand(L_S);
                                break;
                            }
                        case 2:
                            {
                                unregisterLeftHand(L_T);
                                break;
                            }
                        case 3:
                            {
                                unregisterLeftHand(L_H);
                                break;
                            }
                        case 4:
                            {
                                unregisterLeftHand(L_R);
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
                                unregisterRightHand(R_N);
                                break;
                            }
                        case 10:
                            {
                                unregisterRightHand(R_G);
                                break;
                            }
                        case 11:
                            {
                                unregisterRightHand(R_H);
                                break;
                            }
                        case 12:
                            {
                                unregisterRightHand(R_S);
                                break;
                            }
                        case 13:
                            {
                                unregisterRightHand(R_Y);
                                break;
                            }
                        }
                        break;
                    }
                case 5: // Thumb
                    {
                        switch (nPhysicalCol)
                        {
                        case 3:
                            {
                                unregisterThumb(T_A);
                                break;
                            }
                        case 2:
                            {
                                unregisterThumb(T_O);
                                break;
                            }
                        case 11:
                            {
                                unregisterThumb(T_E);
                                break;
                            }
                        case 10:
                            {
                                unregisterThumb(T_U);
                                break;
                            }
                        }
                        break;
                    }
                }

                // Stroke if all keys are released
                if (bitsKeys == 0)
                {
                    stroke();
                }
            }
            break;
        }
    case SFT_DVORAK: // Apply SHIFT and go to LAYER_SHIFT_DVORAK 
        {
            if (record->event.pressed)
            {
                register_code(KC_LSFT);
                layer_on(LAYER_SHIFT_DVORAK);
            }
            else
            {
                unregister_code(KC_LSFT);
                layer_off(LAYER_SHIFT_DVORAK);
            }
            break;
        }
    case SFT_COLEMAK: // Apply SHIFT and go to LAYER_SHIFT_COLEMAK
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
    case UNAPPLY_SFT_DVORAK: // Unapply SHIFT and register keycode on press
        {
            uint16_t keycode = keymap_key_to_keycode(LAYER_DVORAK, record->event.key);
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
                case FR_DLR:
                    {
                        register_code(KC_RALT);
                        register_code(FR_TILD);
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
                        unregister_code(FR_GRTR);
                        break;
                    }
                case FR_DLR:
                    {
                        unregister_code(KC_RALT);
                        unregister_code(FR_TILD);
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
    case UNAPPLY_SFT_COLEMAK: // Unapply SHIFT and register keycode on press
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
    case LAYER_JACKDAW:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        break;
    case LAYER_COLEMAK:
    case LAYER_SHIFT_COLEMAK:
        ergodox_right_led_3_on();
        break;
    default:
        break;
    }

    if (bitsLeftHand || bitsRightHand || bitsThumbs)
    {
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
    }
}
