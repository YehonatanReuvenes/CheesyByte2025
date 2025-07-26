#include <utility>

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

    std::pair<int, int> driveOut = tankDriveOutputs(pwmDrive_x,pwmDrive_y);
    outRightWheel = driveOut.first;
    outLeftWheel = driveOut.second;
    

    analogWrite(pwmOutPinWepond, outWepond);
    analogWrite(pwmOutPinRightWheel, outRightWheel);
    analogWrite(pwmOutPinLeftWheel, outLeftWheel);
}

std::pair<int, int> tankDriveOutputs(int x, int y) {
    x = 2 * (x - 127)
    y = 2 * max(0, y - 127);

    int right = min(max(0, y - x), 255);
    int left = min(max(0, y + x), 255);

    return {right, left};
}
