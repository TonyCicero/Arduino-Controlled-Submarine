#include <AFMotor.h>

AF_DCMotor motorR(4); // Right motor
AF_DCMotor motorL(3); // Left motor
AF_DCMotor motorP(1); // Pump motor

int val = 0;
int bitRate = 500; // time in millis between each bit
int InstructionLength = 3; //number of bytes per instruction
int By1 = 0;
int By2 = 0;
int By3 = 0;
long wakeupTimer = 0; //time of wakeup bit recieved
long lastTime = 0; // time of last bit
bool recieving = false;
int bitNumber = 0;

/*
 * (Byte 1) Instructions
 *1 = Set //sets motor speed
 *
 * (Byte 2)Device ID
 *1 = MR
 *2 = ML
 *3 = P
 *
 * (Byte 3)Value
*/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(14, INPUT);
  motorR.setSpeed(255);
  motorL.setSpeed(255);
  motorP.setSpeed(255);
  motorR.run(RELEASE);
  motorL.run(RELEASE);
  motorP.run(RELEASE);
}

void processBytes(){
   if (By1 == 1){ //SET
    if(By2 == 1){//MotorR
      motorR.setSpeed(255);
      motorR.run(FORWARD);
    }else if(By2 == 2){//MotorL
      motorL.setSpeed(255);
      motorL.run(FORWARD);
    }else if(By2 == 3){//MotorP
      motorP.setSpeed(255);
      motorP.run(FORWARD);
    }
   }
  
}

void processBit(int b){
  bitNumber++; // which bit was recieved
  Serial.print(" bit: ");
  Serial.print(bitNumber);
  Serial.print(" val: ");
  Serial.print(b);
  Serial.print("\n");
  if(bitNumber <= 8){
    //first Byte
    By1 += (b*pow(2,(bitNumber-1)));
  }else if(bitNumber <= 16){
    //second Byte
    By2 += (b*pow(2,(bitNumber-9)));
  }else if(bitNumber <= 24){
    //second Byte
    By3 += (b*pow(2,(bitNumber-17)));
  }

  if (bitNumber == InstructionLength*8){
    //recieved all 3 bytes
    recieving = false;
    bitNumber = 0;
    processBytes();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(14); // Digital input from sound sensor
  //Serial.print(val);
  if(val == 1 && !recieving){ // first high bit is a wakeup signal
    Serial.print("Wakeup \n");
    wakeupTimer = millis();
    lastTime = wakeupTimer;
    recieving = true;

  }else if(recieving && (millis()-lastTime)>= bitRate ){
    lastTime = millis();
    Serial.print(lastTime);
    processBit(val);
  }
}
