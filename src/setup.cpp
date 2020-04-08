/**
 * @file setup.cpp
 *
 * @brief Implementation for Setup and derived classes
 *
 * @author Sergio Boatella Ojeda
 * Contact: sergioboatella@gmail.com
 * 
 */
#include "setup.hpp"

/** Simulates the powermeter D and G, given the battery power and the stored P and C
 *  @param bat Output/input power of battery
 */ 
void Setup::simulate(int battery)
{
    B = battery;
    D = -(P - C);
    G = -P + C - B;
}

Setup::Setup(int P, int C)
{
    this->P = P;
    this->C = C;
}

void Setup::randomize()
{
    P = rand() % 20;
    C = rand() % 15 + 5;
}
 
std::vector < Powermeter > Setup::getAllPowermeters()
{
    std::vector < Powermeter > powermeters;
    powermeters.push_back(std::make_pair('P', P));
    powermeters.push_back(std::make_pair('C', C));
    powermeters.push_back(std::make_pair('D', D));
    powermeters.push_back(std::make_pair('G', G));
    powermeters.push_back(std::make_pair('B', B));
    return powermeters;
}

 /** Calculates the setpoint for this setup 1 
 * 
 *  @param P Power of photovoltaics
 *  @param C Consumption
 *  @return setpoint
 */
int SetupOne::setpoint(int P, int C)
{
    return P - C;
}

int SetupOne::verify()
{
    return P - C + B;
}

int SetupOne::setpoint()
{
    return this->P - this->C;
}

std::vector < Powermeter > SetupOne::getPowermeters()
{
    std::vector < Powermeter > powermeters;
    powermeters.push_back(std::make_pair('P', P));
    powermeters.push_back(std::make_pair('C', C));
    return powermeters;
}

std::string SetupOne::str()
{
    return "Setup 1";
}

 /** Calculates the setpoint for setup 3
 * 1. setpoint = P - C
 * 2. D + P - C = 0
 * 3. D = -P + C = -(P - C) = -setpoint
 * 
 *  @param D Differential
 *  
 *  @return setpoint
 */

int SetupThree::setpoint(int D)
{
    return -D;
}

int SetupThree::setpoint()
{
    return -this->D;
}

std::vector < Powermeter > SetupThree::getPowermeters()
{
    std::vector < Powermeter > powermeters;
    powermeters.push_back(std::make_pair('P', P));
    powermeters.push_back(std::make_pair('D', D));
    return powermeters;
}

int SetupThree::verify()
{
    return D + P - C;
}

std::string SetupThree::str()
{
    return "Setup 3";
}


 /** Calculates the setpoint for this setup 4
 * 1. setpoint = P - C
 * 2. P - C + G + B = 0
 * 3. P - C = - (G + B)
 *
 * NOTE: As setpoint alters B value, in this setup, it takes two iterations of setpoint
 * calculation to correctly set the proper value for B and setpoint.
 *
 * @param G Power at grid connection point.
 * @param B Output/input power of battery. Positive if battery is discharging.
 *  
 * @return setpoint
 */
int SetupFour::setpoint(int G, int B)
{
    return -(G + B);
}

int SetupFour::setpoint()
{
    return -(this->G + this->B);
}

std::vector < Powermeter > SetupFour::getPowermeters()
{
    std::vector < Powermeter > powermeters;
    powermeters.push_back(std::make_pair('P', P));
    powermeters.push_back(std::make_pair('G', G));
    return powermeters;
}

int SetupFour::verify()
{
    return P - C + G + B;
}

std::string SetupFour::str()
{
    return "Setup 4";
}
