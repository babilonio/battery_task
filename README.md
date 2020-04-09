
# Exercise Battery Setup

#### Author: Sergio Boatella
## Description
C++ project created to solve the Battery setup excersises.
- Unit tests (Google Test) covering Setup 1, 3 and 4 use cases have been included.
### Application
The developed application starts one of the described setup and dynamically adapts the battery behavior.
- Infinite loop. Display values every 500ms.
- Radomized Photovoltaics and Consumption every 5 loop iterations.
- Battery power set by calculating the setpoint.

## Solution
For all solutions, it has been assumed that power meters are capable of measuring both positive and negative powers.
### Setup 1
As stated in the exercise, there is no need for further calculations if P and C are given, the setpoint will be P minus C.
```c++
/** Calculates the setpoint for this setup 1
*
* @param P Power of photovoltaics
* @param C Consumption
* @return setpoint
*/

int SetupOne::setpoint(int P, int C)
{
	return P - C;
}
```
File: https://github.com/babilonio/battery_task/blob/master/src/setup.cpp

### Setup 3
In this case D is the result of the difference of P and C. If D is positive, it means C is higher than P and the battery must be discharged (therefore, negative setpoint), and viceversa.
```c++
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
```
File: https://github.com/babilonio/battery_task/blob/master/src/setup.cpp

### Setup 4
G powermeter will measure the adition of P, C and B (Battery power), plus the power flowing from/to the grid.

Since the sum of all values (P, C, G, B) must be zero, the set point turns out to be -(G + B).

NOTE: The B value is set as the negative value of the set point. A positive sign on B means that the battery is being discharged.

```c++
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
```
File: https://github.com/babilonio/battery_task/blob/master/src/setup.cpp

## Building and executing instructions
### Requirements
- GCC 4.9

#### Download
Clone the project from repository:
```console
$ git clone https://github.com/babilonio/battery_task
```
NOTE: Google test library is included in project files (lib/googletest)

#### Build
```console
$ cd battery_task
$ ./compile.sh
```
#### Run
```console
$ ./src/battery_task
```
Different setups can be selected via input params in command line:
```console
$ ./src/battery_task 4
```
NOTE: Interrupt execution with CTRL+C.
#### Tests
The Google test library is included but needs to be built (requires CMake).

```console
$ cd lib/googletest && mkdir build && cd build
$ cmake ..
$ make
```
To compile and run unit test:
```console
$ cd battery_task
$ ./run_test.sh
```

## Example output

#### Basic usage
```console
$ ./src/battery_task 4
Randomizing P and C...
P: 3, C: 6, D: 3, G: 3, B: 0, Setup 4
{P: 3, G: 3,  Setpoint: -3} Discharging!

P: 3, C: 6, D: 3, G: 0, B: 3, Setup 4
{P: 3, G: 0,  Setpoint: -3} Discharging!

P: 3, C: 6, D: 3, G: 0, B: 3, Setup 4
{P: 3, G: 0,  Setpoint: -3} Discharging!

P: 3, C: 6, D: 3, G: 0, B: 3, Setup 4
{P: 3, G: 0,  Setpoint: -3} Discharging!

P: 3, C: 6, D: 3, G: 0, B: 3, Setup 4
{P: 3, G: 0,  Setpoint: -3} Discharging!

Randomizing P and C...
P: 17, C: 15, D: -2, G: -5, B: 3, Setup 4
{P: 17, G: -5,  Setpoint: 2} Charging!

P: 17, C: 15, D: -2, G: 0, B: -2, Setup 4
{P: 17, G: 0,  Setpoint: 2} Charging!

P: 17, C: 15, D: -2, G: 0, B: -2, Setup 4
{P: 17, G: 0,  Setpoint: 2} Charging!

P: 17, C: 15, D: -2, G: 0, B: -2, Setup 4
{P: 17, G: 0,  Setpoint: 2} Charging!

P: 17, C: 15, D: -2, G: 0, B: -2, Setup 4
{P: 17, G: 0,  Setpoint: 2} Charging!
```

