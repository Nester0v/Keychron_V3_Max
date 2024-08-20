/* v3_max.h */

#ifndef V3_MAX_H
#define V3_MAX_H

#include "quantum.h"
#include "rgb_matrix.h"

// Function prototypes
void rgb_matrix_custom_wave(void);

// External variables
extern void rgb_matrix_set_custom_mode(void (*mode)(void));
extern uint16_t scale16by8(uint16_t a, uint8_t b);

#endif // V3_MAX_H