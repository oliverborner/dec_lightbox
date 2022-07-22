/*
  
  DECROW'S 

  $$\       $$$$$$\  $$$$$$\  $$\   $$\ $$$$$$$$\ $$$$$$$\   $$$$$$\  $$\   $$\ 
  $$ |      \_$$  _|$$  __$$\ $$ |  $$ |\__$$  __|$$  __$$\ $$  __$$\ $$ |  $$ |
  $$ |        $$ |  $$ /  \__|$$ |  $$ |   $$ |   $$ |  $$ |$$ /  $$ |\$$\ $$  |
  $$ |        $$ |  $$ |$$$$\ $$$$$$$$ |   $$ |   $$$$$$$\ |$$ |  $$ | \$$$$  / 
  $$ |        $$ |  $$ |\_$$ |$$  __$$ |   $$ |   $$  __$$\ $$ |  $$ | $$  $$<  
  $$ |        $$ |  $$ |  $$ |$$ |  $$ |   $$ |   $$ |  $$ |$$ |  $$ |$$  /\$$\ 
  $$$$$$$$\ $$$$$$\ \$$$$$$  |$$ |  $$ |   $$ |   $$$$$$$  | $$$$$$  |$$ /  $$ |
  \________|\______| \______/ \__|  \__|   \__|   \_______/  \______/ \__|  \__|
                                                                                                                                                    
  -------------------------------------------------------------------

  "Darkness cannot drive out darkness: only light can do that. 
   Hate cannot drive out hate: only love can do that."

  ― Martin Luther King Jr.
  
  -------------------------------------------------------------------
  
  README FIRST ->
  
  Runs max. 15 LED'S, best suited for words with 6 letters.
  3 LEDS in series and a 200Ohm resistor for each letter will do it.

  STATES:
    Default on startup: JUST_ON
    Toggle Switch 1: DISCO
    Toggle Switch 2: SOUND RECOGNITION
    Both Switches on: SMOOTH FADE
    Dimmer: adjust brightness wit a potentiometer

  -------------------------------------------------------------------

  Developed by Oliver Borner, 2022
  MIT LICENCE
  
  https://github.com/oliverborner

*/



/* ----------------------- GLOBAL CONFIG ----------------------------- */
  

// LEDS

int all_letters[] = { 9, 10, 11, 3, 5, 6 };  // PWM, 9 -> D, 10 -> E, 11 -> C, 3 -> R, 5 ->0, 6 -> W
int letterCount = 6; // how many letters you want to drive


// initialize toggle switches and their state

int toggleSwitch1 = 7;   // digital pin, has internal pull up resistor
int toggleSwitchState1 = 0;  

int toggleSwitch2 = 8;   // digital pin, has internal pull up resistor
int toggleSwitchState2= 0;  



// OTHER

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

int soundSensor = 2;


/* ----------------------------- SETUP ------------------------------- */

void setup() {
  
  // DEBUG
  Serial.begin(9600);
  
  // SETUP LED PINS
  for (int i = 0; i <= letterCount; i++) {
      pinMode(all_letters[i], OUTPUT);        // Set the mode to OUTPUT
  }
  
  // SOUNDSENSOR
  pinMode(soundSensor, INPUT);

  // TOGGLESWITCH 1 & 2
  pinMode(toggleSwitch1, INPUT_PULLUP);
  pinMode(toggleSwitch2, INPUT_PULLUP);

}


/* --------------------------- MAIN LOOP ----------------------------- */

void loop() {
  
  // Toggle Switch 1
  toggleSwitchState1 = digitalRead(toggleSwitch1);
  toggleSwitchState2 = digitalRead(toggleSwitch2);


  if (toggleSwitchState1 == HIGH && toggleSwitchState2 == HIGH) {
    // Default State all LED's turned on
    dec_just_on(all_letters);
  }
  
  if (toggleSwitchState1 == LOW && toggleSwitchState2 == HIGH) {
    // Disco Mode
    dec_disco(all_letters[0], all_letters[1], all_letters[2], all_letters[3], all_letters[4], all_letters[5]);
  }
  
  if (toggleSwitchState2 == LOW && toggleSwitchState1 == HIGH) {
    // Sound Recognition
    dec_sound_recognition(all_letters);
  }

  if (toggleSwitchState1 == LOW && toggleSwitchState2 == LOW) {
    // Dimming Mode
 
    brightness = 0;
    fadeAmount = 5;
    
    for (int i = 0; i <= 30; i++) {
      analogWrite(all_letters[0], brightness);
      analogWrite(all_letters[1], brightness);
      analogWrite(all_letters[2], brightness);
      analogWrite(all_letters[3], brightness);
      analogWrite(all_letters[4], brightness);
      analogWrite(all_letters[5], brightness);
        
      // change the brightness for next time through the loop:
      brightness = brightness + fadeAmount;
    
      // reverse the direction of the fading at the ends of the fade:
      if (brightness <= 0 || brightness >= 255) {
        fadeAmount = -fadeAmount;
      }
      // wait for 30 milliseconds to see the dimming effect
      delay(30);
      
    }
    delay(1000);

  }
  
  // STARTUP
  // if no toggleswitch on
  
  // dec_just_on(all_letters);

  
  // DISCO
  
  //dec_disco(all_letters[0], all_letters[1]);
  

  // TESTS

  //dec_disco(letter_D, letter_E);
  // dec_on(letter_E);
  // dec_on(letter_D);
  // dec_off(letter_D);
  // dec_blink(letter_D);
  // dec_blink(letter_D);
  // dec_sound_recognition(letter_D);
  
}


