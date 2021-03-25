///////////////////////////////////////////////////////////////////////////////////
// Biofeedback
// von Ulrich Schmerold
// 09/2020
////////////////////////////////////////////////////////////////////////////////////
#include "LED.h"

unsigned int value;       // Wert vom Pulssensor
const int Abstand = 6;    // Abstand von Puls ein - Puls aus
unsigned long timer;
unsigned long duration = 700;  // Abstand (Zeit) zwischen zwei Pulssequenzen. Wert wird später angepasst.
byte state = 0;

float Output;         // Ergebnis der Mittelwert-Rechnung.
float Oldvalue = 700; // wird durch Mittelwertberechnung angepasst
const float n = 0.98; // Wert für die Berechnung vom Gleitenden Mittelwert (n < 1)


int RSA;  //Respiratorische SinusArrhythmie 
// die folgenden vier Variablen werden zur Berechnung eines RSA aus einer Atemsequenz (Aus + Einatmung) benötigt
long T_Ein = 0L;
long T_Aus = 0L;
 int N_Ein = 0;
 int N_Aus = 0;
 
void setup() {
  Serial.begin(9600);
  pinMode( A0, INPUT );     // Pin, an dem der Pulssensor angeschlossen ist
  SetupLED();               // Initialisierung aller Variablen für die LED Anzeigen (LED.h)
  digitalWrite(RGBr, HIGH); 
}

void loop() {
  
  int z = Atmung(); // LED-Balkenanzeige laufen lassen  
  
  //**************** Messung Pulssignal ***********************
    
  value = analogRead(A0);
  
  //***************** gleitender Mittelwert (Lowpass-Filter )***************
  
  Output = Oldvalue * n + value * (1 - n); // wobei n < 1
  Oldvalue = Output;
  
  //************************************************************************
  if (value > (Output + Abstand))
  {
    if (state == 0) { // Pulsschlag erkannt
      state = 1;
      duration = millis() - timer;
      timer = millis();
      digitalWrite(LEDPuls, HIGH); // Puls LED einschalten
      
      // ***************** Ausgabe der Dauer einer Pulssequenz für den Arduino Serial Plotter
      // if ((duration >750) && (duration<900))   Serial.println(duration);
      
      //****************** hier wird die Respiratorische SinusArrhythmie (RSA) aus einer Atemsequenz ermittelt ********
      if ( z > 0 && z < 10) {  // Einatmung
        N_Ein++;
        T_Ein = T_Ein + duration;
      }
      if ( z > 10 && z <= 19) { // Ausatmung
        N_Aus++;
        T_Aus = T_Aus + duration;
      }
      if (z == 0){ // eine Atemsequenz abgeschlossen
        RSA = ((T_Aus / N_Aus) - (T_Ein / N_Ein));
        if (RSA >= 0) { 
          digitalWrite(RGBr, LOW);
          digitalWrite(RGBg, HIGH);
        }
        if (RSA < 0){
          digitalWrite(RGBg, LOW);
          digitalWrite(RGBr, HIGH);
        }
        T_Aus = 0L;
        T_Ein = 0L;
        N_Ein = 0;
        N_Aus = 0;
      }
      //**************************************************************************
    }
  }
  if (state == 1) {
    if  (value < (Output )) {
      state = 0;
      digitalWrite(LEDPuls, LOW);  //Puls LED auschalten
    }
  }

  // *************** Testausgabe der Werte *****************
    Serial.print(value);

    Serial.print(","); Serial.print(Output+Abstand);
    Serial.print(","); Serial.print(Output);

    Serial.println(); 

  //*************************************************************
}
