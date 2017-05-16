#include "Character.h"

void Character::setSide(Side s)
{
	this->side = s;
	if (this->side == Side::Right)
		this->setScaleX(-1.0f);
	else
		this->setScaleX(1.0f);
}

Side Character::getSide()
{
	return this->side;
}

bool Character::init()
{
	if (!Node::init())
		return false;
	this->side = Side::Left;
	this->timeline = cocos2d::CSLoader::createTimeline("Character.csb");
	this->timeline->retain();
	return true;
}

void Character::onExit()
{
	this->timeline->release();
	Node::onExit();
}

void Character::runChopAnimation()
{
	this->stopAllActions();
	this->runAction(this->timeline);
	this->timeline->play("chop", false);
}
