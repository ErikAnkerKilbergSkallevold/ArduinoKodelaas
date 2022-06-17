
#include <Keypad.h>
const int RELAY_PIN  = 12; // the Arduino pin, which connects to the IN pin of relay
const int ROW_NUM    = 4; //four rows
const int COLUMN_NUM = 3; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3',},
  {'4', '5', '6',},
  {'7', '8', '9',},
  {'*', '0', '#',}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );
Keypad codeKeypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

String password_1 = "1234"; // change your password here
const String password_2 = "5642";  // change your password here

String input_password;
String input_password_2;

void setup() {
  Serial.begin(9600);
  input_password.reserve(32); // maximum input characters is 33, change if needed
  pinMode(RELAY_PIN, OUTPUT); // initialize pin as an output.
  digitalWrite(RELAY_PIN, HIGH); // lock the door
}

void loop() {

  char key = keypad.getKey();

  if (key) {
    Serial.println(key);

    if (key == '#') {
      Serial.println(password_1);
      Serial.println(input_password);
      if (input_password == password_1) {
        Serial.println("password is correct");
        digitalWrite(RELAY_PIN, LOW);  // unlock the door for 20 seconds
        delay(20000);
        digitalWrite(RELAY_PIN, HIGH); // lock the door
      } else {
        Serial.println("password is incorrect, try again");
      }

      input_password = ""; // reset the input password
    } else if (key == '*') {
      if (input_password == password_2) {
        delay(1000);
        byttPassord();
      } else {
        input_password = "";
        Serial.println("Feil masterpassord");
      }
    } else {
      input_password += key; // append new character to input password string
    }
  }
}


void byttPassord() {
  boolean kjor = true;
  Serial.println("Bytt passord");
  input_password = "";
  input_password_2 = "";
  Serial.println(input_password_2);
  while (kjor) {
    char keyCode = codeKeypad.getKey();
    if (keyCode == '#') {
      password_1 = "";
      password_1 = input_password_2;
      password_1.trim();
      kjor = false;
      Serial.println(input_password_2);
      Serial.println("Passordet er byttet");
    }
    if (keyCode) {
      input_password_2 += keyCode; // append new character to input password string
      Serial.println(keyCode);
      delay(300);
    }
  }
  Serial.println(password_1);
}
