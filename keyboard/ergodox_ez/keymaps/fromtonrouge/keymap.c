#include "ergodox_ez.h"

#define AZERTY 1
#include "lookup_tables/shelton_table.h"

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

// Keys family
enum key_family
{
    FAMILY_UNKNOWN,
    FAMILY_CASE_CONTROL,
    FAMILY_LEFT_HAND,
    FAMILY_THUMBS,
    FAMILY_RIGHT_HAND,
    FAMILY_SPACES,
    NB_FAMILY
};

// Bit to identify a steno key
#define STENO_BIT (1L << 31) 

// 8 bits for the left hand
#define OFFSET_LEFT_HAND 0
#define L_A (0 | (FAMILY_LEFT_HAND << 4) | STENO_BIT)
#define L_S (1 | (FAMILY_LEFT_HAND << 4) | STENO_BIT)
#define L_C (2 | (FAMILY_LEFT_HAND << 4) | STENO_BIT)
#define L_T (3 | (FAMILY_LEFT_HAND << 4) | STENO_BIT)
#define L_W (4 | (FAMILY_LEFT_HAND << 4) | STENO_BIT)
#define L_H (5 | (FAMILY_LEFT_HAND << 4) | STENO_BIT)
#define L_N (6 | (FAMILY_LEFT_HAND << 4) | STENO_BIT)
#define L_R (7 | (FAMILY_LEFT_HAND << 4) | STENO_BIT)

// 4 bits for the thumbs
#define OFFSET_THUMBS 8
#define T_A (0 | (FAMILY_THUMBS << 4) | STENO_BIT)
#define T_O (1 | (FAMILY_THUMBS << 4) | STENO_BIT)
#define T_E (2 | (FAMILY_THUMBS << 4) | STENO_BIT)
#define T_U (3 | (FAMILY_THUMBS << 4) | STENO_BIT)

// 8 bits for the right hand
#define OFFSET_RIGHT_HAND 12
#define R_R (0 | (FAMILY_RIGHT_HAND << 4) | STENO_BIT)
#define R_N (1 | (FAMILY_RIGHT_HAND << 4) | STENO_BIT)
#define R_L (2 | (FAMILY_RIGHT_HAND << 4) | STENO_BIT)
#define R_G (3 | (FAMILY_RIGHT_HAND << 4) | STENO_BIT)
#define R_C (4 | (FAMILY_RIGHT_HAND << 4) | STENO_BIT)
#define R_H (5 | (FAMILY_RIGHT_HAND << 4) | STENO_BIT)
#define R_T (6 | (FAMILY_RIGHT_HAND << 4) | STENO_BIT)
#define R_S (7 | (FAMILY_RIGHT_HAND << 4) | STENO_BIT)

// 4 bits for space control keys (space, backspace, tab, return)
#define OFFSET_SPACE_CONTROLS 20
#define S_SPC  (0 | (FAMILY_SPACES << 4) | STENO_BIT)
#define S_BSPC (1 | (FAMILY_SPACES << 4) | STENO_BIT)
#define S_TAB  (2 | (FAMILY_SPACES << 4) | STENO_BIT)
#define S_RET  (3 | (FAMILY_SPACES << 4) | STENO_BIT)

// 2 bits for case control keys (upper case, initial case)
#define OFFSET_CASE_CONTROLS 27
#define C_UP   (0 | (FAMILY_CASE_CONTROL << 4) | STENO_BIT)
#define C_IUP  (1 | (FAMILY_CASE_CONTROL << 4) | STENO_BIT)

// Table to convert family id to bit offset
const uint8_t g_family_to_bit_offset[NB_FAMILY] =
{
    0,
    OFFSET_CASE_CONTROLS,
    OFFSET_LEFT_HAND,
    OFFSET_THUMBS,
    OFFSET_RIGHT_HAND,
    OFFSET_SPACE_CONTROLS
};

// Global vars for the steno layer
uint32_t g_bits_keys_pressed = 0;
uint8_t g_family_bits[NB_FAMILY] = {0};
typedef const uint8_t lookup_table_t[ENCODE_SIZE];
lookup_table_t* g_family_tables[NB_FAMILY] = 
{
    0,
    0,
    g_left_hand_table,
    g_thumbs_table,
    g_right_hand_table,
    g_spaces_ctl_table
};

