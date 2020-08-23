#include <iostream>
#include <string>
#include <jni.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "Animal.h"
#include "Oviparous.h"
#include "Mammal.h"
#include "Crocodile.h"
#include "Goose.h"
#include "Pelican.h"
#include "Bat.h"
#include "Whale.h"
#include "SeaLion.h"

using namespace std;

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}

/**
 * Params t_number
 *
 * Converts an int to a string
 *
 * Return string
 */
string NumberToString(int t_number) {
	ostringstream stringStream;
	stringStream << t_number;
	return stringStream.str();
}

/**
 * Params t_string
 *
 * Converts string to int
 *
 * Return int
 */
int StringToNumber(string t_string) {
	try {
		int number = stoi(t_string);
		return number;
	}
	catch (invalid_argument &excpt) {
		cout << "Invalid animal data. Select Display Animal Data from the menu.\n"
				"Then, select Delete Record to remove the invalid data to continue." << excpt.what() << "\n";
	}
}

 void DisplayAnimalData(vector<Animal>& t_animalsList) {

	cout << left << setw(6) << "Track#" << " "
			<< left << setw(15) << "Name" << "  "
			<< left << setw(15) << "Type" << "  "
			<< left << setw(15) << "Sub-Type" << "  "
			<< left << setw(1) << "Eggs" << "  "
			<< left << setw(1) << "Nurse" << "  " << endl;

	if (t_animalsList.size() > 0) {
		for (unsigned int i = 0; i < t_animalsList.size(); ++i) {
			Animal animal = t_animalsList.at(i);
			string animalAttributes;
			ostringstream animalAttr;

			animalAttr << right << setfill('0') << setw(6) << animal.TrackNum << " ";
			animalAttr << left << setw(15) << setfill(' ') << animal.name << "  "
					<< left << setw(15) << animal.type << "  "
					<< left << setw(15) << animal.subType << "  ";
			auto padded{ animalAttr.str() };

			animalAttributes += padded;
			if (animal.type == "Mammal") {
				animalAttributes += "0     " + NumberToString(animal.additionalData); // Nurse
			}
			else {
				animalAttributes += NumberToString(animal.additionalData) + "     0"; // Eggs
			}

			cout << animalAttributes << "\n";
		}
	}
	else {
		cout << "\nSelect Load Animal Data from the menu to view current animals on file.\n\n";
	}
 }

/**
 * Params t_animalsList
 *
 * Adds Animal from vector
 */
void AddAnimal(vector<Animal>& t_animalsList)
{
	int trackNumber;
	string animalName;
	string animalType;
	string subType;
	int numEggs;
	int nurse;
	char yKey;

	cout << "Track Number: ";
	cin >> setw(6) >> trackNumber;

	if (!cin) {
		throw runtime_error("Numbers only. Please try again. \n");
	}

	cout << "Enter Animal Name: ";
	cin >> setw(15) >> animalName;

	if (!cin) {
		throw runtime_error("Entry not acceptable. Please try again. \n");
	}

	cout << "Enter Animal Type: ";
	cin >> setw(15) >> animalType;

	if (!cin) {
		throw runtime_error("Entry not acceptable. Please try again. \n");
	}

	cout << "Enter Animal Sub-type: ";
	cin >> setw(15) >> subType;

	if (!cin) {
		throw runtime_error("Entry not acceptable. Please try again. \n");
	}

	cout << "Enter Number of Eggs: ";
	cin >> setw(1) >> numEggs;

	if (!cin) {
		throw runtime_error("Numbers only. Please try again. \n");
	}

	cout << "Enter 1 if Nursing, 0 if not: ";
	cin >> setw(1) >> nurse;

	if (!cin) {
		throw runtime_error("Numbers only. Please try again. \n");
	}

	cout << "Save data? (Y for yes)";
	cin >> yKey;
	yKey = toupper(yKey);

	if (yKey == 'Y') {

		int counter = 0;
		for (unsigned int i = 0; i < t_animalsList.size(); ++i) {
			Animal animalInVector = t_animalsList.at(i);
			if (trackNumber == animalInVector.TrackNum) {	// Check to see if track num already exists in array
				++counter; // Increment if duplicate record
			}
		}

		if (counter == 0){ // Add only unique animals to vector
			if (animalType == "Mammal") {
				Animal newAnimal(trackNumber, animalName, "Mammal", subType, nurse);
				t_animalsList.push_back(newAnimal);
			}
			else if (animalType == "Oviparous"){
				Animal newAnimal(trackNumber, animalName, "Oviparous", subType, numEggs); // Eggs
				t_animalsList.push_back(newAnimal);
			}
			else {
				Animal newAnimal(trackNumber, animalName, animalType, subType, 0); // Generic Animal, can edit later
				t_animalsList.push_back(newAnimal);
			}

			cout << "\nAnimal successfully added \n" << endl;
		}
		else {
			cout << "\nTrack number already exists. Animal not saved.\n"
					"Review existing Animal track numbers and try again." << endl;
		}
	}
	else {
		cout << "\nAnimal not saved \n" << endl;
	}
}

