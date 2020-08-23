/*
 * Mammal.cpp
 *
 *  Created on: Aug 15, 2020
 *      Author: 1503282_snhu
 */

#include "Mammal.h"

// Constructor
Mammal::Mammal(int t_trackNum, string t_name, string t_type, string t_subType, int t_Nurse) : Animal(t_trackNum, t_name, t_type, t_subType, t_Nurse){
	this->Nurse = t_Nurse;
}

//Destructor
Mammal::~Mammal(){

}
