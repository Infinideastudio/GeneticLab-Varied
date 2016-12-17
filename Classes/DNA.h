#ifndef DNA_H
#define DNA_H
#include "cocos2d.h"
class DNA
{
public:
	std::vector<bool>genes;
	DNA(){}
	DNA(int DNASize_,int minPhrase_);
	DNA crossover(DNA partner);
	virtual void mutate(float mutationRate);
	virtual cocos2d::Size getPhrase();
	int DNASize;
	int minPhrase;
};
#endif
