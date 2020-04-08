/**
 * @file sonnen_test.cpp
 *
 * @brief Unit tests for Battery Task
 *
 * @author Sergio Boatella Ojeda
 * Contact: sergioboatella@gmail.com
 */
#include <gtest/gtest.h>
#include "setup.hpp"


void base_test(Setup& test_setup, int calculated_setpoint){
    
    int expected_setpoint = test_setup.getP() - test_setup.getC();
    
    int battery_power =  -calculated_setpoint;
    test_setup.simulate(battery_power);
    
    ASSERT_EQ(expected_setpoint, calculated_setpoint);
    ASSERT_EQ(0, test_setup.verify());
}

void base_setup_one_test(int P_test, int C_test){
    SetupOne test_setup(P_test, C_test);  
    int calculated_setpoint = test_setup.setpoint(P_test, C_test);
    
    base_test(test_setup, calculated_setpoint);
}

void base_setup_three_test(int P_test, int C_test){
    SetupThree test_setup(P_test, C_test);    
    int D_test = C_test - P_test;
    int calculated_setpoint = test_setup.setpoint(D_test);
    
    base_test(test_setup, calculated_setpoint);
}

// Setup 4 takes two iterations of setpoint calculation to adapt
void base_setup_four_test(int P_test, int C_test){
    
    int B_test = 0;
    
    SetupFour test_setup(P_test, C_test);
    int G_test = - P_test + C_test - B_test;
    int calculated_setpoint = test_setup.setpoint(G_test, B_test);
        
    B_test = -calculated_setpoint;
    G_test = - P_test + C_test - B_test;
    calculated_setpoint = test_setup.setpoint(G_test, B_test);
    
    base_test(test_setup, calculated_setpoint);
    ASSERT_EQ(0, G_test);
}

// P higher than C
TEST(BatteryTask, SetupCase1)
{    
    int P_test = 20;
    int C_test = 10;    
    base_setup_one_test(P_test, C_test);  
    base_setup_three_test(P_test, C_test);    
    base_setup_four_test(P_test, C_test);   
}

// C higher than P
TEST(BatteryTask, SetupCase2)
{
    int P_test = 10;
    int C_test = 20;
    base_setup_one_test(P_test, C_test);  
    base_setup_three_test(P_test, C_test);
    base_setup_four_test(P_test, C_test);   
}

// C and P are equals
TEST(BatteryTask, SetupCase3)
{
    int P_test = 20;
    int C_test = 20;
    base_setup_one_test(P_test, C_test);  
    base_setup_three_test(P_test, C_test);
    base_setup_four_test(P_test, C_test);   
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}