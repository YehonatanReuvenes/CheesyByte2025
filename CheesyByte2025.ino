const int pwmInPinWepond = 1;
const int pwmInPinDrive_x = 1;
const int pwmInPinDrive_y = 1;

const int pwmOutPinWepond = 1;
const int pwmOutPinRightWheel = 1;
const int pwmOutPinLefttWheel = 1;

unsigned long pwmWepond, pwmDrive_x, pwmDrive_y;

void setup(){
    pinMode(pwmOutPinWepond, OUTPUT);
    pinMode(pwmOutPinRightWheel, OUTPUT);
    pinMode(pwmOutPinLefttWheel, OUTPUT);
}

void loop(){
    pwmWepond = pulseIn(pwmInPinWepond, HIGH);
    pwmDrive_x = pulseIn(pwmInPinDrive_x, HIGH);
    pwmDrive_y = pulseIn(pwmInPinDrive_y, HIGH);

    int outWepond, outRightWheel, outLeftWheel;

    analogWrite(pwmOutPinWepond, outWepond);
    analogWrite(pwmOutPinRightWheel, outRightWheel);
    analogWrite(pwmOutPinLeftWheel, outLeftWheel);
}