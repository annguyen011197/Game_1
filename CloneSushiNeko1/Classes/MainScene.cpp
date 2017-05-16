#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CharacterReader.h"
#include "PieceReader.h"
#define COCOS2D_DEBUG 1


USING_NS_CC;

using namespace cocostudio::timeline;

Scene* Main::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Main::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Main::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	CSLoader* instance = CSLoader::getInstance();
	instance->registReaderObject("CharacterReader", (ObjectFactory::Instance) CharacterReader::getInstance);
	instance->registReaderObject("PieceReader", (ObjectFactory::Instance) PieceReader::getInstance);

	
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
	Size size = Director::getInstance()->getVisibleSize();
	rootNode->setContentSize(size);
	ui::Helper::doLayout(rootNode);

	this->pieceNode = rootNode->getChildByName("pieceNode");
	this->character = rootNode->getChildByName<Character*>("character");
	this->pieceIndex = 0;
	this->gameState = GameState::Title;
	this->scoredLabel = rootNode->getChildByName<cocos2d::ui::Text*>("scoreLabel");
	this->lifeBG = rootNode->getChildByName<cocos2d::Sprite*>("life_bg");
	this->timebar = lifeBG->getChildByName<cocos2d::Sprite*>("lifeBar");



	for (int i = 0; i < 10; ++i)
	{	
		Piece* piece = dynamic_cast<Piece*>(CSLoader::createNode("Piece.csb"));

		this->lastObstacleSide = this->getSideForObstacle(this->lastObstacleSide);
		piece->setObstacleSlide(this->lastObstacleSide);

		float rollHeight = piece->getSpriteHeight();
		piece->setPosition(0.0f, rollHeight / 2.0f * i);

		this->pieceNode->addChild(piece);

		this->pieces.pushBack(piece);

	}

    this->addChild(rootNode);
	this->resetGameState();
    return true;
}

bool Main::isGameOver()
{
	bool gameOver = false;
	Piece* currentPiece = this->pieces.at(this->pieceIndex);
	if (currentPiece->getObstacleSlide() == this->character->getSide()) {
		gameOver = true;
	}	
	if (this->timeLeft == 0)
		gameOver = true;
	return gameOver;
}

void Main::onEnter()
{
	Layer::onEnter();
	this->setupTouchHandling();
	this->triggerTitle();
	this->scheduleUpdate();
	this->flyingPiecePosition = this->pieceNode->getPosition();
}

void Main::setupTouchHandling()
{
	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		switch (this->gameState)
		{
		case GameState::Ready:
			this->triggerPlaying();
		case GameState::Playing: {
			// get the location of the touch in the MainScene's coordinate system
			Vec2 touchLocation = this->convertTouchToNodeSpace(touch);

			// check if the touch was on the left or right side of the screen
			// move the character to the appropriate side
			if (touchLocation.x < this->getContentSize().width / 2.0f)
			{
				this->character->setSide(Side::Left);
			}
			else
			{
				this->character->setSide(Side::Right);
			}
			this->stepTower();
			this->character->runChopAnimation();
			if (this->isGameOver()) {
				this->triggerGameOver();
				return true;
			}
			this->setTimeLeft(this->timeLeft+0.25);
			this->setScore(this->score + 1);
			break;	
			}
		case GameState::GameOver: {
			this->resetGameState();
			this->triggerReady();
			break;
		}
		case GameState::Title: {
			this->triggerReady();
			break;
		}
		}
		return true;
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}



Side Main::getSideForObstacle(Side lastSide)
{
	Side s;
	switch (lastSide)
	{
	case Side::Left:
	case Side::Right:
		s = Side::None;
		break;
	case Side::None:
	{
		float random = CCRANDOM_0_1();
		if (random < 0.45)
			s = Side::Left;
		else if (random < 0.9)
			s = Side::Right;
		else
			s = Side::None;
		break;
	}
	}

	return s;
}

void Main::stepTower()
{
	Piece*  currentPiece = this->pieces.at(this->pieceIndex);
	this->animateHitPiece(currentPiece->getObstacleSlide());
	currentPiece->setPosition(currentPiece->getPosition() + 
		Vec2(0.0f, currentPiece->getSpriteHeight() / 2.0f * 10.0f));
	currentPiece->setLocalZOrder(currentPiece->getLocalZOrder() + 1);
	currentPiece->setObstacleSlide(this->getSideForObstacle(this->lastObstacleSide));	
	this->lastObstacleSide = currentPiece->getObstacleSlide();
	cocos2d::MoveBy* moveAction = cocos2d::MoveBy::create(0.15f, 
		Vec2(0.0f, -1.0f * currentPiece->getSpriteHeight() / 2.0f));
	this->pieceNode->runAction(moveAction);
	this->pieceIndex = (this->pieceIndex + 1) % 10;
}

