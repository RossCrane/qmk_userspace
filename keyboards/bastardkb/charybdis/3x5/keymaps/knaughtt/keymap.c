/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

/*
LAYOUT_charybdis_3x5( \
K00,   K01,   K02,   K03,   K04,          K05,   K06,   K07,   K08,   K09, \
K10,   K11,   K12,   K13,   K14,          K15,   K16,   K17,   K18,   K19, \
K20,   K21,   K22,   K23,   K24,          K25,   K26,   K27,   K28,   K29, \
              K32,   K33,   K34,          K35,   K36 \
*/

#include QMK_KEYBOARD_H

#define _LAYER0 0 //BASE
#define _LAYER1 1 //SYMBOL
#define _LAYER2 2 //NUM
#define _LAYER3 3 //NAV
#define _LAYER4 4 //MEDIA
#define _LAYER5 5 //FUNCTION
#define _LAYER6 6 //GAMING
#define _LAYER7 7 //MMO

enum charybdis_keymap_layers {
    LAYER0 = SAFE_RANGE,
    LAYER1,
    LAYER2,
    LAYER3,
    LAYER4,
    LAYER5,
    LAYER6,
    LAYER7,
};

#define CTL_BSP CTL_T(KC_BSPC)
#define SFT_SPC SFT_T(KC_SPC)
#define GUI_ENT GUI_T(KC_ENT)
#define KC_COPY LCTL(KC_C)
#define KC_PASTE LCTL(KC_V)

/*
enum combos {
    COMBO_ESC,
    COMBO_TAB,
    COMBO_ENTER,
    COMBO_DEL,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;
const uint16_t PROGMEM combo_keys_esc[] = {KC_F, KC_W, COMBO_END};
const uint16_t PROGMEM combo_keys_tab[] = {KC_S, KC_R, COMBO_END};
const uint16_t PROGMEM combo_keys_enter[] = {KC_I, KC_E, COMBO_END};
const uint16_t PROGMEM combo_keys_del[] = {KC_Y, KC_U, COMBO_END};
combo_t key_combos[] = {
    [COMBO_ESC] = COMBO(combo_keys_esc, KC_ESC),
    [COMBO_TAB] = COMBO(combo_keys_tab, KC_TAB),
    [COMBO_ENTER] = COMBO(combo_keys_enter, KC_ENTER),
    [COMBO_DEL] = COMBO(combo_keys_del, KC_DELETE),
};
*/

