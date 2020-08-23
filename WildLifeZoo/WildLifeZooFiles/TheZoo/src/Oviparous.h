/*
 * Oviparous.h
 *
 *  Created on: Aug 15, 2020
 *      Author: 1503282_snhu
 */

#ifndef WILDLIFEZOOFILES_THEZOO_SRC_OVIPAROUS_H_
#define WILDLIFEZOOFILES_THEZOO_SRC_OVIPAROUS_H_

#include "Animal.h"

class Oviparous : public Animal{
public:
	Oviparous(int t_trackNum, string t_name, string t_type, string t_subType, int t_NumEggs);
	virtual ~Oviparous();
	int NumEggs;
};



#endif /* WILDLIFEZOOFILES_THEZOO_SRC_OVIPAROUS_H_ */
