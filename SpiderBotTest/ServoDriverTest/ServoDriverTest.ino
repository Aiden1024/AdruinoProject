#include <HCPCA9685.h>

#define I2CAdd 0x40

HCPCA9685 HCPCA9685(I2CAdd);

int angle_to_pos(int ang) {
  return map(ang, 0, 180, 0, 450);
}

void setup() {
  // put your setup code here, to run once:
  HCPCA9685.Init(SERVO_MODE);

  HCPCA9685.Sleep(false);

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int Pos;
  unsigned int ang;
  int re_ang = 180 - ang;


  // int init_base_ang = 90;
  // HCPCA9685.Servo(0, angle_to_pos(init_base_ang));
  // HCPCA9685.Servo(1, angle_to_pos(init_base_ang));
  // HCPCA9685.Servo(2, angle_to_pos(init_base_ang));
  // HCPCA9685.Servo(3, angle_to_pos(init_base_ang));  
  // delay(1000);
  // HCPCA9685.Servo(4, angle_to_pos(init_base_ang));
  // HCPCA9685.Servo(5, angle_to_pos(init_base_ang));
  // HCPCA9685.Servo(6, angle_to_pos(init_base_ang));
  // HCPCA9685.Servo(7, angle_to_pos(init_base_ang));  
  // delay(1000);
  // HCPCA9685.Servo(8, angle_to_pos(init_base_ang));
  // HCPCA9685.Servo(9, angle_to_pos(init_base_ang));
  // HCPCA9685.Servo(10, angle_to_pos(init_base_ang));
  // HCPCA9685.Servo(11, angle_to_pos(init_base_ang));  
  // delay(1000);
 
  // for (ang = 80; ang < 120; ang ++) {
  //   HCPCA9685.Servo(4, angle_to_pos(ang));
  //   HCPCA9685.Servo(5, angle_to_pos(180 - ang));
  //   HCPCA9685.Servo(6, angle_to_pos(180- ang));
  //   HCPCA9685.Servo(7, angle_to_pos(ang));
  //   delay(15);
  // }

  // for (ang = 120; ang >= 80; ang --) {
  //   HCPCA9685.Servo(4, angle_to_pos(ang));
  //   HCPCA9685.Servo(5, angle_to_pos(180 - ang));
  //   HCPCA9685.Servo(6, angle_to_pos(180 - ang));
  //   HCPCA9685.Servo(7, angle_to_pos(ang));
  //   delay(15);
  // }

  for (ang = 80; ang < 120; ang ++) {
    re_ang = 180 - ang;
    //servo 0 to 3
    HCPCA9685.Servo(0, angle_to_pos(ang));
    HCPCA9685.Servo(1, angle_to_pos(180 - ang));
    HCPCA9685.Servo(2, angle_to_pos(ang));
    HCPCA9685.Servo(3, angle_to_pos(180 - ang));
    //servo 4 to 7
    HCPCA9685.Servo(4, angle_to_pos(ang));
    HCPCA9685.Servo(5, angle_to_pos(180 - ang));
    HCPCA9685.Servo(6, angle_to_pos(180- ang));
    HCPCA9685.Servo(7, angle_to_pos(ang));
    // servo 8 to 11
    HCPCA9685.Servo(8, angle_to_pos( 180 - ang));
    HCPCA9685.Servo(9, angle_to_pos( 180 - ang));
    HCPCA9685.Servo(10, angle_to_pos( ang));
    HCPCA9685.Servo(11, angle_to_pos(ang));
    delay(15);
  }

  for (ang = 120; ang >= 80; ang --) {
    HCPCA9685.Servo(0, angle_to_pos(ang));
    HCPCA9685.Servo(1, angle_to_pos(180 - ang));
    HCPCA9685.Servo(2, angle_to_pos(ang));
    HCPCA9685.Servo(3, angle_to_pos(180 - ang));
    
    HCPCA9685.Servo(4, angle_to_pos(ang));
    HCPCA9685.Servo(5, angle_to_pos(180 - ang));
    HCPCA9685.Servo(6, angle_to_pos(180 - ang));
    HCPCA9685.Servo(7, angle_to_pos(ang));
    
    HCPCA9685.Servo(8, angle_to_pos( 180 - ang));
    HCPCA9685.Servo(9, angle_to_pos( 180 - ang));
    HCPCA9685.Servo(10, angle_to_pos( ang));
    HCPCA9685.Servo(11, angle_to_pos(ang));
    delay(15);
  }



  // for (Pos = 0; Pos < 450; Pos ++) {
  //   HCPCA9685.Servo(0, Pos);
  //   HCPCA9685.Servo(1, Pos);
  //   HCPCA9685.Servo(2, Pos);
  //   HCPCA9685.Servo(3, Pos);
  //   delay(5);
  // }

  // for (Pos = 450; Pos > 0; Pos --) {
  //   HCPCA9685.Servo(0, Pos);
  //   HCPCA9685.Servo(1, Pos);
  //   HCPCA9685.Servo(2, Pos);
  //   HCPCA9685.Servo(3, Pos);
  //   delay(5);
  // }



}
