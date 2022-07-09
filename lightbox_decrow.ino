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
  
  open sauce
  https://github.com/oliverborner

*/



/* ----------------------- GLOBAL CONFIG ----------------------------- */
  

// LEDS

int all_letters[] = { 9, 10 };  // PWM, 9 -> D, 10 -> E
int letterCount = 2;            // how many letters you want to drive


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

}


/* --------------------------- MAIN LOOP ----------------------------- */

void loop() {

  // STARTUP
  // if no toggleswitch on
  
  // dec_just_on(all_letters);

  
  // DISCO
  
  dec_disco(all_letters[0], all_letters[1]);
  

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

void dec_disco(int led1, int led2) {
  
  // Blink 10 times
  
  int j = 30;
  
  for (int i = 0; i <= 10; i++) {
    j = j + 30;
    dec_blink(led1, j);
    dec_blink(led2, j); 
  }

  
  // Blink all
  
  for (int i = 0; i <= 3; i++) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    delay(500);
  }

  
  // Fade
  brightness = 0;
  fadeAmount = 5;
  
  for (int i = 0; i <= 30; i++) {
    analogWrite(led1, brightness);
    analogWrite(led2, brightness);
      
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
  delay(1000);
  
  
  // Fade
  brightness = 0;
  fadeAmount = 5;
  
  for (int i = 0; i <= 30; i++) {
    analogWrite(led1, brightness);
    analogWrite(led2, brightness);
      
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
  delay(1000);


  // Blink all slow
  for (int i = 0; i <= 3; i++) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    delay(1000);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    delay(1000);
  }


  // turn off
  dec_off(led1);
  dec_off(led2); 
  delay(1000);


  // DE - CROW
  dec_on(led1); 
  delay(1000);
  dec_on(led2); 
  delay(1000);

  // D - W  E - O  C - R 
  // 0 - 5  1 - 4  2 - 3 (and reversed)

  
}


// SOUND_RECOGNITION

void dec_sound_recognition(int led) {
  int statusSensor = digitalRead (soundSensor);

  if (statusSensor == 1)
  {
    digitalWrite(led, HIGH);
    Serial.write("High");
  }
  else
  {
    digitalWrite(led, LOW);
    Serial.write("LOW");
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
