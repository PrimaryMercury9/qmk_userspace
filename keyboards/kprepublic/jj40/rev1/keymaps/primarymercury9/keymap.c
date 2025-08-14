#include QMK_KEYBOARD_H

enum layers {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _ARROWS,
  _PAGES,
  _NUMBERS,
  _NUMPAD,
  _FUNCTIONS
};


#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define SPACE  LT(_NUMBERS,KC_SPC)
#define CC_ESC LT(_ARROWS,KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_planck_mit( \
  KC_TAB,   KC_Q,   KC_W,    KC_E,     KC_R,   KC_T, KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC, \
  CC_ESC,   KC_A,   KC_S,    KC_D,     KC_F,   KC_G, KC_H,    KC_J,   KC_K,    KC_L,   KC_SCLN,  KC_QUOT, \
  SC_LSPO,  KC_Z,   KC_X,    KC_C,     KC_V,   KC_B, KC_N,    KC_M,  KC_COMM, KC_DOT,  KC_SLSH,  SC_RSPC, \
  KC_LCTL, KC_LBRC, KC_LALT, LOWER,  KC_LGUI,    SPACE   ,   KC_RGUI, RAISE, KC_RALT, KC_RBRC,  RCTL_T(KC_ENT)\
),

[_LOWER] = LAYOUT_planck_mit( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL , \
  CC_ESC,  _______, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,     _______     , _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

[_NUMBERS] = LAYOUT_planck_mit( \
  KC_GRV,  _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, KC_BSLS, \
  KC_CAPS,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,     _______     , _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

[_ARROWS] = LAYOUT_planck_mit( \
  _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______, _______, \
  _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN,  KC_UP , KC_RIGHT, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______\
),

};
void keyboard_post_init_user(void) {
    rgblight_setrgb(RGB_TEAL);
}