// Steno keymap
const uint32_t PROGMEM g_steno_keymap[1][MATRIX_ROWS][MATRIX_COLS] =
{
    KEYMAP(
                // Left hand
                0,      0,         0,    0,    0,    0,        0,
                S_TAB,  0,         0,    0,    0,    0,        0,
                C_IUP,  L_A,       L_C,  L_W,  L_N,  KC_BSPC,
                C_UP,   L_S,       L_T,  L_H,  L_R,  KC_ENT,   0,
                0,      FR_SCLN,   0,    0,    0,
                                                                 0,     0,
                                                                        0,
                                                          T_A,   T_O,   0,
                // Right hand
                            0,     0,      0,    0,    0,        0,       0,
                            0,     0,      0,    0,    0,        0,       0,
                                   S_SPC,  R_R,  R_L,  R_C,      R_T,     C_IUP,
                            0,     KC_DEL, R_N,  R_G,  R_H,      R_S,     C_UP,
                                           0,    0,    FR_COMM,  FR_DOT,  0,
                0,     0,
                0,
                0,     T_E,   T_U
          )
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
#define ST_ON M(STENO)
[LAYER_STENO] = KEYMAP(
        // left hand
        ST_ON,        ST_ON,      ST_ON,      ST_ON,      ST_ON,      ST_ON,        ST_ON,
        ST_ON,        ST_ON,      ST_ON,      ST_ON,      ST_ON,      ST_ON,        KC_TRNS,
        ST_ON,        ST_ON,      ST_ON,      ST_ON,      ST_ON,      ST_ON,   
        ST_ON,        ST_ON,      ST_ON,      ST_ON,      ST_ON,      ST_ON,        KC_TRNS,
        KC_TRNS,      ST_ON,      KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                                                        KC_TRNS,    KC_TRNS,
                                                                                                    KC_TRNS,
                                                                            ST_ON,      ST_ON,      KC_TRNS,
        // right hand
                    ST_ON,          ST_ON,      ST_ON,      ST_ON,      ST_ON,      ST_ON,      ST_ON,
                    KC_TRNS,        ST_ON,      ST_ON,      ST_ON,      ST_ON,      ST_ON,      ST_ON,
                                    ST_ON,      ST_ON,      ST_ON,      ST_ON,      ST_ON,      ST_ON,   
                    KC_TRNS,        ST_ON,      ST_ON,      ST_ON,      ST_ON,      ST_ON,      ST_ON,   
                                                KC_TRNS,    KC_TRNS,    ST_ON,      ST_ON,      KC_TRNS,
        KC_TRNS,      KC_TRNS,
        KC_TRNS,
        KC_TRNS,      ST_ON,      ST_ON    
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
    // Send characters for each key family
    bool initial_shift_state = false; // TODO
    bool upper_case = false;
    bool initial_case_1 = false;
    bool initial_case_2 = false;
    for (int family_id = 0; family_id < NB_FAMILY; ++family_id)
    {
        const uint8_t family_bits = g_family_bits[family_id];
        if (family_id == FAMILY_CASE_CONTROL)
        {
            upper_case = family_bits == 1;
            initial_case_1 = family_bits == 2;
            initial_case_2 = family_bits == 3;

            if (upper_case || initial_case_1 || initial_case_2)
            {
                register_code(KC_LSFT);
            }
        }

        lookup_table_t* lookup_table = g_family_tables[family_id];
        uint8_t sent_count = 0;
        if (lookup_table)
        {
            for (int char_pos = 0; char_pos < ENCODE_SIZE; ++char_pos)
            {
                const uint8_t byte = pgm_read_byte(&(lookup_table[family_bits][char_pos]));
                if (byte)
                {
                    register_code(byte);
                    unregister_code(byte);
                    sent_count++;

                    if ((initial_case_1 && sent_count == 1) || (initial_case_2 && sent_count == 2))
                    {
                        unregister_code(KC_LSFT);
                    }
                }
                else
                {
                    break;
                }
            }
        }
    }

    if ((upper_case || initial_case_1 || initial_case_2) && !initial_shift_state)
    {
        unregister_code(KC_LSFT);
    }

    // Clear bits
    for (int i = 0; i < NB_FAMILY; ++i)
    {
        g_family_bits[i] = 0;
    }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t macroId, uint8_t opt)
{
    switch (macroId)
    {
    case STENO:
        {
            const uint32_t dword = pgm_read_dword(&(g_steno_keymap[0][record->event.key.row][record->event.key.col]));
            if (dword & STENO_BIT)
            {
                const uint8_t key_offset = dword & 0x0F;
                const uint32_t bit_key = 1L << key_offset;
                const uint8_t family = (dword >> 4) & 0x0F;
                const uint8_t family_offset = g_family_to_bit_offset[family];
                if (record->event.pressed)
                {
                    if (dword)
                    {
                        g_bits_keys_pressed |= (bit_key << family_offset);
                        g_family_bits[family] |= bit_key;
                    }
                }
                else
                {
                    if (dword)
                    {
                        g_bits_keys_pressed &= ~(bit_key << family_offset);
                    }

                    // Stroke if all steno keys are released
                    if (g_bits_keys_pressed == 0)
                    {
                        stroke();
                    }
                }
            }
            else
            {
                // Send mods and key code
                const uint16_t word = dword & 0xFFFF;
                const uint8_t mod_bits = (word >> 8) & 0xFF;
                const uint8_t code = word & 0xFF;
                if (record->event.pressed)
                {
                    add_mods(mod_bits);
                    register_code(code);
                }
                else
                {
                    del_mods(mod_bits);
                    unregister_code(code);
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
void * matrix_init_user(void) { return 0; }

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

    if (g_bits_keys_pressed)
    {
        ergodox_right_led_2_on();
    }
    return 0;
}
