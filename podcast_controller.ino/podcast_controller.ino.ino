#include <EEPROM.h>
#include <Bounce2.h>

bool readyToRecord = false;
bool recording = false;
bool isRecorded = false;
bool isSaved = false;

Bounce button_openProgram = Bounce();
Bounce button_startRecording = Bounce();
Bounce button_saveRecording = Bounce();
Bounce button_playbackRecording = Bounce();
Bounce button_deleteRecording = Bounce();
Bounce button_reset = Bounce();

const int PIN_deleteRecording = 2;
const int PIN_openProgram = 3;
const int PIN_reset = 4;
const int PIN_startRecording = 5;
const int PIN_saveRecording = 9;
const int PIN_playbackRecording = 7;

const int led_deleteRecording = 22;
const int led_openProgram = 21;
const int led_reset = 20;
const int led_startRecording = 19;
const int led_saveRecording = 17;
const int led_playbackRecording = 18;

int lights[] = { led_openProgram, led_startRecording, led_saveRecording, led_playbackRecording, led_deleteRecording, led_reset };
bool isNotOpenLights[sizeof(lights)] = { true, true, true, true, true, true };
bool readyLights[sizeof(lights)] = { true, true, false, false, false, true };
bool recordingLights[sizeof(lights)] = { false, true, false, false, false, true };
bool isRecordedLights[sizeof(lights)] = { true, false, true, true, true, true, true };

void setup() {
  // put your setup code here, to run once:

  button_openProgram.attach(PIN_openProgram, INPUT_PULLUP);
  button_startRecording.attach(PIN_startRecording, INPUT_PULLUP);
  button_saveRecording.attach(PIN_saveRecording, INPUT_PULLUP);
  button_playbackRecording.attach(PIN_playbackRecording, INPUT_PULLUP);
  button_deleteRecording.attach(PIN_deleteRecording, INPUT_PULLUP);
  button_reset.attach(PIN_reset, INPUT_PULLUP);
  
  button_openProgram.interval(25);
  button_startRecording.interval(25);
  button_saveRecording.interval(25);
  button_playbackRecording.interval(25);
  button_deleteRecording.interval(25);
  button_reset.interval(25);

//  pinMode(PIN_deleteRecording, INPUT_PULLUP);
//  pinMode(PIN_openProgram, INPUT_PULLUP);
//  pinMode(PIN_reset, INPUT_PULLUP);
//  pinMode(PIN_startRecording, INPUT_PULLUP);
//  pinMode(PIN_saveRecording, INPUT_PULLUP);
//  pinMode(PIN_playbackRecording, INPUT_PULLUP);
  
  pinMode(led_openProgram, OUTPUT);
  pinMode(led_startRecording, OUTPUT);
  pinMode(led_saveRecording, OUTPUT);
  pinMode(led_playbackRecording, OUTPUT);
  pinMode(led_deleteRecording, OUTPUT);
  pinMode(led_reset, OUTPUT);

  Serial.begin(9600);

  // TEST SEQUENCE - DELTE
  delay(1000); // need to wait after being plugged in to init USB keyboard connection

  digitalWrite(led_openProgram , HIGH);
  digitalWrite(led_startRecording , HIGH);
  digitalWrite(led_saveRecording , HIGH);
  digitalWrite(led_playbackRecording , HIGH);
  digitalWrite(led_deleteRecording , HIGH);
  digitalWrite(led_reset , HIGH);

  Serial.println("Starting");
  
//  openProgram();
//  delay(5000);
//  startRecording();
//  delay(4000);
//  stopRecording();
//  playbackRecording();
//  delay(4000);
//  saveRecording();
//  delay(2000);
//  resetEverything();
}

