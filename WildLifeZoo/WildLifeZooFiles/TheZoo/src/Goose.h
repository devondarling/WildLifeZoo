/*
 * Goose.h
 *
 *  Created on: Aug 15, 2020
 *      Author: 1503282_snhu
 */

#ifndef WILDLIFEZOOFILES_THEZOO_SRC_GOOSE_H_
#define WILDLIFEZOOFILES_THEZOO_SRC_GOOSE_H_

#include "Oviparous.h"

class Goose : public Oviparous {
public:
	Goose(int t_trackNum, string t_name, string t_type, string t_subType, int t_NumEggs);
	virtual ~Goose();
};

#endif /* WILDLIFEZOOFILES_THEZOO_SRC_GOOSE_H_ */
