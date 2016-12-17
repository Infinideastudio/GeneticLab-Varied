#include "Bloop.h"
#include "HelloWorldScene.h"
#include "genetic_lab_varied.h"
using namespace cocos2d;
Bloop::~Bloop()
{
	label->removeFromParent();
	sprite->removeFromParent();
}
void Bloop::init(Layer& layer, int ZOrder)
{
	initSprite(layer, "images\\bloop.png", ZOrder);
	shape = Shape::circle;
	setColor(Color3B(255, 255, 0));
	setRandomPosition(Vec2(0, 0), genetic_lab_varied::superHugeSize);
	setSize(dna.getPhrase());
	label = Label::createWithTTF("1", "fonts/Marker Felt.ttf", 0.6*size.width);
	layer.addChild(label, ZOrder + 1);
	speed = speedCalcPrmA + size.width*speedCalcPrmB;
	noise.seed = random<unsigned long long>(0, 18446744073709551615ULL);
	noise.amplitude = 1;
	noise.frequency = 0.0025*(speed);
	noiseX = 0;
	cycle = maxCycle / 4;
	die = false;
}
Bloop::Bloop(Layer& layer, int ZOrder)
{
	dna = DNA(8,32);
	init(layer, ZOrder);
	cycle = random<int>(maxCycle * 1 / 6, maxCycle * 1 / 4);
}
Bloop::Bloop(Layer& layer, int ZOrder, Bloop& parent)
{
	dna = parent.dna.crossover(parent.dna);
	dna.mutate(0.02);
	init(layer, ZOrder);
}
Bloop::Bloop(Layer& layer, int ZOrder, Bloop& parentA, Bloop& parentB)
{
	dna = parentA.dna.crossover(parentB.dna);
	dna.mutate(0.02);
	init(layer, ZOrder);
}
//改变cycle
void Bloop::changeCycle(World& world)
{
	cycle += 0.03;
}
//吃食物
void Bloop::eatFood(World& world)
{
	for (auto iter = world.food.begin(); iter != world.food.end();)
	{
		if (hit(**iter))
		{
			cycle += Food::energy;
			iter = world.food.erase(iter);
		}
		else ++iter;
	}
}
//吃Bloop
void Bloop::eatBloop(World& world)
{
	/*if (eatCD > 0)return;
	for (auto iter = world.bloop.begin(); iter != world.bloop.end(); ++iter)
	{
		if (((*iter)->bloopType == BloopType::floop || (*iter)->bloopType == BloopType::gloop) && hit(**iter) && size.width>(*iter)->getSize().width)
		{
			(*iter)->die = true;
			cycle += (*iter)->cycle*genetic_lab_varied::energyTransferEfficiency;
				eatCD = (*iter)->bloopType == BloopType::floop ? 500 : 250;
			break;
		}
	}*/
}
//掉落食物
void Bloop::provideFood(World& world)
{
	float randomNumber = random<float>(0, 1);
	if (randomNumber < foodProvideRatePerTick())
	{
		cycle -= Food::energy / genetic_lab_varied::energyTransferEfficiency;
		world.food.emplace_back(std::make_shared<Food>(world, 1));
		(*(world.food.end() - 1))->setPosition(getPosition());
	}
}
float Bloop::foodProvideRatePerTick()
{
	if (cycle < 70)return 0;
	else return 0.0008 + cycle*0.000005;
}
void Bloop::divide(World& world)
{
	if (cycle >= maxCycle)
	{
		die = true;
		for (int i = 0; i < 2; ++i)
		{
			world.bloop.emplace_back(std::make_shared<Bloop>(world, 1, *this));
			(*(world.bloop.end() - 1))->setPosition(getPosition());
		}
	}
}
void Bloop::move()
{
	float rad = noise.perlin_noise(noiseX);
	rad -= ((int)(rad / (2.0 * PI))) * 2.0 * PI;
	Vec2 deltaPosition= Vec2(cosf(rad),sinf(rad))*speed;
	setPosition(getPosition() + deltaPosition);
	if (getPosition().x < -100)setPosition(getPosition()+Vec2(worldSizeX+150,0));
	if (getPosition().x > worldSizeX+100)setPosition(getPosition() + Vec2(-1 * worldSizeX-150, 0));
	if (getPosition().y < -100)setPosition(getPosition() + Vec2(0, worldSizeY + 150));
	if (getPosition().y > worldSizeY+100)setPosition(getPosition() + Vec2(0, -1 * worldSizeY - 150));
	noiseX++;
}
void Bloop::refreshPosition(Vec2 camera_)
{
	sprite->setPosition(position - camera_);
	label->setPosition(position - camera_);
}
void Bloop::tick(World& world)
{
	//移动
	move();
	//改变cycle
	changeCycle(world);
	//吃食物
	eatFood(world);
	//吃bloop
	eatBloop(world);
	//提供食物
	provideFood(world);
	//绘制
	refreshPosition(world.camera);
	//分裂
	divide(world);
}
