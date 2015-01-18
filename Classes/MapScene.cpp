#include "MapScene.h"

#include "Common.h"

USING_NS_CC;

Scene* MapScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MapScene::create();

	scene -> addChild(layer);

	return scene;
}

bool MapScene::init()
{
	if ( !Layer::init() )
    {
        return false;
    }

	return true;
}
