/*
 * Bat.h
 *
 *  Created on: Aug 15, 2020
 *      Author: 1503282_snhu
 */

#ifndef WILDLIFEZOOFILES_THEZOO_SRC_BAT_H_
#define WILDLIFEZOOFILES_THEZOO_SRC_BAT_H_

#include "Mammal.h"

class Bat : public Mammal {
public:
	Bat(int t_trackNum, string t_name, string t_type, string t_subType, int t_Nurse);
	virtual ~Bat();
};

#endif /* WILDLIFEZOOFILES_THEZOO_SRC_BAT_H_ */
