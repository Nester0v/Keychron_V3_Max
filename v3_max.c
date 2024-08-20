/* Copyright 2024 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "keychron_task.h"
#include "v3_max.h"
#include "rgb_matrix.h"
#include "color.h"

#ifdef FACTORY_TEST_ENABLE
#    include "factory_test.h"
#    include "keychron_common.h"
#endif

#ifdef LK_WIRELESS_ENABLE
#    include "lkbt51.h"
#    include "wireless.h"
#    include "keychron_wireless_common.h"
#    include "battery.h"
#endif

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_kb(uint8_t index, bool active) {
    if (index == 0) {
        default_layer_set(1UL << (active ? 2 : 0));
    }
    dip_switch_update_user(index, active);

    return true;
}
#endif

// Forward declarations
extern void     rgb_matrix_set_custom_mode(void (*mode)(void));
extern uint16_t scale16by8(uint16_t a, uint8_t b);

// Custom RGB Matrix Wave Effect
void rgb_matrix_custom_wave(void) {
    uint8_t wave_speed = scale16by8(g_rgb_timer, rgb_matrix_config.speed);
    uint8_t hue1       = rgb_matrix_config.hsv.h;  // Access the hue component
    uint8_t hue2       = rgb_matrix_config.hsv2.h; // Access the second hue component
    uint8_t sat        = rgb_matrix_config.hsv.s;  // Access the saturation component
    uint8_t val        = rgb_matrix_config.hsv.v;  // Access the value (brightness) component

    // Add your custom wave effect logic here
}

// Consolidated keyboard initialization
void keyboard_post_init_kb(void) {
#ifdef LK_WIRELESS_ENABLE
    palSetLineMode(P2P4_MODE_SELECT_PIN, PAL_MODE_INPUT);
    palSetLineMode(BT_MODE_SELECT_PIN, PAL_MODE_INPUT);

    lkbt51_init(false);
    wireless_init();
#endif

#ifdef ENCODER_ENABLE
    encoder_cb_init();
#endif

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_mode(RGB_MATRIX_CUSTOM_MODE);        // Enable custom mode by default
    rgb_matrix_set_custom_mode(rgb_matrix_custom_wave); // Set the custom wave effect mode
#endif

    keyboard_post_init_user();
}

#ifdef LK_WIRELESS_ENABLE
bool lpm_is_kb_idle(void) {
    return !factory_reset_indicating();
}
#endif
