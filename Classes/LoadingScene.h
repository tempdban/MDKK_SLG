#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"
#include "Common.h"

class LoadingScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene(SceneType targetScene);

	virtual bool init();

	virtual void onEnter();

	void initLoadingAnimation();

	void loadingResource(float delta);

	void loadingProgress();

	void toggleScene();

	void setTargetScene(SceneType targetScene){
		_targetScene = targetScene;
	};

	CREATE_FUNC(LoadingScene);

private:

	SceneType _targetScene;

	int loading_count;

	int complete;

};
#endif