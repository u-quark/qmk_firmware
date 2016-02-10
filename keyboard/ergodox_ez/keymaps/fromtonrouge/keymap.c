#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "keymap_extras/keymap_dvorak.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// WARNING: It's a software-implemented layout so you have to install the Programmer Dvorak driver to use it
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        DV_1,           DV_2,       DV_3,       DV_4,       DV_5,       DV_6,       KC_DEL,
        DV_GRV,         DV_QUOT,    DV_COMM,    DV_DOT,     DV_P,       DV_Y,       KC_BSPC,
        KC_TAB,         DV_A,       DV_O,       DV_E,       DV_U,       DV_I,
        KC_LSFT,        DV_SCLN,    DV_Q,       DV_J,       DV_K,       DV_X,       KC_ESC,
        MO(SYMB),       KC_LCTL,    KC_LALT,    KC_DOWN,    KC_UP,
                                                                                    MO(SYMB),   KC_LGUI,
                                                                                                KC_CALC,
                                                                            KC_ENT, KC_BSPC,    KC_PSCR,
        // right hand
                    KC_CAPS,        DV_7,       DV_8,       DV_9,       DV_0,       DV_LBRC,    DV_RBRC,
                    KC_BSPC,        DV_F,       DV_G,       DV_C,       DV_R,       DV_L,       DV_SLSH,
                                    DV_D,       DV_H,       DV_T,       DV_N,       DV_S,       DV_MINS,
                    SFT_T(KC_ENT),  DV_B,       DV_M,       DV_W,       DV_V,       DV_Z,       KC_RSFT,
                                                KC_LEFT,    KC_RIGHT,   KC_BSLS,    DV_EQL,     TG(MDIA),
        KC_HOME,    KC_END,
        KC_PGUP,
        KC_PGDN,    KC_DEL, KC_SPC
    ),

// SYMBOLS
[SYMB] = KEYMAP(
       // left hand
        KC_TRNS,        KC_F1,      KC_F2,      KC_F3,      KC_F4,          KC_F5,          KC_INS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    LSFT(KC_INS),   LCTL(KC_INS),   KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        LSFT(KC_DEL),   KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                                                        KC_TRNS,    KC_TRNS,
                                                                                                    KC_TRNS,
                                                                            KC_TRNS,    KC_TRNS,    KC_TRNS,
       // right hand
                    KC_INS,         KC_F6,      KC_F7,      KC_F8,      KC_F9,          KC_F10,     KC_F11,
                    KC_TRNS,        KC_TRNS,    KC_KP_7,    KC_KP_8,    KC_KP_9,        KC_TRNS,    KC_F12,
                                    KC_TRNS,    KC_KP_4,    KC_KP_5,    KC_KP_6,        KC_TRNS,    KC_TRNS,
                    KC_TRNS,        KC_TRNS,    KC_KP_1,    KC_KP_2,    KC_KP_3,        KC_TRNS,    KC_TRNS,
                                                KC_KP_0,    KC_KP_DOT,  KC_TRNS,        KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,
        KC_TRNS,
        KC_TRNS,    KC_INS, KC_TRNS
),

// MEDIA AND MOUSE
[MDIA] = KEYMAP(
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_MS_U,    KC_TRNS,    KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_MS_L,    KC_MS_D,    KC_MS_R,    KC_MS_WH_UP,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_MS_WH_DOWN,  KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_BTN2,
                                                                                        KC_TRNS,    KC_TRNS,
                                                                                                    KC_TRNS,
                                                                            KC_BTN1,    KC_TRNS,    KC_TRNS,
    // right hand
                    KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                    KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_MPLY,
                    KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_MPRV,    KC_MNXT,    KC_TRNS,    KC_TRNS,
                                                KC_VOLU,    KC_VOLD,    KC_MUTE,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,
        KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          register_code(KC_RSFT);
        } else {
          unregister_code(KC_RSFT);
        }
        break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void * matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void * matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_2_on();
            break;
        case 2:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            // none
            break;
    }

};
