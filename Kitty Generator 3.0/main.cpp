#include "Kitty.h"
#include<ctime>
#include<iostream>
#include<vector>
#include<cctype>
#include<fstream>
#include<thread>
#include<chrono>
#include<algorithm>

using namespace std;

const int MAX_KITTIES = 5;

Kitty createKitty();                //Nested function which calls functions that set kitty values.
void setGeneralInfo(Kitty&);        //Sets general info for kitty.
void setAttributes(Kitty&);         //Sets attributes for kitty.
void setPersonality(Kitty&);        //Allows user to set 5 personality traits for kitty.
void setColors(Kitty&);             //Allows user to set colors for kitty.
void accessoryDetermination(Kitty&);     //Big function which determines the accessory the kitty will have.
void saveKitties(const vector<Kitty>&);   //Saves kitties to a file once they have been created.
void displayKitties(const vector<Kitty>&);  //Displays kitties to the console.
vector<Kitty> loadKitties();                //Loads kitties from a previous save file.
void interactWithKitty(vector<Kitty>&);     //Lets user select a kitty to interact with. Also holds interact logic.

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

bool isValidTrait(string trait) { //Checks if a personality trait is valid (has no special characters or numbers).
	if (trait.length() == 0)
		return false;
	for (char c : trait) {
		if (!isalpha(c) && !isspace(c)) {
			return false;
		}
	}
	return true;
}

bool fileExists(const string& filename) { //Helper function which checks if there is already a file for the program.
	ifstream check(filename);
	return check.good();
}

void creationDelay() { //Fun cosmetic addition; just delays output statements.
	cout << "\nPlease wait while we finalize the details." << endl;
	cout << "Sending kitty to a groomer..." << endl;
	this_thread::sleep_for(chrono::seconds(5));
	cout << "Giving kitty a bath..." << endl;
	this_thread::sleep_for(chrono::seconds(7));
	cout << "Drying kitty off..." << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << "Brushing kitty's fur..." << endl;
	this_thread::sleep_for(chrono::seconds(5));
	cout << "Trimming kitty's nails..." << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << "Apparently our groomer wants to paint the kitty's nails..." << endl;
	this_thread::sleep_for(chrono::seconds(5));
	cout << "Fighting with groomer for the kitty..." << endl;
	this_thread::sleep_for(chrono::seconds(7));
	cout << "We won, putting kitty's accessories back on..." << endl;
	this_thread::sleep_for(chrono::seconds(5));
	cout << "Placing kitty in its carrier..." << endl;
	this_thread::sleep_for(chrono::seconds(3));
	cout << "All finished!" << endl;
}

string toLower(string data) { //Helper function which acts like cctype's tolower() function but for strings.
	transform(data.begin(), data.end(), data.begin(),
		[](unsigned char c) {return tolower(c); });
	return data;
}

