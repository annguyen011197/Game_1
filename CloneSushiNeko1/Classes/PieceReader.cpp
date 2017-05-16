#include "PieceReader.h"
#include "Piece.h"
using namespace cocos2d;

static PieceReader* _instanceCharacterReader = nullptr;

PieceReader* PieceReader::getInstance() {
	if (!_instanceCharacterReader) {
		_instanceCharacterReader = new PieceReader;
	}
	return _instanceCharacterReader;
}

void PieceReader::purge() {
	CC_SAFE_DELETE(_instanceCharacterReader);
}

Node* PieceReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions) {
	Piece* node = Piece::create();
	setPropsWithFlatBuffers(node, nodeOptions);
	return node;
}