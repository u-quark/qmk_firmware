#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "keymap_extras/keymap_french.h"
#include "led.h"

#define LAYER_COLEMAK 0             // Colemak layer
#define LAYER_JACKDAW 1             // Jackdaw layer
#define LAYER_SHIFT_COLEMAK 2       // Shifted Layer
#define LAYER_FN 3                  // Fn Layer

#define SFT_CMAK 0
#define USFT_CMAK 1
#define STENO 2

uint32_t bits_keys = 0;
uint32_t bits_left_hand = 0;
uint32_t bits_right_hand = 0;
uint32_t bits_thumbs = 0;

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

const unsigned long PROGMEM lookup_left[256] =
{
	// TODO
};

const unsigned long PROGMEM lookup_right[256] =
{
	// TODO
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
        TG(LAYER_JACKDAW),
        KC_NO,      KC_DEL,     KC_SPC
),

// JACKDAW LAYER
[LAYER_JACKDAW] = KEYMAP(
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
	const uint8_t index_left = bits_left_hand % 256;
	const uint8_t index_right = bits_right_hand % 256;
	const unsigned long left_keys = pgm_read_dword(&(lookup_left[index_left]));
	const unsigned long right_keys = pgm_read_dword(&(lookup_right[index_right]));

	/* TOO BIG FIRMWARE !
#define REGISTER1(bits, c1) case bits: register_code(c1); break
#define REGISTER2(bits, c1, c2) case bits: register_code(c1); unregister_code(c1); register_code(c2); break
#define REGISTER3(bits, c1, c2, c3) case bits: register_code(c1); unregister_code(c1); register_code(c2); unregister_code(c2); register_code(c3); break
#define REGISTER4(bits, c1, c2, c3, c4) case bits: register_code(c1); unregister_code(c1); register_code(c2); unregister_code(c2); register_code(c3); unregister_code(c3); register_code(c4); break
#define REGISTER5(bits, c1, c2, c3, c4, c5) case bits: register_code(c1); unregister_code(c1); register_code(c2); unregister_code(c2); register_code(c3); unregister_code(c3); register_code(c4); unregister_code(c4); register_code(c5); break

    // Left hand lookup table
    switch (bits_left_hand)
    {
        REGISTER1(  L_A,                           FR_A);
        REGISTER1(  L_S,                           KC_S);
        REGISTER1(  L_C,                           KC_C);
        REGISTER1(  L_T,                           KC_T);
        REGISTER1(  L_W,                           FR_W);
        REGISTER1(  L_H,                           KC_H);
        REGISTER1(  L_N,                           KC_N);
        REGISTER1(  L_R,                           KC_R);
        REGISTER2(  L_S|L_C,                       KC_S, KC_C);
        REGISTER2(  L_S|L_T,                       KC_S, KC_T);
        REGISTER2(  L_S|L_W,                       KC_S, FR_W);
        REGISTER2(  L_S|L_H,                       KC_S, KC_H);
        REGISTER2(  L_S|L_N,                       KC_S, KC_N);
        REGISTER3(  L_S|L_R,                       KC_S, KC_E, KC_R);
        REGISTER1(  L_C|L_T,                       KC_D);
        REGISTER1(  L_C|L_W,                       KC_P);
        REGISTER2(  L_C|L_H,                       KC_C, KC_H);
        REGISTER1(  L_C|L_N,                       FR_Z);
        REGISTER2(  L_C|L_R,                       KC_C, KC_R);
        REGISTER2(  L_T|L_W,                       KC_T, FR_W);
        REGISTER2(  L_T|L_H,                       KC_T, KC_H);
        REGISTER1(  L_T|L_N,                       KC_V);
        REGISTER2(  L_T|L_R,                       KC_T, KC_R);
        REGISTER2(  L_W|L_H,                       FR_W, KC_H);
        REGISTER1(  L_W|L_N,                       FR_M);
        REGISTER2(  L_W|L_R,                       FR_W, KC_R);
        REGISTER1(  L_H|L_N,                       KC_Y);
        REGISTER2(  L_H|L_R,                       KC_R, KC_H);
        REGISTER1(  L_N|L_R,                       KC_L);
        REGISTER1(  L_S|L_C|L_T,                   KC_G);
        REGISTER2(  L_S|L_C|L_W,                   KC_S, KC_P);
        REGISTER3(  L_S|L_C|L_H,                   KC_S, KC_C, KC_H);
        REGISTER2(  L_S|L_C|L_N,                   KC_S, KC_S);
        REGISTER3(  L_S|L_C|L_R,                   KC_S, KC_C, KC_R);
        REGISTER1(  L_S|L_T|L_W,                   KC_X);
        REGISTER2(  L_S|L_T|L_N,                   KC_S, KC_V);
        REGISTER3(  L_S|L_T|L_R,                   KC_S, KC_T, KC_R);
        REGISTER2(  L_S|L_W|L_N,                   KC_S, FR_M);
        REGISTER2(  L_S|L_H|L_N,                   KC_S, KC_Y);
        REGISTER3(  L_S|L_H|L_R,                   KC_S, KC_H, KC_R);
        REGISTER2(  L_S|L_N|L_R,                   KC_S, KC_L);
        REGISTER2(  L_C|L_T|L_W,                   KC_D, FR_W);
        REGISTER1(  L_C|L_T|L_H,                   KC_F);
        REGISTER3(  L_C|L_T|L_N,                   KC_D, KC_E, KC_V);
        REGISTER2(  L_C|L_T|L_R,                   KC_D, KC_R);
        REGISTER2(  L_C|L_W|L_H,                   KC_P, KC_H);
        REGISTER2(  L_C|L_W|L_N,                   KC_P, KC_N);
        REGISTER2(  L_C|L_W|L_R,                   KC_P, KC_R);
        REGISTER2(  L_C|L_H|L_N,                   KC_C, KC_Y);
        REGISTER3(  L_C|L_H|L_R,                   KC_C, KC_H, KC_R);
        REGISTER2(  L_C|L_N|L_R,                   KC_C, KC_L);
        REGISTER1(  L_T|L_W|L_H,                   KC_K);
        REGISTER1(  L_T|L_W|L_N,                   KC_J);
        REGISTER2(  L_T|L_H|L_N,                   KC_T, KC_Y);
        REGISTER3(  L_T|L_H|L_R,                   KC_T, KC_H, KC_R);
        REGISTER1(  L_T|L_N|L_R,                   FR_Q);
        REGISTER2(  L_W|L_H|L_N,                   KC_M, KC_Y);
        REGISTER2(  L_W|L_N|L_R,                   KC_M, KC_R);
        REGISTER2(  L_H|L_N|L_R,                   KC_L, KC_Y);
        REGISTER2(  L_S|L_C|L_T|L_W,               KC_G, KC_W);
        REGISTER2(  L_S|L_C|L_T|L_H,               KC_G, KC_H);
        REGISTER2(  L_S|L_C|L_T|L_N,               KC_G, KC_N);
        REGISTER2(  L_S|L_C|L_T|L_R,               KC_G, KC_R);
        REGISTER3(  L_S|L_C|L_W|L_H,               KC_S, KC_P, KC_H);
        REGISTER3(  L_S|L_C|L_W|L_R,               KC_S, KC_P, KC_R);
        REGISTER2(  L_S|L_T|L_W|L_H,               KC_S, KC_K);
        REGISTER2(  L_S|L_T|L_W|L_R,               KC_X, KC_R);
        REGISTER3(  L_S|L_T|L_H|L_N,               KC_S, KC_T, KC_Y);
        REGISTER2(  L_S|L_T|L_N|L_R,               KC_S, FR_Q);
        REGISTER3(  L_S|L_H|L_N|L_R,               KC_S, KC_L, KC_Y);
        REGISTER1(  L_C|L_T|L_W|L_H,               KC_B);
        REGISTER3(  L_C|L_T|L_W|L_N,               KC_D, KC_E, FR_M);
        REGISTER3(  L_C|L_T|L_W|L_R,               KC_D, KC_E, KC_R);
        REGISTER2(  L_C|L_T|L_H|L_N,               KC_D, KC_Y);
        REGISTER2(  L_C|L_T|L_H|L_R,               KC_F, KC_R);
        REGISTER3(  L_C|L_T|L_N|L_R,               KC_D, KC_E, KC_L);
        REGISTER2(  L_C|L_W|L_H|L_N,               KC_P, KC_Y);
        REGISTER3(  L_C|L_W|L_H|L_R,               KC_P, KC_H, KC_R);
        REGISTER2(  L_C|L_W|L_N|L_R,               KC_P, KC_L);
        REGISTER3(  L_C|L_H|L_N|L_R,               KC_C, KC_R, KC_Y);
        REGISTER2(  L_T|L_W|L_H|L_N,               KC_K, KC_N);
        REGISTER2(  L_T|L_W|L_H|L_R,               KC_K, KC_R);
        REGISTER3(  L_T|L_W|L_N|L_R,               KC_J, KC_E, KC_R);
        REGISTER3(  L_T|L_H|L_N|L_R,               KC_T, KC_R, KC_Y);
        REGISTER2(  L_S|L_C|L_T|L_H|L_N,           KC_G, KC_Y);
        REGISTER2(  L_S|L_C|L_T|L_N|L_R,           KC_G, KC_L);
        REGISTER3(  L_S|L_C|L_W|L_H|L_N,           KC_S, KC_P, KC_Y);
        REGISTER3(  L_S|L_C|L_W|L_N|L_R,           KC_S, KC_P, KC_L);
        REGISTER2(  L_S|L_T|L_W|L_H|L_N,           KC_X, KC_Y);
        REGISTER4(  L_S|L_T|L_W|L_N|L_R,           KC_S, KC_E, KC_R, KC_V);
        REGISTER4(  L_S|L_T|L_H|L_N|L_R,           KC_S, KC_T, KC_R, KC_Y);
        REGISTER2(  L_C|L_T|L_W|L_H|L_N,           KC_B, KC_Y);
        REGISTER2(  L_C|L_T|L_W|L_H|L_R,           KC_B, KC_R);
        REGISTER2(  L_C|L_T|L_H|L_N|L_R,           KC_F, KC_L);
        REGISTER3(  L_C|L_W|L_H|L_N|L_R,           KC_P, KC_H, KC_L);
        REGISTER2(  L_T|L_W|L_H|L_N|L_R,           KC_K, KC_L);
        REGISTER2(  L_C|L_T|L_W|L_H|L_N|L_R,       KC_B, KC_L);
        REGISTER2(  L_A|L_S,                       FR_A, KC_S);
        REGISTER2(  L_A|L_C,                       FR_A, KC_C);
        REGISTER2(  L_A|L_T,                       FR_A, KC_T);
        REGISTER2(  L_A|L_W,                       FR_A, FR_W);
        REGISTER2(  L_A|L_H,                       FR_A, KC_H);
        REGISTER2(  L_A|L_N,                       FR_A, KC_N);
        REGISTER2(  L_A|L_R,                       FR_A, KC_R);
        REGISTER3(  L_A|L_S|L_C,                   FR_A, KC_S, KC_C);
        REGISTER3(  L_A|L_S|L_T,                   FR_A, KC_S, KC_T);
        REGISTER3(  L_A|L_S|L_H,                   FR_A, KC_S, KC_H);
        REGISTER3(  L_A|L_S|L_N,                   FR_A, KC_N, KC_N);
        REGISTER3(  L_A|L_S|L_R,                   FR_A, KC_R, KC_R);
        REGISTER2(  L_A|L_C|L_T,                   FR_A, KC_D);
        REGISTER2(  L_A|L_C|L_W,                   FR_A, KC_P);
        REGISTER3(  L_A|L_C|L_H,                   FR_A, KC_C, KC_H);
        REGISTER2(  L_A|L_C|L_N,                   FR_A, FR_Z);
        REGISTER3(  L_A|L_C|L_R,                   FR_A, KC_C, KC_R);
        REGISTER3(  L_A|L_T|L_W,                   FR_A, KC_T, KC_T);
        REGISTER3(  L_A|L_T|L_H,                   FR_A, KC_T, KC_H);
        REGISTER2(  L_A|L_T|L_N,                   FR_A, KC_V);
        REGISTER3(  L_A|L_T|L_R,                   FR_A, KC_T, KC_R);
        REGISTER3(  L_A|L_W|L_H,                   FR_A, FR_W, KC_H);
        REGISTER2(  L_A|L_W|L_N,                   FR_A, FR_M);
        REGISTER2(  L_A|L_H|L_N,                   FR_A, KC_Y);
        REGISTER2(  L_A|L_N|L_R,                   FR_A, KC_L);
        REGISTER2(  L_A|L_S|L_C|L_T,               FR_A, KC_G);
        REGISTER3(  L_A|L_S|L_C|L_W,               FR_A, KC_S, KC_P);
        REGISTER3(  L_A|L_S|L_C|L_N,               FR_A, KC_S, KC_S);
        REGISTER4(  L_A|L_S|L_C|L_R,               FR_A, KC_S, KC_C, KC_R);
        REGISTER2(  L_A|L_S|L_T|L_W,               FR_A, KC_X);
        REGISTER4(  L_A|L_S|L_T|L_H,               FR_A, KC_S, KC_T, KC_H);
        REGISTER3(  L_A|L_S|L_W|L_N,               FR_A, KC_S, FR_M);
        REGISTER3(  L_A|L_S|L_H|L_N,               FR_A, KC_S, KC_Y);
        REGISTER3(  L_A|L_S|L_N|L_R,               FR_A, KC_S, KC_L);
        REGISTER3(  L_A|L_C|L_T|L_W,               FR_A, KC_D, KC_D);
        REGISTER2(  L_A|L_C|L_T|L_H,               FR_A, KC_F);
        REGISTER3(  L_A|L_C|L_T|L_N,               FR_A, KC_D, KC_V);
        REGISTER3(  L_A|L_C|L_T|L_R,               FR_A, KC_D, KC_R);
        REGISTER3(  L_A|L_C|L_W|L_H,               FR_A, KC_P, KC_H);
        REGISTER3(  L_A|L_C|L_W|L_N,               FR_A, FR_M, FR_M);
        REGISTER3(  L_A|L_C|L_W|L_R,               FR_A, KC_P, KC_R);
        REGISTER3(  L_A|L_C|L_H|L_N,               FR_A, KC_C, KC_C);
        REGISTER4(  L_A|L_C|L_H|L_R,               FR_A, KC_C, KC_C, KC_R);
        REGISTER2(  L_A|L_T|L_W|L_H,               FR_A, KC_K);
        REGISTER2(  L_A|L_T|L_W|L_N,               FR_A, KC_J);
        REGISTER4(  L_A|L_T|L_W|L_R,               FR_A, KC_T, KC_T, KC_R);
        REGISTER2(  L_A|L_T|L_N|L_R,               FR_A, FR_Q);
        REGISTER3(  L_A|L_W|L_N|L_R,               FR_A, KC_L, KC_L);
        REGISTER3(  L_A|L_S|L_C|L_T|L_W,           FR_A, KC_G, KC_G);
        REGISTER3(  L_A|L_S|L_C|L_T|L_H,           FR_A, KC_G, KC_H);
        REGISTER3(  L_A|L_S|L_C|L_T|L_N,           FR_A, KC_G, KC_N);
        REGISTER3(  L_A|L_S|L_C|L_T|L_R,           FR_A, KC_G, KC_R);
        REGISTER4(  L_A|L_S|L_C|L_W|L_H,           FR_A, KC_S, KC_P, KC_H);
        REGISTER3(  L_A|L_S|L_C|L_W|L_N,           FR_A, KC_P, KC_P);
        REGISTER4(  L_A|L_S|L_C|L_W|L_R,           FR_A, KC_P, KC_P, KC_R);
        REGISTER3(  L_A|L_S|L_T|L_W|L_H,           FR_A, KC_S, KC_K);
        REGISTER3(  L_A|L_S|L_T|L_N|L_R,           FR_A, KC_S, FR_Q);
        REGISTER2(  L_A|L_C|L_T|L_W|L_H,           FR_A, KC_B);
        REGISTER3(  L_A|L_C|L_T|L_W|L_N,           FR_A, KC_D, FR_M);
        REGISTER4(  L_A|L_C|L_T|L_W|L_R,           FR_A, KC_D, KC_D, KC_R);
        REGISTER3(  L_A|L_C|L_T|L_H|L_N,           FR_A, KC_F, KC_F);
        REGISTER3(  L_A|L_C|L_T|L_H|L_R,           FR_A, KC_F, KC_R);
        REGISTER3(  L_A|L_C|L_T|L_N|L_R,           FR_A, KC_C, FR_Q);
        REGISTER4(  L_A|L_C|L_W|L_H|L_R,           FR_A, KC_P, KC_H, KC_R);
        REGISTER3(  L_A|L_C|L_W|L_N|L_R,           FR_A, KC_P, KC_L);
        REGISTER4(  L_A|L_C|L_H|L_N|L_R,           FR_A, KC_C, KC_C, KC_L);
        REGISTER4(  L_A|L_T|L_W|L_H|L_N,           FR_A, KC_C, KC_K, KC_N);
        REGISTER4(  L_A|L_T|L_H|L_H|L_R,           FR_A, KC_T, KC_H, KC_L);
        REGISTER3(  L_A|L_S|L_C|L_T|L_W|L_H,       FR_A, KC_B, KC_B);
        REGISTER3(  L_A|L_S|L_C|L_T|L_W|L_N,       FR_A, KC_D, KC_J);
        REGISTER4(  L_A|L_S|L_C|L_T|L_W|L_R,       FR_A, KC_G, KC_G, KC_R);
        REGISTER3(  L_A|L_S|L_C|L_T|L_H|L_N,       FR_A, KC_F, KC_T);
        REGISTER4(  L_A|L_S|L_C|L_T|L_H|L_R,       FR_A, KC_F, KC_F, KC_R);
        REGISTER3(  L_A|L_S|L_C|L_T|L_N|L_R,       FR_A, KC_G, KC_L);
        REGISTER5(  L_A|L_S|L_C|L_W|L_H|L_N,       FR_A, KC_S, KC_P, KC_H, KC_Y);
        REGISTER4(  L_A|L_S|L_C|L_W|L_N|L_R,       FR_A, KC_P, KC_P, KC_L);
        REGISTER3(  L_A|L_C|L_T|L_W|L_H|L_N,       FR_A, KC_B, KC_Y);
        REGISTER3(  L_A|L_C|L_T|L_W|L_H|L_R,       FR_A, KC_B, KC_R);
        REGISTER4(  L_A|L_C|L_T|L_W|L_N|L_R,       FR_A, KC_D, KC_D, KC_L);
        REGISTER3(  L_A|L_C|L_T|L_H|L_N|L_R,       FR_A, KC_F, KC_L);
        REGISTER4(  L_A|L_S|L_C|L_T|L_W|L_H|L_R,   FR_A, KC_B, KC_B, KC_R);
        REGISTER4(  L_A|L_S|L_C|L_T|L_W|L_N|L_R,   FR_A, KC_G, KC_G, KC_L);
        REGISTER4(  L_A|L_S|L_C|L_T|L_H|L_N|L_R,   FR_A, KC_F, KC_F, KC_L);
        REGISTER3(  L_A|L_C|L_T|L_W|L_H|L_N|L_R,   FR_A, KC_B, KC_L);
    }

    // Thumb lookup table
    switch (bits_thumbs)
    {
        REGISTER1(  T_A,                           FR_A);
        REGISTER1(  T_O,                           KC_O);
        REGISTER1(  T_E,                           KC_E);
        REGISTER1(  T_U,                           KC_U);
        REGISTER2(  T_A|T_O,                       KC_I, KC_O);
        REGISTER2(  T_A|T_E,                       KC_E, FR_A);
        REGISTER2(  T_O|T_E,                       KC_I, KC_E);
        REGISTER2(  T_O|T_U,                       KC_O, KC_U);
        REGISTER1(  T_E|T_U,                       KC_I);
        REGISTER2(  T_A|T_O|T_E,                   KC_E, KC_E);
        REGISTER2(  T_O|T_E|T_U,                   KC_O, KC_I);
        REGISTER2(  T_A|T_O|T_U,                   KC_O, KC_O);
    }

    // Right hand lookup table
    switch (bits_right_hand)
    {
        REGISTER1(  R_R,                           KC_R);
        REGISTER1(  R_N,                           KC_N);
        REGISTER1(  R_L,                           KC_L);
        REGISTER1(  R_G,                           KC_G);
        REGISTER1(  R_C,                           KC_C);
        REGISTER1(  R_H,                           KC_H);
        REGISTER1(  R_T,                           KC_T);
        REGISTER1(  R_S,                           KC_S);
        REGISTER2(  R_R|R_N,                       KC_R, KC_N);
        REGISTER2(  R_R|R_L,                       KC_R, KC_L);
        REGISTER2(  R_R|R_G,                       KC_R, KC_G);
        REGISTER2(  R_R|R_C,                       KC_R, KC_C);
        REGISTER1(  R_R|R_H,                       FR_W);
        REGISTER2(  R_R|R_T,                       KC_R, KC_T);
        REGISTER2(  R_R|R_S,                       KC_R, KC_S);
        REGISTER1(  R_N|R_L,                       KC_S);
        REGISTER2(  R_N|R_G,                       KC_N, KC_G);
        REGISTER2(  R_N|R_C,                       KC_N, KC_C);
        REGISTER1(  R_N|R_H,                       KC_V);
        REGISTER2(  R_N|R_T,                       KC_N, KC_T);
        REGISTER2(  R_N|R_S,                       KC_N, KC_S);
        REGISTER2(  R_L|R_G,                       KC_L, KC_G);
        REGISTER1(  R_L|R_C,                       KC_P);
        REGISTER1(  R_L|R_H,                       FR_Z);
        REGISTER2(  R_L|R_T,                       KC_L, KC_T);
        REGISTER2(  R_L|R_S,                       KC_L, KC_S);
        REGISTER1(  R_G|R_C,                       KC_B);
        REGISTER2(  R_G|R_H,                       KC_G, KC_H);
        REGISTER1(  R_G|R_T,                       KC_K);
        REGISTER2(  R_G|R_S,                       KC_G, KC_S);
        REGISTER2(  R_C|R_H,                       KC_C, KC_H);
        REGISTER2(  R_C|R_T,                       KC_C, KC_T);
        REGISTER2(  R_C|R_S,                       KC_C, KC_S);
        REGISTER2(  R_H|R_T,                       KC_T, KC_H);
        REGISTER2(  R_H|R_S,                       KC_H, KC_S);
        REGISTER2(  R_T|R_S,                       KC_T, KC_S);
        REGISTER2(  R_R|R_N|R_L,                   KC_L, KC_L);
        REGISTER2(  R_R|R_N|R_G,                   KC_G, KC_N);
        REGISTER2(  R_R|R_N|R_H,                   KC_W, KC_N);
        REGISTER3(  R_R|R_N|R_T,                   KC_R, KC_N, KC_T);
        REGISTER3(  R_R|R_N|R_S,                   KC_R, KC_N, KC_S);
        REGISTER2(  R_R|R_L|R_C,                   KC_R, KC_P);
        REGISTER2(  R_R|R_L|R_H,                   FR_W, KC_L);
        REGISTER3(  R_R|R_L|R_S,                   KC_R, KC_L, KC_S);
        REGISTER2(  R_R|R_G|R_C,                   KC_R, KC_B);
        REGISTER3(  R_R|R_G|R_H,                   KC_R, KC_G, KC_H);
        REGISTER2(  R_R|R_G|R_T,                   KC_R, KC_K);
        REGISTER3(  R_R|R_G|R_S,                   KC_R, KC_G, KC_S);
        REGISTER3(  R_R|R_C|R_H,                   KC_R, KC_C, KC_H);
        REGISTER3(  R_R|R_C|R_S,                   KC_R, KC_C, KC_S);
        REGISTER3(  R_R|R_H|R_T,                   KC_R, KC_T, KC_H);
        REGISTER2(  R_R|R_H|R_S,                   FR_W, KC_S);
        REGISTER3(  R_R|R_T|R_S,                   KC_R, KC_T, KC_S);
        REGISTER1(  R_N|R_L|R_G,                   KC_D);
        REGISTER2(  R_N|R_L|R_C,                   KC_S, KC_P);
        REGISTER2(  R_N|R_L|R_H,                   KC_S, KC_H);
        REGISTER2(  R_N|R_L|R_T,                   KC_S, KC_T);
        REGISTER2(  R_N|R_L|R_S,                   KC_S, KC_S);
        REGISTER2(  R_N|R_G|R_C,                   KC_G, KC_G);
        REGISTER1(  R_N|R_G|R_H,                   FR_M);
        REGISTER2(  R_N|R_G|R_T,                   KC_N, KC_K);
        REGISTER3(  R_N|R_G|R_S,                   KC_N, KC_G, KC_S);
        REGISTER3(  R_N|R_C|R_H,                   KC_N, KC_C, KC_H);
        REGISTER4(  R_N|R_C|R_T,                   KC_T, KC_I, KC_O, KC_N);
        REGISTER4(  R_N|R_C|R_S,                   KC_N, KC_C, KC_E, KC_S);
        REGISTER3(  R_N|R_H|R_T,                   KC_N, KC_T, KC_H);
        REGISTER3(  R_N|R_H|R_S,                   KC_V, KC_E, KC_S);
        REGISTER3(  R_N|R_T|R_S,                   KC_N, KC_T, KC_S);
        REGISTER2(  R_L|R_G|R_C,                   KC_B, KC_L);
        REGISTER1(  R_L|R_G|R_H,                   KC_X);
        REGISTER2(  R_L|R_G|R_T,                   KC_K, KC_L);
        REGISTER2(  R_L|R_C|R_H,                   KC_P, KC_H);
        REGISTER2(  R_L|R_C|R_T,                   KC_P, KC_T);
        REGISTER2(  R_L|R_C|R_S,                   KC_P, KC_S);
        REGISTER3(  R_L|R_H|R_T,                   KC_L, KC_T, KC_H);
        REGISTER3(  R_L|R_H|R_S,                   FR_Z, KC_E, KC_S);
        REGISTER3(  R_L|R_T|R_S,                   KC_L, KC_T, KC_S);
        REGISTER1(  R_G|R_C|R_H,                   KC_F);
        REGISTER2(  R_G|R_C|R_T,                   KC_C, KC_K);
        REGISTER2(  R_G|R_C|R_S,                   KC_B, KC_S);
        REGISTER3(  R_G|R_H|R_T,                   KC_G, KC_H, KC_T);
        REGISTER3(  R_G|R_H|R_S,                   KC_G, KC_H, KC_S);
        REGISTER2(  R_G|R_T|R_S,                   KC_K, KC_S);
        REGISTER3(  R_C|R_H|R_T,                   KC_T, KC_C, KC_H);
        REGISTER1(  R_C|R_H|R_S,                   KC_D);
        REGISTER3(  R_C|R_T|R_S,                   KC_C, KC_T, KC_S);
        REGISTER3(  R_H|R_T|R_S,                   KC_T, KC_H, KC_S);
        REGISTER2(  R_R|R_N|R_L|R_G,               KC_D, KC_L);
        REGISTER2(  R_R|R_N|R_L|R_C,               KC_P, KC_L);
        REGISTER2(  R_R|R_N|R_L|R_H,               KC_L, KC_V);
        REGISTER3(  R_R|R_N|R_L|R_T,               KC_R, KC_S, KC_T);
        REGISTER3(  R_R|R_N|R_L|R_S,               KC_L, KC_L, KC_S);
        REGISTER2(  R_R|R_N|R_G|R_H,               KC_R, FR_M);
        REGISTER3(  R_R|R_N|R_G|R_S,               KC_G, KC_N, KC_S);
        REGISTER2(  R_R|R_N|R_C|R_H,               KC_R, KC_V);
        REGISTER3(  R_R|R_N|R_H|R_T,               FR_W, KC_T, KC_H);
        REGISTER3(  R_R|R_N|R_H|R_S,               FR_W, KC_N, KC_S);
        REGISTER3(  R_R|R_L|R_C|R_S,               KC_R, KC_P, KC_S);
        REGISTER3(  R_R|R_L|R_H|R_S,               FR_W, KC_L, KC_S);
        REGISTER2(  R_R|R_G|R_C|R_H,               KC_R, KC_F);
        REGISTER3(  R_R|R_G|R_C|R_S,               KC_R, KC_B, KC_S);
        REGISTER2(  R_R|R_G|R_H|R_T,               FR_W, KC_K);
        REGISTER3(  R_R|R_G|R_T|R_S,               KC_R, KC_K, KC_S);
        REGISTER2(  R_R|R_C|R_H|R_S,               KC_R, KC_D);
        REGISTER4(  R_R|R_H|R_T|R_S,               KC_R, KC_T, KC_H, KC_S);
        REGISTER2(  R_N|R_L|R_G|R_H,               KC_S, FR_M);
        REGISTER2(  R_N|R_L|R_G|R_T,               KC_S, KC_K);
        REGISTER2(  R_N|R_L|R_G|R_S,               KC_D, KC_S);
        REGISTER3(  R_N|R_L|R_C|R_T,               KC_N, KC_S, KC_T);
        REGISTER3(  R_N|R_L|R_C|R_S,               KC_S, KC_P, KC_S);
        REGISTER4(  R_N|R_L|R_H|R_S,               KC_S, KC_H, KC_E, KC_S);
        REGISTER3(  R_N|R_L|R_T|R_S,               KC_S, KC_T, KC_S);
        REGISTER2(  R_N|R_G|R_C|R_H,               FR_M, KC_B);
        REGISTER2(  R_N|R_G|R_C|R_T,               KC_B, KC_T);
        REGISTER3(  R_N|R_G|R_C|R_S,               KC_G, KC_G, KC_S);
        REGISTER4(  R_N|R_G|R_T|R_H,               KC_N, KC_G, KC_T, KC_H);
        REGISTER2(  R_N|R_G|R_H|R_S,               FR_M, KC_S);
        REGISTER3(  R_N|R_G|R_T|R_S,               KC_N, KC_K, KC_S);
        REGISTER2(  R_N|R_C|R_H|R_S,               KC_N, KC_D);
        REGISTER4(  R_N|R_H|R_T|R_S,               KC_N, KC_T, KC_H, KC_S);
        REGISTER2(  R_L|R_G|R_C|R_H,               KC_L, KC_F);
        REGISTER3(  R_L|R_G|R_C|R_T,               KC_C, KC_K, KC_L);
        REGISTER4(  R_L|R_G|R_C|R_S,               KC_B, KC_L, KC_E, KC_S);
        REGISTER2(  R_L|R_G|R_H|R_T,               KC_X, KC_T);
        REGISTER3(  R_L|R_G|R_H|R_S,               KC_X, KC_E, KC_S);
        REGISTER3(  R_L|R_C|R_H|R_T,               KC_P, KC_T, KC_H);
        REGISTER3(  R_L|R_C|R_H|R_S,               KC_P, KC_H, KC_S);
        REGISTER2(  R_G|R_C|R_H|R_T,               KC_F, KC_T);
        REGISTER2(  R_G|R_C|R_H|R_S,               KC_D, KC_G);
        REGISTER3(  R_G|R_C|R_T|R_S,               KC_C, KC_K, KC_S);
        REGISTER4(  R_G|R_H|R_T|R_S,               KC_G, KC_H, KC_T, KC_S);
        REGISTER2(  R_C|R_H|R_T|R_S,               KC_D, KC_S);
        REGISTER2(  R_R|R_N|R_L|R_G|R_C,           KC_L, KC_B);
        REGISTER2(  R_R|R_N|R_L|R_G|R_H,           KC_L, FR_M);
        REGISTER2(  R_R|R_N|R_L|R_G|R_T,           KC_L, KC_K);
        REGISTER3(  R_R|R_N|R_L|R_C|R_H,           KC_L, KC_C, KC_H);
        REGISTER2(  R_R|R_N|R_L|R_C|R_T,           KC_L, KC_P);
        REGISTER4(  R_R|R_N|R_L|R_C|R_S,           KC_P, KC_L, KC_E, KC_S);
        REGISTER4(  R_R|R_N|R_L|R_H|R_S,           KC_L, KC_V, KC_E, KC_S);
        REGISTER4(  R_R|R_N|R_L|R_T|R_S,           KC_R, KC_S, KC_T, KC_S);
        REGISTER3(  R_R|R_N|R_G|R_H|R_S,           KC_R, FR_M, KC_S);
        REGISTER2(  R_R|R_N|R_C|R_H|R_S,           FR_W, KC_D);
        REGISTER4(  R_R|R_N|R_H|R_T|R_S,           FR_W, KC_T, KC_H, KC_S);
        REGISTER3(  R_R|R_L|R_G|R_H|R_S,           KC_R, KC_L, KC_D);
        REGISTER3(  R_R|R_G|R_H|R_T|R_S,           FR_W, KC_K, KC_S);
        REGISTER3(  R_R|R_C|R_H|R_T|R_S,           KC_R, KC_D, KC_S);
        REGISTER2(  R_N|R_L|R_G|R_C|R_H,           FR_M, KC_P);
        REGISTER3(  R_N|R_L|R_G|R_H|R_T,           KC_D, KC_T, KC_H);
        REGISTER3(  R_N|R_L|R_G|R_H|R_S,           KC_S, KC_M, KC_S);
        REGISTER3(  R_N|R_L|R_G|R_T|R_S,           KC_S, KC_K, KC_S);
        REGISTER3(  R_N|R_G|R_C|R_H|R_S,           FR_M, KC_B, KC_S);
        REGISTER3(  R_N|R_G|R_C|R_T|R_S,           KC_B, KC_T, KC_S);
        REGISTER5(  R_N|R_G|R_H|R_T|R_S,           KC_N, KC_G, KC_T, KC_H, KC_S);
    }
	*/

    // Clear bits and keyboard
    bits_left_hand = 0;
    bits_right_hand = 0;
    bits_thumbs = 0;
    clear_keyboard_but_mods();
}

void registerLeftHand(uint32_t bit)
{
    bits_keys |= bit;
    bits_left_hand |= bit;
}

void unregisterLeftHand(uint32_t bit)
{
    bits_keys &= ~bit;
}

void registerRightHand(uint32_t bit)
{
    bits_keys |= bit;
    bits_right_hand |= bit;
}

void unregisterRightHand(uint32_t bit)
{
    bits_keys &= ~bit;
}

void registerThumb(uint32_t bit)
{
    bits_keys |= bit;
    bits_thumbs |= bit;
}

void unregisterThumb(uint32_t bit)
{
    bits_keys &= ~bit;
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
                if (bits_keys == 0)
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
    case LAYER_JACKDAW:
        ergodox_right_led_3_on();
        break;
    default:
        break;
    }

    if (bits_left_hand || bits_right_hand || bits_thumbs)
    {
        ergodox_right_led_2_on();
    }
}
