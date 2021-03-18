// Author: Koosha Hosseiny (https://github.com/hkoosha)
// Program: Parallel printer to type writer
//
// Tested on Epson dot matrix printer LQ-300+
//
// Convert your printer into a type writer! print as you write.
// Theoritically should support all printers that have a LPT port.
//
// Connect stobe pin of parallel port to Arduino pin 11 (defined below).
// Connect data pins 0 to 7 to Arduino pins 3 to 10 (defined below).
// Look at the Parallel_port reference (link below) to find pin numbers
// on a LPT connector.
//
// https://en.wikipedia.org/wiki/Parallel_port
// https://en.wikipedia.org/wiki/ESC/P
// https://files.support.epson.com/pdf/general/escp2ref.pdf
//
//
// Ideas to extend: 
// - Extend and inherit from the Arduino's Print class.
// - Support full set of ESC/P codes.
// - Draw mode to draw ASCII chars above 127 (table chars) easily.
// - Move head/paper commands.
// - Configure on-the-fly by reading pin numbers from Serial port.

const uint8_t DATA_PIN_0 = 3; 
const uint8_t DATA_PIN_1 = 4;
const uint8_t DATA_PIN_2 = 5;
const uint8_t DATA_PIN_3 = 6;
const uint8_t DATA_PIN_4 = 7;
const uint8_t DATA_PIN_5 = 8;
const uint8_t DATA_PIN_6 = 9;
const uint8_t DATA_PIN_7 = 10;

const uint8_t STROBE_PIN = 11;

const uint16_t STROBE_DELAY_MICROS = 2000;
const uint16_t SERIAL_SPEED = 9600;
const uint16_t INITIAL_DELAY_MILLIS = 1000;

const uint8_t EPSON_ESC = 27;
const uint8_t EPSON_ADVANCE_PRINT_POSITION_VERTICALLY = 27;
const uint8_t CHAR_NEW_LINE = '~';
const uint8_t ASCII_NEW_LINE = 13;

void say(const uint8_t c);
void flushBuffer();

void setup() {
  for (int i = 3; i < 12; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }

  delay(INITIAL_DELAY_MILLIS);

  Serial.begin(SERIAL_SPEED);
  Serial.println(__FILE__);
}

bool led = false;
void loop() {
  if(Serial.available() < 1)
    return;

  digitalWrite(LED_BUILTIN, led ? LOW : HIGH);
  led = !led;

  const int read = Serial.read();
  switch(read) {
    case CHAR_NEW_LINE:
      Serial.println();
      say(ASCII_NEW_LINE);
      break;

    default:
      Serial.println(read);
      say(read);
      flushBuffer();
  }
}


void say(const uint8_t c) {
  digitalWrite(DATA_PIN_7, c & 0b10000000);
  digitalWrite(DATA_PIN_6, c & 0b01000000);
  digitalWrite(DATA_PIN_5, c & 0b00100000);
  digitalWrite(DATA_PIN_4, c & 0b00010000);
  digitalWrite(DATA_PIN_3, c & 0b00001000);
  digitalWrite(DATA_PIN_2, c & 0b00000100);
  digitalWrite(DATA_PIN_1, c & 0b00000010);
  digitalWrite(DATA_PIN_0, c & 0b00000001);

  digitalWrite(STROBE_PIN, LOW);
  delayMicroseconds(STROBE_DELAY_MICROS);
  digitalWrite(STROBE_PIN, HIGH);
}

void flushBuffer() {
  // Advancing position by 0 causes a buffer flush.
  // Just found out by trial and error :shrug:
  say(EPSON_ESC);
  say(EPSON_ADVANCE_PRINT_POSITION_VERTICALLY);
  say(0);  
}
