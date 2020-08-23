/*
 * SeaLion.h
 *
 *  Created on: Aug 15, 2020
 *      Author: 1503282_snhu
 */

#ifndef WILDLIFEZOOFILES_THEZOO_SRC_SEALION_H_
#define WILDLIFEZOOFILES_THEZOO_SRC_SEALION_H_

#include "Mammal.h"

class SeaLion : public Mammal{
public:
	SeaLion(int t_trackNum, string t_name, string t_type, string t_subType, int t_Nurse);
	virtual ~SeaLion();
};

#endif /* WILDLIFEZOOFILES_THEZOO_SRC_SEALION_H_ */
