/*
 * 
 * PikaBot
 * DYOR
 * 
 * Lluna Sanz Montrull
 * 2019
 * 
 */

#include <IRremote.h>
#include <Servo.h>

Servo right_arm;
Servo left_arm;
Servo r_wh;
Servo l_wh;

IRrecv irrecv(11);
decode_results results;

int pos_arm_0 = 45;
int pos_arm_1 = 175;
int trig = 9;
int echo = 10;
long duration;
long cm;

int linea = 0;
int randNumero;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  left_arm.attach(5);       // Brazo izquierdo
  right_arm.attach(4);        // Brazo derecho
  r_wh.attach(7);             // Rueda derecha
  l_wh.attach(6);             // Rueda izquierda

  pinMode(A0, INPUT);         // Salida analógica del sensor IR para el siguelíneas
  pinMode(trig, OUTPUT);      // Señal "trig" del ultrasonidos
  digitalWrite(trig, LOW);    // Se apaga el ultrasonidos
  pinMode(echo, INPUT);       // Señal "echo" del ultrasonidos

// Necesario para que PikaBot empiece en reposo
  r_wh.write(89);
  delay(300);
  l_wh.write(89);
  delay(300);
  left_arm.write(pos_arm_1);
  delay(300);
  right_arm.write(pos_arm_0);
  delay(300);
}

