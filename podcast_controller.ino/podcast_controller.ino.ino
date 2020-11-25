#include <Bounce2.h>

bool readyToRecord = false;
bool recording = false;
bool isRecorded = false;
bool issaveed = false;

const Bounce button_openProgram = Bounce();
const Bounce button_startRecording = Bounce();
const Bounce button_saveRecording = Bounce();
const Bounce button_playbackRecording = Bounce();
const Bounce button_deleteRecording = Bounce();
const Bounce button_reset = Bounce();

const int PIN_openProgram = 10;
const int PIN_startRecording = 11;
const int PIN_stopRecording = 12;
const int PIN_saveRecording = 13;
const int PIN_playbackRecording = 14;
const int PIN_deleteRecording = 15;
const int PIN_reset = 16;

const int led_openProgram = 3;
const int led_startRecording = 4;
const int led_saveRecording = 6;
const int led_playbackRecording = 7;
const int led_deleteRecording = 8;
const int led_reset = 9;

int lights[] = { led_openProgram, led_startRecording, led_saveRecording, led_playbackRecording, led_deleteRecording };
bool isNotOpenLights[sizeof(lights)] = { true, false, false, false, false };
bool readyLights[sizeof(lights)] = { true, true, false, false, false };
bool recordingLights[sizeof(lights)] = { false, true, false, false, false };
bool isRecordedLights[sizeof(lights)] = { true, false, true, true, true, true };

void setup() {
  // put your setup code here, to run once:

  button_openProgram.attach(PIN_openProgram, INPUT);
  button_startRecording.attach(PIN_startRecording, INPUT);
  button_saveRecording.attach(PIN_saveRecording, INPUT);
  button_playbackRecording.attach(PIN_playbackRecording, INPUT);
  button_deleteRecording.attach(PIN_deleteRecording, INPUT);
  button_reset.attach(PIN_reset, INPUT);
  button_openProgram.interval(25);
  button_startRecording.interval(25);
  button_saveRecording.interval(25);
  button_playbackRecording.interval(25);
  button_deleteRecording.interval(25);
  button_reset.interval(25);
  
  pinMode(led_openProgram, OUTPUT);
  pinMode(led_startRecording, OUTPUT);
  pinMode(led_saveRecording, OUTPUT);
  pinMode(PIN_playbackRecording, OUTPUT);
  pinMode(led_deleteRecording, OUTPUT);

  // TEST SEQUENCE - DELTE
  delay(10000); // need to wait after being plugged in to init USB keyboard connection
  
  openProgram();
  delay(5000);
  startRecording();
  delay(4000);
  stopRecording();
  playbackRecording();
  delay(4000);
  saveRecording();
  delay(2000);
  resetEverything();
}

void loop() {
  button_openProgram.interval(25);
  button_startRecording.interval(25);
  button_saveRecording.interval(25);
  button_playbackRecording.interval(25);
  button_deleteRecording.interval(25);
  button_reset.interval(25);

  if ( button_reset.rose() ) {
    resetEverything();
    updateLeds();
  } else if ( button_openProgram.rose() && !recording ) {
    openProgram();
    updateLeds();
  } else if ( button_startRecording.rose() && !recording && readyToRecord ) {
    startRecording();
    updateLeds();
  } else if ( button_startRecording.rose() && recording ) {
    stopRecording();
    updateLeds();
  } else if ( button_playbackRecording.rose() && isRecorded ) {
    playbackRecording();
    updateLeds();
  } else if ( button_deleteRecording.rose() && isRecorded ) {
    deleteRecording();
    updateLeds();
  } else if ( button_saveRecording.rose() && isRecorded ) {
    saveRecording();
    deleteRecording();
    updateLeds();
  }
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

  readyToRecord = false;
  recording = false;
  isRecorded = false;
  issaveed = false;
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
  delay(10000);

  //TODO - might need something here to dismiss a notification

  readyToRecord = true;
  recording = false;
  isRecorded = false;
  issaveed = false;
}

void startRecording() {

  // mute speakers
  Keyboard.press(KEY_MEDIA_MUTE);
  Keyboard.release(KEY_MEDIA_MUTE);

  // create track within reaper
  Keyboard.press(MODIFIERKEY_CTRL);
  Keyboard.press(KEY_T);
  delay(100);
  Keyboard.release(MODIFIERKEY_CTRL);
  Keyboard.release(KEY_T);

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

  // unmute speakers
  Keyboard.press(KEY_MEDIA_MUTE);
  Keyboard.release(KEY_MEDIA_MUTE);

  // unarm track for recording
  // TODO - make a keybinding in the app that responds to CTRL+8 which un arms all tracks for recording
  Keyboard.press(MODIFIERKEY_CTRL);
  Keyboard.press(KEY_8);
  delay(100);
  Keyboard.release(MODIFIERKEY_CTRL);
  Keyboard.release(KEY_8);

  isRecorded = true;
  recording = false;
}

void playbackRecording() {

  Keyboard.press(KEY_SPACE);
  Keyboard.release(KEY_SPACE);
}

void saveRecording() {
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
  String randomString = "Somerandomstring";
  Keyboard.println(randomString);

  // wait for file to finish rendering
  delay(10000); // 10 seconds, might need more

  Keyboard.press(KEY_ENTER);
  Keyboard.release(KEY_ENTER);

  isRecorded = false;
  issaveed = true;
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

  // reaper will want confirmation
  delay(200);
  Keyboard.press(KEY_ENTER);
  Keyboard.release(KEY_ENTER);

  readyToRecord = true;
  recording = false;
  isRecorded = false;
  issaveed = false;
}

void updateLeds() {
  bool boolArr[ sizeof(lights)];

  if ( readyToRecord ) {
    *boolArr = readyLights;
  } else if ( recording ) {
    *boolArr = recordingLights;
  } else if ( isRecorded ) {
    *boolArr = isRecordedLights;
  }

  for ( int i = 0; i < sizeof(lights); i++ ) {
    digitalWrite(lights[i], boolArr[i]);
  }
}
