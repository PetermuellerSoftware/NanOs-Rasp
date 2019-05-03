
#include <arch/vga.h>
#include <arch/mbox.h>

#include <libk.h>
#include <NanOs_logo.h>
#include <printf.h>

int vga_width, vga_height;
int vga_pitch;
void* vga_buffer;


void vga_init(uint32_t mbox[]) {
    
    mbox[0] = 35*4;
    mbox[1] = MBOX_REQUEST;
    
    mbox[2] = 0x48003;  // setze physische Auflösung
    mbox[3] = mbox[4] = 8;
    mbox[5] = 1024;
    mbox[6] = 768;

    mbox[7] = 0x48004;  // setze virtuelle Auflösung
    mbox[8] = mbox[9] = 8;
    mbox[10] = 1024;
    mbox[11] = 768;
    
    mbox[12] = 0x48009;  // setze virtuelles Offset
    mbox[13] = mbox[14] = 8;
    mbox[15] = 0;
    mbox[16] = 0;
    
    mbox[17] = 0x48005; // setze bit-Tiefe
    mbox[18] = mbox[19] = 4;
    mbox[20] = 32;

    mbox[21] = 0x48006; // setze Pixel-Ordnung
    mbox[22] = mbox[23] = 4;
    mbox[24] = 1; // RGB
    
    mbox[25] = 0x40001; // hole Puffer, fordere auf 4k bündig an  
    mbox[26] = mbox[27] = 8;
    mbox[28] = 4096;
    mbox[29] = 0;

    mbox[30] = 0x40008; // hole Pitch
    mbox[31] = 4;
    mbox[32] = 4;
    mbox[33] = 0;
    
    mbox[34] = MBOX_TAG_LAST;

    if (mbox_call( MBOX_CH_PROP, mbox) && mbox[20]==32 && mbox[28]!=0) {
        vga_width=mbox[5];
        vga_height=mbox[6];
        vga_pitch = mbox[33];
        vga_buffer = (void *) (unsigned long) mbox[28];     
    }else {
        abort();
    }
    
}

/**
 * Show a picture
 */
void lfb_showpicture()
{
    unsigned int x,y;
    unsigned char *ptr= (unsigned char*) vga_buffer;
    char *data=logo_data, pixel[4];

    ptr += (vga_height-logo_height)/2*vga_pitch + (vga_width-logo_width)*2;
    for(y=0;y<logo_height;y++) {
        for(x=0;x<logo_width;x++) {
            HEADER_PIXEL(data, pixel);
            *((unsigned int*)ptr)=*((unsigned int *)&pixel);
            ptr+=4;
        }
        ptr+=vga_pitch-logo_width*4;
    }
}

