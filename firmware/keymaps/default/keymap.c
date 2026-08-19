// ©2026 VERTYPAD BY VIHAAN VINOTH. ALL RIGHTS RESERVED.

#include QMK_KEYBOARD_H

// UI menu screens
enum ui_screens {
    SCREEN_HOME = 0,
    SCREEN_OS_SELECT,
    SCREEN_STATUS,
    NUM_SCREENS
};

uint8_t current_screen = SCREEN_HOME;
bool is_macos_mode = true;

enum custom_keycodes
{
    COPY = SAFE_RANGE, 
    PASTE,             
    SPOTLIGHT,         // Spotlight (Mac) / Search (Win)
    LOCK,              // Lock Mac / Lock Windows (Win+L)
    UI_SELECT          // Changes settings inside the current menu (e.g., toggle OS)
};

// Row 0: SW1 (Copy),  SW3 (Paste), SW5 (Spotlight), SW8 (R. Encoder - Mute)
// Row 1: SW2 (Num 4), SW4 (SW_SELECT), SW6 (Num 6),    SW7 (Lock)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        COPY,    PASTE,     SPOTLIGHT, KC_MUTE,
        KC_4,    UI_SELECT, KC_6,      LOCK
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if (record->event.pressed)
    {
        switch (keycode)
        {
        case UI_SELECT:
            // Toggle OS mode when pressed on the OS selection screen or globally
            is_macos_mode = !is_macos_mode;
            return false;

        case COPY:
            if (is_macos_mode) {
                SEND_STRING(SS_DOWN(X_LGUI) "c" SS_UP(X_LGUI));
            } else {
                SEND_STRING(SS_DOWN(X_LCTL) "c" SS_UP(X_LCTL));
            }
            return false;

        case PASTE:
            if (is_macos_mode) {
                SEND_STRING(SS_DOWN(X_LGUI) "v" SS_UP(X_LGUI));
            } else {
                SEND_STRING(SS_DOWN(X_LCTL) "v" SS_UP(X_LCTL));
            }
            return false;

        case SPOTLIGHT:
            if (is_macos_mode) {
                SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_SPACE) SS_UP(X_LGUI));
            } else {
                SEND_STRING(SS_DOWN(X_LGUI) "s" SS_UP(X_LGUI)); // Win+S for Windows Search
            }
            return false;

        case LOCK:
            if (is_macos_mode) {
                SEND_STRING(SS_DOWN(X_LGUI) SS_DOWN(X_LCTL) "q" SS_UP(X_LCTL) SS_UP(X_LGUI));
            } else {
                SEND_STRING(SS_DOWN(X_LGUI) "l" SS_UP(X_LGUI)); // Win+L to lock Windows
            }
            return false;
        }
    }
    return true;
}

#if defined(ENCODER_ENABLE)
bool encoder_update_user(uint8_t index, bool clockwise)
{
    if (index == 0)
    {
        // Turning the encoder cycles through the OLED UI screens
        if (clockwise)
        {
            current_screen = (current_screen + 1) % NUM_SCREENS;
        }
        else
        {
            current_screen = (current_screen - 1 + NUM_SCREENS) % NUM_SCREENS;
        }
    }
    return true;
}
#endif

#if defined(OLED_ENABLE)
oled_rotation_t oled_init_user(oled_rotation_t rotation)
{
    return rotation;
}

bool oled_task_user(void)
{
    // Render dynamic UI screens based on current_screen variable
    oled_write_P(PSTR("== VERTYPAD ==\n"), false);
    
    switch (current_screen) {
        case SCREEN_HOME:
            oled_write_P(PSTR("Mode: Dashboard\n"), false);
            if (is_macos_mode) {
                oled_write_P(PSTR("OS: [macOS] Win\n"), false);
            } else {
                oled_write_P(PSTR("OS: Mac [Windows]\n"), false);
            }
            oled_write_P(PSTR("Turn wheel to menu\n"), false);
            break;

        case SCREEN_OS_SELECT:
            oled_write_P(PSTR("Menu: OS Config\n"), false);
            if (is_macos_mode) {
                oled_write_P(PSTR("> macOS (Active)\n  Windows\n"), false);
            } else {
                oled_write_P(PSTR("  macOS\n> Windows (Active)\n"), false);
            }
            oled_write_P(PSTR("Press SW4 to Toggle\n"), false);
            break;

        case SCREEN_STATUS:
            oled_write_P(PSTR("Menu: Hardware\n"), false);
            oled_write_P(PSTR("Encoder: UI Nav\n"), false);
            oled_write_P(PSTR("Matrix: 2x4 Active\n"), false);
            break;
    }
    return false;
}
#endif