/**
 * Params t_animalsList
 *
 * Removes Animal from vector
 */
void RemoveAnimal(vector<Animal>& t_animalsList)
{
	cout << "To delete a record enter six-digit Track number" << endl;

	int trackNumber;
	cin >> trackNumber;

	// Input validation
	if (!cin || trackNumber < 000001 || trackNumber > 999999) {
		throw runtime_error("\nSelection not recognized. Please try again. \n");
	}

	for (unsigned int i = 0; i < t_animalsList.size(); ++i) {
		Animal animalInVector = t_animalsList.at(i);

		if (animalInVector.TrackNum == trackNumber) {
			cout << "Are you sure you want to delete this record? Select 'Y' to continue. " << endl;

			char answer;
			cin >> answer;
			answer = toupper(answer);

			if (answer == 'Y') {
				t_animalsList.erase(t_animalsList.begin() + i); // Deletes element at index
				cout << "\nAnimal successfully deleted \n" << endl;
			}
			else {
				cout << "\nAnimal not deleted \n" << endl;
				continue;
			}
		}
	}
}

/**
 * Params t_animalsList, t_linesFromFile, fromJava
 *
 * Parses lines from file, builds Animal objects and adds them to vector
 */
void AddAnimalsToVector(vector<Animal>& t_animalsList, vector<string>& t_linesFromFile, bool fromJava = false) {
	for (unsigned int i = 0; i < t_linesFromFile.size(); ++i) {

		string track;
		string name;
		string type;
		string subType;
		string eggs;
		string nurse;

		try {
			if(fromJava) { // Parsing data from Java file
				track =  t_linesFromFile.at(i).substr(1, 6); // Track
				name =  t_linesFromFile.at(i).substr(8, 15);	// Name
				type =  t_linesFromFile.at(i).substr(25, 15);	// Type
				subType = t_linesFromFile.at(i).substr(42, 15);	// Sub-type
				eggs =  t_linesFromFile.at(i).substr(59, 1);	// Eggs
				nurse =  t_linesFromFile.at(i).substr(61, 1);	// Nurse
			}
			else {
				track =  t_linesFromFile.at(i).substr(0, 6); // Track
				name =  t_linesFromFile.at(i).substr(7, 15);	// Name
				type =  t_linesFromFile.at(i).substr(24, 15);	// Type
				subType = t_linesFromFile.at(i).substr(41, 15);	// Sub-type
				eggs =  t_linesFromFile.at(i).substr(58, 1);	// Eggs
				nurse =  t_linesFromFile.at(i).substr(60, 1);	// Nurse
			}
		} catch (out_of_range & ex) {
			cout << "Uh-oh, unable to import Animal data.\n\n"
					"Select Display Animal Data from the main menu.\n\n"
					"Ensure the format listed below is followed:\n"
					"Track: Number between 0 and 999999.\n"
					"Name: Less than 16 letters.\n"
					"Type: Mammal or Oviparous.\n"
					"Sub-type should be one of the following:\n\n"
					"Crocodile\n"
					"Goose\n"
					"Pelican\n"
					"Bat\n"
					"Whale\n"
					"SeaLion\n\n"
					"Enter a one digit number for Eggs or Nurse.\n";
		}

		int counter = 0;
		for (unsigned int j = 0; j < t_animalsList.size(); ++j) {
			Animal animalInVector = t_animalsList.at(j);
			if (StringToNumber(track) == animalInVector.TrackNum) {	// Check to see if track # already exists in array
				++counter; // Increment if duplicate record
			}
		}

		if (counter == 0){ // Add only unique animals to vector
			if(subType == "Crocodile") {
				Crocodile newCroc(StringToNumber(track), // Track
						name, // Name
						"Oviparous", // Type
						subType, // Sub-type
						StringToNumber(eggs)); // Eggs
				t_animalsList.push_back(newCroc);
			}
			else if (subType == "Goose") {
				Goose newGoose(StringToNumber(track), // Track
						name, // Name
						"Oviparous", // Type
						subType, // Sub-type
						StringToNumber(eggs)); // Eggs
				t_animalsList.push_back(newGoose);
			}
			else if (subType == "Pelican") {
				Pelican newPelly(StringToNumber(track), // Track
						name, // Name
						"Oviparous", // Type
						subType, // Sub-type
						StringToNumber(eggs)); // Eggs
				t_animalsList.push_back(newPelly);
			}
			else if (subType == "Bat") {
				Bat newBat(StringToNumber(track), // Track
						name, // Name
						"Mammal", // Type
						subType, // Sub-type
						StringToNumber(nurse)); // Nurse;
				t_animalsList.push_back(newBat);
			}
			else if (subType == "Whale") {
				Whale newWhale(StringToNumber(track), // Track
						name, // Name
						"Mammal", // Type
						subType, // Sub-type
						StringToNumber(nurse)); // Nurse;
				t_animalsList.push_back(newWhale);
			}
			else if (subType == "SeaLion") {
				SeaLion newSeaLion(StringToNumber(track), // Track
						name, // Name
						"Mammal", // Type
						subType, // Sub-type
						StringToNumber(nurse)); // Nurse;
				t_animalsList.push_back(newSeaLion);
			}
			else {
				// Placeholder animal if unknown type
				Animal newAnimal(StringToNumber(track), // Track
						name, // Name
						type, // Type
						subType, // Sub-type
						0); // Nurse or eggs field placeholder value; can be edited later
				t_animalsList.push_back(newAnimal);
			}
		}
	}
}

