/*
 * Crocodile.h
 *
 *  Created on: Aug 15, 2020
 *      Author: 1503282_snhu
 */

#ifndef WILDLIFEZOOFILES_THEZOO_SRC_CROCODILE_H_
#define WILDLIFEZOOFILES_THEZOO_SRC_CROCODILE_H_

#include "Oviparous.h"

class Crocodile : public Oviparous{
public:
	Crocodile(int t_trackNum, string t_name, string t_type, string t_subType, int t_NumEggs);
	virtual ~Crocodile();
};

#endif /* WILDLIFEZOOFILES_THEZOO_SRC_CROCODILE_H_ */
