#define LED_BUILTIN_PIN 13

#define NUM_DATA_PINS    8
#define NUM_ADDRESS_PINS 16
#define NUM_CONTROL_PINS 11

#define HALT_PIN   8
#define NMI_PIN    9
#define RESET_PIN 10
#define E_PIN     11
#define Q_PIN     12
//FIXME: bad pin
#define CART_PIN  32

#define RW_PIN    24
#define CTS_PIN   25
#define SND_PIN   26
#define SCS_PIN   27
#define SLENB_PIN 28

int DATA_PINS[]    = {0, 1, 2, 3, 4, 5, 6, 7}; // Might be obvious, but could be reassigned
int ADDRESS_PINS[] = {23,22,21,20,19,18,17,16,15,14,39,38,37,36,35,34};
int CONTROL_PINS[] = {HALT_PIN, NMI_PIN, RESET_PIN, E_PIN, Q_PIN, CART_PIN, RW_PIN, CTS_PIN, SND_PIN, SCS_PIN, SLENB_PIN};

int Q_STATE = LOW;

void setup() {
  // Set all data pins to input
  for(int i=0; i<NUM_DATA_PINS; i++) {
    pinMode(DATA_PINS[i], INPUT);
  }

  // Set all address pins to input
  for(int i=0; i<NUM_ADDRESS_PINS; i++) {
    pinMode(ADDRESS_PINS[i], INPUT);
  }

  // Set all control pins to input
  for(int i=0; i<NUM_CONTROL_PINS; i++) {
    pinMode(CONTROL_PINS[i], INPUT);
  }

  // Initialize serial output so we can see what's happening:

  Serial.begin(9600);

  // Initialize LED for status
  pinMode(LED_BUILTIN_PIN, OUTPUT);

  // Set the builtin LED to high to say we are ready
  digitalWrite(LED_BUILTIN_PIN, HIGH);
 

}

void loop() {

  int currentQ = digitalReadFast(Q_PIN);
  if(currentQ == HIGH) {
    if(Q_STATE == LOW) {
      Q_STATE = HIGH;

      // Rising edge
      uint16_t bus_address = 0;
      for(int i = 0; i < NUM_ADDRESS_PINS; i++) {
        bus_address = bus_address | (digitalReadFast(ADDRESS_PINS[i]) << (15-i));
      }
      if(bus_address == 65341) {
        Serial.println(bus_address);
        Serial.flush();
      }
      
    }
    
  }
  else {
    Q_STATE = LOW;
  }



}
