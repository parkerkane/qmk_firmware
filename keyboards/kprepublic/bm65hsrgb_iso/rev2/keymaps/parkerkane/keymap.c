/* Copyright 2021 deadolus
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#define UNICODE_SELECTED_MODES UNICODE_MODE_WINCOMPOSE

enum layers {
	_BASE,
    _EXT,
	_UNI,
};

enum unicode_names {
    AUML_SMALL,
    AUML_BIG,
    OUML_SMALL,
    OUML_BIG,
};

const uint32_t unicode_map[] PROGMEM = {
    [AUML_SMALL] = L'ä',
    [AUML_BIG] = L'Ä',
    [OUML_SMALL] = L'ö',
    [OUML_BIG] = L'Ö',
};

#define KC_AUML XP(AUML_SMALL, AUML_BIG)
#define KC_OUML XP(OUML_SMALL, OUML_BIG)

#define MO_EXT MO(_EXT)
#define TG_UNI TG(_UNI)
#define MO_UNI2 MO(_UNI2)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_65_iso_blocker(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_PGDN,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,  KC_HOME,
        SC_LSPO,KC_GRAVE, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, MO_EXT,           KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_EXT] = LAYOUT_65_iso_blocker(
        _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,   KC_DEL, _______,
        _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_OUML, KC_AUML, _______, _______, _______,
        _______, _______, UC_WINC,  UC_MAC, _______, _______, QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                            _______,                    TG_UNI, _______,          _______, _______, _______
    ),


    [_UNI] = LAYOUT_65_iso_blocker(
         TG_UNI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_OUML, KC_AUML, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                            _______,                   _______, _______,          _______, _______, _______
    ),


/*

    [2] = LAYOUT_65_iso_blocker(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                            _______,                   _______, _______,          _______, _______, _______
    ),


*/

};

#ifdef RGB_MATRIX_ENABLE

static bool uniState = false;

// __attribute__ ((weak))
bool rgb_matrix_indicators_user(void)
{
    if (uniState)
    {
        int i;
        for (i = 16; i < 27; i++) rgb_matrix_set_color(i, 0xFF, 0x00, 0x00);
        for (i = 31; i < 42; i++) rgb_matrix_set_color(i, 0xFF, 0x00, 0x00);
        for (i = 46; i < 53; i++) rgb_matrix_set_color(i, 0xFF, 0x00, 0x00);
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // rgblight_set_layer_state(2, layer_state_cmp(state, _FN));
    // rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));

    uniState = layer_state_cmp(state, _UNI);

    return state;
}

#endif
