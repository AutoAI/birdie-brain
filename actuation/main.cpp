// main.cpp
// Author: Travis Vanderstad

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "Serial.hpp"

#define GAS_DURATION 1.0
#define BRAKE_DURATION 1.0

using namespace std;

int main() {
	cout << "initializing serial port... ";
	if(Serial::open() < 0) {
		exit(-1);
	}
	cout << "done\n\n";

	cout << "CONTROLS" << endl;
	cout << "gas:\t\tg <0.0 to 1.0>\t\texample: \"g 1.5\"\t" << endl;
	cout << "brakes:\t\tb <0.0 to 1.0>\t\texample: \"b 3.5\"" << endl;
	cout << "steering:\ts <-1.0 (l) to 1.0 (r)>\texample: \"s -2.5\"" << endl;
	cout << "kill:\t\tk\t\t\texample: \"k\"" << endl << endl;

	string temp;
	char control = '\0';
	char value = '\0';
	while(true) {
		// get the next command
		getline(cin, temp);
		control = temp[0];
		if(control == 'k') {
			break;
		}

		value = stof(&temp[2], 0);
		switch(control) {
			case 'g':
				Serial::gas(value);
				usleep(GAS_DURATION * 1000000);
				Serial::gas(0);
				cout << "✓" << endl;
				break;
			case 'b':
				Serial::brake(value);
				sleep(BRAKE_DURATION * 1000000);
				Serial::brake(0);
				cout << "✓" << endl;
				break;
			case 's':
				Serial::steer(value);
				cout << "✓" << endl;
				break;
			default:
				cout << "input not recognized" << endl;
		}
	}
	Serial::brake(1);
	Serial::kill();
	return 0;
}