/*
 * Animal.cpp
 *
 *  Created on: Aug 15, 2020
 *      Author: 1503282_snhu
 */

#include "Animal.h"

// Constructor
Animal::Animal(int t_trackNum, string t_name, string t_type, string t_subType, int additionalData){
	this->TrackNum = t_trackNum;
	this->name = t_name;
	this->type = t_type;
	this->subType = t_subType;
	this->additionalData = additionalData;
}

//Destructor
Animal::~Animal(){

}


