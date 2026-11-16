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
 * Dylan's Charybdis Nano keymap, version 2 (2026-11-15).
 *
 * Physical layout (LAYOUT):
 *   K00 K01 K02 K03 K04        K05 K06 K07 K08 K09
 *   K10 K11 K12 K13 K14        K15 K16 K17 K18 K19
 *   K20 K21 K22 K23 K24        K25 K26 K27 K28 K29
 *           K32 K33 K34        K35 K36
 *
 * USB is in the LEFT half. The trackball is on the RIGHT half.
 *
 * Combos and tap dances are owned by the Argos module and are set at
 * argos.bastardkb.com, not in this file. The four combos from the 2023 keymap:
 *   W + F -> Ctrl+C     R + S -> Ctrl+V
 * (the two layer combos are gone: MMO was dropped, gaming is now a double tap).
 */

#include QMK_KEYBOARD_H
#include "bk_pointing_device.h"

/*
 * Layer order matters: a higher layer hides a lower one. The three "typing"
 * layers (Colemak, QWERTY, gaming) must sit below the held layers so that
 * symbols, numbers and navigation work on top of any of them.
 */
enum layers {
    L_BASE = 0, // Colemak-DH
    L_QWERTY,   // QWERTY fallback, toggled from the function layer
    L_GAME,     // left-hand gaming, toggled by double-tapping the "/" key
    L_SYM,      // symbols        (hold Tab)
    L_NUM,      // numbers        (hold Enter)
    L_NAV,      // arrows, mouse buttons on thumbs (hold Q or ;)
    L_MOUSE,    // one-hand mouse (turns on when the ball moves, or hold B)
    L_FUNC,     // F-keys, media, RGB, system (hold Esc or J)
};

enum custom_keycodes {
    SL_GAME = SAFE_RANGE, // tap: "/"   double tap: toggle the gaming layer
};

