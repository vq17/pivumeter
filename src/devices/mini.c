#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "../pivumeter.h"

#define DAT 23
#define CLK 24

#define OUTPUTFILE "/home/pi/audioLevels"


static void sof(void){
    int x;
    for(x = 0; x<4; x++){
        write_byte(0);
    }
}

static void eof(void){
    int x;
    for(x = 0; x<5; x++){
        write_byte(0);
    }
}


static void clear_display(void){
    int x;
    for(x = 0; x < NUM_PIXELS; x++){
        pixels[x] = 0;
    }
    show();
}

static int init(void){
    // system("gpio export 23 output");
    // system("gpio export 24 output");
    // wiringPiSetupSys();

    // clear_display();

    // atexit(clear_display);

    return 0;
}



static void update(int meter_level_l, int meter_level_r, snd_pcm_scope_ameter_t *level){
    // Here write to a file
    FILE *fp;
    fp = fopen(OUTPUTFILE,'w');

    fprintf(fp, "%d %d\n",meter_level_l,meter_level_r);
    fclose(fp);

}

device mini(){
    struct device _mini;
    _mini.init = &init;
    _mini.update = &update;
    return _mini;
}
