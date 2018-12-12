//code from iforce2d found at
//https://www.youtube.com/watch?v=kuBG0U6X7Jw&t=200s
//Video date: Mar 28, 2018

//Modified by LeRoy Miller Dec 7, 2018

/*
 * [m3]artificial Xiaoyan (female, recommended speakers)
 * [m51] man for long time (male, reommended speakers)
 * [m52] pronunciation of many people (male)
 * [m53] pronunciation madeleine human (female)
 * [m54] Donald created artificial pronunciation (effect)
 * [m55] artificial Xu Andy (girls sound)
 * [v1] to [v10] volume from whisper to loud
 * [s1] to [s10] speed from slowly to fast
 * [p?] integer indicating the length of pause in milliseconds
 * [t0] to [t10] tone
 * [x?] 0 speech, 1 sound effect
 * [h?] determine pronunciation of word (0 auto, 1 letters pronunciation way, 2 word pronunciation)
 * [g?] 1 for Chinese, 2 for English - Arabic numerals, units of measure, special symbols
 * [d] reset to defaults
 * [n?] Numbers - 1 read as individual numbers, 2 read as numerical values (one million, one hundred, ect)
 */
 
#include <SoftwareSerial.h>

SoftwareSerial ss(7, 8); // rx, tx

void speak(char* msg) {
  ss.write(0xFD);
  ss.write((byte)0x0);
  ss.write(2 + strlen(msg));
  ss.write(0x01);
  ss.write((byte)0x0);
  ss.write(msg);
}

void waitForSpeech(unsigned long timeout = 60000) {
  unsigned long start = millis();
  bool done = false;
  while ( ! done && (millis() - start) < timeout ) {
    while ( ss.available() ) {
      if ( ss.read() == 0x4F ) {
        done = true;
        break;
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  ss.begin(9600);
}

void loop() {

  char buf[64];

  speak("[d][x0][t6][v5][s6][m51][g2][h2][n1]Hello! I am a XFS5152 speech synthsizer, I will play sounds now.");
  waitForSpeech();

speak("[x0][t6][v5][s6][m51][g2][h2][n1]Message tones.");
waitForSpeech();


  for (int i = 101; i < 126; i++) { // message tones
    sprintf(buf, "[x1]sound%d", i);
    speak(buf);
    waitForSpeech();  
  }
  
  speak("Ring tones.");
  waitForSpeech();
  
  for (int i = 201; i < 226; i++) { // ring tones
    sprintf(buf, "[x1]sound%d", i);
    speak(buf);
    waitForSpeech();  
  }
  
  speak("[m55][t5][n2][s6]Alarm Tones.");
  waitForSpeech();
  
  for (int i = 301; i < 331; i++) { // alarm tones
    sprintf(buf, "[x1]sound%d", i);
    speak(buf);
    waitForSpeech();
  }

  int count = 1;
  while ( count <= 12) {
    sprintf( buf, "[m55][t5][n2][s6]Check %d. Battery is %d percent charged.", count, random(1, 100));
    speak(buf);
    waitForSpeech();
    if ( count++ % 10 == 0 ) {
      speak("[s0]I'm feeling sleepy");
      waitForSpeech();
    }
    delay(1000);
  }
  
 
  speak("[v3]I whisper.[v10]I speak loud.");
  waitForSpeech();
  speak("[s1]I speak really slow.[s8]I can speak really fast.");
  waitForSpeech();
  speak("[s4][m3]I am Xiaoyan an artificial female voice");
  waitForSpeech();
  speak("[m51]I am the Recommended male voice. Called Long Time.");
  waitForSpeech();
  speak("[m52]This is a male voice for many people.");
  waitForSpeech();
  speak("[m53]I am Madeleine, a Female human voice.");
  waitForSpeech();
  speak("[m54]I am Donald a artificial male voice. (duck)?");
  waitForSpeech();
  speak("[m55]I am a Andy an artificial girls voice.");
  waitForSpeech();
  
  speak("[m52][h0][g2]123km 123m 123in 1402");
  waitForSpeech();
  speak("[d][m52][g2][h2][n1]123456789");
  waitForSpeech();
  speak("[d][m53][g2][h2][n2]123456789");
  waitForSpeech();
  while(1);
}



