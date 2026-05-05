/*Name: Caitlyn Swick
//CIS 1202-501
//Development began 5/2/26
//Uploaded to GitHub for fun. Check it out: https://github.com/kbitykot/Kitty-Generator-3.0.git
// What the heck why isn't my code block working-- */

#ifndef KITTY_H
#define KITTY_H

#include<string>
#include<vector>

enum class TailLength { Short, Medium, Long };
enum class FurPattern { Plain, Point, Speckles, Spots, Patches, Stripes};
enum class FurLength { Hairless, Short, Average, Long, ExtraFluffy};
enum class KittySize { Tiny, Small, Average, Big, Monster };

struct Age {
	int amount;
	bool isAdult;
};

class Kitty {
private:
	std::string name, accessory, gender;
	std::vector<std::string> furColors;
	TailLength tail;
	std::vector<std::string> personality;
	Age age;
	bool isKitten, hasHeterochromia;
	std::vector<std::string> eyeColors;
	std::vector<FurPattern> patterns;
	FurLength furLength;
	KittySize size;

public:
    void setName(std::string n) {
        name = n;
    }
    void setAge(int amount, bool isAdult) {
        age.amount = amount;
        age.isAdult = isAdult;
    }
    void setFurLength(FurLength f) {
        furLength = f;
    }
    void setSize(KittySize s) {
        size = s;
    }

    //Vectors: "add" one at a time
    void addPattern(FurPattern p) {
        if (patterns.size() < 3)
            patterns.push_back(p);
    }
    void addPersonality(std::string p) {
        if (personality.size() < 5)
            personality.push_back(p);
    }
    void addEyeColor(std::string c) {
        if (eyeColors.size() < 2)
            eyeColors.push_back(c);
    }

    // --- Getters ---
    std::string getName() const {
        return name;
    }
    Age getAge() const {
        return age;
    }
    FurLength getFurLength() const {
        return furLength;
    }
    KittySize getSize() const {
        return size;
    }

    // Returning vectors by reference is more efficient
    const std::vector<FurPattern>& getPatterns() const {
        return patterns;
    }
    const std::vector<std::string>& getPersonality() const {
        return personality;
    }
    const std::vector<std::string>& getEyeColors() const {
        return eyeColors;
    }

    // --- Interaction Function Prototypes ---
    // These functions may change in the future; not a final list.
    void meow();
    void hiss();
    void play(std::string toy);
    void play(Kitty &friendKitty);
    void attack();
};

#endif