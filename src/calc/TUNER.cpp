#include "main.h"
using namespace std;

bool t1 = false;
bool t2 = false;
bool t3 = false;
int run = 1;
double dist = 1;
double angle = 0;
bool tperfect = true;
double k[3] = {10, 1.5, 0.05}; //12, 2, .1 //10, 1.5, 0.06 //12, 1.48074, 0.101605 //12, 1.48074, 0.108856
double k2[3] = {0, 0, 0};
// std::ofstream outFile;

int tune(double tolerance)
{
  robot.to.pid.setPID(k[0], k[1], k[2]);
  // robot.to.pidTheta.setPID(k2[0], k2[1], k2[2]);
  // thread save_data_thread = thread(saveData);
  robot.to.update(feature::Coordinate(0, 1, 0, 0, feature::Coordinate::rotationType::DEG));
  // outFile.close();
  if(abs(robot.to.pid.error) > tolerance) //robot.to.pid.error is a place holder for 
  {
    double errRatio = robot.to.pid.position/robot.to.pid.target;
    if(abs(errRatio) > 1) //checks if the bot overshoot the target
    {
      if(abs(errRatio) > 1.10)
      {
        if(!t1)
        {
          k[0] = k[0] - k[0]*(errRatio-1)/20;
          tperfect = true;
        }
        else
        {
          k[1] = k[1] - k[1]*(errRatio-2)/20;
          tperfect = false;
        }
      }
      else
      {
        k[2] = k[2] + k[2]*(errRatio-1)/5;
        if(!t1)
          tperfect = true;
        else
          tperfect = false;
      }
    }
    else 
    {
      if(abs(errRatio) < .90)
      {
        if(!t1)
        {
          k[0] = k[0] + k[0]*(errRatio-1)/20;
          tperfect = true;
        }
        else
        {
          k[1] = k[1] + k[1]*(errRatio-2)/20;
          tperfect = false;
        }
      }
      else
      {
        k[2] = k[2] - k[2]*(errRatio-1)/20;
        if(!t1)
          tperfect = true;
        else
          tperfect = false;
      }
    }
    if(robot.to.pid.position + abs(dist) < 3)
      dist = abs(dist);
    else if(robot.to.pid.position - abs(dist) > 0)
      dist = -abs(dist);
    else
    {
      robot.to.update(feature::Coordinate());
      vex::task::sleep(500);
      dist = abs(dist);
    }
    cout << "k[0]: " << k[0] << " on dist: " << dist << " with error " << robot.to.pid.error << " at pos " << robot.to.pid.position << " [ Failed X ]" << endl;
    cout << "k[1]: " << k[1] << " on dist: " << dist << " with error " << robot.to.pid.error << " at pos " << robot.to.pid.position << " [ Failed X ]" << endl;
    cout << "k[2]: " << k[2] << " on dist: " << dist << " with error " << robot.to.pid.error << " at pos " << robot.to.pid.position << " [ Failed X ]" << endl << endl;
    // cout << "k2[0]: " << k2[0] << " [Failed]" << endl;
    // cout << "k2[1]: " << k2[1] << " [Failed]" << endl;
    // cout << "k2[2]: " << k2[2] << " [Failed]" << endl;
    run = 1;
  }
  else
  {
    if(t1 && t2 && t3 && tperfect && run > 3)
    {
      cout << "k[0]: " << k[0] << " [ Complete ! ]" << endl;
      cout << "k[1]: " << k[1] << " [ Complete ! ]" << endl;
      cout << "k[2]: " << k[2] << " [ Complete ! ]" << endl << endl;
      // cout << "k2[0]: " << k2[0] << " [OK]" << endl;
      // cout << "k2[1]: " << k2[1] << " [OK]" << endl;
      // cout << "k2[2]: " << k2[2] << " [OK]" << endl;
      return 1; //kill statement
    }
    else if(t1 && t2 && t3 && tperfect)
    {
      t1 = false;
      t2 = false;
      t3 = false;
      cout << "k[0]: " << k[0] << " [ Round " << run << " ] [ Passed ! ]" << endl;
      cout << "k[1]: " << k[1] << " [ Round " << run << " ] [ Passed ! ]" << endl;
      cout << "k[2]: " << k[2] << " [ Round " << run << " ] [ Passed ! ]" << endl << endl;
      run++;
    }
    else if(t1 && t2 && t3)
    {
      t1 = false;
      t2 = false;
      t3 = false;
      cout << "k[0]: " << k[0] << " [ Verifying... ]" << endl;
      cout << "k[1]: " << k[1] << " [ Verifying... ]" << endl;
      cout << "k[2]: " << k[2] << " [ Verifying... ]" << endl << endl;
    }
    else if(abs(dist) == 1)
    {
      dist = 2;
      cout << "k[0]: " << k[0] << " [ Check 1 ] [ OK ! ]" << endl;
      cout << "k[1]: " << k[1] << " [ Check 1 ] [ OK ! ]" << endl;
      cout << "k[2]: " << k[2] << " [ Check 1 ] [ OK ! ]" << endl << endl;
      t1 = true;
      tperfect = true;
    }
    else if(abs(dist) == 2)
    {
      dist = 3;
      cout << "k[0]: " << k[0] << " [ Check 2 ] [ OK ! ]" << endl;
      cout << "k[1]: " << k[1] << " [ Check 2 ] [ OK ! ]" << endl;
      cout << "k[2]: " << k[2] << " [ Check 2 ] [ OK ! ]" << endl << endl;
      t2 = true;
    }
    else if(abs(dist) == 3)
    {
      dist = 1;
      cout << "k[0]: " << k[0] << " [ Check 3 ] [ OK ! ]" << endl;
      cout << "k[1]: " << k[1] << " [ Check 3 ] [ OK ! ]" << endl;
      cout << "k[2]: " << k[2] << " [ Check 3 ] [ OK ! ]" << endl << endl;
      t3 = true;
    }
    if(robot.to.pid.position + abs(dist) < 3)
      dist = abs(dist);
    else if(robot.to.pid.position - abs(dist) > 0)
      dist = -abs(dist);
    else
    {
      robot.to.update(feature::Coordinate());
      dist = abs(dist);
    }
  }
  vex::task::sleep(500);
  tune(tolerance);
  return 0;
}