void Main::triggerGameOver()
{
	this->gameState = GameState::GameOver;
	this->setTimeLeft(0);
	auto scene = this->getChildByName("Scene");
	auto mat = scene->getChildByName("mat");
	auto play = static_cast<cocos2d::ui::Button*>(scene->getChildByName("play"));
	cocos2d::ui::Text* gameOverScoreLabel = mat->getChildByName<cocos2d::ui::Text*>
										("gameOverScoreLabel");
	gameOverScoreLabel->setString(std::to_string(this->score));

	cocostudio::timeline::ActionTimeline* gameOverTimeLine = CSLoader::createTimeline("MainScene.csb");
	this->stopAllActions();
	this->runAction(gameOverTimeLine);
	gameOverTimeLine->play("gameOver", false);

	if (play) {
		play->addClickEventListener([=](Ref*) {
			this->resetGameState();
			this->triggerReady();
		});
	}
}

void Main::resetGameState()
{
	Piece *currentPiece = this->pieces.at(this->pieceIndex);
	this->setScore(0);
	this->setTimeLeft(5);
	currentPiece->setObstacleSlide(Side::None);
}

void Main::triggerPlaying()
{
	this->gameState = GameState::Playing;

	auto scene = this->getChildByName("Scene");
	cocos2d::Sprite* tapL = scene->getChildByName<cocos2d::Sprite*>("tap_left");
	cocos2d::Sprite* tapR = scene->getChildByName<cocos2d::Sprite*>("tap_right");

	cocos2d::FadeOut* leftFade = cocos2d::FadeOut::create(0.35f);
	cocos2d::FadeOut* rightFade = cocos2d::FadeOut::create(0.35f);

	tapL->runAction(leftFade);
	tapR->runAction(rightFade);

	this->scoredLabel->setVisible(true);
	this->lifeBG->setVisible(true);


}

void Main::triggerTitle()
{
	this->gameState = GameState::Title;

	cocostudio::timeline::ActionTimeline* titleTimeLine = CSLoader::createTimeline("MainScene.csb");
	this->stopAllActions();
	this->runAction(titleTimeLine);
	titleTimeLine->play("title", false);
}

void Main::triggerReady()
{
	this->gameState = GameState::Ready;
	auto scene = this->getChildByName("Scene");
	cocos2d::Sprite* tapL = scene->getChildByName<cocos2d::Sprite*>("tap_left");
	cocos2d::Sprite* tapR = scene->getChildByName<cocos2d::Sprite*>("tap_right");

	tapL->setOpacity(255);
	tapR->setOpacity(255);

	cocostudio::timeline::ActionTimeline* readyTimeline = CSLoader::createTimeline("MainScene.csb");
	this->stopAllActions();
	this->runAction(readyTimeline);
	readyTimeline->play("ready", false);
}

void Main::setScore(int score)
{
	this->score = score;
	this->scoredLabel->setString(std::to_string(score));
}

void Main::setTimeLeft(float timeLeft)
{
	this->timeLeft = clampf(timeLeft, 0, 10);
	this->timebar->setScaleX(timeLeft / 10);
	CCLOG("%f",this->timeLeft);
}

void Main::update(float dt)
{
	Layer::update(dt);
	if (this->gameState == GameState::Playing) {
		this->setTimeLeft(this->timeLeft - dt);
		if (this->timeLeft == 0)
			this->triggerGameOver();
	}
}

void Main::animateHitPiece(Side ObstacleSide)
{
	Piece* flyingPiece = dynamic_cast<Piece*>(CSLoader::createNode("Piece.csb"));
	flyingPiece->setObstacleSlide(ObstacleSide);

	flyingPiece->setPosition(this->flyingPiecePosition);
	this->addChild(flyingPiece);

	cocostudio::timeline::ActionTimeline* pieceTimeLine =
		CSLoader::createTimeline("Piece.csb");
	Side characterSide = this->character->getSide();
	std::string animationName = (characterSide == Side::Left) ? "moveRight" : "moveLeft";
	flyingPiece->runAction(pieceTimeLine); 
	pieceTimeLine->play(animationName, false);
	pieceTimeLine->setLastFrameCallFunc([this, &flyingPiece]() {
		this->removeChild(flyingPiece);
	});

}
