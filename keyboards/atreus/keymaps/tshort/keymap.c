
#include "atreus.h"

#define _QWERTY 0
#define _SYM    1
#define _MOVE   2
#define _FN     3

#define _______ KC_TRNS


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = {
  {KC_Q,    KC_W,   KC_E, KC_R,          KC_T,   _______,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P    },
  {KC_A,    KC_S,   KC_D, KC_F,          KC_G,   _______,  KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT },
  {KC_Z,    KC_X,   KC_C, KC_V,          KC_B,   KC_LALT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH },
  {KC_BTN1,  LT(_MOVE, KC_GRV), GUI_T(KC_TAB), OSL(_SYM), SFT_T(KC_ENT), CTL_T(KC_ESC), LT(_MOVE, KC_SPC), LT(_SYM, KC_BSPC), KC_MINS, KC_SCLN, LT(_FN, KC_ENT)  }
},
[_SYM] = {
  {KC_PIPE, KC_EXLM, KC_LCBR, KC_RCBR, KC_AT,   _______, KC_PLUS,  KC_7, KC_8, KC_9, KC_CIRC},
  {KC_AMPR, KC_HASH, KC_LPRN, KC_RPRN, KC_DLR,  _______, KC_EQL,   KC_4, KC_5, KC_6, KC_ASTR},
  {KC_SCLN, KC_PERC, KC_LBRC, KC_RBRC, KC_BSLS, KC_LALT, KC_MINS,  KC_1, KC_2, KC_3, KC_SLSH},
  {KC_EQL,  KC_GRV,  _______, _______, KC_LSFT, CTL_T(KC_ESC), _______, _______, KC_0, KC_DOT, _______  }
},
[_MOVE] = {
  {KC_BTN2, KC_WH_U, KC_MS_U, KC_WH_D,  KC_WH_U, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,   _______},
  {KC_BTN3, KC_MS_L, KC_MS_D, KC_MS_R,  KC_LGUI, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, LALT(KC_TAB)},
  {KC_BTN5, KC_BTN1, KC_BTN2, KC_BTN1,  KC_WH_D, _______, KC_CAPS, KC_DEL,  KC_DEL,  _______,  RESET},
  {_______, _______, GUI_T(KC_TAB), _______, KC_LSFT, CTL_T(KC_ESC), _______, KC_BSPC, _______, KC_SCLN, KC_ENT  },
},
[_FN] = {
  {KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_WH_U, _______, _______, _______, _______, _______, _______},
  {KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_LGUI, _______, KC_CALC, KC_MAIL, KC_MYCM, KC_WHOM, _______},
  {KC_F9, KC_F10,  KC_F11, KC_F12, KC_WH_D, _______, _______, _______, _______, _______,  RESET},
  {_______,  _______, GUI_T(KC_TAB), _______, KC_LSFT, CTL_T(KC_ESC), _______, KC_BSPC, _______, KC_SCLN, LT(_FN, KC_ENT) },
}};

const uint16_t PROGMEM fn_actions[] = {};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {}

  return MACRO_NONE;
};