#define AI_TALK KC_F13 // the "talk to AI" key; the PC binds F13 to the app

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASE] = LAYOUT(
      LT(L_NAV,KC_Q), KC_W,         KC_F,         KC_P,         LT(L_MOUSE,KC_B),      LT(L_FUNC,KC_J), KC_L,         KC_U,            KC_Y,           LT(L_NAV,KC_SCLN),
      KC_A,           KC_R,         KC_S,         KC_T,         KC_G,                  KC_M,            KC_N,         KC_E,            KC_I,           KC_O,
      LGUI_T(KC_Z),   LALT_T(KC_X), LCTL_T(KC_C), LSFT_T(KC_D), KC_V,                  KC_K,            RSFT_T(KC_H), RCTL_T(KC_COMM), RALT_T(KC_DOT), SL_GAME,
                              LT(L_FUNC,KC_ESC), KC_SPC, LT(L_SYM,KC_TAB),             LT(L_NUM,KC_ENT), KC_BSPC
  ),

  // Same mods, thumbs and layer keys as the base layer; only the letters change.
  [L_QWERTY] = LAYOUT(
      LT(L_NAV,KC_Q), KC_W,         KC_E,         KC_R,         LT(L_MOUSE,KC_T),      LT(L_FUNC,KC_Y), KC_U,         KC_I,            KC_O,           LT(L_NAV,KC_P),
      KC_A,           KC_S,         KC_D,         KC_F,         KC_G,                  KC_H,            KC_J,         KC_K,            KC_L,           KC_SCLN,
      LGUI_T(KC_Z),   LALT_T(KC_X), LCTL_T(KC_C), LSFT_T(KC_V), KC_B,                  KC_N,            RSFT_T(KC_M), RCTL_T(KC_COMM), RALT_T(KC_DOT), _______,
                                       _______, _______, _______,                      _______, _______
  ),

  // Left hand only. A W D on the home row, S below W. Q E R F keep their
  // QWERTY positions relative to A W D. Mods on the pinky.
  // The right half falls through to the typing layer below.
  [L_GAME] = LAYOUT(
      KC_ESC,  KC_Q,    KC_X,    KC_E,    KC_R,                          _______, _______, _______, _______, _______,
      KC_LSFT, KC_A,    KC_W,    KC_D,    KC_F,                          _______, _______, _______, _______, _______,
      KC_LCTL, KC_Z,    KC_S,    KC_C,    KC_V,                          _______, _______, _______, _______, _______,
                                 KC_1,    KC_SPC,  KC_TAB,               _______, _______
  ),

  [L_SYM] = LAYOUT(
      LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5),        KC_GRV,        LSFT(KC_LBRC), LSFT(KC_RBRC), KC_BSLS,       KC_SCLN,
      LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), KC_COMM,    KC_DOT,            KC_QUOT,       LSFT(KC_9),    LSFT(KC_0),    LSFT(KC_MINS), KC_EQL,
      KC_LGUI,    KC_LALT,    KC_LCTL,    KC_LSFT,    KC_NO,             LSFT(KC_QUOT), KC_LBRC,       KC_RBRC,       KC_MINS,       KC_SLSH,
                                    KC_ESC, KC_SPC, _______,             KC_ENT, KC_BSPC
  ),

  [L_NUM] = LAYOUT(
      KC_PSLS, KC_7, KC_8, KC_9, KC_PAST,                                KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,
      KC_PMNS, KC_4, KC_5, KC_6, KC_PPLS,                                KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,
      KC_EQL,  KC_1, KC_2, KC_3, KC_DOT,                                 KC_NO, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
                           LSFT(KC_MINS), KC_0, KC_ENT,                  _______, KC_BSPC
  ),

  [L_NAV] = LAYOUT(
      KC_NO,   KC_PGDN, KC_UP,   KC_PGUP, MS_ACL2,                       MS_ACL2, KC_PGUP, KC_UP,   KC_PGDN, KC_NO,
      _______, KC_LEFT, KC_DOWN, KC_RGHT, MS_ACL0,                       MS_ACL0, KC_LEFT, KC_DOWN, KC_RGHT, _______,
      KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,                         MS_BTN3, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
                              MS_BTN2, MS_BTN1, MS_BTN3,                 MS_BTN2, MS_BTN1
  ),

  // One-hand mouse, all on the right hand. Thumb rolls the ball.
  //   M (index, inner) hold = scroll by rolling
  //   N = left click, E = right click, I = middle click
  //   O (pinky) hold = precision (slow pointer)
  // Every other key is transparent, so typing any other key leaves the layer.
  [L_MOUSE] = LAYOUT(
      _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______,                       DRGSCRL, MS_BTN1, MS_BTN2, MS_BTN3, SNIPING,
      _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______,
                                 _______, _______, _______,              _______, _______
  ),

  // Function keys on the right. Media, RGB and system keys on the left.
  [L_FUNC] = LAYOUT(
      QK_BOOT, EE_CLR,  RM_PREV, RM_TOGG, RM_NEXT,                       KC_PSCR, KC_F7, KC_F8, KC_F9, KC_F12,
      KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT,                       KC_SCRL, KC_F4, KC_F5, KC_F6, KC_F11,
      KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, TG(L_QWERTY),                  KC_PAUS, KC_F1, KC_F2, KC_F3, KC_F10,
                                 _______, KC_MPLY, KC_MSTP,              AI_TALK, KC_MPLY
  ),
};
// clang-format on

/*
 * SL_GAME: a small double-tap key written here because tap dances belong to
 * Argos. One tap types "/" (sent when the tapping term runs out or when the
 * next key is pressed). Two taps inside the tapping term toggle the gaming layer.
 */
static bool     sl_pending = false;
static uint16_t sl_timer   = 0;

static void sl_flush(void) {
    if (sl_pending) {
        sl_pending = false;
        tap_code(KC_SLSH);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == SL_GAME) {
        if (record->event.pressed) {
            if (sl_pending && timer_elapsed(sl_timer) < TAPPING_TERM) {
                sl_pending = false;
                layer_invert(L_GAME);
            } else {
                sl_flush();
                sl_pending = true;
                sl_timer   = timer_read();
            }
        }
        return false;
    }
    if (record->event.pressed) {
        sl_flush(); // keep "/" in order when another key follows it quickly
    }
    return true;
}

void housekeeping_task_user(void) {
    if (sl_pending && timer_elapsed(sl_timer) >= TAPPING_TERM) {
        sl_flush();
    }

    // Turn the automatic mouse layer on once after boot. Argos can switch it
    // off for the current session; it comes back on at the next power-up.
    static bool auto_mouse_done = false;
    if (!auto_mouse_done && timer_read32() > 1500) {
        auto_mouse_done = true;
        if (!bkpd_get_auto_mouse_layer_enabled()) {
            bkpd_set_auto_mouse_layer_enabled(true);
        }
    }
}
