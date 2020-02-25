//VEX_H
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include "v5_vcs.h"
#include "robot-config.h"
#include "usercontrol.h"
#include "record.h"
#include "controls.h"
#include "play.h"
#include "manual.h"
#include "drivefunctions.h"
#include "autonomous.h"
#include "gui.h"
#include "ACCESS_OS.h"

//port 3&4&10&11 ded
extern ACCESS_OS os;
extern IMU imu;
extern BASE_DRIVE base;
extern MECH_DRIVE mech;
extern bot::ROBOT robot;