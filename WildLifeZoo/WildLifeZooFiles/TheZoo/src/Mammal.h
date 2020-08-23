/*
 * Mammal.h
 *
 *  Created on: Aug 15, 2020
 *      Author: 1503282_snhu
 */

#ifndef WILDLIFEZOOFILES_THEZOO_SRC_MAMMAL_H_
#define WILDLIFEZOOFILES_THEZOO_SRC_MAMMAL_H_

#include "Animal.h"

class Mammal : public Animal{
public:
	Mammal(int t_trackNum, string t_name, string t_type, string t_subType, int t_Nurse);
	virtual ~Mammal();
	int Nurse;
};


#endif /* WILDLIFEZOOFILES_THEZOO_SRC_MAMMAL_H_ */
