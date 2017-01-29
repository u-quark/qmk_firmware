
#include "atreus.h"

#define _QWERTY 0
#define _SYM    1
#define _MOVE   2
#define _FN     3


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = {
  {KC_Q,    KC_W,   KC_E, KC_R,          KC_T,   KC_TRNS,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P    },
  {KC_A,    KC_S,   KC_D, KC_F,          KC_G,   KC_TRNS,  KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT },
  {KC_Z,    KC_X,   KC_C, KC_V,          KC_B,   KC_LALT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH },
  {OSL(_MOVE),  KC_GRV, GUI_T(KC_TAB), OSL(_SYM), SFT_T(KC_ENT), CTL_T(KC_ESC), LT(_MOVE, KC_SPC), LT(_SYM, KC_BSPC), KC_MINS, KC_SCLN, KC_ENT  }
},
[_SYM] = {
  {KC_PIPE, KC_EXLM, KC_LCBR, KC_RCBR, KC_AT,   KC_TRNS, KC_PLUS,  KC_7, KC_8, KC_9, KC_CIRC},
  {KC_AMPR, KC_HASH, KC_LPRN, KC_RPRN, KC_DLR,  KC_TRNS, KC_EQL,   KC_4, KC_5, KC_6, KC_ASTR},
  {KC_SCLN, KC_PERC, KC_LBRC, KC_RBRC, KC_BSLS, KC_LALT, KC_MINS,  KC_1, KC_2, KC_3, KC_SLSH},
  {KC_EQL,  KC_GRV,  KC_TRNS, KC_TRNS, KC_LSFT, CTL_T(KC_ESC), KC_TRNS, KC_TRNS, KC_0, KC_DOT, KC_ENT  }
},
[_MOVE] = {
  {KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_WH_U, KC_TRNS, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_WH_U},
  {KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_LGUI, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, KC_WH_D},
  {KC_F9, KC_F10,  KC_F11, KC_F12, KC_WH_D, KC_TRNS, KC_CAPS, KC_WH_R, KC_DEL, KC_TRNS,  RESET},
  {KC_TRNS,  KC_TRNS, GUI_T(KC_TAB), KC_TRNS, KC_LSFT, CTL_T(KC_ESC), KC_TRNS, KC_BSPC, KC_TRNS, KC_SCLN, KC_ENT  },
}};

const uint16_t PROGMEM fn_actions[] = {};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {}

  return MACRO_NONE;
};
