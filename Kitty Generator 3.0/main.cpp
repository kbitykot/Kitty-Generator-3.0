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

void createKitty(Kitty&);/
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

	for (int i = 0; i < 5; i++) {
		Kitty tempKitty;
		string tempName;


	}

}