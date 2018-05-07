#include "usb_names.h"

//We name the controller here:
#define MIDI_NAME   {'N','C','M','C','-','W','W','M'}
#define MIDI_NAME_LEN  8 //<-- change this number if the number of chars above changes


// USB required code:
struct usb_string_descriptor_struct usb_string_product_name = {
        2 + MIDI_NAME_LEN * 2,
        3,
        MIDI_NAME
};
