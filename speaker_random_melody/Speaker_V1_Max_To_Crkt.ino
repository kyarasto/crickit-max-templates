// ---- Max sends a MIDI note (36–96) and the Crickit speaker plays a tone ---

#include <Adafruit_CircuitPlayground.h>

const int NOTE_DURATION = 150; // duration of each note in ms 

void setup() {
  Serial.begin(115200);       
  delay(2000);
  CircuitPlayground.begin();

  // enable the speaker
  CircuitPlayground.speaker.enable(true);

  Serial.println("Send a MIDI note 36–96 from Max (0 = silence).");
}

// convert MIDI note number to frequency in Hz
//  freq = 440 * 2^((note – 69) / 12)
float midiToFreq(int note) {
  return 440.0 * pow(2.0, (note - 69.0) / 12.0);
}

void loop() {
  if (Serial.available() > 0) {
    int note = Serial.read();    // read one byte from Max

    if (note == 0) {
      noTone(A0);                // A0 is the CPX speaker
      Serial.println("Silence");
      return;
    }

    float freq = midiToFreq(note);

    // play the tone on pin A0 
    CircuitPlayground.playTone(freq, NOTE_DURATION);

    Serial.print("Note: ");
    Serial.print(note);
    Serial.print("Freq: ");
    Serial.print(freq);
    Serial.println(" Hz");
  }
}
