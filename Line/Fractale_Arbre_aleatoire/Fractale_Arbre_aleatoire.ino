/*
 * Générateur de fractale d'arbre sur plateforme Arduino
 */

/* Includes */
#include <SPI.h>              // Pour la communication avec l'écran
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"


#define TFT_DC 9
#define TFT_CS 10

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


/* Fonction setup */
void setup() {
  
/* Initialise l'écran LCD */
  Serial.begin(9600);
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
   
  /* Dessine la fractale */
  drawTree (160, 240, -90, 9);

  
}

/* Fonction loop() */

void loop() {

}


/* 

 * Dessine une fractale de Mandelbrot

 */
void drawTree(int x1, int y1, int angle, int profondeur){
  if (profondeur){
    int x2 = x1 + int(cos(radians(angle))*profondeur*5.0);
    int y2 = y1 + int(sin(radians(angle))*profondeur*5.0);
    
    
    
    if (profondeur > 2){
      tft.drawLine(x1, y1, x2, y2, ILI9341_WHITE);
    
    }
    
    else{
      tft.drawLine(x1, y1, x2, y2, ILI9341_GREEN);
    }
      
    
    drawTree(x2, y2, angle-random(-50,0), profondeur-1);
    drawTree(x2, y2, angle-random(1,50), profondeur-1);
    drawTree(x2, y2, angle-random(-10,10), profondeur-1);
    
  }
  //delay(50);
}
  
