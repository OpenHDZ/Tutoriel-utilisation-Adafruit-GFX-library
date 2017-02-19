/*
 * Générateur de fractale de Mandelbrot sur plateforme Arduino
 */

/* Includes */
#include <SPI.h>              // Pour la communication avec l'écran
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

const uint16_t MAX_ITERATION = 99; // Nombre de couleurs
const uint16_t SCREEN_WIDTH  = 320; // 
const uint16_t SCREEN_HEIGHT = 240; // Taille de l'écran

#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


/**
 * Tableaux de couleurs (99 couleurs + noir, tiré d'un nuancier trouvé sur le web)
 */

const uint16_t COLOR_TABLE[100] = { // HTML color
  0xf7df, 0xff5a, 0x07ff, 0x7ffa, 0xf7ff, 0xf7bb, 0xff38, 0xff59, 0x001f, 0x895c, 
  0xa145, 0xddd0, 0x5cf4, 0x7fe0, 0xd343, 0xfbea, 0x64bd, 0xffdb, 0xd8a7, 0x7ff, 
  0x0011, 0x0451, 0xbc21, 0xad55, 0x0320, 0xbdad, 0x8811, 0x5345, 0xfc60, 0x9999, 
  0x8800, 0xecaf, 0x8df1, 0x49f1, 0x2a69, 0x067a, 0x901a, 0xf8b2, 0x05ff, 0x6b4d, 
  0x1c9f, 0xd48e, 0xb104, 0xffde, 0x2444, 0xf81f, 0xdefb, 0xffdf, 0xfea0, 0xdd24, 
  0x8410, 0x0400, 0xafe5, 0xf7fe, 0xfb56, 0xcaeb, 0x4810, 0xfffe, 0xf731, 0xe73f, 
  0xff9e, 0x7fe0, 0xffd9, 0xaedc, 0xf410, 0xe7ff, 0xffda, 0xd69a, 0x9772, 0xfdb8, 
  0xfd0f, 0x2595, 0x867f, 0x839f, 0x7453, 0xb63b, 0xfffc, 0x07e0, 0x3666, 0xff9c, 
  0xf81f, 0x8000, 0x6675, 0x0019, 0xbaba, 0x939b, 0x3d8e, 0x7b5d, 0x07d3, 0x4e99, 
  0xc0b0, 0x18ce, 0xf7ff, 0xff3c, 0xff36, 0xfef5, 0x0010, 0xffbc, 0x8400, 0x0000
};

/* Fonction setup */
void setup() {
  
/* Initialise l'écran LCD */
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
   
  /* Dessine la fractale */

  draw_mandelbrot();
}

/* Fonction loop() */

void loop() {

}


/* 

 * Dessine une fractale de Mandelbrot

 */

void draw_mandelbrot() {

  tft.setCursor(0,0);
  float new_r = 0.0, new_i = 0.0, old_r = 0.0, old_i = 0.0;

  /* Pour chaque pixel en X */

  for(uint16_t x = 0; x < SCREEN_WIDTH; x++) {
    
    /* Pour chaque pixel en Y */
    for(uint16_t y = 0; y < SCREEN_HEIGHT; y++) {      
      
      uint16_t i = 0;

      old_r = mapfloat(x, 0, SCREEN_WIDTH, -1.7, 1.5);
      old_i = mapfloat(y, 0, SCREEN_HEIGHT,-1.5, 1.5);
     
      float c_r = old_r;
      float c_i = old_i;
      

      while ((old_r * old_r + old_i * old_i) < 4.0 && i < MAX_ITERATION) {
        
        
        new_r = old_r * old_r - old_i * old_i ;
        new_i = 2.0 * old_r * old_i;

        old_r = new_r+c_r;
        old_i = new_i+c_i;
        
        i++;
      }

      /* Affiche le pixel */
      tft.drawPixel(x,y,COLOR_TABLE[i]);
    }
  }
}

float mapfloat(uint16_t x, uint16_t in_min, uint16_t in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


