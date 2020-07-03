#pragma once

#define TWO_MOTOR_ENC 0
#define TWO_PARA_SHAFT_ENC 1
#define TWO_PERP_SHAFT_ENC 2
#define ONE_MOTOR_ENC 3
#define ONE_SHAFT_ENC 4
#define THREE_SHAFT_ENC 5

class FPS
{
  private:
  static double pos[2];
  static double dPos[2];
  static double prevPos[2];
  static void printData();
  static void twoMotorEnc();
  static void twoParaShaftEnc();
  static void twoPerpShaftEnc();
  public:
  FPS();
  static double theta;
  static double magnitude;
  static double coordinates[2]; // 0 is X component
                                // 1 is Y component
  void setUpdate(int SETUP_TYPE);
  void print();
  void reset();
};



