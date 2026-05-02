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
enum class KittenSize { Tiny, Small, Average, Big };
enum class AdultSize { Small, Average, Big, Monster };

class Kitty {
private:
	std::string name;
	std::vector<std::string> furColors;
	TailLength tail;
	std::vector<std::string> personality;
	int age;
	bool isKitten, hasHeterochromia;
	std::vector<std::string> eyeColors;
	std::vector<FurPattern> patterns;
	FurLength furLength;
	KittenSize kSize;
	AdultSize aSize;
	std::string accessory, gender;

public:
	
};

#endif