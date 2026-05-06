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

Kitty createKitty();                //Nested function which calls functions that set kitty values.
void setGeneralInfo(Kitty&);        //Sets general info for kitty.
void setAttributes(Kitty&);         //Sets attributes for kitty.
void setPersonality(Kitty&);        //Allows user to set 5 personality traits for kitty.
void setColors(Kitty&);             //Allows user to set colors for kitty.
void accessoryDetermination(Kitty&);    //Big function which determines the accessory the kitty will have.
void saveKitties(const vector<Kitty>&); //Saves kitties to a file once they have been created.
void displayKitties();                  //Displays kitties to the console.
vector<Kitty> loadKitties();            //Loads kitties from a previous save file.

bool isValidTrait(string trait) {
	if (trait.length() == 0)
		return false;
	for (char c : trait) {
		if (!isalpha(c) && !isspace(c)) {
			return false;
		}
	}
	return true;
}

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

void setPersonality(Kitty& k) {
	char confirmed = 'N';

	while (confirmed == 'N') {
		k.clearPersonality();

		cout << "It's time to define your kitty's personality! You can pick 5 adjectives of your choosing to describe your kitty." << endl;
		cin >> ws;

		for (int i = 0; i < 5; i++) {
			string trait;
			cout << "Please enter trait #" << (i + 1) << ": ";
			getline(cin, trait);

			while (!isValidTrait(trait)) {
				cout << "Invalid trait! Please try again using only letters and spaces: ";
				getline(cin, trait);
			}
			k.addPersonality(trait);
		}
		cout << "Here are the traits you've specified for " << k.getName() << ":" << endl;
		for (const string& t : k.getPersonality()) {
			cout << "- " << t << endl;
		}
		confirmed = getValidatedChar("Are these traits OK? [Y/N]: ", "YN");
	}
}

void setColors(Kitty& k) {
	char confirmed = 'N';
	cout << "First, let's set the kitty's eye color(s)." << endl;
	while (confirmed == 'N') {
		k.clearEyeColors();
		char heterochromia = getValidatedChar("Is your kitty heterochromatic (2 different eye colors)? [Y/N]: ", "YN");
		cin >> ws;
		if (heterochromia == 'Y') {
			cout << "Enter the kitty's left eye color: ";
			string left;
			getline(cin, left);
			cout << "Now enter the kitty's right eye color: ";
			string right;
			getline(cin, right);

			k.addEyeColor(left);
			k.addEyeColor(right);
			cout << "You chose these colors for your kitty's eyes:" << endl;
			cout << "Left: " << left << endl;
			cout << "Right: " << right << endl;
			cout << "Do you like these colors? [Y/N]: ";
		}
		else {
			cout << "Enter the kitty's eye color: ";
			cin >> ws;
			string color;
			getline(cin, color);
			k.addEyeColor(color);
			cout << "You chose " << color << " for your kitty's eyes. Do you like this color? [Y/N]: ";
		}
		confirmed = getValidatedChar("", "YN");
	}

	//Set patterns
	confirmed = 'N';
	cout << "\nNext, let's pick the patterns. Your kitty can have up to 3 patterns, or none at all." << endl;
	while (confirmed == 'N') {
		k.clearPatterns();
		char hasPat = getValidatedChar("Does your kitty have patterns? [Y/N]: ", "YN");

		if (hasPat == 'Y') {
			cout << "Here are the available patterns:" << endl;
			cout << "1 - Point\n2 - Speckles\n3 - Spots\n4 - Patches\n5 - Stripes" << endl;
			bool adding = true;
			while (adding && k.getPatterns().size() < 3) {
				int choice = getValidatedInput<int>("Enter your pattern choice (1-5): ", 1, 5);
				k.addPattern(static_cast<FurPattern>(choice));

				if (k.getPatterns().size() < 3) {
					char more = getValidatedChar("Add another? [Y/N]: ", "YN");
					if (more == 'N')
						adding = false;
				}
			}
		}
		else {
			k.addPattern(FurPattern::Plain);
		}
		const auto& selectedPatterns = k.getPatterns();

		cout << "Here are the patterns you selected:" << endl;
		for (const auto& p : selectedPatterns) {
			cout << "- " << k.getPatternLabel(p) << endl;
		}
		confirmed = getValidatedChar("Do you like these colors? [Y/N]", "YN");
	}

	//Set fur colors
	confirmed = 'N';
	cout << "Now that we've selected your kitty's patterns, we can choose the fur colors." << endl;

	while (confirmed == 'N') {
		k.clearFurColors();
		cin >> ws;

		string primary;
		cout << "Please enter the kitty's primary fur color: ";
		getline(cin, primary);
		k.addFurColor(primary);

		const auto& patterns = k.getPatterns();

		if (!patterns.empty() && patterns[0] != FurPattern::Plain) {
			for (size_t i = 0; i < patterns.size(); i++) {
				string patternColor;
				string label = k.getPatternLabel(patterns[i]);

				cout << "Please enter the color for your kitty's " << label << ": ";
				getline(cin, patternColor);
				k.addFurColor(patternColor);
			}
		}
		cout << "Here are your chosen fur colors:" << endl;
		const auto& colors = k.getFurColors();
		cout << "Primary: " << colors[0] << endl;

		if (colors.size() > 1) {
			for (size_t i = 0; i < patterns.size(); i++) {
				cout << k.getPatternLabel(patterns[i]) << ": " << colors[i + 1] << endl;
			}
		}
		confirmed = getValidatedChar("Do these colors look OK? [Y/N]: ", "YN");
	}
}

