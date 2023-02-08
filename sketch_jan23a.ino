#include <MotorWheel.h> 
// #include <AltSoftSerial.h>
                  
irqISR(irq1,isr1);                             
MotorWheel wheel1(3,2,4,5,&irq1);
irqISR(irq2,isr2); 
MotorWheel wheel2(11,12,14,15,&irq2); 
irqISR(irq3,isr3); 
MotorWheel wheel3(9,8,0,1,&irq3); 
irqISR(irq4,isr4);
MotorWheel wheel4(10,7,18,19,&irq4);

struct robot{
  float toDeg = 0.0108663;
  float distConst = 3.7;

  void forward(){
    wheel1.runPWM(100, true);
    wheel2.runPWM(100, true);
    wheel3.runPWM(100, false);
    wheel4.runPWM(100, false);
  }  
  void backward(){
    wheel1.runPWM(100, false);
    wheel2.runPWM(100, false);
    wheel3.runPWM(100, true);
    wheel4.runPWM(100, true);
  }
  void rotateRight(){
    wheel1.runPWM(100, true);
    wheel2.runPWM(100, true);
    wheel3.runPWM(100, true);
    wheel4.runPWM(100, true);
  }
  void right(){
    wheel1.runPWM(100, false);
    wheel2.runPWM(100, true);
    wheel3.runPWM(100, true);
    wheel4.runPWM(100, false);
  }
  void rotateLeft(){
    wheel1.runPWM(100, false);
    wheel2.runPWM(100, false);
    wheel3.runPWM(100, false);
    wheel4.runPWM(100, false);
  }
  void left(){
    wheel1.runPWM(100, true);
    wheel2.runPWM(100, false);
    wheel3.runPWM(100, false);
    wheel4.runPWM(100, true);
  }
  void stop(){
    wheel1.runPWM(0, false);
    wheel2.runPWM(0, true);
    wheel3.runPWM(0, true);
    wheel4.runPWM(0, false);
  }
  void diagonalLeft(bool dir){
    if(dir){
      wheel1.runPWM(100, false);
      wheel2.runPWM(0, true);
      wheel3.runPWM(100, true);
      wheel4.runPWM(0, false);
    }else{
      wheel1.runPWM(100, true);
      wheel2.runPWM(0, true);
      wheel3.runPWM(100, false);
      wheel4.runPWM(0, false);     
    }
  }
   void diagonalRight(bool dir){
    if(dir){
      wheel1.runPWM(0, false);
      wheel2.runPWM(100, false);
      wheel3.runPWM(0, true);
      wheel4.runPWM(100, true);
    }else{
      wheel1.runPWM(0, true);
      wheel2.runPWM(100, true);
      wheel3.runPWM(0, false);
      wheel4.runPWM(100, false);     
    }
  }
  void goInMeters(float distance){
    delay(distance*distConst*1000);
  }
  void rotateInDeg(int deg){
    delay(deg*toDeg*1000);
  }
  void stayInSec(int sec){
    stop();
    delay(sec*1000);
  }
};

struct robotFunc{
  robot robot;
  void dorelFunc(){
    robot.forward();
    robot.goInMeters(3);
    robot.stayInSec(5);
    robot.rotateLeft();
    robot.rotateInDeg(180);
    robot.forward();
    robot.goInMeters(3);
    robot.stop();
  }
  void demo(){
    robot.rotateLeft();
    robot.rotateInDeg(180);
    robot.rotateRight();
    robot.rotateInDeg(180);
    robot.right();
    robot.goInMeters(0.4);
    robot.left();
    robot.goInMeters(0.4);    
    robot.forward();
    robot.goInMeters(0.4);
    robot.backward();
    robot.goInMeters(0.4);  
    robot.diagonalLeft(true);
    robot.goInMeters(0.4);  
    robot.diagonalLeft(false);
    robot.goInMeters(0.4);  
    robot.diagonalRight(true);
    robot.goInMeters(0.4);  
    robot.diagonalRight(false);
    robot.goInMeters(0.4); 
    robot.stop(); 
  }
};


// AltSoftSerial altSerial;
// RX, TX
void setup() {
   robotFunc robotFunc;
   robotFunc.demo();
}
  

     



// / Serial.begin(9600);
//   // while (!Serial) ; // wait for Arduino Serial Monitor to open
//   // // Serial.println("AltSoftSerial Test Begin");
//   // altSerial.begin(9600);
//   // altSerial.println("Hello World");



// }
// String inS = "";
void loop(){}

  
//   char c;
 
//   if (altSerial.available()) {
//     inS="";
//     char c = (char)altSerial.read(); 
//     inS += c;  
//     Serial.println(inS);
//     if(c == 'r') {
//       Omni.setCarRight(0);
//       Omni.setCarSpeedMMPS(70,500); 
//       Omni.delayMS(50);
//     }
//     if(c == 'l') {
//       Omni.setCarLeft(0);
//       Omni.setCarSpeedMMPS(70,500); 
//       Omni.delayMS(50);
     
//     }if(c == 'f') {
//       Omni.setCarBackoff(0);
//       Omni.setCarSpeedMMPS(70,500); 
//       Omni.delayMS(50);
     
//     }
//   // Omni.setCarSpeedMMPS(200,500);  
//   //     Omni.delayMS(50);
//   //     Omni.setCarRight(0);
//   //     Omni.setCarSpeedMMPS(200,500); 
//   //     Omni.delayMS(50);
  
  
