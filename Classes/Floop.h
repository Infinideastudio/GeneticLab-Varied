#ifndef FLOOP_H
#define FLOOP_H
#include "cocos2d.h"
#include "Bloop.h"
#include "DNA.h"
using namespace cocos2d;
//Floop:���������ߣ���GloopΪʳ
class Floop :public Bloop
{
public:
	~Floop();
	//�������
	Floop(Layer& layer, int ZOrder);
	//���׷�ֳ
	Floop(Layer& layer, int ZOrder, Floop& parent);
	//˫�׷�ֳ
	Floop(Layer& layer, int ZOrder, Floop& parentA, Floop& parentB);
	//ÿtickҪ������
	virtual void tick(World& world);
private:
	DNA dna;
	//size��32~287����ӳ�䵽speed��10~2
	//����size�����ٶȵĲ���A��B��speed=A+B*size
	const float speedCalcPrmA = 11.004;
	const float speedCalcPrmB = -0.0314;
	//tick��cycle�����ٶ�
	const float cycleIncPerTick = -0.03;
	int eatCD;
	//���ϸ�����ڣ����������
	const float maxCycle = 500;
	virtual void init(Layer& layer, int ZOrder);
	virtual void refreshPosition(Vec2 camera_);
};
#endif