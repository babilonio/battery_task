#! /bin/bash
g++ -o tst/setup_test src/setup.cpp tst/setup_test.cpp -std=c++11 -I src/ -L lib/googletest/build/lib/* -lpthread
tst/setup_test