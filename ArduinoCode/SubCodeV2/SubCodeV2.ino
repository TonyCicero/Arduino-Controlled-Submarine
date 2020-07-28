#include <AFMotor.h>
#include <arduinoFFT.h>

#define SAMPLES 128
#define SAMPLING_FREQUENCY 4096

arduinoFFT FFT = arduinoFFT();

AF_DCMotor motorR(4); // Right motor
AF_DCMotor motorL(3); // Left motor
AF_DCMotor motorP(1); // Pump motor

unsigned int samplingPeriod;
unsigned long microSeconds;

double vReal[SAMPLES]; //vector to hold real values
double vImag[SAMPLES]; //vector to hold imaginary values

int precision = 100;

void setup() {

  Serial.begin(115200);
  samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY)); //Period in microseconds
  

  motorR.setSpeed(255);
  motorL.setSpeed(255);
  motorP.setSpeed(255);
  motorR.run(RELEASE);
  motorL.run(RELEASE);
  motorP.run(RELEASE);
}

void forward(int speed=255){ //cmd 4; 400hz
  motorR.setSpeed(speed);
  motorL.setSpeed(speed);
  motorR.run(FORWARD);
  motorL.run(FORWARD);
}

void reverse(int speed=255){ //cmd 5; 500hz
  motorR.setSpeed(speed);
  motorL.setSpeed(speed);
  motorR.run(BACKWARD);
  motorL.run(BACKWARD);
}

void right(int speed=255){ //cmd 6; 600hz
  motorL.setSpeed(speed);
  motorR.run(RELEASE);
  motorL.run(FORWARD);
}

void left(int speed=255){ //cmd 7; 700hz
  motorR.setSpeed(speed);
  motorL.run(RELEASE);
  motorR.run(FORWARD);
}

void stopProp(){  //cmd 8; 800hz
  motorR.run(RELEASE);
  motorL.run(RELEASE);
}

void up(int speed=255){ //cmd 9; 900hz
  motorP.setSpeed(speed);
  motorP.run(FORWARD);
}

void down(int speed=255){ //cmd 10; 1000hz
  motorP.setSpeed(speed);
  motorP.run(BACKWARD);
}

void stopPump(){ //cmd 11; 1100hz
  motorP.run(RELEASE);
}

void runCommand(int freq){
  int command = (int)(freq/precision);
  Serial.println(command);
  switch(command){
    case 4:
      forward();
      break;
    case 5:
      reverse();
      break;
    case 6:
      right();
      break;
    case 7:
      left();
      break;
    case 8:
      stopProp();
      break;
    case 9:
      up();
      break;
    case 10:
      down();
      break;
    case 11:
      stopPump();
      break;
    default:
      break;
  }
}

void loop() {

  for(int i=0; i<SAMPLES;i++){
    microSeconds = micros(); //elapsed run time

    vReal[i] = analogRead(0);
    vImag[i] = 0;

    while(micros()<microSeconds+samplingPeriod){
      //Wait between samples if needed
    }
  }

  //Perform FFT on samples
  FFT.Windowing(vReal, SAMPLES,FFT_WIN_TYP_HAMMING,FFT_FORWARD);
  FFT.Compute(vReal,vImag,SAMPLES,FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal,vImag,SAMPLES);

  //Find Peak
  double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
  //Serial.println(peak);
  runCommand(peak);

}