void loop() {
  button_openProgram.update();
  button_startRecording.update();
  button_saveRecording.update();
  button_playbackRecording.update();
  button_deleteRecording.update();
  button_reset.update();

  Serial.print("data: \treset: ");
  Serial.print(digitalRead(PIN_reset));
  Serial.print("\topen: ");
  Serial.print(digitalRead(PIN_openProgram));
  Serial.print("\tstart: ");
  Serial.print(digitalRead(PIN_startRecording));
  Serial.print("\tplayback: ");
  Serial.print(digitalRead(PIN_playbackRecording));
  Serial.print("\tdelete: ");
  Serial.print(digitalRead(PIN_deleteRecording));
  Serial.print("\tsave: ");
  Serial.println(digitalRead(PIN_saveRecording));

  String saveName;

  if ( button_reset.fell() ) {
    resetEverything();
    updateLeds();
  } else if ( button_openProgram.fell() && !recording ) {
    Serial.println("pressed open");
    openProgram();
    updateLeds();
  } else if ( button_startRecording.fell() && !recording && readyToRecord ) {
    Serial.println("pressed start");
    startRecording();
    updateLeds();
  } else if ( button_startRecording.fell() && recording ) {
    Serial.println("pressed stop");
    stopRecording();
    updateLeds();
  } else if ( button_playbackRecording.fell() && isRecorded ) {
    Serial.println("pressed playback");
    playbackRecording();
    updateLeds();
  } else if ( button_deleteRecording.fell() && isRecorded ) {
    Serial.println("pressed delete");
    deleteRecording();
    updateLeds();
  } else if ( button_saveRecording.fell() && isRecorded ) {
    Serial.println("pressed save");
    saveName = saveRecording();
    deleteRecording();
    updateLeds();
  }
  delay(10);
}

void resetEverything() {
  // Windows kill task
  Keyboard.press(MODIFIERKEY_ALT);
  Keyboard.press(KEY_F4);
  Keyboard.release(MODIFIERKEY_ALT);
  Keyboard.release(KEY_F4);

  delay(100);

  // prompt asking for saving
  Keyboard.press(KEY_N);
  Keyboard.release(KEY_N);

  //reset leds here manually
  resetLeds();

  readyToRecord = false;
  recording = false;
  isRecorded = false;
  isSaved = false;
}

void openProgram() {
  // Windows start reaper program
  Keyboard.press(MODIFIERKEY_RIGHT_GUI);
  Keyboard.release(MODIFIERKEY_RIGHT_GUI);
  delay(2000);
  Keyboard.println("reaper");
  delay(1000);
  Keyboard.press(KEY_ENTER);
  Keyboard.release(KEY_ENTER);

  // wait 10 seconds for the program to open
  delay(5000);

  // create track within reaper
  Keyboard.press(MODIFIERKEY_CTRL);
  Keyboard.press(KEY_T);
  delay(100);
  Keyboard.release(MODIFIERKEY_CTRL);
  Keyboard.release(KEY_T);
  

  //TODO - might need something here to dismiss a notification

  readyToRecord = true;
  recording = false;
  isRecorded = false;
  isSaved = false;
}

void startRecording() {

  // mute speakers
  Keyboard.press(KEY_MEDIA_MUTE);
  Keyboard.release(KEY_MEDIA_MUTE);

  // arm track for recording
  // TODO - make a keybinding within the app that responds to CTRL+9 which arms all tracks for recording
  Keyboard.press(MODIFIERKEY_CTRL);
  Keyboard.press(KEY_9);
  delay(100);
  Keyboard.release(MODIFIERKEY_CTRL);
  Keyboard.release(KEY_9);

  // Start recording
  Keyboard.press(MODIFIERKEY_CTRL);
  Keyboard.press(KEY_R);
  delay(100);
  Keyboard.release(MODIFIERKEY_CTRL);
  Keyboard.release(KEY_R);

  readyToRecord = false;
  recording = true;
}

