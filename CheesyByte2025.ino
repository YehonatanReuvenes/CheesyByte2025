struct pair {
    int first;
    int second;
    pair(int first, int second) : first(first), second(second) {}
};

const int pwmInPinWepond   = 11;
const int pwmInPinDrive_x  = 10;
const int pwmInPinDrive_y  = 9;

const int pwmOutPinWepond     = 5;  
const int pwmOutPinRightWheel = 3;  
const int pwmOutPinLeftWheel  = 6;  

unsigned long pwmWepond, pwmDrive_x, pwmDrive_y;

pair tankDriveOutputs(int x, int y) {
    x = 2 * (x - 127);           
    y = 2 * max(0, y - 127);     

    int right = min(max(0, y - x), 255);
    int left  = min(max(0, y + x), 255);

    return pair(right, left);
}

void setup() {
    pinMode(pwmOutPinWepond, OUTPUT);
    pinMode(pwmOutPinRightWheel, OUTPUT);
    pinMode(pwmOutPinLeftWheel, OUTPUT);

    // (Optional) set input modes if your receiver needs it:
    pinMode(pwmInPinWepond, INPUT);
    pinMode(pwmInPinDrive_x, INPUT);
    pinMode(pwmInPinDrive_y, INPUT);
}

void loop() {
    pwmWepond  = pulseIn(pwmInPinWepond,  HIGH);
    pwmDrive_x = pulseIn(pwmInPinDrive_x, HIGH);
    pwmDrive_y = pulseIn(pwmInPinDrive_y, HIGH);

    pair driveOut = tankDriveOutputs(pwmDrive_x, pwmDrive_y);

    analogWrite(pwmOutPinWepond,     pwmWepond);
    analogWrite(pwmOutPinRightWheel, driveOut.first);
    analogWrite(pwmOutPinLeftWheel,  driveOut.second);
}
