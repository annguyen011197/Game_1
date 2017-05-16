#include "Piece.h"
using namespace cocos2d;

float Piece::getSpriteHeight() const
{
	Sprite* roll = this->getChildByName<Sprite*>("roll");
	return roll->getContentSize().height;
}

void Piece::setObstacleSlide(Side s)
{
	this->obstacleSlide = s;
	Sprite* roll = this->getChildByName<Sprite*>("roll");
	Sprite* lChopsticks = roll->getChildByName<Sprite*>("leftChopstick");
	Sprite* rChopsticks = roll->getChildByName<Sprite*>("rightChopstick");
	switch (s)
	{
	case Side::Left:
		lChopsticks->setVisible(false);
		rChopsticks->setVisible(true);
		break;
	case Side::Right:
		lChopsticks->setVisible(true);
		rChopsticks->setVisible(false);
		break;
	case Side::None:
		lChopsticks->setVisible(false);
		rChopsticks->setVisible(false);
		break;
	}
}

Side Piece::getObstacleSlide()
{
	return this->obstacleSlide;
}

bool Piece::init()
{
	if (!Node::init())
	{
		return false;
	}

	// a piece defaults to having no obstacle
	this->obstacleSlide = Side::None;

	return true;
}
