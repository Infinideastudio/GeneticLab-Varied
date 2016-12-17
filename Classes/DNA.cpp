#include "DNA.h"
using namespace cocos2d;
DNA::DNA(int DNASize_, int minPhrase_)
{
	DNASize = DNASize_;
	minPhrase = minPhrase_;
	for (int i = 0; i < DNASize; ++i)
		genes.emplace_back(random<int>(0,1));
}
DNA DNA::crossover(DNA partner)
{
	DNA child = DNA();
	for (int i = 0; i<DNASize; i++)
	{
		if (random<int>(1, 100) >= 50)child.genes.push_back(genes[i]);
		else child.genes.push_back(partner.genes[i]);
	}
	return child;
}
void DNA::mutate(float mutationRate)
{
	for (int i = 0; i<DNASize; i++)
	{
		if (random() % 10000 / 10000.0 <= mutationRate)
			genes[i] = random() % 2;
	}
}
Size DNA::getPhrase()
{
	Size s = Size(0, 0);
	for (int i = 0; i<DNASize; i++)
		s.height += genes[i] << i;
	s.height += minPhrase;
	s.width = s.height;
	return s;
}