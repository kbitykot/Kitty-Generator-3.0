#include "Kitty.h"
#include<iostream>

void Kitty::meow() {
	std::string adultMeows[] = {
		"meows happily.",
		"chirps.",
		"silently meows.",
		"chatters in the window.",
		"sings the best they can.",
		"growls at something.",
		"lets out a cute purreow."
	};
	std::string kittenMeows[] = {
		"mews happily.",
		"mews for a straight 10 seconds.",
		"growls at something.",
		"quietly mews.",
		"mews nonstop.",
		"silently mews.",
		"cries."
	};
	int totalMeows = 7;

	int random = rand() % totalMeows;

	if (isKitten == false) {
		std::cout << name << " " << adultMeows[random] << std::endl;
	}
	else if (isKitten == true) {
		std::cout << name << " " << kittenMeows[random] << std::endl;
	}
}

void Kitty::hiss() {
	std::string hisses[] = {
		"feels scared and hisses!",
		"feels threatened and hisses!",
		"has had enough of your games and lets you know with a hiss.",
		"doesn't like the current situation and hisses!",
		"feels uncomfortable and hisses!",
		"feels angry and hisses!",
		"hisses."
	};
	int hissTotal = 7;

	int random = rand() % hissTotal;

	std::cout << name << hisses[random] << std::endl;
}

void Kitty::play(std::string toy) {
	std::string actions[] = {
		" pounces on the ",
		" bats the ",
		" swats at the ",
		" stares intently at the ",
		" jumps at the ",
		" paws at the ",
		" runs towards the "
	};
	int random = rand() % 7;

	std::cout << name << actions[random] << toy << "!" << std::endl;
}

void Kitty::play(Kitty& friendKitty) {
	std::string interactions[] = {
		" and " + friendKitty.getName() + " are wrestling on the rug.",
		" chases " + friendKitty.getName() + " around the room.",
		" sneaks up on " + friendKitty.getName() + " and pounces!",
		" swats at " + friendKitty.getName() + " to get their attention. " + friendKitty.getName() + " responds with a bite.",
		" and " + friendKitty.getName() + " get into a loud argument of meows, hisses, and tail flicks."
	};
	int random = rand() % 5;
	std::cout << name << interactions[random] << std::endl;
}

void Kitty::attack() {
	std::string attacks[] = {
		"feels threatened and bites!",
		"unsheathes their claws and scratches with all their fury!",
		"has had enough of your games and makes you aware of it by sinking their teeth into your hands.",
		"feels scared and bites!",
		"lets their claws out and swats at you.",
		"feels overstimulated and claws at you to stop.",
		"doesn't like the situation and bunny-kicks you."
	};
	int random = rand() % 7;
	std::cout << name << attacks[random] << std::endl;
}