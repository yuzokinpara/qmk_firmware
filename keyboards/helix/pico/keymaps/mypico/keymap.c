#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _NUMLK,
    _FUNCT
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  NUMLK,
  FUNCT,
  BACKLIT,
  EISU,
  KANA,
  TGL_JP,
  CTALDL,
  SHAIN,
  CTRL_Y,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Tap Dance Declarations
enum {
	_TD_SS_Z = 0,
	_TD_PP_MINS,
	_TD_OO_MINS,
	_TD_LL_LBRC,
	_TD_KK_EQL,
	_TD_TB_ESC,
	_TD_SCL_RBRC
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define SFT_SPC MT(MOD_LSFT, KC_SPACE)
#define CTL_ENT MT(MOD_LCTL, KC_ENT)

#define LT_RAIS LT(_RAISE,KC_BTN2)
#define LT_LOWR LT(_LOWER,KC_BTN1)
#define SPC_LOW LT(_LOWER,KC_SPACE)
#define MO_RAIS MO(_RAISE)
#define MO_LOWR MO(_LOWER)
#define MO_FNC MO(_FUNCT)
#define MO_LOWR MO(_LOWER)
#define MO_ADJ  MO(_FUNCT)
#define TO_RAIS TO(_RAISE)
#define TO_LOWR TO(_LOWER)
#define TO_DF   TO(_QWERTY)
#define OSL_FNC OSL(_FUNCT)
#define MY_KANA KC_LANG1
#define MY_EISU KC_LANG2
#define MY_ZKHK KC_ZKHK
#define CTALDEL LALT(LCTL(KC_DEL))

#define TD_SS_Z TD(_TD_SS_Z)
#define TD_P_MN TD(_TD_PP_MINS)
#define TD_O_MN TD(_TD_OO_MINS)
#define TD_L_BR TD(_TD_LL_LBRC)
#define TD_K_EQ TD(_TD_KK_EQL)
#define TD_TBES TD(_TD_TB_ESC)
#define TD_SCBR TD(_TD_SCL_RBRC)

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT( \
      TD_TBES, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    TD_O_MN, TD_P_MN, KC_BSPC, \
      KC_LCTL, KC_A,    TD_SS_Z, KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    TD_L_BR, TD_SCBR, KC_ENT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_SLSH, \
      KC_ESC,  NUMLK,   FUNCT,   KC_LGUI, FUNCT,   SPC_LOW, KC_LALT, RAISE,   TGL_JP,  KC_MINS, KC_QUOT, KC_LEFT, KC_DOWN, KC_RGHT \
      ),

  [_LOWER] = LAYOUT( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
      XXXXXXX, KC_DOWN, KC_UP,   KC_DEL,  KC_PGDN, XXXXXXX,                   XXXXXXX, XXXXXXX, KC_EQL,  KC_LBRC, KC_RBRC, XXXXXXX,\
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_END \
      ),

  [_RAISE] = LAYOUT( \
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, \
      XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F11,  XXXXXXX, KC_PLUS, KC_LBRC, KC_RBRC, XXXXXXX, \
      XXXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                    KC_F12,  XXXXXXX, XXXXXXX, CTRL_Y,  XXXXXXX, KC_BSLS, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX\
      ),

   [_NUMLK] =  LAYOUT( \
      XXXXXXX, SHAIN,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_7,    KC_8,    KC_9,    KC_SLSH, XXXXXXX, XXXXXXX, \
      XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_4,    KC_5,    KC_6,    KC_ASTR, XXXXXXX, XXXXXXX, \
      XXXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                    KC_1,    KC_2,    KC_3,    KC_MINS, XXXXXXX, XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2, KC_0,    KC_0,    KC_DOT,  KC_PLUS, XXXXXXX, XXXXXXX \
      ),
   [_FUNCT] =  LAYOUT( \
    G(KC_TAB), SHAIN,   KC_DOWN, KC_UP,   C(KC_Y), XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL, \
      XXXXXXX, AU_TOG,  C(KC_S), KC_DEL,  KC_PGDN, XXXXXXX,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP,                   XXXXXXX, G(KC_M), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, RESET,   XXXXXXX, CTALDL,  XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
      )
};



#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
float tone_goodbye[][2]    = SONG(MUSIC_OFF_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting FUNCT layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE + 1);
          #endif
        }
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _FUNCT);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _FUNCT);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE);
          #endif
        }
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _FUNCT);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_RAISE);
        TOG_STATUS = false;
        update_tri_layer_RGB(_LOWER, _RAISE, _FUNCT);
      }
      return false;
      break;
    case FUNCT:
        if (record->event.pressed) {
          layer_on(_FUNCT);
        } else {
          layer_off(_FUNCT);
        }
        return false;
        break;
    case NUMLK:
        if (record->event.pressed) {
          layer_on(_NUMLK);
        } else {
          layer_off(_NUMLK);
        }
        return false;
        break;
       //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case EISU:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
   case TGL_JP:
      if (record->event.pressed) {
          SEND_STRING(SS_LALT("`"));
      }
      return false;
      break;
    case CTALDL:
      if (record->event.pressed) {
        register_code(KC_LCTRL);
        register_code(KC_LALT);
        register_code(KC_DEL);
      }else{
        unregister_code(KC_LCTRL);
        unregister_code(KC_LALT);
        unregister_code(KC_DEL);
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_goodbye);
        #endif
      }
      return false;
      break;
    case SHAIN:
      if (record->event.pressed) {
          SEND_STRING("1113163");
      }else{
      }
      return false;
      break;
   }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(50); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_FUNCT (1<<_FUNCT)
#define L_FUNCT (L_FUNCT|L_RAISE|L_LOWER)

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}



void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }else{
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\nLayer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Default"));
           break;
        case L_RAISE:
           matrix_write_P(matrix, PSTR("Raise"));
           break;
        case L_LOWER:
           matrix_write_P(matrix, PSTR("Lower"));
           break;
        case L_FUNCT:
        case L_FUNCT_TRI:
           matrix_write_P(matrix, PSTR("Function"));
           break;
        default:
           matrix_write(matrix, buf);
    }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [_TD_SS_Z] = ACTION_TAP_DANCE_DOUBLE(KC_S, KC_Z),
    [_TD_PP_MINS] = ACTION_TAP_DANCE_DOUBLE(KC_P, KC_MINS),
    [_TD_OO_MINS] = ACTION_TAP_DANCE_DOUBLE(KC_O, KC_MINS),
    [_TD_LL_LBRC] = ACTION_TAP_DANCE_DOUBLE(KC_L, KC_LBRC),
    [_TD_KK_EQL] = ACTION_TAP_DANCE_DOUBLE(KC_K, KC_EQL),
    [_TD_TB_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_ESC),
    [_TD_SCL_RBRC] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_RBRC)
};


