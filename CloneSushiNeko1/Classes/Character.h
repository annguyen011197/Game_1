#ifndef __SushiNeko__Character__
#define __SushiNeko__Character__

#include "cocos2d.h"
#include "Constants.h"
#include "cocostudio\CocoStudio.h"
#include "ui/CocosGUI.h"	

class Character : public cocos2d::Node
{
public:
	CREATE_FUNC(Character);
	void setSide(Side);
	Side getSide();
	void runChopAnimation();
protected:
	Side side;
	cocostudio::timeline::ActionTimeline* timeline;

	bool init() override;
	void onExit() override;

};

#endif