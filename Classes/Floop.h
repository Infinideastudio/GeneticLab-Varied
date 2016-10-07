#ifndef FLOOP_H
#define FLOOP_H
#include "cocos2d.h"
#include "Bloop.h"
#include "DNA.h"
using namespace cocos2d;
//Floop:初级消费者，以Gloop为食
class Floop :public Bloop
{
public:
	~Floop();
	//随机产生
	Floop(Layer& layer, int ZOrder);
	//单亲繁殖
	Floop(Layer& layer, int ZOrder, Floop& parent);
	//双亲繁殖
	Floop(Layer& layer, int ZOrder, Floop& parentA, Floop& parentB);
	//每tick要做的事
	virtual void tick(World& world);
private:
	DNA dna;
	//size的32~287线性映射到speed的10~2
	//根据size计算速度的参数A和B，speed=A+B*size
	const float speedCalcPrmA = 11.004;
	const float speedCalcPrmB = -0.0314;
	//tick的cycle增长速度
	const float cycleIncPerTick = -0.03;
	int eatCD;
	//最大细胞周期，超过则分裂
	const float maxCycle = 500;
	virtual void init(Layer& layer, int ZOrder);
	virtual void refreshPosition(Vec2 camera_);
};
#endif
