#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;

class Exercise {
private:
	string name;	//Name
	int exType;		//Muscle group
	int sets;		//Sets
	int* reps;		//Reps
	double* weight;	//Weight of exercise machine or dumbbell, or barbell

public:
	Exercise() {

	}
	Exercise(string n, int tp, int s) {
		name = n;
		exType = tp;
		sets = s;				
		reps = new int[s];		//Reps and weight arrays size is the same as sets count because in every set there is
		weight = new double[s]; //specific rep count and weight
	}

	//Put given rep count in rep array
	void putRepsIn(int rep, int i) {
		this->reps[i] = rep;
	}

	//Put given weight in weight array
	void putWeightIn(double we, int i) {
		this->weight[i] = we;
	}

	//getters to get object private parameters
	int getSets() {
		return this->sets;
	}
	//
	int getType() {
		return this->exType;
	}
	//
	string getName() {
		return this->name;
	}

	//Calculates lifted weight in exercise
	double getExerciseLiftedWeight(double bodyweight) {
		double returnWeight = 0;
		int repCount = 0;
		double weight = 0;
		for (int i = 0; i < this->sets; i++) {
			repCount = this->reps[i];
			if (this->exType == 2 || this->exType == 4) //Core and Back exercises weight is equal to weight of exercise machine + 1/2 of body weight
				weight = this->weight[i] + bodyweight / 2; //because while training these muscle groups body weight is also lifted
			else
				weight = this->weight[i];
			returnWeight += (repCount * weight);
		}
		return returnWeight;
	}
};

//Deletes redundant input
void clear() {
	cin.clear();
	cin.ignore(256, '\n');
}

//Checks if double data type input is correct
double checkDouble(double number) {
	while (true) {
		if (!cin.good()) { //Checks if input is number
			cout << "Please, enter a number" << endl;
			clear();
			cin >> number;
			continue;
		}
		break;
	}
	return number;
}

//Checks if int data type input is correct
int checkInt(int number) {
	while (true) {
		if (!cin.good()) { //Checks if input is number
			cout << "Please, enter a number" << endl;
			clear();
			cin >> number;
			continue;
		}
		break;
	}
	return number;
}

//Checks if date and time input is correct
string checkStringInput(int deal) {
	string returnString = "";
	while (true) {
		cin >> returnString;
		if (returnString.length() != 5) { //Checks if input length is correct (5 characters)
			cout << "Try again" << endl;
			continue;
		}
		if (deal == 1) { //Date input check
			if (stoi(returnString.substr(0, 2)) < 1 || stoi(returnString.substr(3, 4)) < 1) { //Checks if input is NOT negative and/or zero
				cout << "The numbers you entered are invalid" << endl;
				continue;
			}
			if (stoi(returnString.substr(0, 2)) > 31 || stoi(returnString.substr(3, 4)) > 12) { //Checks the number of day and month input
				cout << "The numbers you entered are invalid" << endl;
				continue;
			}
		}
		else { //deal == 2; Time input check
			if (stoi(returnString.substr(0, 2)) < 0 || stoi(returnString.substr(3, 4)) < 0) { //Checks if input is NOT negative 
				cout << "The numbers you entered are invalid" << endl;
				continue;
			}
			if (stoi(returnString.substr(0, 2)) > 23 || stoi(returnString.substr(3, 4)) > 60) { //Checks the number of hours and minutes input
				cout << "The numbers you entered are invalid" << endl;
				continue;
			}
		}
		break;
	}
	return returnString;
}

//Checks if input double is positive number
double checkDoublePositive(double number) {
	double returnNumber = number;
	while (true) {
		cin >> returnNumber;
		clear();
		returnNumber = checkDouble(returnNumber);
		if (returnNumber <= 0.0) {
			cout << "Enter positive number" << endl;
			continue;
		}
		break;
	}
	return returnNumber;
}

//Checks if input int is positive number
int checkIntPositive(int number) {
	int returnNumber = number;
	while (true) {
		cin >> returnNumber;
		clear();
		returnNumber = checkInt(returnNumber);
		if (returnNumber <= 0) {
			cout << "Enter positive number" << endl;
			continue;
		}
		break;
	}
	return returnNumber;
}

