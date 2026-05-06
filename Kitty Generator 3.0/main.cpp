#include "Kitty.h"
#include<ctime>
#include<iostream>
#include<vector>
#include<cctype>
#include<fstream>
#include<thread>
#include<chrono>

using namespace std;

const int MAX_KITTIES = 5;

template <typename T>
T getValidatedInput(string prompt, T min, T max) { //Validates most input.
	T input;
	bool isValid = false;
	while (!isValid) {
		cout << prompt;
		if (cin >> input && input >= min && input <= max) {
			isValid = true;
		}
		else {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input. Please enter a value between " << min << " and " << max << ": ";
		}
	}
	return input;
}
char getValidatedChar(string prompt, string allowed) { //Validates specific character input, mainly for Y/N options.
	char input = ' ';
	bool matchFound = false;

	while (!matchFound) {
		cout << prompt;
		cin >> input;
		input = toupper(input);

		if (allowed.find(input) != string::npos) {
			matchFound = true;
		}
		else {
			cout << "Invalid selection. Choices are: ";
			for (char c : allowed) {
				cout << "[" << c << "] " << endl;
			}
		}
	}
	return input;
}

Kitty createKitty(); //Nested function which calls functions that set kitty values.
void setGeneralInfo(Kitty&); //Sets general info for kitty.
void setAttributes(Kitty&); //Sets attributes for kitty.
void setPersonality(Kitty&); //Allows user to set 5 personality traits for kitty.
void setColors(Kitty&); //Allows user to set colors for kitty.
void accessoryDetermination(Kitty&); //Big function which determines the accessory the kitty will have.
void saveKitties(const Kitty[], int); //Saves kitties to a file once they have been created.
void displayKitties(const Kitty[], int); //Displays kitties to the console.

int main() {
	srand(time(0));
	char selection, newKitty;
	vector<Kitty> salon;
	Kitty temp;
	temp.setName("Unnamed");

	cout << "Welcome to the Kitty Salon! We have prepared an even better system to create kitties since Kitty Generator 2.5. Now, you can take them home with you!" << endl;
	cout << "Press ENTER to begin kitty creation...";
	cin.get();

	do {
		if (salon.size() < MAX_KITTIES) {
			Kitty temp = createKitty();
			salon.push_back(temp);
		}
		else {
			cout << "You've reached the max number of kitties that can be created!";
			break;
		}
	} while (toupper(newKitty) == 'Y');
}

Kitty createKitty() {
	Kitty temp;
	cout << "Great! Let's begin. First, we'll need to get the kitty's general information, such as name, gender, and age." << endl;
	setGeneralInfo(temp);
	cout << "\nNow that we've found the kitty's general information, we can now set the kitty's attributes. These include the fur and tail lengths, body size, and personality traits." << endl;
	setAttributes(temp);
	setPersonality(temp);
	cout << "\nNow we can set the fur and eye colors! We'll also set the patterns while we're at it." << endl;
	setColors(temp);
	accessoryDetermination(temp);
	cout << temp.getName() << " has been created!";

	return temp;
}