/**
 * Params t_animalsList
 *
 * Loads file contents into vector of Animal objects
 */
void LoadDataFromFile(vector<Animal>& t_animalsList)
{
	ifstream file1{"zoodata.txt"}; // Java generated file, contains one animal, if GenerateData() has been called
	string line1;
	vector<string> linesFromFile1;

	while (getline(file1, line1)) {
		linesFromFile1.push_back(line1); // Add each line from file into vector
	}

	AddAnimalsToVector(t_animalsList, linesFromFile1, true); // Parse Java file and build Animal vector

	file1.close();
	remove("zoodata.txt");

	ifstream file2{"composite-zoodata.txt"}; // C++ generated source of truth file, contains all animals
	string line2;
	vector<string> linesFromFile2;

	while (getline(file2, line2)) {
		linesFromFile2.push_back(line2); // Add each line from file into vector
	}

	AddAnimalsToVector(t_animalsList, linesFromFile2); // Parse C++ file and build Animal vector

	file2.close();

	cout << "\nLoad complete\n";
}

/**
 * Params t_animalsList
 *
 * Saves Animal elements from vector into file
 */
void SaveDataToFile(vector<Animal>& t_animalsList)
{
	ofstream outputFile{"composite-zoodata.txt"}; // Create file

	for (unsigned int i = 0; i < t_animalsList.size(); ++i) {
		Animal animal = t_animalsList.at(i);
		string animalAttributes;
		ostringstream animalAttr;

		animalAttr << right << setfill('0') << setw(6) << animal.TrackNum << " ";
		animalAttr	<< left << setfill(' ') << setw(15) << animal.name << "  "
				<< left << setw(15) << animal.type << "  "
				<< left << setw(15) << animal.subType << "  ";
		auto padded{ animalAttr.str() };

		animalAttributes += padded;
		if (animal.type == "Mammal") {
			animalAttributes += "0 " + NumberToString(animal.additionalData); // Nurse
		}
		else {
			animalAttributes += NumberToString(animal.additionalData) + " 0"; // Eggs
		}

		outputFile << animalAttributes << "\n";
	}

	outputFile.close(); // Cleanup/close file

	cout << "\nSave successfully completed\n";

}

/**
 * Params t_animalsList, t_userSelection
 *
 * Takes user input and calls appropriate function
 */
void DirectTraffic(vector<Animal>& t_animalsList, int t_userSelection) {
	switch(t_userSelection) {
		case 1:
			LoadDataFromFile(t_animalsList);
			break;
		case 2:
			GenerateData();
			cout << "\nSelect Load Animal Data to add it to the animals on file.\n";
			break;
		case 3:
			DisplayAnimalData(t_animalsList);
			break;
		case 4:
			AddAnimal(t_animalsList);
			break;
		case 5:
			RemoveAnimal(t_animalsList);
			break;
		case 6:
			SaveDataToFile(t_animalsList);
			break;
		default:
			throw runtime_error("Selection not recognized. Please try again. \n"); // Should never execute
	}
}

/**
 * Params t_animalsList
 *
 * Displays user interface
 */
void DisplayMenu(vector<Animal>& t_animalsList)
{
	char quitCmd = 'a';
	int userSelection;
	vector<string> menuOptions = {
			"[1] Load Animal Data",
			"[2] Generate Data",
			"[3] Display Animal Data",
			"[4] Add Record",
			"[5] Delete Record",
			"[6] Save Animal Data",
			"[7] Quit"
	};

	while (quitCmd != 'q') { // Use infinite loop to re-prompt user for valid menu selection

		try {

			cout << "\n";

			for (unsigned int i = 0; i < menuOptions.size(); ++i){
				cout << menuOptions.at(i) << endl;
			}

			cin >> userSelection;

			// Input validation
			if (!cin || userSelection < 1 || userSelection > 7) {
				throw runtime_error("Selection not recognized. Please try again. \n");
			}

			if (userSelection == 7) {
				cout << "\nYou selected quit. Goodbye.\n";
				quitCmd = 'q';
			}
			else {
				DirectTraffic(t_animalsList, userSelection); // Call correct method from user input
			}
		}
		catch(runtime_error& except) {
			cin.clear(); // Clear error flags
			cin.ignore(1000, '\n'); // Clear buffer of 1000 chars
			cout << except.what() << endl;
		}
	}
}

int main()
{
	vector<Animal> animalsList; // This is our source of truth vector
	try {
		DisplayMenu(animalsList);
	}
	catch(runtime_error& excpt) {
		cout << "Something wonky happened. Error code: " << excpt.what() << "\n";
	}

	return 1;
}
