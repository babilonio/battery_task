/**
 * @file main.cpp
 *
 * @brief Main function for sonnen task application
 *
 * @author Sergio Boatella Ojeda
 * Contact: sergioboatella@gmail.com
 *
 */  
 
#include <iostream>
#include <unistd.h>
#include <memory>
#include "setup.hpp" 

using namespace std;

int main(int argc, char *argv[]) 
{    
    std::shared_ptr<Setup> setup;
    if(argc==1) {
        setup = make_shared<SetupOne>();
        cout << endl << "Default setup: Setup 1" << endl << endl;
    }
    else{
        switch( atoi(argv[1])){
            case 1:
                setup = make_shared<SetupOne>();
                break;
            case 3:
                setup = make_shared<SetupThree>();
                break;
            case 4:
                setup = make_shared<SetupFour>();
                break;
            default:
                cerr << "Setup " << argv[1] << " is not implemented" << endl;
                return -1;
        }
    }
    
    cout << "Randomizing P and C..." << endl;
    setup->randomize();
    int battery_power = 0;
    
    int counter = 0;
    while(true){
        
        setup->simulate(battery_power);        
        
        int setpoint = setup->setpoint();
        battery_power = -setpoint;
        
        for (auto e: setup->getAllPowermeters()){
            cout << e.first << ": " << e.second << ", ";
        }
        cout << setup->str() << endl;
        
        string charging_str = (setpoint > 0) ? "Charging!":"Discharging!";        
        cout << "{";
        for (auto e: setup->getPowermeters()){
            cout << e.first << ": " << e.second << ", ";
        }        
        cout << " Setpoint: " << setpoint << "} " << charging_str << endl << endl;
        
        
        counter++;
        if (counter % 5 == 0){
            cout << "Randomizing P and C..." << endl;
            setup->randomize();
        }        
        usleep(500000);
    }
    
    return 0;
}