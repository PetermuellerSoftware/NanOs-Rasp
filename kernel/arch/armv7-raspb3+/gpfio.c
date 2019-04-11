#include "arch/gpfio.h"
#include "arch/baseIO.h"


void gpfio_set_func ( uint8_t pin, uint8_t function) {
    // welches Selector Register? jeweils 10 Einträge pro Register
    const uint8_t selector_offset = pin / 10;
    // bit Position im Register: 3 bit pro Eintrag
    const uint8_t selector_bit =  (pin % 10) * 3;
    
    // bisherigen Wert auslesen
    uint32_t selector = get32(GPFSEL0 +  (selector_offset << 2));
    // unsere 3 bits löschen
    selector &= ~( 0x7 << selector_bit);
    // 3 Bits fpr ide neue Funktion
    selector |= (function & 0x7) << selector_bit;
    // Registerwert zurück schreiben
    put32( GPFSEL0 + (selector_offset << 2), selector);
}