void loop() {
  int bucle = 1;                              // Variable necesaria para estar usando una misma función.
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    switch (results.value) {


      // Tecla 1  - brazo izquierdo
        // Se mueve hacia arriba y baja.
      case 0x61D6E916:  // a
        left_arm.write(pos_arm_0);
        delay(500);
        left_arm.write(pos_arm_1);
        delay(500);
        break;
      case 0x6DDEFD5E:  // b
        left_arm.write(pos_arm_0);
        delay(500);
        left_arm.write(pos_arm_1);
        delay(500);
        break;


      // Tecla 2  - Ir hacia delante
        // El robot se mueve hacia delante hasta que no se apriete la tecla 5
      case 0xE17F7462:  // a
        l_wh.write(114); // 95
        r_wh.write(0);   // 83
        break;
      case 0x61D66996:  // b
        l_wh.write(114); // 95
        r_wh.write(0);   //
        break;


      // Tecla 3  - brazo derecho
        // Se mueve hacia arriba y baja.
      case 0x61D6A956:
        right_arm.write(pos_arm_1);
        delay(500);
        right_arm.write(pos_arm_0);
        delay(500);
        break;
      case 0x8DA6497A:
        right_arm.write(pos_arm_1);
        delay(500);
        right_arm.write(pos_arm_0);
        delay(500);
        break;


      // Tecla 4 - Girar a la izquierda
        // Se detiene una rueda y la otra gira.
      case 0x2771A3FE:
        l_wh.write(89); // 95
        r_wh.write(74);   // 83
        break;
      case 0x61D629D6:
        l_wh.write(89); // 95
        r_wh.write(74);   // 83
        break;

      
      // Tecla 5  - Parar o salir de bucle (caso de teclas 8 y 0).
      case 0x61D6C936:  // a
        r_wh.write(89); 
        l_wh.write(89);
        break;
      case 0x806E1322:  // b
        r_wh.write(89);
        l_wh.write(89);
        break;

        
        // Tecla 6 - Girar a la derecha
        // Se detiene una rueda y la otra gira.
        case 0xF40E8A26:
          l_wh.write(96); // 95
          r_wh.write(89);   // 83
          break;
        case 0x61D649B6:
          l_wh.write(96); // 95
          r_wh.write(89);   // 83
          break;

        
        // Tecla 7 - Giro atrás izquierda
        case 0x61D68976:
          l_wh.write(89);
          r_wh.write(110);
          break;
        case 0x81BA3BE:
          l_wh.write(89);
          r_wh.write(110);
          break;

        
        // Tecla 8 - Comportamiento basado en tipo bicho
          // El robot se desplaza hacia delante hasta encontrar un obstáculo.
          // Gira 90 grados (antihorario u horario al azar) y sigue recto durante 2 segundos.
          // Gira 90 grados en el sentido contrario al anterior y vuelve al inicio del bucle.
        case 0x4930B07A:
          randNumero = random(2);
          while(bucle){
            l_wh.write(114);
            r_wh.write(0);
            delay(250);
            digitalWrite(trig, LOW);
            delayMicroseconds(2);
            digitalWrite(trig, HIGH);
            delayMicroseconds(10);
            digitalWrite(trig, LOW);
            duration = pulseIn(echo, HIGH);
            cm = duration*0.034/2;
            if(irrecv.decode(&results)){
              Serial.println(results.value);
              if(results.value == 0x61D6C936 || results.value == 0x806E1322){
                bucle = 0;
                r_wh.write(89); 
                l_wh.write(89);
              }
            }
            irrecv.resume();
            if(cm<15){
              if(randNumero = 1){   // Girar a la izquierda y atrás hasta situarse en 90º.
                l_wh.write(89);
                r_wh.write(100);
                delay(1100);
                l_wh.write(114);
                r_wh.write(0);
                delay(2000);
                l_wh.write(80);
                r_wh.write(89);
                delay(1550);
              }
              else{                 // Girar derecha y atrás hasta situarse en 90º.
                l_wh.write(80);
                r_wh.write(89);
                delay(1550);
                l_wh.write(114);
                r_wh.write(0);
                delay(2000);
                l_wh.write(89);
                r_wh.write(100);
                delay(1100);
              }
            }
              cm = 100;              // Se reinicia para el correcto funcionamiento.
          }
          break;
        case 0x61D609F6:
          randNumero = random(2);
          while(bucle){
            l_wh.write(114);
            r_wh.write(0);
            delay(250);
            digitalWrite(trig, LOW);
            delayMicroseconds(2);
            digitalWrite(trig, HIGH);
            delayMicroseconds(10);
            digitalWrite(trig, LOW);
            duration = pulseIn(echo, HIGH);
            cm = duration*0.034/2;
            if(irrecv.decode(&results)){
              Serial.println(results.value);
              if(results.value == 0x61D6C936 || results.value == 0x806E1322){   // Si se pulsa la tecla 5.
                bucle = 0;
                r_wh.write(89); 
                l_wh.write(89);
              }
            }
            irrecv.resume();
            if(cm<15){
              if(randNumero = 1){   // Girar a la izquierda y atrás hasta situarse en 90º.
                l_wh.write(89);
                r_wh.write(100);
                delay(1100);
                l_wh.write(114);
                r_wh.write(0);
                delay(2000);
                l_wh.write(80);
                r_wh.write(89);
                delay(1550);
              }
              else{                 // Girar derecha y atrás hasta situarse en 90º.
                l_wh.write(80);
                r_wh.write(89);
                delay(1550);
                l_wh.write(114);
                r_wh.write(0);
                delay(2000);
                l_wh.write(89);
                r_wh.write(100);
                delay(1100);
              }
            }
              cm = 100;              // Se reinicia para el correcto funcionamiento.
          }
          break;

          
        // Tecla 9 - Giro atrás derecha
        case 0x62A8A1B6:
          l_wh.write(80);
          r_wh.write(89);
          break;
        case 0x61D6F10E:
          l_wh.write(80);
          r_wh.write(89);
          break;

        
        // Tecla 0 - IR y siguelíneas
        case 0x61D6718E:
          while(bucle){
            linea = analogRead(A0);
            Serial.println(linea);
            delay(50);
            if(irrecv.decode(&results)){
              Serial.println(results.value);
              if(results.value == 0x61D6C936 || results.value == 0x806E1322){   // Si se pulsa la tecla 5.
                bucle = 0;
                r_wh.write(89); 
                l_wh.write(89);
              }
            }
            irrecv.resume();
            if(linea>150){  // Está en la linea negra
              l_wh.write(75);
              r_wh.write(75);
            }
            else{ // Fuera de la línea negra
              l_wh.write(100);
              r_wh.write(100);
            }
            delay(50);
          }
          break;
        case 0xD64918BA:
          while(bucle){
            linea = analogRead(A0);
            Serial.println(linea);
            delay(50);
            if(irrecv.decode(&results)){
              Serial.println(results.value);
              if(results.value == 0x61D6C936 || results.value == 0x806E1322){   // Si se pulsa la tecla 5.
                bucle = 0;
                r_wh.write(89); 
                l_wh.write(89);
              }
            }
            irrecv.resume();
            if(linea>150){  // Está en la linea negra
              l_wh.write(75);
              r_wh.write(75);
            }
            else{ // Fuera de la línea negra
              l_wh.write(100);
              r_wh.write(100);
            }
            delay(50);
          }
          break;
    }
    irrecv.resume();
    delay(50);
  }

  
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  cm = duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(cm);
  // Si choca contra la pared, gira atrás a la izquierda y se para para no seguir detectando el obstáculo.
  if(cm<8){    
    l_wh.write(89);
    r_wh.write(100);
    delay(1100);
    l_wh.write(89);
    r_wh.write(89);
  }
}
