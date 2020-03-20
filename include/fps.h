#pragma once

#define TWO_MOTOR_ENC 0
#define TWO_SHAFT_ENC 1
#define ONE_MOTOR_ENC 2
#define ONE_SHAFT_ENC 3
#define THREE_SHAFT_ENC 4

class FPS
{
  private:
  static void printData();
  static void twoMotorEnc();
  static void twoShaftEnc();
  public:
  FPS();
  static double theta;
  static double prevPos[2];
  static double dPos[2];
  static double pos[2];
  static double coordinates[2]; // 0 is X component
                                // 1 is Y component
  void setUpdate(int SETUP_TYPE);
  static void print();
};



