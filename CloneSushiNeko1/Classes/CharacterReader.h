#include "cocos2d.h"
#include "cocostudio\WidgetReader\NodeReader\NodeReader.h"
#include "Character.h"

class CharacterReader : public cocostudio::NodeReader
{
public:
	static CharacterReader* getInstance();
	static void purge();
	cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};