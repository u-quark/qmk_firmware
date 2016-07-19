// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include "atreus.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QW 0
#define _RS 2
#define _LW 1


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QW] = { /* Qwerty */
  {KC_Q,    KC_W,   KC_E, KC_R,          KC_T,   KC_TRNS,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P    },
  {KC_A,    KC_S,   KC_D, KC_F,          KC_G,   KC_TRNS,  KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT },
  {KC_Z,    KC_X,   KC_C, LT(_LW, KC_V), LT(_LW, KC_B),   KC_LALT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH },
  {KC_EQL,  KC_GRV, GUI_T(KC_TAB), OSL(_RS), KC_LSFT, CTL_T(KC_ESC), KC_SPC, LT(_RS, KC_BSPC), LT(_LW, KC_MINS), KC_SCLN, KC_ENT  }
},
[_RS] = {
  {KC_PIPE, KC_EXLM, KC_LCBR, KC_RCBR, KC_AT,   KC_TRNS, KC_PLUS,  KC_7, KC_8, KC_9, KC_CIRC},
  {KC_AMPR, KC_HASH, KC_LPRN, KC_RPRN, KC_DLR,  KC_TRNS, KC_EQL,   KC_4, KC_5, KC_6, KC_ASTR},
  {KC_SCLN, KC_PERC, KC_LBRC, KC_RBRC, KC_BSLS, KC_LALT, KC_MINS,  KC_1, KC_2, KC_3, KC_SLSH},
  {KC_EQL,  KC_GRV, GUI_T(KC_TAB), KC_TRNS, KC_LSFT, CTL_T(KC_ESC), KC_SPC, KC_TRNS, KC_0, KC_DOT, KC_ENT  }
},
[_LW] = {
  {KC_F1,  KC_F2,  KC_F3, KC_F4, KC_F5,   KC_TRNS, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_TRNS},
  {KC_F6,  KC_F7,  KC_F8, KC_F9, KC_F10,  KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, KC_TRNS},
  {KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_TRNS,  RESET},
  {KC_EQL,  KC_GRV, GUI_T(KC_TAB), KC_TRNS, KC_LSFT, CTL_T(KC_ESC), KC_SPC, KC_BSPC, KC_TRNS, KC_SCLN, KC_ENT  }
}};

const uint16_t PROGMEM fn_actions[] = {

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
