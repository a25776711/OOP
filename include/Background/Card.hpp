//
// Created by bingho on 2025/3/20.
//

#ifndef CARD_HPP
#define CARD_HPP
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <string>


class Card : public Util::GameObject {
public:
      Card() : GameObject() {
            // 初始化卡片圖片
            m_peashooter = std::make_shared<Util::Image>(RESOURCE_DIR "/Background/Card/card1.png");
            m_sunflow = std::make_shared<Util::Image>(RESOURCE_DIR "/Background/Card/card2.png");
            m_cherrybomb = std::make_shared<Util::Image>("/Background/Card/card3.png");
            m_wallnut = std::make_shared<Util::Image>(RESOURCE_DIR "/Background/Card/card4.png");
            m_mine = std::make_shared<Util::Image>(RESOURCE_DIR "/Background/Card/card5.png");
            m_iceshooter = std::make_shared<Util::Image>(RESOURCE_DIR "/Background/Card/card6.png");
            m_chomper = std::make_shared<Util::Image>(RESOURCE_DIR "/Background/Card/card7.png");
      }

      std::vector<std::shared_ptr<Util::Image>> SetCards(int level) {
            std::cout<<"test"<<std::endl;
            std::vector<std::shared_ptr<Util::Image>> cards;
            cards.push_back(m_sunflow);
            cards.push_back(m_peashooter);
            if (level >= 2) cards.push_back(m_cherrybomb);
            if (level >= 3) cards.push_back(m_wallnut);
            if (level >= 4) cards.push_back(m_iceshooter);
            if (level >= 5) cards.push_back(m_chomper);
            return cards;
      }




protected:
      std::shared_ptr<Util::Image> m_peashooter;
      std::shared_ptr<Util::Image> m_cherrybomb;
      std::shared_ptr<Util::Image> m_iceshooter;
      std::shared_ptr<Util::Image> m_chomper;
      std::shared_ptr<Util::Image> m_mine;
      std::shared_ptr<Util::Image> m_wallnut;
      std::shared_ptr<Util::Image> m_sunflow;
};



#endif //CARD_HPP
