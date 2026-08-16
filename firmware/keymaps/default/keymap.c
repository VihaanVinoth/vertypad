#include QMK_KEYBOARD_H

// 1. Define custom Mac macro keycode identifiers
enum custom_keycodes {
    MC_COPY = SAFE_RANGE, // Mac Copy (Cmd+C)
    MC_PASTE,             // Mac Paste (Cmd+V)
    MC_SPOTLIGHT,         // Open Spotlight Search (Cmd+Space)
    MC_LOCK               // Lock Mac Screen (Cmd+Ctrl+Q)
};

// 2. Assign macros to your specific Vertypad layout matrix
// Row 0: SW1 (Copy),  SW3 (Paste), SW5 (Spotlight), SW8 (Encoder Click - Mute)
// Row 1: SW2 (Num 4), SW4 (Num 5), SW6 (Num 6),     SW7 (Lock Mac)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    = LAYOUT(
        MC_COPY,  MC_PASTE, MC_SPOTLIGHT, KC_MUTE,  
        KC_4,     KC_5,     KC_6,         MC_LOCK     
    )
};

// 3. Define the exact macOS key sequence logic
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case MC_COPY:
                // Holds down Left GUI (Command key on Mac), taps 'c', releases Left GUI
                SEND_STRING(SS_DOWN(X_LGUI) "c" SS_UP(X_LGUI));
                return false; 

            case MC_PASTE:
                // Holds down Left GUI, taps 'v', releases Left GUI
                SEND_STRING(SS_DOWN(X_LGUI) "v" SS_UP(X_LGUI));
                return false; 

            case MC_SPOTLIGHT:
                // Holds down Left GUI, taps Spacebar, releases Left GUI
                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_SPACE) SS_UP(X_LGUI));
                return false;

            case MC_LOCK:
                // Holds Left GUI + Left Control, taps 'q', releases both modifiers
                SEND_STRING(SS_DOWN(X_LGUI) SS_DOWN(X_LCTL) "q" SS_UP(X_LCTL) SS_UP(X_LGUI));
                return false;
        }
    }
    return true; // Pass through regular keycodes (like numbers 4, 5, 6)
}

#if defined(ENCODER_ENABLE)
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { 
        if (clockwise) {
            tap_code(KC_VOLU); // Turns Mac Volume Up
        } else {
            tap_code(KC_VOLD); // Turns Mac Volume Down
        }
    }
    return true;
}
#endif

#if defined(OLED_ENABLE)
bool oled_init_user(uint8_t idx) { return true; }

bool oled_task_user(void) {
    oled_write_P(PSTR("Vertypad macOS\n"), false);
    oled_write_P(PSTR("Mac Macros Active\n"), false);
    return false;
}
#endif
