int inputPinA = D3;
int inputPinB = D4;
int pirStateA = LOW; 
int pirStateB = LOW;
int valB = 0;
int valA = 0;                    
int LEDA = D0;
int LEDB = D1;
int count = 0;
char publishString[40];

//super descriptive labels for the booleans the sensors flip
boolean A = false;
boolean B = false;

void setup() {
  pinMode(inputPinA, INPUT);
  pinMode(inputPinB, INPUT);
  pinMode(LEDA, OUTPUT);
  pinMode(LEDB, OUTPUT);
  char publishString[40];
  Serial.begin(9600);
  delay(5000);
}

void loop(){
    readTheSensor();
    reportA();
    reportB();
    PushData();
}



void readTheSensor() {
  valA = digitalRead(inputPinA);
  valB = digitalRead(inputPinB);
}

void reportA() {
  if (valA == LOW) {
    if (pirStateA == LOW) {
      //Serial.println("A On");
      digitalWrite(LEDA, HIGH);
      A = true;
      delay(350);
      //Spark.publish("spark-hq/motion");
      pirStateA = HIGH;
    }
  } else {
    if (pirStateA == HIGH) {
      //Serial.println("Motion ended!");
      digitalWrite(LEDA, LOW);
      pirStateA = LOW;
      A = false;
    }
  }
}

void reportB() {
  if (valB == LOW) {
    if (pirStateB == LOW) {
      //Serial.println("B On");
      digitalWrite(LEDB, HIGH);
      B = true;
      delay(350);
      //Spark.publish("spark-hq/motion");
      pirStateB = HIGH;
    }
  } else {
    if (pirStateB == HIGH) {
      //Serial.println("Motion ended!");
      digitalWrite(LEDB, LOW);
      pirStateB = LOW;
      B = false;
    }
  }
}

void PushData() {
    if (A == true) {
        if (B == false) {
            Serial.println("Exit");
            delay(350);
        }
    }
    if (B == true) {
        if (A == false) {
            Serial.println("Enter");
            count = count + 1;
            sprintf(publishString, "%u", count);
            Spark.publish("Count", publishString);
            delay(350);
        }
    }
}
