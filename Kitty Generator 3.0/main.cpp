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

void createKitty(Kitty&);
void setGeneralInfo(Kitty&);
void setAttributes(Kitty&);
void setPersonality(Kitty&);
void setColors(Kitty&);
void accessoryDetermination(Kitty&);
void saveKitties(const Kitty[], int);
void displayKitties(const Kitty[], int);

int main() {
	srand(time(0));
	vector<Kitty> salon;

	cout << "Welcome to the Kitty Salon! We have prepared an even better system to create kitties. Now, you can take them home with you!" << endl;
	cout << "Press ENTER to begin kitty creation...";
	cin.get();
}

void createKitty(Kitty& temp) {

}