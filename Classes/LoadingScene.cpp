#include "LoadingScene.h"
#include "MapScene.h"

USING_NS_CC;

Scene* LoadingScene::createScene(SceneType target)
{
	auto scene = Scene::create();

	auto layer = LoadingScene::create();

	scene -> addChild(layer);

	layer->setTargetScene(target);

	return scene;
}

void LoadingScene::initLoadingAnimation()
{
	auto loading_animation = AnimationCache::getInstance()->getAnimation("loading");

	if(loading_animation)
	{
		return;
	}else{
		auto animation = Animation::create();

        animation->setDelayPerUnit(0.05f);

		for(int i = 0;i<25;i++)
		{
			auto sp_name = String::createWithFormat("load/load_%02d.png",i+1)->getCString();
			animation->addSpriteFrameWithFileName(sp_name);
		}
		AnimationCache::getInstance()->addAnimation(animation,"loading");
	}
}


bool LoadingScene::init()
{
	if ( !Layer::init() )
    {
        return false;
    }
	//clear cache
	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();

	TextureCache::getInstance()->removeUnusedTextures();

	//init loading sprite
	Size visibleSize = Director::getInstance()->getVisibleSize();

	initLoadingAnimation();

	auto loading_sprite = Sprite::create("load/load_01.png");

	loading_sprite->setTag(Tag::LOADING);

	loading_sprite->setPosition(Vec2(visibleSize.width-100,78));

	addChild(loading_sprite,0);

	auto label = LabelTTF::create("Now Loading...","Arial",20);

	label->setPosition(Vec2(visibleSize.width-100,25));

	addChild(label,0);

	return true;
}

void LoadingScene::onEnter()
{
	Layer::onEnter();

	auto loading_sprite = getChildByTag(Tag::LOADING);

	auto repeat = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("loading")));

	loading_sprite->runAction(repeat);
	
	//loadingResource();
	scheduleOnce(schedule_selector(LoadingScene::loadingResource),1.25f);
}


void LoadingScene::loadingResource(float delta)
{
	complete = 5;

	loading_count = 0;

	TextureCache::getInstance()->addImageAsync("MapB.png",CC_CALLBACK_0(LoadingScene::loadingProgress,this));
	TextureCache::getInstance()->addImageAsync("SO016.png",CC_CALLBACK_0(LoadingScene::loadingProgress,this));
	TextureCache::getInstance()->addImageAsync("SO010.png",CC_CALLBACK_0(LoadingScene::loadingProgress,this));
	TextureCache::getInstance()->addImageAsync("button.png",CC_CALLBACK_0(LoadingScene::loadingProgress,this));
	TextureCache::getInstance()->addImageAsync("loading.png",CC_CALLBACK_0(LoadingScene::loadingProgress,this));
}

void LoadingScene::toggleScene()
{
	auto mapScene = MapScene::createScene();

	Director::getInstance()->replaceScene(mapScene);
}

void LoadingScene::loadingProgress()
{
	loading_count++;

	if(complete<=loading_count){
		auto loading_sprite = getChildByTag(Tag::LOADING);

		loading_sprite->stopAllActions();

		toggleScene();
	}
}