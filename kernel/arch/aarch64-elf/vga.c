
#include <vga.h>
#include <arch/mbox.h>


int vga_width, vga_height;
int vga_pitch;
void* vga_buffer;


vga_init() {
    
    mbox[0] = 35*4;
    mbox[1] = MBOX_REQUEST;
    
    mbox[2] = 0x48003;  // setze physische Auflösung
    mbox[3] = mbox[4] = 8;
    mbox[5] = 640;
    mbox[6] = 480;

    mbox[7] = 0x48004;  // setze virtuelle Auflösung
    mbox[8] = mbox[9] = 8;
    mbox[10] = 640;
    mbox[11] = 480;
    
    mbox[12] = 0x48009;  // setze virtuelles Offset
    mbox[13] = mbox[14] = 8;
    mbox[15] = 0;
    mbox[16] = 0;
    
    mbox[17] = 0x48005; // setze bit-Tiefe
    mbox[18] = mbox[19] = 4;
    mbox[20] = 32;

    mbox[21] = 0x48005; // setze Pixel-Ordnung
    mbox[22] = mbox[23] = 4;
    mbox[24] = 1; // RGB
    
    mbox[25] = 0x40001; // hole Puffer, fordere auf 4k bündig an  
    mbox[26] = mbox[27] = 8;
    mbox[28] = 4096
    mbox[29] = 0;

    mbox[30] = 0x40001; // hole Pitch
    mbox[31] = mbox[32] = 4;
    mbox[33] = 0
    
    mbox[34] = MBOX_TAG_LAST;

    if (mbox_call( MBOX_CH_PROP, mbox) && mbox[20]==32 && mbox[28]!=0) {
        vga_width=mbox[5];
        vga_height=,box[6];
        vga_pitch = mbox[33];
        vga_buffer = mbox[28];        
    }else {
        abort();
    }
    
}

void vga_test() {
    void* vgaline = vga_buffer;
    void* vgapixel;
    for (int y=0; y<8; y++)
    {
        vgapixel = vgaline;        
        for (int x==; x<8; x++) {
            *vgapixel = 0xff00ff00; // magenta
            vgapixel++;
        }
        vgaline += vga_pitch;
    }