#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "led.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define SHIFTED_LAYER 3 // Shifted Layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        S(KC_7),        KC_LBRC,    S(KC_LBRC), S(KC_RBRC), S(KC_9),    KC_EQL,     KC_DEL,
        S(KC_4),        KC_QUOT,    KC_COMM,    KC_DOT,     KC_P,       KC_Y,       KC_BSPC,
        KC_TAB,         KC_A,       KC_O,       KC_E,       KC_U,       KC_I,
        M(0),           KC_SCLN,    KC_Q,       KC_J,       KC_K,       KC_X,       KC_ESC,
        KC_LCTL,        S(KC_7),    KC_LALT,    KC_DOWN,    KC_UP,
                                                                                    MO(SYMB),   TG(SYMB),
                                                                                                KC_PSCR,
                                                                            KC_ENT, KC_BSPC,    KC_LGUI,
        // right hand
                    KC_CAPS,        S(KC_8),    S(KC_0),    S(KC_EQL),  KC_RBRC,    S(KC_1),    S(KC_3),
                    KC_BSPC,        KC_F,       KC_G,       KC_C,       KC_R,       KC_L,       KC_SLSH,
                                    KC_D,       KC_H,       KC_T,       KC_N,       KC_S,       KC_MINS,
                    KC_ENT,         KC_B,       KC_M,       KC_W,       KC_V,       KC_Z,       M(0),
                                                KC_LEFT,    KC_RIGHT,   KC_BSLS,    S(KC_2),    KC_RCTL,
        TG(SYMB),   MO(SYMB),
        MO(MDIA),
        TG(MDIA),   KC_DEL, KC_SPC
    ),

// SYMBOLS
[SYMB] = KEYMAP(
       // left hand
        KC_TRNS,        KC_F1,      KC_F2,      KC_F3,      KC_F4,          KC_F5,          KC_F6,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    LSFT(KC_INS),   LCTL(KC_INS),   KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        LSFT(KC_DEL),   KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_PGDN,    KC_PGUP,
                                                                                        KC_TRNS,    KC_TRNS,
                                                                                                    KC_TRNS,
                                                                            KC_BSPC,    KC_TRNS,    KC_TRNS,
       // right hand
                    KC_F7,          KC_F8,      KC_F9,      KC_F10,     KC_F11,         KC_F12,     KC_TRNS,
                    KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,    KC_TRNS,
                                    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,    KC_TRNS,
                    KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,    KC_TRNS,
                                                KC_HOME,    KC_END,     KC_TRNS,        KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,
        KC_TRNS,
        KC_TRNS,    KC_INS, KC_BSPC
),

// KEYPAD AND MOUSE
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
                    KC_TRNS,        KC_TRNS,    KC_KP_7,    KC_KP_8,    KC_KP_9,    KC_TRNS,    KC_TRNS,
                                    KC_TRNS,    KC_KP_4,    KC_KP_5,    KC_KP_6,    KC_TRNS,    KC_TRNS,
                    KC_TRNS,        KC_TRNS,    KC_KP_1,    KC_KP_2,    KC_KP_3,    KC_TRNS,    KC_TRNS,
                                                KC_KP_0,    KC_KP_DOT,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,
        KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS
),

// SHIFTED LAYER
[SHIFTED_LAYER] = KEYMAP(
        KC_5,           M(1),       M(1),       M(1),       M(1),       M(1),           KC_TRNS,
        KC_GRV,         KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,
        KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                                                        KC_TRNS,    KC_TRNS,
                                                                                                    KC_TRNS,
                                                                            KC_TRNS,    KC_TRNS,    KC_TRNS,
    // right hand
                    KC_TRNS,        M(1),       M(1),       M(1),       M(1),       M(1),       M(1),
                    KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                    KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_6,       KC_TRNS,
        KC_TRNS,    KC_TRNS,
        KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS
),

};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t macroId, uint8_t opt)
{
    switch (macroId)
    {
    case 0: // M(0) : Apply SHIFT and go to SHIFTED_LAYER
        {
            if (record->event.pressed)
            {
                register_code(KC_LSFT);
                layer_on(SHIFTED_LAYER);
            }
            else
            {
                unregister_code(KC_LSFT);
                layer_off(SHIFTED_LAYER);
            }
            break;
        }
    case 1: // M(1) : Unapply SHIFT and register keycode on press
        {
			uint16_t keycode = keymap_key_to_keycode(BASE, record->event.key);
            if (record->event.pressed)
            {
				unregister_code(KC_LSFT);
				switch (keycode)
				{
				case KC_LBRC:
					{
						register_code(KC_7);
						break;
					}
				case S(KC_LBRC):
					{
						register_code(KC_5);
						break;
					}
				case S(KC_RBRC):
					{
						register_code(KC_3);
						break;
					}
				case S(KC_9):
					{
						register_code(KC_1);
						break;
					}
				case KC_EQL:
					{
						register_code(KC_9);
						break;
					}
				case S(KC_8):
					{
						register_code(KC_0);
						break;
					}
				case S(KC_0):
					{
						register_code(KC_2);
						break;
					}
				case S(KC_EQL):
					{
						register_code(KC_4);
						break;
					}
				case KC_RBRC:
					{
						register_code(KC_6);
						break;
					}
				case S(KC_1):
					{
						register_code(KC_8);
						break;
					}
				case S(KC_3):
					{
						register_code(KC_GRV);
						break;
					}
				}
            }
            else
            {
				switch (keycode)
				{
				case KC_LBRC:
					{
						unregister_code(KC_7);
						break;
					}
				case S(KC_LBRC):
					{
						unregister_code(KC_5);
						break;
					}
				case S(KC_RBRC):
					{
						unregister_code(KC_3);
						break;
					}
				case S(KC_9):
					{
						unregister_code(KC_1);
						break;
					}
				case KC_EQL:
					{
						unregister_code(KC_9);
						break;
					}
				case S(KC_8):
					{
						unregister_code(KC_0);
						break;
					}
				case S(KC_0):
					{
						unregister_code(KC_2);
						break;
					}
				case S(KC_EQL):
					{
						unregister_code(KC_4);
						break;
					}
				case KC_RBRC:
					{
						unregister_code(KC_6);
						break;
					}
				case S(KC_1):
					{
						unregister_code(KC_8);
						break;
					}
				case S(KC_3):
					{
						unregister_code(KC_GRV);
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

    ergodox_led_all_off();
    switch (layer)
    {
    case 1:
        ergodox_right_led_2_on();
        break;
    case 2:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        break;
    default:
        break;
    }

    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK))
    {
        ergodox_right_led_1_on();
    }
}