int main() {
	srand(time(0));
	vector<Kitty> salon;
	string filename = "kitties.dat";

	if (fileExists(filename)) {
		char choice = getValidatedChar("Welcome back! Would you like to load your saved kitties or create new ones? [L/C]: ", "LC");

		if (choice == 'L') {
			salon = loadKitties();
		}
		else {
			cout << "You will not be able to recover your saved kitties once you save new ones. It is recommended that you make a backup of your kitties before continuing." << endl;
			char choice = getValidatedChar("Are you certain that you would like to create a new set of kitties? [Y/N]: ", "YN");
			if (choice == 'Y') {
				cout << "Starting fresh!~ Your kitties will be kept until you save the new ones, so take this time to make your backup if you haven't already!" << endl;
			}
			else {
				cout << "Okay, we'll load your saved kitties instead." << endl;
				salon = loadKitties();
			}
		}
	}
	else {
		cout << "Welcome to the Kitty Salon! We have prepared an even better system to create kitties since Kitty Generator 2.5. Now, you can take them home with you!" << endl;
	}
	
	if (salon.empty()) {
		cout << "Let's create your first kitty!\nPress ENTER to begin kitty creation...";
		cin.get();

		Kitty newKitty = createKitty();

		creationDelay();
		salon.push_back(newKitty);
	
		salon.back().introduce();
	}
	
	bool running = true;
	while (running) {
		cout << "\n--- MAIN MENU ---" << endl;
		cout << "1. Create Another Kitty (up to 5)" << endl;
		cout << "2. View Kitties" << endl;
		cout << "3. Interact with a Kitty" << endl;
		cout << "4. Save Progress" << endl;
		cout << "5. Exit Program" << endl;

		int menuChoice = getValidatedInput<int>("Please enter your number choice: ", 1, 5);

		switch (menuChoice) {
		case 1: {
			if (salon.size() >= 5) {
				cout << "\nThe salon is full! You cannot have more than 5 kitties at once." << endl;
			}
			else {
				Kitty newKitty = createKitty();
				creationDelay();
				salon.push_back(newKitty);
				newKitty.introduce();
			}
			break;
		}
		case 2: {
			displayKitties(salon);
			break;
		}
		case 3: {
			interactWithKitty(salon);
			break;
		}
		case 4: {
			saveKitties(salon);
			break;
		}
		case 5: {
			cout << "Would you like to save before leaving? ";
			if (getValidatedChar("[Y/N]: ", "YN") == 'Y') {
				saveKitties(salon);
			}
			cout << "Thank you for visiting the Kitty Salon! Have a purr-fect day." << endl;
			running = false;
			break;
			}
		}
	}
	return 0;
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
			ageVal = getValidatedInput<int>("\nPlease enter your kitty's age in years (1-100000): ", 1, 100000); //I know, this is not a reasonable lifespan for a cat. However... this is a program. We can do whatever we desire in a program, and I choose to let kitties live for ETERNITY! Mwahahaha!
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

		cout << "You chose " << k.getFurLabel() << " fur type for your kitty. Is this OK? [Y/N]: ";
		confirmed = getValidatedChar("", "YN");
	}

	//Set tail length
	confirmed = 'N';
	while (confirmed == 'N') {
		cout << "Now let's choose a tail length:\n1 - Short\n2 - Medium\n3 - Long" << endl;
		int choice = getValidatedInput<int>("Enter your choice (1-3): ", 1, 3);
		k.setTail(static_cast<TailLength>(choice - 1));

		cout << "Your kitty will have a " << k.getTailLabel() << " tail. Is this OK? [Y/N]: ";
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
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
		if (heterochromia == 'Y') {
			cout << "Enter the kitty's left eye color: ";
			string left;
			getline(cin >> ws, left);
			cout << "Now enter the kitty's right eye color: ";
			string right;
			getline(cin >> ws, right);

			k.addEyeColor(left);
			k.addEyeColor(right);
			cout << "You chose these colors for your kitty's eyes:" << endl;
			cout << "Left: " << left << endl;
			cout << "Right: " << right << endl;
			cout << "Do you like these colors? [Y/N]: ";
		}
		else {
			cout << "Enter the kitty's eye color: ";
			string color;
			getline(cin >> ws, color);
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
		confirmed = getValidatedChar("Do you like these patterns? [Y/N]: ", "YN");
	}

	//Set fur colors
	confirmed = 'N';
	cout << "Now that we've selected your kitty's patterns, we can choose the fur colors." << endl;

	while (confirmed == 'N') {
		k.clearFurColors();

		string primary;
		cout << "Please enter the kitty's primary fur color: ";
		getline(cin >> ws, primary);
		k.addFurColor(primary);

		const auto& patterns = k.getPatterns();

		if (!patterns.empty() && patterns[0] != FurPattern::Plain) {
			for (size_t i = 0; i < patterns.size(); i++) {
				string patternColor;
				string label = k.getPatternLabel(patterns[i]);

				cout << "Please enter the color for your kitty's " << label << ": ";
				getline(cin >> ws, patternColor);
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

void saveKitties(const vector<Kitty>& salon) { //Binary file to assist in saving and loading kitties. Gemini helped with writing.
	ofstream mew("kitties.dat", ios::out | ios::binary);

	if (mew.is_open()) {
		size_t count = salon.size();
		mew.write(reinterpret_cast<const char*>(&count), sizeof(count));

		for (const auto& k : salon) {
			//Save strings
			auto saveString = [&](const string& s) {
				size_t len = s.length();
				mew.write(reinterpret_cast<const char*>(&len), sizeof(len));
				mew.write(s.c_str(), len);
				};
			saveString(k.getName());
			saveString(k.getGender());
			saveString(k.getAccessory());

			//Struct
			Age kAge = k.getAge();
			mew.write(reinterpret_cast<const char*>(&kAge), sizeof(kAge));

			//Enum classes
			KittySize ks = k.getSize();
			FurLength fl = k.getFurLength();
			TailLength tl = k.getTail();
			mew.write(reinterpret_cast<const char*>(&ks), sizeof(ks));
			mew.write(reinterpret_cast<const char*>(&fl), sizeof(fl));
			mew.write(reinterpret_cast<const char*>(&tl), sizeof(tl));

			//Vectors
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

vector<Kitty> loadKitties() { //Loads kitties. Gemini helped with writing.
	vector<Kitty> loadedSalon;
	ifstream mew("kitties.dat", ios::in | ios::binary);

	if (mew.is_open()) {
		size_t count = 0;
		mew.read(reinterpret_cast<char*>(&count), sizeof(count));
		

		for (size_t i = 0; i < count; i++) {
			Kitty k;
			//Load strings
			auto readString = [&]() -> string {
				size_t len = 0;
				mew.read(reinterpret_cast<char*>(&len), sizeof(len));
				string s(len, ' ');
				mew.read(&s[0], len);
				return s;
				};
			k.setName(readString());
			k.setGender(readString());
			k.setAccessory(readString());

			//Struct
			Age kAge;
			mew.read(reinterpret_cast<char*>(&kAge), sizeof(kAge));
			k.setAge(kAge.amount, kAge.isAdult);

			//Enum classes
			KittySize ks;
			FurLength fl;
			TailLength tl;
			mew.read(reinterpret_cast<char*>(&ks), sizeof(ks));
			mew.read(reinterpret_cast<char*>(&fl), sizeof(fl));
			mew.read(reinterpret_cast<char*>(&tl), sizeof(tl));
			k.setSize(ks);
			k.setFurLength(fl);
			k.setTail(tl);

			//Vectors
			size_t traitCount = 0;
			mew.read(reinterpret_cast<char*>(&traitCount), sizeof(traitCount));
			for (size_t j = 0; j < traitCount; j++) {
				k.addPersonality(readString());
			}
			size_t eyeColorCount = 0;
			mew.read(reinterpret_cast<char*>(&eyeColorCount), sizeof(eyeColorCount));
			for (size_t j = 0; j < eyeColorCount; j++) {
				k.addEyeColor(readString());
			}
			size_t furColorCount = 0;
			mew.read(reinterpret_cast<char*>(&furColorCount), sizeof(furColorCount));
			for (size_t j = 0; j < furColorCount; j++) {
				k.addFurColor(readString());
			}
			size_t patternCount = 0;
			mew.read(reinterpret_cast<char*>(&patternCount), sizeof(patternCount));
			for (size_t j = 0; j < patternCount; j++) {
				FurPattern p;
				mew.read(reinterpret_cast<char*>(&p), sizeof(p));
				k.addPattern(p);
			}
			loadedSalon.push_back(k);
		}
		
		mew.close();
		cout << loadedSalon.size() << " kitties have been loaded and are ready to play!" << endl;
	}
	else {
		cout << "No save data found. Starting from scratch..." << endl;
	}
	return loadedSalon;
}

void displayKitties(const vector<Kitty>& salon) {
	if (salon.empty()) {
		cout << "You haven't created any kitties, or they could not be found." << endl;
		return;
	}

	cout << "\n*********************************************" << endl;
	cout << "             KITTY SALON REGISTRY              " << endl;
	cout << "*********************************************" << endl;

	for (size_t i = 0; i < salon.size(); i++) {
		const Kitty& k = salon[i];
		Age kAge = k.getAge();

		cout << "Kitty #" << (i + 1) << ": " << k.getName() << endl;
		cout << "-----------------------------------------" << endl;

		int years = kAge.amount / 12;
		int months = kAge.amount % 12;

		cout << "Age: " << (kAge.isAdult ? "Adult" : "Kitten") << " | " << years << " years and " << months << " months old" << endl;
		cout << "Gender: " << k.getGender() << endl;
		cout << "Size: " << k.getSizeLabel() << endl;
		cout << endl;

		cout << "[ APPEARANCE ]" << endl;
		
		const auto& eyes = k.getEyeColors();
		if (eyes.size() > 1) {
			cout << "Eye Colors:" << endl;
			cout << "- Left: " << eyes[0] << endl;
			cout << "- Right: " << eyes[1] << endl;
		}
		else {
			cout << "Eye Color: " << eyes[0] << endl;
		}

		cout << "Fur Type: " << k.getFurLabel() << endl;

		const auto& patterns = k.getPatterns();
		const auto& colors = k.getFurColors();

		if (!colors.empty()) {
			cout << "Primary Color: " << colors[0] << endl;
		}

		if (!patterns.empty() && patterns[0] != FurPattern::Plain) {
			cout << "Patterns: ";
			for (size_t p = 0; p < patterns.size(); p++) {
				if ((p + 1) < colors.size()) {
					cout << colors[p + 1] << " ";
				}
				cout << k.getPatternLabel(patterns[p]);
				if (p < patterns.size() - 1) {
					cout << ", ";
				}
			}
			cout << endl;
		}
		else {
			cout << "Patterns: None (Plain)" << endl;
		}

		cout << endl;
		cout << "[ PURRSONALITY ]" << endl;
		const auto& traits = k.getPersonality();
		for (size_t j = 0; j < traits.size(); j++) {
			cout << "- " << traits[j] << endl;
		}
		cout << endl;

		cout << "Accessory: " << k.getAccessory() << endl;
		cout << "*********************************************" << endl;
	}
}

void interactWithKitty(vector<Kitty>& salon) {
	if (salon.empty()) {
		cout << "The room is empty. You haven't created any kitties yet, or they could not be found." << endl;
		return;
	}

	cout << "\n--- Search for a Kitty ---" << endl;
	cout << "Enter the name of the kitty you'd like to see: ";
	string searchName;
	getline(cin >> ws, searchName);
	int foundIndex = -1;
	for (size_t i = 0; i < salon.size(); i++) {
		if (toLower(salon[i].getName()) == toLower(searchName)) {
			foundIndex = (int)i;
			break;
		}
	}
	if (foundIndex == -1) {
		cout << "Sorry, a kitty named \"" << searchName << "\" wasn't found. " << endl;
		return;
	}

	Kitty& k = salon[foundIndex];
	k.resetPatience();
	cout << "\nYou walk up to " << k.getName() << "." << endl;
	k.setTolerance(rand() % 48 + 3); //Some kitties don't like interacting, while others tolerate anything ... (looks at ragdoll cats) ... In this program, the tolerance will change with every interaction, because kitties are quite unpredictable at times.

	bool interacting = true;
	while (interacting) {
		if (k.isGrumpy()) {
			k.attack();
			interacting = false;
			break;
		}

		cout << "\n" << k.getName() << " looks up at you. What should they do?" << endl;
		cout << "1 - Play\n2 - Meow\n3 - Hiss\n4 - Play with friend\n5 - Leave" << endl;
		int action = getValidatedInput<int>("Enter your choice: ", 1, 5);

		if (action == 1) {
			vector<string> toyBox = { "Feather Wand", "Laser Pointer", "Jingly Ball", "Interactive Bird" };
			cout << "\nChoose a toy from the toy box:" << endl;
			for (size_t t = 0; t < toyBox.size(); t++) {
				cout << t + 1 << " - " << toyBox[t] << endl;
			}
			cout << toyBox.size() + 1 << " - Other" << endl;

			int toyChoice = getValidatedInput<int>("Select a toy: ", 1, toyBox.size() + 1);
			string selectedToy;

			if (toyChoice <= toyBox.size()) {
				selectedToy = toyBox[toyChoice - 1];
			}
			else {
				cout << "What toy do you use to play with the kitty?: ";
				cin >> ws;
				getline(cin, selectedToy);
			}
			k.play(selectedToy);
			k.losePatience();
		}
		else if (action == 2) {
			k.meow();
			k.losePatience();
		}
		else if (action == 3) {
			k.hiss();
			k.losePatience();
		}
		else if (action == 4) {
			if (salon.size() < 2) {
				cout << "There are no other kitties in the salon for " << k.getName() << " to play with." << endl;
			}
			else {
				cout << "Who should " << k.getName() << " play with? ";
				string friendName;
				getline(cin >> ws, friendName);

				int friendIndex = -1;
				for (size_t i = 0; i < salon.size(); i++) {
					string currentName = toLower(salon[i].getName());
					string targetFriend = toLower(friendName);
					string seekerName = toLower(k.getName());

					if (currentName == targetFriend && currentName != seekerName) {
						friendIndex = (int)i;
						break;
					}
				}
				if (friendIndex != -1) {
					k.play(salon[friendIndex]);
					k.losePatience();
					salon[friendIndex].losePatience();
				}
				else {
					cout << "That kitty couldn't be found." << endl;
				}
			}
		}
		else {
			interacting = false;
		}
	}
}