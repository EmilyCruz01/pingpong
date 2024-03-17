//lcd
#include <LiquidCrystal_I2C.h>
#include <wire.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
//teclado matricial
#include <Keypad.h>
const byte ROWS = 4; //numero de filas 
const byte COLS = 4; //numero de columnas
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {13, 12, 11, 10}; //conexion de los pines de salida de las filas 
byte colPins[COLS] = {9, 8, 7, 6}; //conexion de los pines de salida de las columnas

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char key;
char entrada[7] = {' ', ' ', ' ', ' ', ' ', ' ', '\0'};
int dato;
int bandera = 1;
char matricula[7] = {' ', ' ', ' ', ' ', ' ', ' ', '\0'};
//moneda
int dinero = 0;
int recaudado;

//modo

void setup() {
Serial.begin(9600);
attachInterrupt(digitalPinToInterrupt(2),suma,RISING);
lcd.init();
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("Bienvenido");
lcd.setCursor(0,1);
lcd.print("espere un momento");
lcd.setCursor(0,2);
lcd.print("..........");
delay(1000);
lcd.clear();
lcd.setCursor(0,2);
lcd.print("iniciando sistema");
delay(1000);
lcd.clear();
digitalWrite(4,HIGH);

//pines de monedas
pinMode (2, INPUT);
digitalWrite(2, LOW);
}

void loop() {
 static byte indice = 0; // Índice para almacenar el código
 lcd.setCursor(4,0);
 lcd.print("BIENVENIDO");
 lcd.setCursor(2,1);
 lcd.print("INGRESE 5 PESOS");


 key = keypad.getKey();
  if (key && key != 'D' && key != 'B' && dinero>10 && key != 'C' && key != '*') {
    lcd.setCursor(0,2);
    lcd.print("Matricula:");
    lcd.setCursor(indice, 3); // Posiciona el cursor en la segunda fila
    lcd.print(key); // Muestra la tecla presionada
    entrada[indice++] = key; // Almacena la tecla en el código y avanza al siguiente índice
    matricula[indice++]=key;
    bandera=1;
    Serial.println(matricula);
    if(key=='#')
    {
      lcd.setCursor(0, 3);
      lcd.print("                   ");
      indice=0;
       
    
    }

    if (indice >= 6 && bandera==1) {
      lcd.setCursor(8, 3);
      lcd.print("Guardar...A");// Posiciona el cursor en la tercera fila
      if(key=='A')
      {
        recaudado=recaudado+dinero;
        dinero=0;
        lcd.clear();
        bandera==0;
        indice=0;
      }


    }
  }

  if (key)
  {
    if (key=='D')
    {
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Modo Versus     A");
       lcd.setCursor(0,1);
       lcd.print("Ver dinero      B");
       lcd.setCursor(0,2);
       lcd.print("Regresar        *");
       dato = 1;
       while(dato)
       {
        key = keypad.getKey();
        static byte indice = 0; // Índice para almacenar el código
        if (key=='A')
        {
          key = keypad.getKey();
          static byte indice2 = 0; // 
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Modo Versus");
          lcd.setCursor(0,1);
          lcd.print("J1:");
          lcd.setCursor(0,3);
          lcd.print("J2:");
         if (key && key != '#') {
           lcd.setCursor(indice2, 3); // Posiciona el cursor en la segunda fila
           lcd.print(key); // Muestra la tecla presionada
           entrada[indice2++] = key; // Almacena la tecla en el código y avanza al siguiente índice
           bandera=1;
           if (indice2 >= 6 && bandera==1) {
             lcd.setCursor(8, 3);
             lcd.print("sisis");// Posiciona el cursor en la tercera fila
             if(key=='*')
             {
               indice2=0;
               lcd.clear();

               bandera=0;
              }

            }
          }
          if (key=='*')
          {
            dato=0;
            lcd.clear();
          }
          
        }
        if(key=='*')
        {
          dato=0;
          key;
        
          lcd.clear();
        }
       if(key=='B')
       {
         lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Su Saldo es");
          lcd.setCursor(0,1);
          lcd.print(recaudado);
          lcd.setCursor(19,1);
          lcd.print("$");
          if (key=='*')
          {
            dato=0;
            lcd.clear();
          }
       }
      }

    }
  }

}  
void suma()
{
 dinero++;
 Serial.println(dinero);
}