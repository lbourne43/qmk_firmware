// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later


#include QMK_KEYBOARD_H



enum custom_keycodes {
    LB_CDOX = SAFE_RANGE,
    LB_NAGIOS,
    LB_TERM,
    LB_YOUTUBE,
    LB_GOOGLE,
    LB_LINODE,
    LB_HUBSPOT,
    LB_CAL
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LB_CDOX:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("r") SS_DELAY(100) "https://cognidox.cognidox.com" SS_TAP(X_ENTER));
      } else {
            break;
      }
      break;
    case LB_NAGIOS:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("r") SS_DELAY(100) "https://admin.cognidox.com/nagios/" SS_TAP(X_ENTER));
      } else {
            break;
      }
      break;
    case LB_YOUTUBE:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("r") SS_DELAY(100) "https://www.youtube.com/" SS_TAP(X_ENTER));
      } else {
            break;
      }
      break;
    case LB_GOOGLE:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("r") SS_DELAY(100) "https://www.google.com/" SS_TAP(X_ENTER));
      } else {
            break;
      }
      break;
    case LB_CAL:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("r") SS_DELAY(100) "https://calendar.google.com/" SS_TAP(X_ENTER));
      } else {
            break;
      }
      break;
    case LB_LINODE:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("r") SS_DELAY(100) "https://cloud.linode.com/" SS_TAP(X_ENTER));
      } else {
            break;
      }
      break;
    case LB_HUBSPOT:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("r") SS_DELAY(100) "https://app.hubspot.com/" SS_TAP(X_ENTER));
      } else {
            break;
      }
      break;
    case LB_TERM:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("r") SS_DELAY(100) "ubuntu" SS_TAP(X_ENTER));
      } else {
            break;
      }
      break;
  }
  return true;
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT(
  QK_GESC,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   
  KC_TAB,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,  
  KC_LSFT,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   
  KC_TRNS,  KC_TRNS,KC_TRNS,  KC_TRNS,KC_SPC, KC_LCTL,
  KC_TRNS,  KC_TRNS,KC_TRNS,  KC_TRNS,MO(1),  KC_MS_BTN1,

  KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,    KC_BSPC,
  KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN, KC_ENT,
  KC_N,   KC_M,   KC_COMMA,KC_DOT,KC_SLASH,KC_RSFT,
  KC_RCTL,KC_SPC,KC_TRNS,  KC_TRNS,KC_TRNS,  KC_TRNS,
  KC_LGUI,MO(1),KC_TRNS,  KC_TRNS,KC_TRNS,  KC_TRNS),

  /* Keymap _FL: Function Layer
   */
[1] = LAYOUT(
  KC_GRAVE,  KC_TRNS,   KC_UP,   KC_TRNS,   KC_NUHS,   KC_LEFT_BRACKET,   
 KC_TAB,   KC_LEFT,   KC_DOWN,   KC_RIGHT,   KC_QUOTE,   KC_LCBR, 
KC_LSFT,  KC_PGUP,   KC_PGDN,   KC_PSCR,   KC_NUBS,   KC_LPRN,
  KC_TRNS,  KC_TRNS,KC_TRNS,  KC_TRNS,KC_SPC, KC_RCTL,
  KC_TRNS,  KC_TRNS,KC_TRNS,  KC_TRNS,MO(2),  KC_MS_BTN2,

  KC_RIGHT_BRACKET,   KC_7,   KC_8,   KC_9,   KC_0,    KC_DELETE,
  KC_RCBR,   KC_4,   KC_5,   KC_6,   KC_MINUS, KC_ENT,
     KC_RPRN,   KC_1,   KC_2,KC_3,KC_EQUAL,KC_RSFT,
KC_RCTL,KC_SPC,KC_TRNS,  KC_TRNS,KC_TRNS,  KC_TRNS,
KC_LGUI,MO(2),KC_TRNS,  KC_TRNS,KC_TRNS,  KC_TRNS),

[2] = LAYOUT(
  KC_GRAVE,  KC_TRNS,   KC_PGUP,   LB_LINODE,   LB_CAL,   LB_TERM,
  KC_TAB,   KC_HOME,   KC_PGDN,   KC_END,   KC_QUOTE,   LB_GOOGLE,   
  KC_LSFT,  KC_PGUP,   KC_PGDN,   LB_CDOX,   KC_NUBS,   KC_LPRN,   
    KC_TRNS,  KC_TRNS,KC_TRNS,  KC_MS_BTN3,KC_SPC, KC_RCTL,
  KC_TRNS,  KC_TRNS,KC_TRNS,  KC_TRNS,KC_TRNS,  KC_MS_BTN3,
 
  LB_YOUTUBE,   KC_F7,   KC_F8,   KC_F9,   KC_F10,    KC_DELETE,
LB_HUBSPOT,   KC_F4,   KC_F5,   KC_F6,   KC_F11, KC_ENT,
LB_NAGIOS,   KC_F1,   KC_F2,KC_F3,KC_F12,KC_RSFT,
KC_RCTL,KC_SPC,KC_TRNS,  KC_TRNS,KC_TRNS,  KC_TRNS,
KC_LGUI,KC_TRNS,KC_TRNS,  KC_TRNS,KC_TRNS,  KC_TRNS),

};