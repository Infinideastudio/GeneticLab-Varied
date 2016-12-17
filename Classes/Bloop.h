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
	//�������
	Bloop(cocos2d::Layer& layer, int ZOrder);
	//���׷�ֳ
	Bloop(cocos2d::Layer& layer, int ZOrder, Bloop& parent);
	//˫�׷�ֳ
	Bloop(cocos2d::Layer& layer, int ZOrder, Bloop& parentA, Bloop& parentB);
	~Bloop();
	//����size�����ٶȵĲ���A��B��speed=A+B*size
	float speedCalcPrmA;
	float speedCalcPrmB;
	//tick��cycle�����ٶ�
	float cycleIncPerTick;
	//���ϸ�����ڣ����������
	float maxCycle;
	virtual void refreshPosition(cocos2d::Vec2 camera_);
	virtual void move();
	void tick(World& world);
	bool die;
	//ϸ������
	float cycle;
private:
	DNA dna;
	//��ʳ��
	void eatFood(World& world);
	//��Bloop
	void eatBloop(World& world);
	//�ı�cycle
	void changeCycle(World& world);
	//ÿtick����ʳ��ĸ��ʣ���Χ��0~1֮�䡣
	float foodProvideRatePerTick();
	//����ʳ��
	void provideFood(World& world);
	//����
	void divide(World& world);
	cocos2d::Label* label;
	PerlinNoise noise;
	int eatCD;
	unsigned long long noiseX;
	void init(cocos2d::Layer& layer, int ZOrder);
};
#endif