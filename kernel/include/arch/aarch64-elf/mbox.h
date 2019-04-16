
#include <arch/gpfio.h>
#include <stdint.h>

// Kanäle für die Mailboxen
enum  {
    MBOX_CH_POWER = 0,
    MBOX_CH_FB = 1,
    MBOX_CH_VUART = 2,
    MBOX_CH_VCHIQ = 3,
    MBOX_CH_LEDS = 4,
    MBOX_CH_BTNS = 5,
    MBOX_CH_TOUCH = 6,
    MBOX_CH_COUNT = 7,
    MBOX_CH_PROP = 8,
};

// Mailbox tags
enum {
    MBOX_TAG_LAST = 0,
    MBOX_TAG_GETBOARDMODEL = 0x10001,
    MBOX_TAG_GETBOARDREVISION = 0x10002,
    MBOX_TAG_GETBOARDMAC = 0x10003,
    MBOX_TAG_GETSERIAL = 0x10004
};

uint32_t mbox_get_boardmodel();
uint32_t mbox_get_boardrevision();
const uint8_t* mbox_get_boardmac();
uint64_t mbox_get_Serial();