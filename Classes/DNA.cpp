#include "DNA.h"
using namespace cocos2d;
DNA::DNA()
{
	for (int i = 0; i < DNASize; i++)
	{
		genes[i] = random() % 2;
	}
}
DNA DNA::crossover(DNA partner)
{
	DNA child = DNA();
	for (int i = 0; i<DNASize; i++)
	{
		if (random() % 100 + 1 >= 50)child.genes[i] = genes[i];
		else child.genes[i] = partner.genes[i];
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