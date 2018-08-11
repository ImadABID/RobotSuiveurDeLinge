
/*-----------Déclaration des variables globales:--------------*/
    #define WAITING_FOR_PASSANGERS 15000
    #define DELAY 50
    bool EstCapteurDansNoire(char PositionDeCapteur);
    void Replay_Actions();
    /*Les variables de Moteur Gauche*/
        #define PIN_EN_G 3
        #define PIN_SENS_AVANCE_G 2
        #define PIN_SENS_ARRIERE_G 4
        int en_G=0;
        int sens_avance_G=1;
        int sens_arriere_G=0;
        
    /*Les variables de Moteur Droite*/
        #define PIN_EN_D 5
        #define PIN_SENS_AVANCE_D 7
        #define PIN_SENS_ARRIERE_D 8
        int en_D=0;
        int sens_avance_D=1;
        int sens_arriere_D=0;

    /*Les variables des Capteurs*/
        #define PIN_CAPTEUR_G A0
        #define PIN_CAPTEUR_D A1
        #define SIGNAL_MAX_POUR_NOIRE 50
        bool capteurGdansN;
        bool capteurDdansN;
        
        bool EstCapteurDansNoire(char PositionDeCapteur){
          int pinC;
          if(PositionDeCapteur=='G') pinC=PIN_CAPTEUR_G;
          else pinC=PIN_CAPTEUR_D ;
          if(analogRead(pinC)<SIGNAL_MAX_POUR_NOIRE) return true;
          return false;
        }
        
    /*Les Fonctions:*/
        void Replay_Actions(){
          //MoteurD:
             analogWrite(PIN_EN_D,en_D);
             digitalWrite(PIN_SENS_AVANCE_D,sens_avance_D);
             digitalWrite(PIN_SENS_ARRIERE_D,sens_arriere_D);

          //MoteurG:
             analogWrite(PIN_EN_G,en_G);
             digitalWrite(PIN_SENS_AVANCE_G,sens_avance_G);
             digitalWrite(PIN_SENS_ARRIERE_G,sens_arriere_G);
        }
        
void setup(){
  
   pinMode(PIN_EN_G,OUTPUT);
   pinMode(PIN_SENS_AVANCE_G,OUTPUT);
   pinMode(PIN_SENS_ARRIERE_G,OUTPUT);
   
   pinMode(PIN_EN_D,OUTPUT);
   pinMode(PIN_SENS_AVANCE_D,OUTPUT);
   pinMode(PIN_SENS_ARRIERE_D,OUTPUT);

   pinMode(PIN_CAPTEUR_G,INPUT);
   pinMode(PIN_CAPTEUR_D,INPUT);

}

void loop() {
     capteurGdansN=EstCapteurDansNoire('G');
     capteurDdansN=EstCapteurDansNoire('D');

  /*Il y a 4 cas:*/
      //1er
      if(capteurGdansN&&capteurDdansN){
        en_D=0; en_G=0;
        Replay_Actions();
        delay(WAITING_FOR_PASSANGERS);
      }

      //2eme
      if(capteurGdansN&&!capteurDdansN){
        en_G=0; en_D=255;
        Replay_Actions();
      }


      //3eme
      if(!capteurGdansN&&capteurDdansN){
        en_G=255; en_D=0;
        Replay_Actions();
      }

      //4eme
      if(!capteurGdansN&&!capteurDdansN){
        en_D=1; en_G=1;
        Replay_Actions();
      }

      delay(DELAY);
}