//Checks exercise machine weight
double checkMachineWeight(double number) {
	double returnNumber = number;
	while (true) {
		cin >> returnNumber;
		clear();
		returnNumber = checkDouble(returnNumber);
		if (returnNumber < 0.0) { //Exercise machine can be positive or zero (bodyweight exercises) 
			cout << "Enter positive number or 0" << endl;
			continue;
		}
		break;
	}
	return returnNumber;
}

//Checks if number is between 1 and 10
int check1To10() {
	int returnNumber = 0;
	while (true) {
		cin >> returnNumber;
		clear();
		returnNumber = checkInt(returnNumber);
		if (returnNumber < 1 || returnNumber > 10) {
			cout << "Enter a number that is between 1 and 10" << endl;
			continue;
		}
		break;
	}
	return returnNumber;
}

//Checks input if yes and no
string checkYesNo() {
	string returnString = "";
	while (true) {
		cin >> returnString;
		if (returnString == "yes" || returnString == "no") {
			break;
		}
		else {
			cout << "Enter \"yes\" or \"no\"" << endl;
			continue;
		}
	}
	return returnString;
}

//Puts values in struct tm (hours and minutes)
void putDataInTimeObject(tm& time, string input) {
	time.tm_hour = stoi(input.substr(0, 2));
	time.tm_min = stoi(input.substr(3, 4));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
	cout << "Welcome to the training results diary and analysis program!" << endl;
	//1. Input of basic data
	//Enter file name in which information will be written
	cout << "Enter file name in which information about training will be written in: (e.g., myTraining)" << endl;
	string filename = "";
	cin >> filename;
	//Input of date
	cout << "Enter date (dd.mm)" << endl;
	string date = checkStringInput(1);
	//Input of training start and end time
	cout << "Enter training start time (hh:mm)" << endl;
	string startTimeInput = checkStringInput(2);
	cout << "Enter training end time (hh:mm)" << endl;
	string endTimeInput = checkStringInput(2);
	struct tm startTime;
	struct tm endTime;
	putDataInTimeObject(startTime, startTimeInput);
	putDataInTimeObject(endTime, endTimeInput);
	while (true) { //Checks time input: Training end time CANT be before training start time
		if (endTime.tm_hour < startTime.tm_hour) { //Checks input of hours
			cout << "Invalid training end time" << endl;
			cout << "Enter training end time (hh:mm)" << endl;
			string endTimeInput = checkStringInput(2);
			putDataInTimeObject(endTime, endTimeInput);
			continue;
		}
		if (endTime.tm_hour == startTime.tm_hour && endTime.tm_min <= startTime.tm_min) { //If hours are the same the minutes are checked
			cout << "Invalid training end time" << endl;
			cout << "Enter training end time (hh:mm)" << endl;
			string endTimeInput = checkStringInput(2);
			putDataInTimeObject(endTime, endTimeInput);
			continue;
		}
		break;
	}
	//Calculates time spent in training
	int trainingTimeInMinutes = (endTime.tm_hour - startTime.tm_hour) * 60;
	trainingTimeInMinutes += endTime.tm_min - startTime.tm_min; //Training length in minutes
	//Input of bodyweight
	cout << "Enter Your bodyweight: (kg)" << endl;
	double bodyWeight = checkDoublePositive(0.0);
	//Input of feelings before and after training (1-10 values)
	cout << "Enter Your feelings before training: (1-10)" << endl;
	int feelBefore = check1To10();
	cout << "Enter Your feelings after training: (1-10)" << endl;
	int feelAfter = check1To10();

	//2. Input of training data
	//Input the name of exercise
	Exercise exerciseArray[100]; //It would be better to use some kind of List or something, but as an array size is 100, 
	//I dont believe there could be a problem, because there is almost no chance that somebody does more than 100 different exercises in one training.
	for (int i = 0; i < 100; i++) {
		string exerciseName = "";
		int exType = 0;
		cout << "Enter the name of exercise: (e.g., Biceps or CrazyLegMachine)" << endl;
		cin >> exerciseName;
		//Gives exercise a muscle group (legs, core (abs and glutes), chest, back, arms)
		cout << "The exercise is for which muscle group? (1 legs, 2 core (abs and glutes), 3 chest, 4 back, 5 arms)" << endl;
		cout << "Enter the number of muscle group: " << endl;
		bool active = true;
		while (active) { //Provides repeating of question in case of wrong input
			int input = 0;
			cin >> input;
			input = checkInt(input);
			clear();
			switch (input) {
			case 1:
				exType = 1;		//Grants muscle group number for Exercise object
				active = false; //Shuts off repeating of question
				break;
			case 2:
				exType = 2;
				active = false;
				break;
			case 3:
				exType = 3;
				active = false;
				break;
			case 4:
				exType = 4;
				active = false;
				break;
			case 5:
				exType = 5;
				active = false;
				break;
			default:
				cout << "Enter a number between 1 and 5" << endl;
				break;
			}
		}
		//Future possibility - extra question: "Was it done with bodyweight?"
		//Input of sets, reps and machine weight
		cout << "Was all SETS with the same REP COUNT? (yes, no)" << endl;
		string answer1 = checkYesNo();
		cout << "Was all SETS done with the same WEIGHT? (yes, no)" << endl;
		string answer2 = checkYesNo();
		int sets = 0;
		int reps = 0;
		double machineWeight = 0;
		if (answer1 == "yes" && answer2 == "yes") { //yes, yes case: REP count and weight is the same
			cout << "Enter SET count: " << endl;
			sets = checkIntPositive(sets);			//Checks input and saves it
			Exercise ex(exerciseName, exType, sets); //Creates Exercise object
			exerciseArray[i] = ex;					//Put created object in object array
			cout << "Enter REP count: " << endl;
			reps = checkIntPositive(reps);		//Checks input and saves it
			for (int j = 0; j < sets; j++) 		//Writes same values because user said that REP count has been the same
				ex.putRepsIn(reps, j);			//Writes values in created Exercise object
			cout << "Enter the weight of the exercise machine/dumbbell/barbell: (kg)" << endl;
			machineWeight = checkMachineWeight(machineWeight); //Checks input and saves it
			for (int j = 0; j < sets; j++)		//Writes same values because user said that WEIGHT has been the same
				ex.putWeightIn(machineWeight, j); //Writes values in created Exercise object

		}
		else if (answer1 == "yes" && answer2 != "yes") { //yes, no case: REP count the same, but WEIGHT differs
			cout << "Enter SET count: " << endl;
			sets = checkIntPositive(sets);
			Exercise ex(exerciseName, exType, sets);
			exerciseArray[i] = ex;
			cout << "Enter REP count: " << endl;
			reps = checkIntPositive(reps);
			for (int j = 0; j < sets; j++)
				ex.putRepsIn(reps, j);
			for (int j = 0; j < sets; j++) {
				cout << "Enter the weight of the exercise machine/dumbbell/barbell in SET number " << (j + 1) << ": (kg)" << endl;
				machineWeight = checkMachineWeight(machineWeight);
				ex.putWeightIn(machineWeight, j);
			}
		}
		else if (answer1 != "yes" && answer2 == "yes") { //no, yes case: REP count differs in SETS, but WEIGHT the same
			cout << "Enter SET count: " << endl;
			sets = checkIntPositive(sets);
			Exercise ex(exerciseName, exType, sets);
			exerciseArray[i] = ex;
			cout << "Enter the weight of the exercise machine/dumbbell/barbell: (kg)" << endl;
			machineWeight = checkMachineWeight(machineWeight);
			for (int j = 0; j < sets; j++)
				ex.putWeightIn(machineWeight, j);
			for (int j = 0; j < sets; j++) {
				cout << "Enter REP count in SET number " << (j + 1) << ": " << endl;
				reps = checkIntPositive(reps);
				ex.putRepsIn(reps, j);
			}
		}
		else {											//no, no case: REP count and WEIGHT differs in every SET
			cout << "Enter SET count: " << endl;
			sets = checkIntPositive(sets);
			Exercise ex(exerciseName, exType, sets);
			exerciseArray[i] = ex;
			for (int j = 0; j < sets; j++) {
				cout << "Enter REP count in SET number " << (j + 1) << ": " << endl;
				reps = checkIntPositive(reps);
				ex.putRepsIn(reps, j);
				cout << "Enter the weight of the exercise machine/dumbbell/barbell in SET number " << (j + 1) << ": (kg)" << endl;
				machineWeight = checkMachineWeight(machineWeight);
				ex.putWeightIn(machineWeight, j);
			}
		}
		cout << "Add exercise? (yes/no)" << endl;
		string answer3 = checkYesNo();
		if (answer3 != "yes"){
			break; //In case of "no", stops cycle of exercise input
		}	
	}
	//3. Training analysis
	int noMoreExercisesInArray = 0;				//number that shows which element is the one in which there is no data
	double totalLiftedWeight = 0;				//total lifted weight in training 
	double legsLifted = 0, coreLifted = 0, chestLifted = 0, backLifted = 0, armsLifted = 0; //total lifted weight of muscle group
	double exerciseLiftedWeight[100];			//store total lifted weight in exercise
	for (int i = 0; i < 100; i++) {
		if (exerciseArray[i].getType() < 1 || exerciseArray[i].getType() > 5) { //Cathces the moment, when there is no data in exerciseArray
			noMoreExercisesInArray = i;
			break;
		}
		exerciseLiftedWeight[i] = exerciseArray[i].getExerciseLiftedWeight(bodyWeight); //Records lifted weight in exercise. Better would be to make a parameter for object Exercise to store this data
		totalLiftedWeight += exerciseLiftedWeight[i];
		switch (exerciseArray[i].getType()) { //switch case block - Adds up lifted weight to muscle group lifted weight
		case 1:
			legsLifted += exerciseLiftedWeight[i];
			break;
		case 2:
			coreLifted += exerciseLiftedWeight[i];
			break;
		case 3:
			chestLifted += exerciseLiftedWeight[i];
			break;
		case 4:
			backLifted += exerciseLiftedWeight[i];
			break;
		case 5:
			armsLifted += exerciseLiftedWeight[i];
			break;
		default:
			break;
		}
	}
	double trainingPower = totalLiftedWeight / trainingTimeInMinutes; //training power (kg/min)
	cout << "You lifted: " << totalLiftedWeight << " kg!" << endl;
	cout << "Training power: " << trainingPower << " kg/min" << endl;

	//4. Writes data in file
	//File is created as .csv file
	ofstream myfile;
	myfile.open(filename + ".csv"); //File is created with the name as user input in beginning
	//First row immutable data
	string firstLine = "Date,Weight,Feel before training,Feel after training,Training length(min),Total weight(kg),Training power(kg/min),";
	for (int i = 0; i < noMoreExercisesInArray; i++) //Makes first row continue with exercises names
		firstLine += exerciseArray[i].getName() + ",";
	firstLine += "Legs,Core,Chest,Back,Arm\n"; //At the end of first row are names of muscle groups
	myfile << firstLine; //writes First line in file 
	//Second line data which can be aquired without effort
	string secondLine = date + "," + to_string(bodyWeight) + "," + to_string(feelBefore) + "," + to_string(feelAfter) + ","
		+ to_string(trainingTimeInMinutes) + "," + to_string(totalLiftedWeight) + "," + to_string(trainingPower) + ",";
	for (int i = 0; i < noMoreExercisesInArray; i++) {
		secondLine += to_string(exerciseLiftedWeight[i]) + ","; //Every exercise lifted weight written as String
		if (i == (noMoreExercisesInArray - 1)) { //Catches moment when all exercises lifted weight is written
			//Every muscle group lifted weight is added to second line
			secondLine += to_string(legsLifted) + "," + to_string(coreLifted) + "," + to_string(chestLifted) + ","
				+ to_string(backLifted) + "," + to_string(armsLifted) + "\n";
			myfile << secondLine;
		}
	}
	myfile.close();
	cout << "Thank You! Goodbye!" << endl;
	cout << "Enter anything to quit program." << endl;
	string endInput;
	cin >> endInput;
	return 0;
}