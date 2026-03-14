// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later


#include QMK_KEYBOARD_H

#include "analog.h"

#define JOYSTICK_AXIS_COUNT 2
#define _CENTER 512
#define _DEAD 50

#define _DOWN_TRESHOLD (_CENTER+_DEAD)
#define _UP_TRESHOLD (_CENTER-_DEAD)

  int16_t xPos = 0;
  int16_t yPos = 0;
  int16_t analogButton = 0;
  int16_t encoderButton = 0;

  bool yDownHeld = false;
  bool yUpHeld = false;
  bool xLeftHeld = false;
  bool xRightHeld = false;
  bool analog_pressed;
  bool encoder_pressed;

  void matrix_init_user(void) { setPinInputHigh(GP28); }

  void matrix_scan_user(void) {
      yPos = analogReadPin(GP26);
      if (!yDownHeld && yPos >= _DOWN_TRESHOLD) {
        register_code(KC_MS_WH_DOWN);
        yDownHeld = true;
      } else if (yDownHeld && yPos < _DOWN_TRESHOLD) {
        unregister_code(KC_MS_WH_DOWN);
        yDownHeld = false;
      } else if (!yUpHeld && yPos <= _UP_TRESHOLD) {
        register_code(KC_MS_WH_UP);
        yUpHeld = true;
      } else if (yUpHeld && yPos > _UP_TRESHOLD) {
        unregister_code(KC_MS_WH_UP);
        yUpHeld = false;
      }

      xPos = analogReadPin(GP27);
      if (!xLeftHeld && xPos >= _DOWN_TRESHOLD) {
        register_code(KC_LEFT);
        xLeftHeld = true;
      } else if (xLeftHeld && xPos < _DOWN_TRESHOLD) {
        xLeftHeld = false;
        unregister_code(KC_LEFT);
      } else if (!xRightHeld && xPos <= _UP_TRESHOLD) {
        xRightHeld = true;
        register_code(KC_RIGHT);
      } else if (xRightHeld && xPos > _UP_TRESHOLD) {
        xRightHeld = false;
        unregister_code(KC_RIGHT);
      }

      analogButton = readPin(GP28);
      if (analogButton) {
        analog_pressed = false;
        unregister_code(KC_MUTE);
      } else {
        if (!analog_pressed) {
          register_code(KC_MUTE);
        }
        analog_pressed = true;
      }
      encoderButton = readPin(GP13);
      if (encoderButton) {
        encoder_pressed = false;
        unregister_code(KC_MS_BTN3);
      } else {
        if (!encoder_pressed) {
          register_code(KC_MS_BTN3);
        }
        encoder_pressed = true;
      }
      
  }

  //joystick config
  joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_IN(GP26, 0, 512, 1023),
    JOYSTICK_AXIS_IN(GP27, 0, 512, 1023)
  };



bool encoder_update_user(uint8_t index, bool clockwise) {
  if (IS_LAYER_ON(1)) {
    if (clockwise) {
      tap_code(KC_VOLD);
    } else {
      tap_code(KC_VOLU);
    }
  } else {
    if ((get_mods() & MOD_BIT(KC_LCTL)) || (get_mods() &  MOD_BIT(KC_RCTL))) {
      if (clockwise) {
        tap_code(KC_MS_WH_DOWN);
      } else {
        tap_code(KC_MS_WH_UP);
      }
    } else {
      if (clockwise) {
        tap_code(KC_MS_WH_UP);
      } else {
        tap_code(KC_MS_WH_DOWN);
      }
    }
  }
  return false;
}


enum custom_keycodes {
    LB_COPY = SAFE_RANGE,
    LB_CUT,
    LB_PASTE,
    LB_SCOPY,
    LB_SCUT,
    LB_SPASTE,
    LB_CLEAR,
    LB_UNDO,
    LB_BREAK,
    LB_CDOX,
    LB_NAGIOS,
    LB_TERM,
    LB_LOCK
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LB_COPY:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("c"));
      } else {
            break;
      }
      break;
    case LB_SCOPY:
      if (record->event.pressed) {
        SEND_STRING(SS_LSFT(SS_LCTL("c")));
      } else {
            break;
      }
      break;
    case LB_CUT:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("x"));
      } else {
            break;
      }
      break;
    case LB_SCUT:
      if (record->event.pressed) {
        SEND_STRING(SS_LSFT(SS_LCTL("x")));
      } else {
            break;
      }
      break;
    case LB_PASTE:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("v"));
      } else {
            break;
      }
      break;
    case LB_SPASTE:
      if (record->event.pressed) {
        SEND_STRING(SS_LSFT(SS_LCTL("v")));
      } else {
            break;
      }
      break;

    case LB_CLEAR:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("a") SS_LCTL("k"));
      } else {
            break;
      }
      break;
    case LB_UNDO:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("z"));
      } else {
            break;
      }
      break;
    case LB_BREAK:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("d"));
      } else {
            break;
      }
      break;

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
    case LB_TERM:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("r") SS_DELAY(100) "ubuntu" SS_TAP(X_ENTER));
      } else {
            break;
      }
      break;
    case LB_LOCK:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("l"));
      } else {
            break;
      }
      break;
  }
  return true;
};




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
[0] = LAYOUT(
  KC_TRNS,  LB_CUT,   LB_COPY,   LB_PASTE,
  MO(1),   LB_CLEAR,   LB_UNDO,   LB_BREAK,
  LB_LOCK,  LB_CDOX,   LB_NAGIOS,   LB_TERM,
  KC_TRNS,KC_TRNS,  KC_MS_BTN1,KC_MS_BTN2),

  // Keymap _FL: Function Layer

[1] = LAYOUT(
  KC_TRNS,  LB_SCUT,   LB_SCOPY,   LB_SPASTE,
  MO(1),   LB_CLEAR,   LB_UNDO,   LB_BREAK,
  LB_LOCK,  LB_CDOX,   LB_NAGIOS,   LB_TERM,
  KC_TRNS,KC_TRNS,  KC_MS_BTN1,KC_MS_BTN2),
*/
[0] = LAYOUT(
  KC_TRNS,  LB_CDOX,   LB_CLEAR,   LB_CUT,
  MO(1),   LB_NAGIOS,   LB_UNDO,   LB_COPY,
  LB_LOCK,  LB_TERM,   LB_BREAK,   LB_PASTE,
  KC_TRNS,KC_TRNS,  KC_MS_BTN1,KC_MS_BTN2),

  // Keymap _FL: Function Layer

[1] = LAYOUT(
  KC_TRNS,  LB_CDOX,   LB_CLEAR,   LB_SCUT,
  MO(1),   LB_NAGIOS,   LB_UNDO,   LB_SCOPY,
  LB_LOCK,  LB_TERM,   LB_BREAK,   LB_SPASTE,
  KC_TRNS,KC_TRNS,  KC_MS_BTN1,KC_MS_BTN2),
};