// void saveData()
// {
//   outFile.open("tuner.txt");
//   while(1)
//   {
//     outFile << "Time: 10 ";
//     outFile << Brain.Timer.time(timeUnits::msec) << std::endl;
//     outFile << "Calc: 11 ";
//     outFile << robot.to.pid.output << std::endl;
//     outFile << "PIDPos: 12 ";
//     outFile << robot.to.pid.position << std::endl;
//     outFile << "DPos: 13 ";
//     outFile << d.position(rev) << std::endl;
//     outFile << "Velocity: 14 ";
//     outFile << d.velocity(percentUnits::pct) << std::endl;
//     outFile << "ImuPos: 15 ";
//     outFile << Inertial.rotation() << std::endl;
//     outFile << "Error: 16 ";
//     outFile << robot.to.pid.error << std::endl;
//     outFile << "Integral: 17 ";
//     outFile << robot.to.pid.integral << std::endl;
//     outFile << "Derivative: 18 ";
//     outFile << robot.to.pid.derivative << std::endl;
//     outFile << "Pout: 19 ";
//     outFile << robot.to.pid.Pout << std::endl;
//     outFile << "Iout: 20 ";
//     outFile << robot.to.pid.Iout << std::endl;
//     outFile << "Dout: 21 ";
//     outFile << robot.to.pid.Dout << std::endl;
//     outFile << std::endl;
//     this_thread::sleep_for(20);
//   }
// }