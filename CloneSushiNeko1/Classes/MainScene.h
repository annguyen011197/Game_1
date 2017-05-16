#ifndef __Main_SCENE_H__
#define __Main_SCENE_H__

#include "cocos2d.h"
#include "Piece.h"
#include "Character.h"
#include "Constants.h"
#include "ui/CocosGUI.h"	

enum class	GameState {
	Title,
	Ready,	
	Playing,
	GameOver
};

class Piece;
class Character;
class Main : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(Main);
private:
	Side lastObstacleSide = Side::Right;
	cocos2d::Node*	pieceNode;
	cocos2d::Vector<Piece*> pieces;
	cocos2d::ui::Text *scoredLabel;
	cocos2d::Sprite* timebar;
	cocos2d::Sprite* lifeBG;
	cocos2d::Vec2 flyingPiecePosition;
	float timeLeft;
	int score;
	GameState gameState;
	int pieceIndex;
	bool  isGameOver();

protected:
	Character* character;
	void onEnter() override;
	void setupTouchHandling();
	Side getSideForObstacle(Side lastSide);
	void stepTower();
	void triggerGameOver();
	void resetGameState();
	void triggerPlaying();
	void triggerTitle();
	void triggerReady();
	void setScore(int);
	void setTimeLeft(float timeLeft);
	void update(float dt) override;
	void animateHitPiece(Side ObstacleSide);

};

#endif // __Main_SCENE_H__
