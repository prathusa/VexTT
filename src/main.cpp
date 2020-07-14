#include "main.h"
using namespace vex;
using namespace std;
double mov = .5;

void read_base()
{
  while(1)
  {
    std::cout 
    << "Time: 10 "
    << Brain.Timer.time(timeUnits::msec) << std::endl
    << "Calc: 11 "
    << robot.base.pid.output << std::endl
    << "PIDPos: 12 "
    << robot.base.pid.position << std::endl
    << "DPos: 13 "
    << d.position(rev) << std::endl
    << "Velocity: 14 "
    << d.velocity(percentUnits::pct) << std::endl
    << "ImuPos: 15 "
    << Inertial.rotation() << std::endl
    << "Error: 16 "
    << robot.base.pid.error << std::endl
    << "Integral: 17 "
    << robot.base.pid.integral << std::endl
    << "Derivative: 18 "
    << robot.base.pid.derivative << std::endl
    << "Pout: 19 "
    << robot.base.pid.Pout << std::endl
    << "Iout: 20 "
    << robot.base.pid.Iout << std::endl
    << "Dout: 21 "
    << robot.base.pid.Dout << std::endl
    // << "Theta Volts: "
    // << robot.base.thetaVolts * 4 << std::endl;
    
    << std::endl;
    this_thread::sleep_for(100);
  }
}

void read_holo()
{
  while(1)
  {
    std::cout 
    << "Time: "
    << Brain.Timer.time(timeUnits::msec) << std::endl
    // << "Calc LF: "
    // << robot.holo.pidLF.output << std::endl
    // << "Calc LR: "
    // << robot.holo.pidLR.output << std::endl
    // << "Calc RF: "
    // << robot.holo.pidRF.output << std::endl
    // << "Calc RR: "
    // << robot.holo.pidRR.output << std::endl
    // << "PIDPos LF: "
    // << robot.holo.pidLF.position << std::endl
    // << "PIDPos LR: "
    // << robot.holo.pidLR.position << std::endl
    // << "PIDPos RF: "
    // << robot.holo.pidRF.position << std::endl
    // << "PIDPos RR: "
    // << robot.holo.pidRR.position << std::endl
    << "DPos: "
    << d.position(rev) << std::endl
    << "LFMPos: "
    << LeftFrontMotor.position(rev) << std::endl
    << "LRMPos: "
    << LeftRearMotor.position(rev) << std::endl
    << "RFMPos: "
    << RightFrontMotor.position(rev) << std::endl
    << "RRMPos: "
    << RightRearMotor.position(rev) << std::endl
    << "Velocity: "
    << d.velocity(percentUnits::pct) << std::endl
    << "ImuPos: "
    << Inertial.rotation() << std::endl
    // << "Error X: "
    // << robot.holo.pidX.error << std::endl
    // << "Error Y: "
    // << robot.holo.pidY.error << std::endl
    // << "Integral X: "
    // << robot.holo.pidX.integral << std::endl
    // << "Integral Y: "
    // << robot.holo.pidY.integral << std::endl
    // << "Derivative X: "
    // << robot.holo.pidX.derivative << std::endl
    // << "Derivative Y: "
    // << robot.holo.pidY.derivative << std::endl
    // << "Pout X: "
    // << robot.holo.pidX.Pout << std::endl
    // << "Pout Y: "
    // << robot.holo.pidY.Pout << std::endl
    // << "Iout X: "
    // << robot.holo.pidX.Iout << std::endl
    // << "Iout Y: "
    // << robot.holo.pidY.Iout << std::endl
    // << "Dout X: "
    // << robot.holo.pidX.Dout << std::endl
    // << "Dout Y: "
    // << robot.holo.pidY.Dout << std::endl
    << "FPS Pos X: "
    << robot.fps.coordinates[0] << std::endl
    << "FPS Pos Y: "
    << robot.fps.coordinates[1] << std::endl

    // << "Theta Volts: "
    // << robot.base.thetaVolts * 4 << std::endl;
    
    << std::endl;
    this_thread::sleep_for(100);
  }
}

void print_pos()
{
  cout << ".";
  cout << "-";
  cout << "|";
  cout << "0";
}

