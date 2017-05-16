#ifndef __SushiNeko	__Character__
#define __SushiNeko	__Character__

#include "cocos2d.h"
#include "Constants.h"

class Piece : public cocos2d::Node
{
public:
	CREATE_FUNC(Piece);
	float getSpriteHeight() const;
	void setObstacleSlide(Side);
	Side getObstacleSlide();

protected:
	Side obstacleSlide;
	bool init() override;
};

#endif