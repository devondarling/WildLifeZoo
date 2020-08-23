/*
 * Oviparous.cpp
 *
 *  Created on: Aug 15, 2020
 *      Author: 1503282_snhu
 */

#include "Oviparous.h"

// Constructor
Oviparous::Oviparous(int t_trackNum, string t_name, string t_type, string t_subType, int t_NumEggs) : Animal (t_trackNum, t_name, t_type, t_subType, t_NumEggs) {
	this->NumEggs = t_NumEggs;
}

// Destructor
Oviparous::~Oviparous(){

}


