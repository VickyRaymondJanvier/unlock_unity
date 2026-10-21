#include <Arduino.h>
#include <Bounce2.h>
#include <MicroOscSlip.h>
#include <Chrono.h>

//define = définir le numéro d'une broche
#define BROCHE_DEL1 5 //
Bounce2::Button bouton;
MicroOscSlip<128> monOsc(&Serial); 

bool etatDel = LOW;

void setup() {
    Serial.begin(115200);
      bouton.attach(2, INPUT_PULLUP);
  bouton.setPressedState(LOW);

  Chrono chronoPot; // /

    pinMode(3,OUTPUT);





    //bouton.attach() = dit que les boutons sont des input
    bouton1.attach(BROCHE_BOUTON1, INPUT_PULLUP);
    bouton2.attach(BROCHE_BOUTON2, INPUT_PULLUP);
    bouton1.setPressedState(LOW);
    bouton2.setPressedState(LOW);

    //Serial.begin(VITESSE) = Vitesse de transfert
    Serial.begin(115200);


}

void loop() {
    monOsc.onOscMessageReceived(traiterMessageOsc); // ACQUISITION DES MESSAGES

  bouton.update();
    if (bouton.pressed()) { // Bouton vient d’être appuyé
      monOsc.sendInt("/valider", 1);
  }
  if ( chronoPot.hasPassed(20)) { // SI LE CHRONO DÉPASSE 20 MILLISECONDES
  chronoPot.restart(); // REPARTIR LE CHRONO

  // LE 2 CI_BAS CORRESPOND À LA BROCHE ANALOGIQUE A2
  int valeur = analogRead(2); // LECTURE DE LA TENSION DE LA BROCHE A2 ENTRE 0 ET 1023

  monOsc.sendInt("/tourner", valeur); // ENVOYER LA VALEUR
}
// FONCTION APPELÉE LORSQU’UN MESSAGE OSC EST REÇU
void traiterMessageOsc(MicroOscMessage & message) {
  // SI L’ADRESSE DU MESSAGE EST "/lumiere" ET QUE LE MESSAGE CONTIENT UN ARGUMENT ENTIER ("i") :
   if (message.checkOscAddressAndTypeTags("/lumiere", "i")) {  

      int valeur = message.nextAsInt();  // RÉCUPÉRER L’ENTIER ("i")

      digitalWrite(3, valeur); // ASSIGNER LA VALEUR A LA DEL
 } 
  } 


}