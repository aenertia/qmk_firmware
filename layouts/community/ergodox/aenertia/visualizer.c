/*
Note: this is a modified copy of ../default/visualizer.c, originally licensed GPL.
*/

#include "simple_visualizer.h"

// This function should be implemented by the keymap visualizer
// Don't change anything else than state->target_lcd_color and state->layer_text as that's the only thing
// that the simple_visualizer assumes that you are updating
// Also make sure that the buffer passed to state->layer_text remains valid until the previous animation is
// stopped. This can be done by either double buffering it or by using constant strings
// Default - !#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwx";
// 
// This has expanded with the quantum visualizer and ugfx lib to use the GDrawStringBox api rather than Drawstring and wordwrap enabled
// The following block renders 4 lines on the screen with fixed 5x8 font and using wordwrap 
// Spaces/Null space is a bit hit or miss so Try and use this format when entering your layer strings \t and \n are pretty hit or miss
/*
		"Gu Ct    Ri 6 7 8 9 0 -   "            
		"Pu En Sp l1 Y U I O P \\  "            
		"Pd       Me H J K L ; '   "           
		"U D [ ] l2  N M , . / Sh  ";  
*/
static void get_visualizer_layer_and_color(visualizer_state_t* state) {
    uint8_t saturation = 60;
    if (state->status.leds & (1u << USB_LED_CAPS_LOCK)) {
        saturation = 255;
    }
    if (state->status.layer & 0x10) {
        state->target_lcd_color = LCD_COLOR(140, 100, 60);
        state->layer_text = "Movement";
    } else if (state->status.layer & 0x8) {
        state->target_lcd_color = LCD_COLOR(0, saturation, 0xFF);
        state->layer_text = "Media";
    } else if (state->status.layer & 0x4) {
        state->target_lcd_color = LCD_COLOR(168, saturation, 0xFF);
        state->layer_text =
		"Ra Rc    l1 6 7 8 9 0 -   "            
		"Pu En Bb l2 Y U I O P \\  "            
		"Pd      Me H J K L ; Play "           
		"V+ V- Vm  l2  N M Pr Ne   ";  
    } else if (state->status.layer & 0x2) {
        state->target_lcd_color = LCD_COLOR(216, 90, 0xFF);
        state->layer_text = 
		"Funct:   Ri 6 7 8 9 10 11 "            
		"Pu En Sp l1 7 8 9 * F12   "            
		"Pd       Me 4 5 6 + Ver   "           
		"0 0 . = l2  & 1 2 3 \\ Sh ";  
    } else {
        state->target_lcd_color = LCD_COLOR(84, saturation, 0xFF);
        state->layer_text = 
		"Gu Ct    Ri 6 7 8 9 0 -   "            
		"Pu En Sp l1 Y U I O P \\  "            
		"Pd       Me H J K L ; '   "           
		"U D [ ] l2  N M , . / Sh  ";  
    }
}