void accessoryDetermination(Kitty& k) {
	char confirmed = 'N';

	cout << "\nYour kitty is almost finished! Let's top it off by adding an accessory." << endl;
	while (confirmed == 'N') {
		cout << "\nChoose from 5 different types of accessories:" << endl;
		cout << "1 - Ribbon (Head or Tail placement)" << endl;
		cout << "2 - Clothes (Custom description)" << endl;
		cout << "3 - Royal Headwear (Crown for boys, Tiara for girls)" << endl;
		cout << "4 - Footwear (Socks or Boots)" << endl;
		cout << "5 - Hat (Custom description)" << endl;

		int choice = getValidatedInput<int>("Enter your choice (1-5): ", 1, 5);
		string finalAccessory = "";

		if (choice == 1) {
			int placement = getValidatedInput<int>("Enter 1 if the ribbon should be on the kitty's head, or 2 if it should be on the tail: ", 1, 2);
			finalAccessory = (placement == 1) ? "Ribbon on Head" : "Ribbon on Tail";
		}
		else if (choice == 2) {
			cout << "\nDescribe the clothes your kitty will wear (example: a sparkling pink dress): ";
			cin >> ws;
			getline(cin, finalAccessory);
		}
		else if (choice == 3) {
			if (k.getGender() == "Male") {
				finalAccessory = "Crown";
			}
			else {
				finalAccessory = "Tiara";
			}
		}
		else if (choice == 4) {
			int footwear = getValidatedInput<int>("Enter 1 for socks or 2 for boots: ", 1, 2);
			finalAccessory = (footwear == 1) ? "Socks" : "Boots";
		}
		else if (choice == 5) {
			cout << "Please describe the hat your kitty will wear (ex: a blue fedora): ";
			cin >> ws;
			getline(cin, finalAccessory);
		}

		k.setAccessory(finalAccessory);
		cout << "\nYour kitty will wear " << finalAccessory << "." << endl;
		confirmed = getValidatedChar("Is this OK? [Y/N]: ", "YN");
	}
}

void saveKitties(const vector<Kitty>& salon) { //Will be a binary file to assist in saving and loading kitties.
	ofstream mew("kitties.dat", ios::out | ios::binary);

	if (mew.is_open()) {
		size_t count = salon.size();
		mew.write(reinterpret_cast<const char*>(&count), sizeof(count));

		for (const auto& k : salon) {
			auto saveString = [&](const string& s) {
				size_t len = s.length();
				mew.write(s.c_str(), len);
				};
			saveString(k.getName());
			saveString(k.getGender());
			saveString(k.getAccessory());
			Age kAge = k.getAge();
			mew.write(reinterpret_cast<const char*>(&kAge), sizeof(kAge));
			KittySize ks = k.getSize();
			FurLength fl = k.getFurLength();
			TailLength tl = k.getTail();
			mew.write(reinterpret_cast<const char*>(&ks), sizeof(ks));
			mew.write(reinterpret_cast<const char*>(&fl), sizeof(fl));
			mew.write(reinterpret_cast<const char*>(&tl), sizeof(tl));
			auto saveVector = [&](const vector<string>& v) {
				size_t vSize = v.size();
				mew.write(reinterpret_cast<const char*>(&vSize), sizeof(vSize));
				for (const string& s : v) saveString(s);
				};
			saveVector(k.getPersonality());
			saveVector(k.getEyeColors());
			saveVector(k.getFurColors());
			const auto& patterns = k.getPatterns();
			size_t pSize = patterns.size();
			mew.write(reinterpret_cast<const char*>(&pSize), sizeof(pSize));
			for (auto p : patterns) {
				mew.write(reinterpret_cast<const char*>(&p), sizeof(p));
			}
		}
		mew.close();
		cout << "Success!~ Kitties were saved to \"kitties.dat\"." << endl;
	}
	else {
		cout << "Error: Could not open binary file." << endl;
	}
}