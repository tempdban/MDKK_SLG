#include "StartScene.h"
#include "LoadingScene.h"

#include "Common.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
	auto scene = Scene::create();

	auto layer = StartScene::create();

	scene -> addChild(layer);

	return scene;
}

bool StartScene::init()
{
	if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto bg = Sprite::create("start_bg.jpg");

	bg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));

	addChild(bg, 1);

	//create Menu
	auto btn_start = MenuItemImage::create("btn_start_0.png","btn_start_1.png",CC_CALLBACK_1(StartScene::toggleMainScene,this));

	btn_start->setPosition(Vec2(-200,-160));

	auto btn_end = MenuItemImage::create("btn_end_0.png","btn_end_1.png",CC_CALLBACK_1(StartScene::exit,this));

	btn_end->setPosition(Vec2(200,-160));

	auto menu = Menu::create(btn_start,btn_end, NULL);

	addChild(menu,2);

	return true;
}

void StartScene::toggleMainScene(Ref* pSender)
{
	auto loadingScene = LoadingScene::createScene(SceneType::MAP);

	Director::getInstance()->replaceScene(loadingScene);
}

void StartScene::exit(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