void stopRecording() {

  // stop recording
  Keyboard.press(MODIFIERKEY_CTRL);
  Keyboard.press(KEY_R);
  delay(100);
  Keyboard.release(MODIFIERKEY_CTRL);
  Keyboard.release(KEY_R);

  // unarm track for recording
  // TODO - make a keybinding in the app that responds to CTRL+8 which un arms all tracks for recording
  Keyboard.press(MODIFIERKEY_CTRL);
  Keyboard.press(KEY_8);
  delay(100);
  Keyboard.release(MODIFIERKEY_CTRL);
  Keyboard.release(KEY_8);

  // unmute speakers
  Keyboard.press(KEY_MEDIA_MUTE);
  Keyboard.release(KEY_MEDIA_MUTE);

  isRecorded = true;
  recording = false;
}

void playbackRecording() {

  Keyboard.press(KEY_SPACE);
  Keyboard.release(KEY_SPACE);
}

String saveRecording() {
  // Right now, I'm using google drive, things automatically show up in a folder. Tab and shift+tab can be used

  // Technically called "render", pulls up a prompt
  Keyboard.press(MODIFIERKEY_CTRL);
  Keyboard.press(MODIFIERKEY_ALT);
  Keyboard.press(KEY_R);
  delay(100);
  Keyboard.release(MODIFIERKEY_CTRL);
  Keyboard.release(MODIFIERKEY_ALT);
  Keyboard.release(KEY_R);

  // Fill out render options prompt
  String randomString = generateRecordingName();
  Keyboard.println(randomString);

  // wait for file to finish rendering
  delay(10000); // 10 seconds, might need more

  Keyboard.press(KEY_ENTER);
  Keyboard.release(KEY_ENTER);

  isRecorded = false;
  isSaved = true;

  return randomString;
}

void deleteRecording() {

  // delete all tracks
  Keyboard.press(MODIFIERKEY_CTRL);
  Keyboard.press(KEY_A);
  delay(100);
  Keyboard.release(MODIFIERKEY_CTRL);
  Keyboard.release(KEY_A);
  delay(100);
  Keyboard.press(KEY_DELETE);
  Keyboard.release(KEY_DELETE);

//  // reaper will want confirmation
//  delay(200);
//  Keyboard.press(KEY_ENTER);
//  Keyboard.release(KEY_ENTER);

  readyToRecord = true;
  recording = false;
  isRecorded = false;
  isSaved = false;
}

void updateLeds() {

  if (readyToRecord && !recording && !isRecorded ) {
    digitalWrite(led_startRecording, HIGH);
    digitalWrite(led_reset, HIGH);

    digitalWrite(led_deleteRecording, LOW);
    digitalWrite(led_openProgram, LOW);
    digitalWrite(led_saveRecording, LOW);
    digitalWrite(led_playbackRecording, LOW);
  } else if ( !readyToRecord && recording && !isRecorded ) {
    digitalWrite(led_startRecording, HIGH);
    
    digitalWrite(led_reset, LOW);
    digitalWrite(led_deleteRecording, LOW);
    digitalWrite(led_openProgram, LOW);
    digitalWrite(led_saveRecording, LOW);
    digitalWrite(led_playbackRecording, LOW);
  } else if ( !readyToRecord && !recording && isRecorded ) {
    digitalWrite(led_startRecording, LOW);
    digitalWrite(led_openProgram, LOW);
    
    digitalWrite(led_reset, HIGH);
    digitalWrite(led_deleteRecording, HIGH);
    digitalWrite(led_saveRecording, HIGH);
    digitalWrite(led_playbackRecording, HIGH);
  }
}

String generateRecordingName(){
  int generated=0;
  String string = "";
  while ( generated < 6 ) {
    byte randomValue = random(0, 26);
    char letter = randomValue + 'a';
    string += letter;
    generated ++;
  }
  return string;
 }

 void resetLeds() {
  digitalWrite(led_startRecording, HIGH);
  digitalWrite(led_openProgram, HIGH);
  digitalWrite(led_reset, HIGH);
  digitalWrite(led_deleteRecording, HIGH);
  digitalWrite(led_saveRecording, HIGH);
  digitalWrite(led_playbackRecording, HIGH);
 }
