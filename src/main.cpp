#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelSelectLayer.hpp>
class $modify(LevelSkipLayer, LevelSelectLayer) {
    bool init(int page) {
        if (!LevelSelectLayer::init(page)) {
            return false;
        }
        auto arrowsNormal = this->getChildByIDRecursive("arrows-menu");
        if (!arrowsNormal) return false;
        
        auto leftArrow = arrowsNormal->getChildByIDRecursive("left-button");
        auto rightArrow = arrowsNormal->getChildByIDRecursive("right-button");
        
        auto bigLeftArrowX = leftArrow->getPosition().x;
        auto bigLeftArrowY = leftArrow->getPosition().y;
        auto bigRightArrowX = rightArrow->getPosition().x;
        auto bigRightArrowY = rightArrow->getPosition().y;
        
        leftArrow->setPosition({leftArrow->getPosition().x + (leftArrow->getContentSize().width * 1.5f), leftArrow->getPosition().y});
        rightArrow->setPosition({rightArrow->getPosition().x - (rightArrow->getContentSize().width * 1.5f), rightArrow->getPosition().y});
        


        auto bigLeftArrow = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png"),
            this,
            menu_selector(LevelSkipLayer::onBigPrev)
        );
        arrowsNormal->addChild(bigLeftArrow);
        bigLeftArrow->setID("big-left-arrow"_spr);
        bigLeftArrow->setPosition({bigLeftArrowX, bigLeftArrowY});

		auto bigRightArrow = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_arrow_03_001.png"),
            this,
            menu_selector(LevelSkipLayer::onBigNext)
        );
        arrowsNormal->addChild(bigRightArrow);
        bigRightArrow->setID("big-right-arrow"_spr);
        bigRightArrow->setPosition({bigRightArrowX, bigRightArrowY});
		bigRightArrow->setScaleX(-1);


        arrowsNormal->updateLayout();
        return true;

		
    }
	void onBigPrev(CCObject* sender) {
		for (int i = 1; i <= Mod::get()->getSettingValue<int64_t>("level-scroll"); i++) {
			LevelSelectLayer::onPrev(sender);
		  }
	}
	void onBigNext(CCObject* sender) {
		for (int i = 1; i <= Mod::get()->getSettingValue<int64_t>("level-scroll"); i++) {
			LevelSelectLayer::onNext(sender);
		  }
	}
};