void setGeneralInfo(Kitty& k) {
	char confirmed = 'N';

	while (confirmed == 'N') {
		cout << "\nPlease enter the desired name for your kitty: ";
		cin >> ws; //clears leftover whitespace or newlines
		string tempName;
		getline(cin, tempName);
		k.setName(tempName);

		cout << "You chose " << k.getName() << " as your kitty's name. Do you like this choice? [Y/N]: ";
		confirmed = getValidatedChar("", "YN");
	}

	if (k.getName().length() >= 15) {
		cout << "Wow, that's a long name for a kitty! Great choice!" << endl;
	}
	if (k.getName() == "Caitlyn") {
		cout << "Hey, that's my name!" << endl;
	}
	else if (k.getName() == "Jordan") {
		cout << "A legendary name for a legendary kitty." << endl;
	}

	//Set kitten/adult
	confirmed = 'N';
	bool adultChoice = false;

	while (confirmed == 'N') {
		int choice = getValidatedInput<int>("\nIs your cat an adult (1) or a kitten (2)?: ", 1, 2);
		adultChoice = (choice == 1);

		cout << "Your kitty will be a(n) " << (adultChoice ? "Adult" : "Kitten") << ". Is this OK? [Y/N]: ";
		confirmed = getValidatedChar("", "YN");
	}

	//Set age value
	confirmed = 'N';
	while (confirmed == 'N') {
		int ageVal;
		if (!adultChoice) {
			ageVal = getValidatedInput<int>("\nPlease enter the kitten's age in months: ", 0, 1200000);
			int years = ageVal / 12;
			int months = ageVal % 12;

			if (years > 0) {
				cout << "Your kitten will be " << years << " year(s) and " << months << " months old. Is this OK? [Y/N]: ";
			}
			else {
				cout << "Your kitty will be " << ageVal << " months old. Is this OK? [Y/N]: ";
			}
		}
		else {
			ageVal = getValidatedInput<int>("\nPlease enter your kitty's age in years (1-100000): ", 1, 100000); //I know, this is not a reasonable lifespan for a cat. However... this is a program. We can do whatever we desire in a program, and I choose to make kitties live for ETERNITY! Mwahahaha!
			cout << "Your kitty will be " << ageVal << " years old. Is this OK? [Y/N]: ";
		}
		confirmed = getValidatedChar("", "YN");
		if (confirmed == 'Y') {
			k.setAge(ageVal, adultChoice);
		}
	}

	//Set gender
	confirmed = 'N';
	while (confirmed == 'N') {
		char g = getValidatedChar("\nTime to set the kitty's gender! Enter [M] for Male or [F] for Female: ", "MF");
		k.setGender(g == 'M' ? "Male" : "Female");
		cout << "Your kitty will be " << k.getGender() << ". Is this OK? [Y/N]: ";
		confirmed = getValidatedChar("", "YN");
	}
}

void setAttributes(Kitty& k) {
	char confirmed = 'N';
	while (confirmed == 'N') {
		cout << "First, let's determine the fur type for your kitty. Here are your options:\n1 - Hairless\n2 - Shorthair\n3 - Average fur\n4 - Longhair\n5 - Extra Fluffy" << endl;

		int choice = getValidatedInput<int>("Enter choice (1-5): ", 1, 5);
		k.setFurLength(static_cast<FurLength>(choice - 1));

		cout << "You chose " << k.getFurLabel() << " fur for your kitty. Is this OK? [Y/N]: ";
		confirmed = getValidatedChar("", "YN");
	}

	//Set tail length
	confirmed = 'N';
	while (confirmed == 'N') {
		cout << "Now let's choose a tail length:\n1 - Short\n2 - Medium\n3 - Long" << endl;
		int choice = getValidatedInput<int>("Enter your choice (1-3): ", 1, 3);
		k.setTail(static_cast<TailLength>(choice - 1));

		cout << "Your kitty will have a(n) " << k.getTailLabel() << "tail. Is this OK? [Y/N]: ";
		confirmed = getValidatedChar("", "YN");
	}

	//Set size
	confirmed = 'N';
	while (confirmed == 'N') {
		cout << "\nNow we'll choose the kitty's size. This is based on the kitty's scale, not weight, unless you want it to be. Here are your options:" << endl;
		if (!k.isAdult()) {
			cout << "1 - Tiny\n2 - Small\n3 - Average\n4 - Big" << endl;
		}
		else {
			cout << "1 - Small\n2 - Average\n3 - Big\n4 - Monster" << endl;
		}
		int choice = getValidatedInput<int>("Enter your choice (1-4): ", 1, 4);

		if (!k.isAdult()) {
			k.setSize(static_cast<KittySize>(choice - 1)); //Kittens: Index 0-4; cannot be "Monster"
		}
		else {
			k.setSize(static_cast<KittySize>(choice)); //Adults: Index 1-5; cannot be "Tiny"
		}

		cout << "You chose " << k.getSizeLabel() << " for your kitty's size. Is this OK? [Y/N]: ";
		confirmed = getValidatedChar("", "YN");
	}
}