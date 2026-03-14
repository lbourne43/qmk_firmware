// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later


#include QMK_KEYBOARD_H

#include "analog.h"

#define JOYSTICK_AXIS_COUNT 2



  int16_t mouseKey = 0;
  int16_t encoderButton = 0;


  bool analog_pressed;
  bool encoder_pressed;


//void matrix_init_user(void) { setPinInputHigh(GP28); }
//void matrix_init_user(void) { setPinInputHigh(GP17); }
void matrix_init_user(void) { }
/*bool dip_switch_update_user(uint8_t index, bool active) 
{ 
 switch (index) {
    case 0:   //ENC0_SW
      if(active) //ENC0 pressed
      { 
        register_code(KC_MS_BTN3);
      } 
      else //ENC0 released
      {
        unregister_code(KC_MS_BTN3);
      }
      break;
  }
  return true;
}
*/
void matrix_scan_user(void) {

      /*mouseKey = readPin(GP28);
      if (IS_LAYER_ON(1)) {
        if (mouseKey) {
          analog_pressed = false;
          unregister_code(KC_MS_BTN2);
        } else {
          if (!analog_pressed) {
            register_code(KC_MS_BTN2);
          }
         analog_pressed = true;
        }
      } else {
        if (mouseKey) {
          analog_pressed = false;
          unregister_code(KC_MS_BTN1);
        } else {
          if (!analog_pressed) {
            register_code(KC_MS_BTN1);
          }
         analog_pressed = true;
        }
      }*/
/*
      encoderButton = readPin(GP17);

        if (encoderButton) {
          encoder_pressed = false;
          unregister_code(KC_MS_BTN3);
        } else {
          if (!encoder_pressed) {
            register_code(KC_MS_BTN3);
         }
         encoder_pressed = true;
        }
      */
      
}


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
    UK_POUND = SAFE_RANGE
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case UK_POUND:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_LALT)  SS_DELAY(20) SS_DOWN(X_P0) SS_DELAY(20) SS_UP(X_P0)  SS_DELAY(20)  SS_DOWN(X_P1)  SS_DELAY(20) SS_UP(X_P1)  SS_DELAY(20) SS_DOWN(X_P6) SS_DELAY(20)  SS_UP(X_P6) SS_DELAY(20)  SS_DOWN(X_P3)  SS_DELAY(20) SS_UP(X_P3)  SS_DELAY(20) SS_UP(X_LALT));
      } else {
            break;
      }
      break;

  }
  return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT(
  QK_GESC,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,    KC_BSPC,
  KC_TAB,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN, KC_ENT,
  KC_LSFT,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMMA,KC_DOT,KC_SLASH,KC_RSFT,
  KC_TRNS,  KC_TRNS,KC_TRNS,  KC_MS_BTN1,KC_SPC, KC_LCTL,KC_RCTL,KC_SPC,KC_TRNS,  KC_TRNS,KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,KC_TRNS,  KC_TRNS,MO(1),  KC_LALT,KC_LGUI,MO(1),KC_TRNS,  KC_TRNS,KC_TRNS,  KC_TRNS),

  /* Keymap _FL: Function Layer
   */
[1] = LAYOUT(
  KC_GRAVE,  KC_TRNS,   KC_UP,   KC_TRNS,   KC_NUHS,   KC_LEFT_BRACKET,   KC_RIGHT_BRACKET,   KC_7,   KC_8,   KC_9,   KC_0,    KC_DELETE,
  KC_TAB,   KC_LEFT,   KC_DOWN,   KC_RIGHT,   KC_QUOTE,   KC_LCBR,   KC_RCBR,   KC_4,   KC_5,   KC_6,   KC_MINUS, KC_ENT,
  KC_LSFT,  KC_PGUP,   KC_PGDN,   KC_PSCR,   KC_NUBS,   KC_LPRN,   KC_RPRN,   KC_1,   KC_2,KC_3,KC_EQUAL,KC_RSFT,
  KC_TRNS,  KC_TRNS,KC_TRNS,  KC_MS_BTN2,KC_SPC, KC_LCTL,KC_RCTL,KC_SPC,KC_TRNS,  KC_TRNS,KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,KC_TRNS,  KC_TRNS,MO(2),  KC_LALT,KC_LGUI,MO(2),KC_TRNS,  KC_TRNS,KC_TRNS,  KC_TRNS),

[2] = LAYOUT(
  KC_GRAVE,  KC_TRNS,   KC_PGUP,   UK_POUND,   KC_NUHS,   KC_LEFT_BRACKET,   KC_RIGHT_BRACKET,   KC_F7,   KC_F8,   KC_F9,   KC_F10,    KC_DELETE,
  KC_TAB,   KC_HOME,   KC_PGDN,   KC_END,   KC_QUOTE,   KC_LCBR,   KC_RCBR,   KC_F4,   KC_F5,   KC_F6,   KC_F11, KC_ENT,
  KC_LSFT,  KC_PGUP,   KC_PGDN,   KC_PSCR,   KC_NUBS,   KC_LPRN,   KC_RPRN,   KC_F1,   KC_F2,KC_F3,KC_F12,KC_RSFT,
  KC_TRNS,  KC_TRNS,KC_TRNS,  KC_MS_BTN3,KC_SPC, KC_LCTL,KC_RCTL,KC_SPC,KC_TRNS,  KC_TRNS,KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS,KC_TRNS,  KC_TRNS,KC_TRNS,  KC_LALT,KC_LGUI,KC_TRNS,KC_TRNS,  KC_TRNS,KC_TRNS,  KC_TRNS),

};
