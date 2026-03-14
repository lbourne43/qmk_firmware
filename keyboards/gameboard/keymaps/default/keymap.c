// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later


#include QMK_KEYBOARD_H

#include "analog.h"
#define JOYSTICK_AXIS_COUNT 2
#define _CENTER 512
#define _DEAD 100

#define _DOWN_TRESHOLD (_CENTER+_DEAD)
#define _UP_TRESHOLD (_CENTER-_DEAD)


  int16_t xPos = 0;
  int16_t yPos = 0;
  int16_t analogButton = 0;

  bool yDownHeld = false;
  bool yUpHeld = false;
  bool xLeftHeld = false;
  bool xRightHeld = false;
  bool analog_pressed;


  void matrix_init_user(void) { setPinInputHigh(GP28); }

  void matrix_scan_user(void) {
      yPos = analogReadPin(GP26);
      if (!yDownHeld && yPos >= _DOWN_TRESHOLD) {
        register_code(KC_DOWN);
        yDownHeld = true;
      } else if (yDownHeld && yPos < _DOWN_TRESHOLD) {
        yDownHeld = false;
        unregister_code(KC_DOWN);
      } else if (!yUpHeld && yPos <= _UP_TRESHOLD) {
        yUpHeld = true;
        register_code(KC_UP);
      } else if (yUpHeld && yPos > _UP_TRESHOLD) {
        yUpHeld = false;
        unregister_code(KC_UP);
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
        unregister_code(KC_L);
      } else {
        if (!analog_pressed) {
          register_code(KC_L);
        }
        analog_pressed = true;
      }
  }

  //joystick config
  joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_IN(GP26, 0, 512, 1023),
    JOYSTICK_AXIS_IN(GP27, 0, 512, 1023)
  };

/*
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
      yPos = mouse_report.y;
      mouse_report.y = 0;
      unregister_code(KC_UP);
      unregister_code(KC_DOWN);
      unregister_code(KC_LEFT);
      unregister_code(KC_RIGHT);
      if (!yUpHeld && yPos >= -30) {
        register_code(KC_UP);
        yUpHeld = true;
      } else if (yUpHeld && yPos < -30) {
        yUpHeld = false;
        unregister_code(KC_UP);
      } else if (!yDownHeld && yPos <= 30) {
        yDownHeld = true;
        register_code(KC_DOWN);
      } else if (yUpHeld && yPos > 30) {
        yDownHeld = false;
        unregister_code(KC_DOWN);
      }

      xPos = mouse_report.x;
      mouse_report.x = 0;
      if (!xLeftHeld && xPos >= -30) {
        register_code(KC_LEFT);
        xLeftHeld = true;
      } else if (xLeftHeld && xPos < -30) {
        xLeftHeld = false;
        unregister_code(KC_LEFT);
      } else if (!xRightHeld && xPos <= 30) {
        xRightHeld = true;
        register_code(KC_RIGHT);
      } else if (xRightHeld && xPos > 30) {
        xRightHeld = false;
        unregister_code(KC_RIGHT);
      }
  return mouse_report;
}*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT(
  QK_GESC,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,
  KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,
  KC_M,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,
  KC_LSFT,KC_B,   KC_Z,   KC_X,   KC_C,   KC_V,KC_LGUI,
  KC_LCTL,KC_N,MO(1),KC_SLASH,KC_SPC, KC_SPC,KC_ENT),

  /* Keymap _FL: Function Layer
   */
[1] = LAYOUT(
  KC_GRV, KC_6,  KC_7,  KC_8,  KC_9,  KC_0,
  _______,KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,
  _______,KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,
  _______,KC_N,   KC_M,   KC_COMMA,KC_DOT,KC_SLASH,KC_LGUI,
  KC_ENT,_______,_______,KC_LALT,KC_BSPC,KC_BSPC,KC_ENT),

};
