#ifndef SETUP_H
#define SETUP_H

#include <iostream>
#include <vector>
#include <utility>

typedef std::pair<char,int> Powermeter;

/** 
 * @class Setup
 * @property P Power of photovoltaics
 * @property C Consumption 
 * @property D Differential (combination of photovoltaics and consumption)
 * @property G Power at grid connection point.
 * @property B Output/input power of battery. Positive if battery is discharging.
 */
 
class Setup{
    protected:
    int P, C, D, G, B;
    
    public:    
    Setup(){};
    Setup(int P, int C);
    
    // Randomize power values of photovoltaics and consumption 
    void randomize();
    
    // Simulates the powermeter D and G, given the battery power and the stored P and C
    void simulate(int bat);
    
    int getP() const{ return P;}
    int getC() const{ return C;}
    int getD() const{ return D;}
    int getG() const{ return G;}
    
    // Returns a vector with all Powermeter values
    std::vector<Powermeter> getAllPowermeters();
    
    // Node power verification function for testing purposes
    virtual int verify() = 0;
    // Calculates setpoint with stored values
    virtual int setpoint() = 0;
    // Str representation
    virtual std::string str() = 0;    
    // Returns a vector with Powermeter values availables in the setup
    virtual std::vector<std::pair<char,int>> getPowermeters() = 0; 
};

/** 
 * @class SetupOne Derives from Setup
 * @brief Powermeters available are P and C
 */
 
class SetupOne : public Setup{
    public:    
    using Setup::Setup;
    
    int setpoint(int P, int C);   
    int setpoint();
    int verify();  
    std::vector<Powermeter> getPowermeters();   
    std::string str();
};

/** 
 * @class SetupThree Derives from Setup
 * @brief Powermeters available are P and D
 */
class SetupThree: public Setup{
    public:
    using Setup::Setup;
    
    int setpoint(int D);   
    int setpoint();
    int verify();  
    std::vector<Powermeter> getPowermeters();   
    std::string str();
};

/** 
 * @class SetupFour Derives from Setup
 * @brief Powermeters available are P and G
 */
class SetupFour: public Setup{    
    public:
    using Setup::Setup;
        
    int setpoint(int G, int B);   
    int setpoint();
    int verify();  
    std::vector<Powermeter> getPowermeters();   
    std::string str();
};

#endif // SETUP_H