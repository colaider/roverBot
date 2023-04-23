#include <MotorWheel.h> 
// #include <AltSoftSerial.h>
#include <Wire.h>              
irqISR(irq1,isr1);                             
MotorWheel wheel1(3,2,4,5,&irq1);
irqISR(irq2,isr2); 
MotorWheel wheel2(11,12,14,15,&irq2); 
irqISR(irq3,isr3); 
MotorWheel wheel3(9,8,0,1,&irq3); 
irqISR(irq4,isr4);
MotorWheel wheel4(10,7,18,19,&irq4);

struct robot{
  float toDeg = 0.0064363;
  float distConst = 3.7;
  int speed;

  void setSpeed(int speedSet){
    speed = speedSet;
  }
  
  int getData1(){
   pinMode(13,INPUT);
   return(digitalRead(13));
  }
  int detector(){
    pinMode(11,INPUT);
    return(digitalRead(11));    
  }
  void comunication(int b){
   pinMode(6, OUTPUT);
   if(b){
    digitalWrite(6, HIGH);
   }else{
     digitalWrite(6, LOW);
   }
  }
  void getData(){
    Serial.println(wheel1.getPWM());     
  }

  void forward(){
    wheel1.runPWM(speed, true);
    wheel2.runPWM(speed, true);
    wheel3.runPWM(speed, false);
    wheel4.runPWM(speed, false);
    getData();
  }  
  void backward(){
    wheel1.runPWM(speed, false);
    wheel2.runPWM(speed, false);
    wheel3.runPWM(speed, true);
    wheel4.runPWM(speed, true);
    getData();
  }
  void rotateRight(){
    wheel1.runPWM(speed, true);
    wheel2.runPWM(speed, true);
    wheel3.runPWM(speed, true);
    wheel4.runPWM(speed, true);
    getData();
  }
  void right(){
    wheel1.runPWM(speed, false);
    wheel2.runPWM(speed, true);
    wheel3.runPWM(speed, true);
    wheel4.runPWM(speed, false);
    getData();
  }
  void rotateLeft(){
    wheel1.runPWM(speed, false);
    wheel2.runPWM(speed, false);
    wheel3.runPWM(speed, false);
    wheel4.runPWM(speed, false);
    getData();
  }
  void left(){
    wheel1.runPWM(speed, true);
    wheel2.runPWM(speed, false);
    wheel3.runPWM(speed, false);
    wheel4.runPWM(speed, true);
    getData();
  }
  void stop(){
    wheel1.runPWM(0, false);
    wheel2.runPWM(0, true);
    wheel3.runPWM(0, true);
    wheel4.runPWM(0, false);
    getData();
  }
  void diagonalLeft(bool dir){
    getData();
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
     getData();
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
    robot.setSpeed(20);
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
  void projecScript(int deg){
    int k = deg/2;    
    for(int i = 0;i<=k;i+=k/10+1){
      robot.setSpeed(i+10);
      robot.rotateRight();
      robot.rotateInDeg(k/i+10);
    }
    for(int i = k;i>=0;i-=k/10+1){
      robot.setSpeed(i+10);
      robot.rotateRight();
      robot.rotateInDeg(k/i+10+1);
    }
    robot.stop();
    delay(500);
    for(int i = 0;i<=k;i+=k/10+1){
      robot.setSpeed(i+11);
      robot.rotateLeft();
      robot.rotateInDeg(k/i+10);
    }
    for(int i = k;i>=0;i-=k/10+1){
      robot.setSpeed(i+11);
      robot.rotateLeft();
      robot.rotateInDeg(k/i+10);
    }
    robot.stop();
    delay(50);
    robot.comunication(1);
    delay(100);
    robot.comunication(0);
  }
};

void setup() {
  Wire.begin(); 
  Serial.begin(9600);
}
void loop(){
  robot robot1;
  robotFunc robotFunc;
  Serial.println(robot1.getData1());
  robot1.comunication(0);
  int a = robot1.getData1();
  Serial.println(a);
  if(robot1.getData1()==1){
   robotFunc.projecScript(460);
  }
  // robotFunc.projecScript(460);
  // delay(1000);
 
}


  
  
