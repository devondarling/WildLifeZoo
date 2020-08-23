/*
 * Animal.h
 *
 *  Created on: Aug 15, 2020
 *      Author: 1503282_snhu
 */

#ifndef WILDLIFEZOOFILES_THEZOO_SRC_ANIMAL_H_
#define WILDLIFEZOOFILES_THEZOO_SRC_ANIMAL_H_

#include <iostream>
using namespace std;

class Animal {
public:
	Animal(int t_trackNum, string t_name, string t_type, string t_subType, int additionalData);
	virtual ~Animal();
	int TrackNum;
	string name;
	string type;
	string subType;
	int additionalData;
};



#endif /* WILDLIFEZOOFILES_THEZOO_SRC_ANIMAL_H_ */
