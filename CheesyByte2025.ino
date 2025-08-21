#include <Servo.h>

const int IN_PIN_WEPOND   = 11;
const int IN_PIN_X  = 9;
const int IN_PIN_Y  = 10;

const int OUT_PIN_WEPOND = 6;  
const int OUT_PIN_RIGHT_WHEEL = 3;  
const int OUT_PIN_LEFT_WHEEL  = 5;  

const int MAX_SPEED = 100;
const double RIGHT_ADAPTATION = 1;
const double LEFT_ADAPTATION = 0.5;


struct Arcade{
  double azi;
  double lat;
};

struct Tank{
  double right;
  double left;

  void update(Arcade inputs){
    if (inputs.azi == 0 && inputs.lat == 0){
      right = 1000;
      left = 1000;
      return;
    }
    right = inputs.lat - inputs.azi;
    left = inputs.lat + inputs.azi;
    double high = max(right, left);
    if(high > 1){
      right = right / high;
      left = left / high;
    }

    right *= RIGHT_ADAPTATION;
    left *= LEFT_ADAPTATION;

    right = right * MAX_SPEED * 10 + 1000;
    left = left * MAX_SPEED * 10  + 1000;
    right = max(1000, min(1000 + MAX_SPEED * 10, right));
    left = max(1000, min(1000 + MAX_SPEED * 10, left));
  }
};

Servo motorWepond;
Servo motorRight;
Servo motorLeft;
Tank tank;
Arcade arcade;

void setup() {
  pinMode(IN_PIN_WEPOND, INPUT);
  pinMode(IN_PIN_X, INPUT);
  pinMode(IN_PIN_Y, INPUT);

  motorWepond.attach(OUT_PIN_WEPOND);
  motorRight.attach(OUT_PIN_RIGHT_WHEEL);
  motorLeft.attach(OUT_PIN_LEFT_WHEEL);

  motorWepond.writeMicroseconds(2000);
  motorRight.writeMicroseconds(2000);
  motorLeft.writeMicroseconds(2000);
  delay(3000);
  motorWepond.writeMicroseconds(1000);
  motorRight.writeMicroseconds(1000);
  motorLeft.writeMicroseconds(1000);

  Serial.begin(9600); 

  // motorRight.writeMicroseconds(2000);
  // motorLeft.writeMicroseconds(2000);
  // delay(4000);
  // //   motorRight.writeMicroseconds(1000);
  // motorLeft.writeMicroseconds(1000);
  // delay(4000);

}

void loop() {
  int inDrive_x = pulseIn(IN_PIN_X, HIGH, 25000);
  int inDrive_y = pulseIn(IN_PIN_Y, HIGH, 25000);
  
  arcade.azi = max(-1, min(1, (inDrive_x / 500.0) - 3));
  arcade.lat = max(0, min(1, (inDrive_y / 500.0) - 3));

  if(inDrive_x == 1000.0 || inDrive_y == 1000.0){
    arcade.azi = 0;
    arcade.lat = 0;
  }

  tank.update(arcade);


  int inWepond = roundTo25(pulseIn(IN_PIN_WEPOND, HIGH, 25000));
  int outWepond = max(1000, min(2000, inWepond));
  if(inWepond == 1075 || inWepond == 1050){
    outWepond = 1000;
  }

  
  motorWepond.writeMicroseconds(outWepond);
  motorRight.writeMicroseconds(tank.right);
  motorLeft.writeMicroseconds(tank.left);

  // Serial.print(inWepond);
  // Serial.print(", ");
  // Serial.print(inDrive_x);
  // Serial.print(", ");
  // Serial.println(inDrive_y);

  // Serial.print(outWepond);
  // Serial.print(", ");
  // Serial.print(tank.right);
  // Serial.print(", ");
  // Serial.println(tank.left);

  // Serial.print(arcade.azi);
  // Serial.print(", ");
  // Serial.println(arcade.lat);

  // Serial.println();
  // Serial.println();
  // Serial.println();


  delay(25);
}

int roundTo25(int n) {
    return (n >= 0) ? ((n + 12) / 25) * 25 : ((n - 12) / 25) * 25;
}