void read_d()
{
  int start = Brain.Timer.time(timeUnits::msec);
  // double data[3000][2]; 
  string data = "";
  string timex = "";
  while(Brain.Timer.time(timeUnits::msec) - start < 3000)
  {
    // std::cout 
    // << "Time: "
    // << Brain.Timer.time(timeUnits::msec) - start << std::endl
    // << "X: "
    // << robot.fps.coordinates[0] << std::endl
    data.append("b"); 
    timex.append("b"); 
    stringstream ss;
    stringstream tt;
    ss << robot.fps.coordinates[1];
    // ss << d.position(rotationUnits::rev);
    tt << Brain.Timer.time(timeUnits::msec) - start;
    string num = ss.str();
    string tim = tt.str();
    data.append(num); 
    timex.append(tim);
    data.append("e");
    timex.append("e");
    // << std::endl

    // int i = Brain.Timer.time(timeUnits::msec) - start;
    // data[i][0] = i;
    // data[i][1] = robot.fps.coordinates[1];

    // << "Theta Volts: "
    // << robot.base.thetaVolts * 4 << std::endl;
    
    // << std::endl;
    this_thread::sleep_for(20);
  }
  cout << data
  << endl
  // << endl
  // << timex
  // << endl
  ;

}

// class arr
// {
//   public:
//   double a[];
// };


// string find_all_from_to(string text, string start, int lenStart, string end, int lenEnd, int gap = 0)
// {
//   int lastIndex = 0;
//   double __list[] = {};
//   int iterations = text.
//   if(start == end)
//   {
//       if Gap > 0 or iterations <= 2:
//           iterations = int(iterations/2)
//       elif iterations%2 == 1:
//           iterations = int(iterations/2)*2
//       else:
//           iterations = iterations-1;
//   }
//   for i in range(iterations):
//       startIndex = Text.index(Start, lastIndex)+LenStart
//       lastIndex = startIndex+1
//       endIndex = Text.index(End, lastIndex)+LenEnd
//       element = Text[startIndex:endIndex]
//       __list.append(element)
//       lastIndex = endIndex+Gap
//   return __list
// }

void data_to_array(string data, int iteration = 0, int start_index = 0)
{
  static string arr[1000];
  int beg = data.find('b', start_index);
  int end = data.find('e', beg);

  if(beg == -1)
  {
    cout << arr;
  }
  else
  {
    arr[iteration] = data.substr(beg, end);
    data_to_array(data, ++iteration, end);
  }
}

// PID_ATune autotune();

int main() 
{
  
  
  // // Run the pre-autonomous function.
  // Inertial.calibrate(2000);
  // vex::task::sleep(2000);
  // pre_auton();
  // Brain.Screen.clearScreen();
  // Brain.Screen.setFont(fontType::mono60);
  // Brain.Screen.setFillColor(RED);
  // cout << "3" << endl;
  // Brain.Screen.print("3");
  // Brain.Screen.clearScreen();
  // vex::task::sleep(100);
  // cout << "2" << endl;
  // Brain.Screen.print("2");
  // Brain.Screen.clearScreen();
  // vex::task::sleep(100);
  // cout << "1" << endl;
  // Brain.Screen.print("1");
  // vex::task::sleep(100);
  // Brain.Screen.clearScreen();
  // cout << "GO!" << endl;
  // Brain.Screen.print("GO!");
      // thread reader = thread(read_d);
      thread reader = thread(read_holo);
      // robot.fps.print();
      // fps.setUpdate(TWO_MOTOR_ENC);
      // fps.print();
      // usercontrol();
  // tune(.03);
//   robot.imu.setPrecise();
//   robot.imu.To(90);
  // robot.base.setIntake();

  // robot.imu.setPrecise();
  // robot.base.setPrecise();
  // Brain.Timer.reset();
  // robot.base.To(1, 90);
  // vex::task::sleep(500);
  // robot.base.To(0, 0);
  // robot.imu.To(90);
  // robot.base.For(1, -90);
  // robot.imu.To(270);
  // robot.base.For(-1);
  // robot.imu.To(180);
  // d.spin(fwd, 20, pct);
  // pre_auton();
  // // thread a = thread(read);
  // usercontrol();
  robot.fps.setUpdate(0);
  double target[] = {0, mov};
  robot.holo.To(target);
  // double inv_target[] = {0, -mov};
  // robot.holo.To(inv_target);
  // cout << "done" << endl;

  // // // Set up callbacks for autonomous and driver control periods.
  // Competition.autonomous(autonomous);
  // Competition.drivercontrol(usercontrol);




  // robot.base.setPrecise();
  // robot.base.To(1, 0);
  // robot.map.frontTo(0, 2);
  // vex::task::sleep(1000);
  // robot.map.frontTo(0, 0);
  // vex::task::sleep(1000);
  // robot.map.frontTo(0, 1);





  // tune(0.05);





















  // Prevent main from exiting with an infinite loop.
  while (1)
  {
    vex::task::sleep(20);
    // Sleep the task for a short amount of time to
    // prevent wasted resources.
  }
}
