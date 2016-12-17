#ifndef BLOOP_H
#define BLOOP_H
#include "cocos2d.h"
#include "Entity.h"
#include "DNA.h"
#include "PerlinNoise.h"
#include "Food.h"
class World;
class Bloop final:public Entity
{
public:
	//随机产生
	Bloop(cocos2d::Layer& layer, int ZOrder);
	//单亲繁殖
	Bloop(cocos2d::Layer& layer, int ZOrder, Bloop& parent);
	//双亲繁殖
	Bloop(cocos2d::Layer& layer, int ZOrder, Bloop& parentA, Bloop& parentB);
	~Bloop();
	//根据size计算速度的参数A和B，speed=A+B*size
	float speedCalcPrmA;
	float speedCalcPrmB;
	//tick的cycle增长速度
	float cycleIncPerTick;
	//最大细胞周期，超过则分裂
	float maxCycle;
	virtual void refreshPosition(cocos2d::Vec2 camera_);
	virtual void move();
	void tick(World& world);
	bool die;
	//细胞周期
	float cycle;
private:
	DNA dna;
	//吃食物
	void eatFood(World& world);
	//吃Bloop
	void eatBloop(World& world);
	//改变cycle
	void changeCycle(World& world);
	//每tick产生食物的概率，范围在0~1之间。
	float foodProvideRatePerTick();
	//掉落食物
	void provideFood(World& world);
	//分裂
	void divide(World& world);
	cocos2d::Label* label;
	PerlinNoise noise;
	int eatCD;
	unsigned long long noiseX;
	void init(cocos2d::Layer& layer, int ZOrder);
};
#endif