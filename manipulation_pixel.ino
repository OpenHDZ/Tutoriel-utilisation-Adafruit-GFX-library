/*

Open Hardware Algerie

Sujet : tutoriel sur la manipulation des pixels des ecrans tft lcd avec la librairie Adafruit GFX

auteur : Areour Mohamed Cherif (OHA)

ce code source est sous licence Gpl v3

outils nécessaire : - une carte arduino
                    - ecrans 2.8" tft lcd shield de chez Adafruit industrie
*/


#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// définition des pins de connexion pour l'écrans 
#define TFT_DC 9
#define TFT_CS 10

// définition des dimension de l'écrans 
#define largeur 240
#define longuer 320

// création d'une instance de la classe Adafruit_ILI9341 
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void setup() {
  
  // initialisation de l'ecrans 
  tft.begin();

  // rotation de l'écrans en mode paysage 
  tft.setRotation(1);

  // background en noir
  tft.fillScreen(BLACK);
  
  // navigation dans la matrice de pixel qui compose l'écrans
	
  for (uint16_t x = 80; x < longuer-80; x++){
    for (uint16_t y = 30; y < largeur-30; y++){

	  // si x et y sont des multiples de 10 colorier le pixel 
      if ((x % 10 == 0) && (y % 10 == 0)) {
		
		// la fonction de colaration du pixel dans dans Adafruit GFX library        
		tft.drawPixel(x, y, BLUE);
        delay(50);
      }
    }
  }
}


void loop(void) {
  
}

