#include"Food.h"
#include"genetic_lab_varied.h"
using namespace cocos2d;
Food::Food(Layer& layer, int ZOrder)
{
	shape = Shape::square;
	initSprite(layer, "images\\food.png", ZOrder);
	setRandomColor();
	setRandomPosition(Vec2(0, 0), genetic_lab_varied::superHugeSize);
	setSize(Size(10, 10));
}
bool Food::hit(Entity* another)
{
	if (getSize().width / 2 + another->getSize().width / 2 <= sqrt(getPosition().distance(another->getPosition())))return false;
	return true;
}