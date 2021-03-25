const byte LEDPuls = 12; // LED blinkt im Tackt vom Puls

const byte RGBg = 11;   //Große LED grün 
const byte RGBr = 10;   //Große LED rot

const byte Balken1 = 2;
const byte Balken2 = 3;
const byte Balken3 = 4;
const byte Balken4 = 5;
const byte Balken5 = 6;
const byte Balken6 = 7;
const byte Balken7 = 8;
const byte Balken8 = 9;

byte z = 0;
unsigned long t = millis();
const unsigned long f = 60000 / 6 / 19; // Zeit pro Atemphase ==> 6 Atemzüge pro Minute  ==> Millisekunden (6000) / Atemzüge (6) / Phasen Balkenanzeige (19)

int zz = 3;

void SetupLED()
{
  pinMode( LEDPuls, OUTPUT );
  
  pinMode( RGBr, OUTPUT );
  pinMode( RGBg, OUTPUT );

  pinMode( Balken1, OUTPUT );
  pinMode( Balken2, OUTPUT );
  pinMode( Balken3, OUTPUT );
  pinMode( Balken4, OUTPUT );
  pinMode( Balken5, OUTPUT );      
  pinMode( Balken6, OUTPUT );  
  pinMode( Balken7, OUTPUT );  
  pinMode( Balken8, OUTPUT );  
}

int Atmung()
{  
  if(millis() - t > f ) {
    switch ( z++ ){
      case 1:
        digitalWrite(Balken1, HIGH);  // Einatmung beginnt
      break;
      case 2:
        digitalWrite(Balken1, LOW);
        digitalWrite(Balken2, HIGH);  
      break;
      case 3:
        digitalWrite(Balken2, LOW);
        digitalWrite(Balken3, HIGH);  
      break;
      case 4:
        digitalWrite(Balken3, LOW);
        digitalWrite(Balken4, HIGH);  
      break;
      case 5:
        digitalWrite(Balken4, LOW);
        digitalWrite(Balken5, HIGH);  
      break;
      case 6:
         digitalWrite(Balken5, LOW);
         digitalWrite(Balken6, HIGH);  
      break;
      case 7:
        digitalWrite(Balken6, LOW);
        digitalWrite(Balken7, HIGH);  
      break;      
      case 8:
        digitalWrite(Balken7, LOW);
        digitalWrite(Balken8, HIGH);  
      break;
      case 9:
           digitalWrite(Balken8, LOW);  
      break;
    
      // ***************   kurze Pause
      
      case 11:
           digitalWrite(Balken8, HIGH);  
      break;    
      case 12:
        digitalWrite(Balken8, LOW);  // Ausatmung beginnt
        digitalWrite(Balken7, HIGH);  
      break;
      case 13:
        digitalWrite(Balken7, LOW);  
        digitalWrite(Balken6, HIGH);  
      break;
      case 14:
        digitalWrite(Balken6, LOW);  
        digitalWrite(Balken5, HIGH);  
      break;
      case 15:
        digitalWrite(Balken5, LOW);  
        digitalWrite(Balken4, HIGH);  
      break;
     case 16:
        digitalWrite(Balken4, LOW);  
        digitalWrite(Balken3, HIGH);  
      break;
     case 17:
        digitalWrite(Balken3, LOW);  
        digitalWrite(Balken2, HIGH);  
      break;
      case 18:
        digitalWrite(Balken2, LOW);  
        digitalWrite(Balken1, HIGH);  
      break;
     case 19:
        digitalWrite(Balken1, LOW);
        z=0;  
      break;      
    }
    t=millis();
  }
  return(z);
      
}
