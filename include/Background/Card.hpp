//
// Created by bingho on 2025/3/20.
//

#ifndef CARD_HPP
#define CARD_HPP
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <string>

class Card : public Util::GameObject{
public:
      Card():GameObject() {
            SetPath();
      };

      std::vector<std::shared_ptr<Card>> SetCards(int level) {
            auto cards =  std::vector<std::shared_ptr<Card>>();
            cards.push_back(m_sunflow,m_peashooter);
            if (level >= 2){cards.push_back(m_cherrybomb);}
            if (level >= 3){cards.push_back(m_wallnut);}
            if (level>=4){cards.push_back(m_iceshooter);}
            if (level>=5){cards.push_back(m_chomper);}
            return cards;

      }

      void SetPath() {
            m_peashooter -> SetImage(RESOURCE_DIR"/Background/Card/card1.png");
            m_sunflow -> SetImage(RESOURCE_DIR"/Background/Card/card2.png");
            m_cherrybomb ->SetImage(RESOURCE_DIR"/Background/Card/card3.png");
            m_wallnut -> SetImage(RESOURCE_DIR"/Background/Card/card4.png");
            m_mine -> SetImage(RESOURCE_DIR"/Background/Card/card5.png");
            m_iceshooter -> SetImage(RESOURCE_DIR"/Background/Card/card6.png");
            m_chomper -> SetImage(RESOURCE_DIR"/Background/Card/card7.png");
      }

protected:
      std::make_shared<Util::Image> m_peashooter;
      std::make_shared<Util::Image> m_cherrybomb;
      std::make_shared<Util::Image> m_iceshooter;
      std::make_shared<Util::Image> m_chomper;
      std::make_shared<Util::Image> m_mine;
      std::make_shared<Util::Image> m_wallnut;
      std::make_shared<Util::Image> m_sunflow;
};


#endif //CARD_HPP