/*
 * Combos are owned by the Argos module (it defines key_combos[] itself), so the
 * four combos from the 2023 keymap are set in Argos (argos.bastardkb.com), not here:
 *
 *   W + F        -> Ctrl+C (copy)
 *   R + S        -> Ctrl+V (paste)
 *   Y + ;        -> TO(7)  (MMO layer)
 *   U + Y        -> TO(6)  (gaming layer)
 *
 * Combo term was 40 ms, combos active from layer 0 only.
 */

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_LAYER0] = LAYOUT( //BASE
  // ╭─────────────────────────────────────────────╮                ╭─────────────────────────────────────────────╮
      LT(3,KC_Q),  KC_W,    KC_F,    KC_P, LT(4,KC_B),              LT(4,KC_J), KC_L, KC_U,   KC_Y, LT(3,KC_SCLN),
  // ├─────────────────────────────────────────────┤                ├─────────────────────────────────────────────┤
      KC_A,  KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N, KC_E,     KC_I,       KC_O,
  // ├─────────────────────────────────────────────┤                ├─────────────────────────────────────────────┤
      LGUI_T(KC_Z), LALT_T(KC_X), LCTL_T(KC_C), LSFT_T(KC_D), KC_V,  KC_K, RSFT_T(KC_H), RCTL_T(KC_COMM), RALT_T(KC_DOT), RGUI_T(KC_SLSH),
  // ╰─────────────────────────────────────────────┤                ├─────────────────────────────────────────────╯
                         LT(5,KC_ESC), KC_SPC, LT(1,KC_TAB),         LT(2,KC_ENT), KC_BSPC
  //                   ╰───────────────────────────╯                ╰──────────────────╯
  ),

  [_LAYER1] = LAYOUT( //SYMBOL
  // ╭─────────────────────────────────────────────╮                ╭─────────────────────────────────────────────╮
      LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5),    KC_GRV, LSFT(KC_LBRC), LSFT(KC_RBRC), KC_BSLS, KC_SCLN,
  // ├─────────────────────────────────────────────┤                ├─────────────────────────────────────────────┤
      LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), KC_COMM, KC_DOT,           KC_QUOT, LSFT(KC_9), LSFT(KC_0), LSFT(KC_MINS), KC_EQL,
  // ├─────────────────────────────────────────────┤                ├─────────────────────────────────────────────┤
      KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,                     LSFT(KC_QUOT), KC_LBRC, KC_RBRC, KC_MINS, KC_SLSH,
  // ╰─────────────────────────────────────────────┤                ├─────────────────────────────────────────────╯
                         KC_ESC, KC_SPC, KC_TRNS,                    KC_ENT, KC_BSPC
  //                   ╰───────────────────────────╯                ╰──────────────────╯
  ),

  [_LAYER2] = LAYOUT( //NUM
  // ╭─────────────────────────────────────────────╮                ╭─────────────────────────────────────────────╮
      KC_PSLS, KC_7, KC_8, KC_9, KC_PAST,                            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
  // ├─────────────────────────────────────────────┤                ├─────────────────────────────────────────────┤
      KC_PMNS, KC_4, KC_5, KC_6, KC_PPLS,                            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
  // ├─────────────────────────────────────────────┤                ├─────────────────────────────────────────────┤
      KC_EQL, KC_1, KC_2, KC_3, KC_DOT,                              KC_NO, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
  // ╰─────────────────────────────────────────────┤                ├─────────────────────────────────────────────╯
                        LSFT(KC_MINS), KC_0, KC_ENT,                 KC_TRNS, KC_BSPC
  //                   ╰───────────────────────────╯                ╰──────────────────╯
  ),

    [_LAYER3] = LAYOUT( //NAV
  // ╭─────────────────────────────────────────────╮                ╭─────────────────────────────────────────────╮
      KC_NO, KC_PGDN, KC_UP, KC_PGUP, MS_ACL2,                       MS_ACL2, KC_PGUP, KC_UP, KC_PGDN, KC_NO,
  // ├─────────────────────────────────────────────┤                ├─────────────────────────────────────────────┤
      KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, MS_ACL0,                   MS_ACL0, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS,
  // ├─────────────────────────────────────────────┤                ├─────────────────────────────────────────────┤
      KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,                     MS_BTN3,    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
  // ╰─────────────────────────────────────────────┤                ├─────────────────────────────────────────────╯
                         MS_BTN2, MS_BTN1, MS_BTN3,                  MS_BTN2, MS_BTN1
  //                   ╰───────────────────────────╯                ╰──────────────────╯
  ),

    [_LAYER4] = LAYOUT( //MEDIA
  // ╭─────────────────────────────────────────────╮                ╭─────────────────────────────────────────────╮
      KC_NO, RM_PREV, RM_TOGG, RM_NEXT, KC_NO,                      KC_NO, RM_NEXT, RM_TOGG, RM_PREV, KC_NO,
  // ├─────────────────────────────────────────────┤                ├─────────────────────────────────────────────┤
      KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT,                   KC_MNXT, KC_VOLU, KC_MUTE, KC_VOLD, KC_MPRV,
  // ├─────────────────────────────────────────────┤                ├─────────────────────────────────────────────┤
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                             KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
  // ╰─────────────────────────────────────────────┤                ├─────────────────────────────────────────────╯
                         KC_TRNS, KC_MPLY, KC_MSTP,                  KC_MSTP, KC_MPLY
  //                   ╰───────────────────────────╯                ╰──────────────────╯
  ),

    [_LAYER5] = LAYOUT( //FUNCTION
  // ╭─────────────────────────────────────────────╮                ╭─────────────────────────────────────────────╮
      KC_TRNS, QK_BOOT, DB_TOGG, EE_CLR, KC_TRNS,                    KC_PSCR, KC_F7, KC_F8, KC_F9, KC_F12,
  // ├─────────────────────────────────────────────┤                ├─────────────────────────────────────────────┤
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                             KC_SCRL, KC_F4, KC_F5, KC_F6, KC_F11,
  // ├─────────────────────────────────────────────┤                ├─────────────────────────────────────────────┤
      KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,                     KC_PAUS, KC_F1, KC_F2, KC_F3, KC_F10,
  // ╰─────────────────────────────────────────────┤                ├─────────────────────────────────────────────╯
                         KC_TRNS, KC_MPLY, KC_MSTP,                  KC_MSTP, KC_MPLY
  //                   ╰───────────────────────────╯                ╰──────────────────╯
  ),

    [_LAYER6] = LAYOUT( //GAMING
  // ╭─────────────────────────────────────────────╮                ╭─────────────────────────────────────────────╮
      KC_ESC, KC_Q, KC_W, KC_E, KC_R,                                KC_T, KC_Y, KC_U, KC_I, KC_O,
  // ├─────────────────────────────────────────────┤                ├─────────────────────────────────────────────┤
      KC_LSFT, KC_A, KC_S, KC_D, KC_F,                               KC_G, KC_H, KC_J, KC_K, KC_L,
  // ├─────────────────────────────────────────────┤                ├─────────────────────────────────────────────┤
      KC_LCTL, KC_Z, KC_X, KC_C, KC_V,                               KC_B, KC_N, KC_M, KC_P, TO(0),
  // ╰─────────────────────────────────────────────┤                ├─────────────────────────────────────────────╯
                         KC_1, KC_SPC, KC_TAB,                       KC_2, KC_MUTE
  //                   ╰───────────────────────────╯                ╰──────────────────╯
  ),

    [_LAYER7] = LAYOUT( //MMO
  // ╭─────────────────────────────────────────────╮                ╭─────────────────────────────────────────────╮
      KC_ESC, KC_1, KC_2, KC_3, KC_4,                                KC_T, KC_Y, KC_U, KC_I, KC_O,
  // ├─────────────────────────────────────────────┤                ├─────────────────────────────────────────────┤
      KC_LSFT, KC_Q, KC_W, KC_E, KC_F,                               KC_G, KC_H, KC_J, KC_K, KC_L,
  // ├─────────────────────────────────────────────┤                ├─────────────────────────────────────────────┤
      KC_LCTL, KC_5, KC_6, KC_7, KC_8,                               KC_B, KC_N, KC_M, KC_X, TO(0),
  // ╰─────────────────────────────────────────────┤                ├─────────────────────────────────────────────╯
                         KC_9, KC_SPC, KC_TAB,                       KC_MUTE, KC_0
  //                   ╰───────────────────────────╯                ╰──────────────────╯
  ),
};
// clang-format on
