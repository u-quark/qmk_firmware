#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_1,           KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_DEL,
        KC_GRV,         KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_BSPC,
        KC_TAB,         KC_A,       KC_S,       KC_D,       KC_F,       KC_G,
        KC_LSFT,        KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       SFT_T(KC_ESC),
        KC_LCTL,    	MO(SYMB),	KC_LALT,    KC_DOWN,    KC_UP,
                                                                                    MO(SYMB),   KC_LGUI,
                                                                                                KC_CALC,
                                                                            KC_ENT, KC_BSPC,    KC_PSCR,
        // right hand
                    KC_DEL,         KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,
                    KC_BSPC,        KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,
                                    KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
                    KC_CAPS,        KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
                                                KC_LEFT,    KC_RIGHT,   KC_BSLS,    KC_RBRC,    TG(MDIA),
        KC_HOME,    KC_END,
        KC_PGUP,
        KC_PGDN,    KC_DEL, KC_SPC
    ),

// SYMBOLS
[SYMB] = KEYMAP(
       // left hand
        KC_TRNS,        KC_F1,      KC_F2,      KC_F3,      KC_F4,          KC_F5,      KC_INS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    LCTL(KC_DOT),   LCTL(KC_I), KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        LCTL(KC_B), KC_TRNS,
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
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