/* --------------------------- FUNCTIONS --------------------------- */

// JUST_ON

void dec_just_on(int leds[]) {
   for (int i = 0; i < letterCount; i++) {
      digitalWrite(leds[i], HIGH);
   }
}


// DISCO

void dec_disco(int led1, int led2, int led3, int led4, int led5, int led6) {
  
  // Blink 10 times
  
  int j = 30;
  
  for (int i = 0; i <= 10; i++) {
    j = j + 30;
    dec_blink(led1, j);
    dec_blink(led2, j); 
    dec_blink(led3, j); 
    dec_blink(led4, j); 
    dec_blink(led5, j); 
    dec_blink(led6, j); 
  }

  
  // Blink all
  
  for (int i = 0; i <= 3; i++) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    delay(500);
  }

  
  // Fade
  brightness = 0;
  fadeAmount = 5;
  
  for (int i = 0; i <= 30; i++) {
    analogWrite(led1, brightness);
    analogWrite(led2, brightness);
    analogWrite(led3, brightness);
    analogWrite(led4, brightness);
    analogWrite(led5, brightness);
    analogWrite(led6, brightness);
      
    // change the brightness for next time through the loop:
    brightness = brightness + fadeAmount;
  
    // reverse the direction of the fading at the ends of the fade:
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
    
  }
  delay(1000);


  // turn off
  dec_off(led1);
  dec_off(led2); 
  dec_off(led3); 
  dec_off(led4);
  dec_off(led5); 
  dec_off(led6); 
  delay(1000);
  
  
  // Fade
  brightness = 0;
  fadeAmount = 5;
  
  for (int i = 0; i <= 30; i++) {
    analogWrite(led1, brightness);
    analogWrite(led2, brightness);
    analogWrite(led3, brightness);
    analogWrite(led4, brightness);
    analogWrite(led5, brightness);
    analogWrite(led6, brightness);
      
    // change the brightness for next time through the loop:
    brightness = brightness + fadeAmount;
  
    // reverse the direction of the fading at the ends of the fade:
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
    
  }
  delay(1000);

  
  // turn off
  dec_off(led1);
  dec_off(led2); 
  dec_off(led3); 
  dec_off(led4);
  dec_off(led5); 
  dec_off(led6); 
  delay(1000);


  // Blink all slow
  for (int i = 0; i <= 3; i++) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
    delay(1000);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    delay(1000);
  }


  // turn off
  dec_off(led1);
  dec_off(led2); 
  dec_off(led3); 
  dec_off(led4);
  dec_off(led5); 
  dec_off(led6); 
  delay(1000);


  // DE - CROW
  dec_on(led1); 
  dec_on(led2); 
  delay(1000);
  dec_on(led3);
  dec_on(led4);
  dec_on(led5);
  dec_on(led6); 
  delay(1000);

   // turn off
  dec_off(led1);
  dec_off(led2); 
  dec_off(led3); 
  dec_off(led4);
  dec_off(led5); 
  dec_off(led6); 
  delay(1000);


  // D - W  E - O  C - R 
  // 0 - 5  1 - 4  2 - 3 (and reversed)
  dec_on(led1); 
  dec_on(led6);
  delay(500);
  dec_on(led2); 
  dec_on(led5);
  delay(500);
  dec_on(led3); 
  dec_on(led4);
  delay(1000);

  // turn off
  dec_off(led1);
  dec_off(led2); 
  dec_off(led3); 
  dec_off(led4);
  dec_off(led5); 
  dec_off(led6); 
  delay(600);

  // reverse
  dec_on(led3); 
  dec_on(led4);
  delay(500);
  dec_on(led2); 
  dec_on(led5);
  delay(500);
  dec_on(led1); 
  dec_on(led6);
  delay(1000);

  // turn off
  dec_off(led1);
  dec_off(led2); 
  dec_off(led3); 
  dec_off(led4);
  dec_off(led5); 
  dec_off(led6); 
  delay(600);


  
}


// SOUND_RECOGNITION

void dec_sound_recognition(int leds[]) {
  int statusSensor = digitalRead (soundSensor);

  if (statusSensor == 1)
  {
     for (int i = 0; i < letterCount; i++) {
        digitalWrite(leds[i], HIGH);
     }

  }
  else
  {
      for (int i = 0; i < letterCount; i++) {
        digitalWrite(leds[i], LOW);
      }
  }
  
}


/* --------------------- HELPER FUNCTIONS ------------------------- */

// ON

void dec_on(int led) {
  digitalWrite(led, HIGH);  
}


// OFF

void dec_off(int led) {
  digitalWrite(led, LOW);  
}


// BLINK

void dec_blink(int led, int blinkspeed) {
  digitalWrite(led, HIGH);  
  delay(blinkspeed);   
  digitalWrite(led, LOW);  
  delay(blinkspeed);
}


// FADE

void dec_fade(int led) {

  analogWrite(led, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
  
}
