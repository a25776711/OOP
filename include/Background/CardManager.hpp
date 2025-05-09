//
// Created by bingho on 2025/3/23.
//

#ifndef CARDMANAGER_HPP
#define CARDMANAGER_HPP


#include "Card.hpp"
#include <vector>
#include <memory>

class CardManager {
public:
    CardManager() {
        allCards.push_back(std::make_shared<Card>(RESOURCE_DIR "/Background/Card/card1.png",1)); // peashooter
        allCards.push_back(std::make_shared<Card>(RESOURCE_DIR "/Background/Card/card2.png",2)); // sunflow
        allCards.push_back(std::make_shared<Card>(RESOURCE_DIR "/Background/Card/card3.png",3)); // cherrybomb
        allCards.push_back(std::make_shared<Card>(RESOURCE_DIR "/Background/Card/card4.png",4)); // wallnut
        allCards.push_back(std::make_shared<Card>(RESOURCE_DIR "/Background/Card/card5.png",5)); // mine
        allCards.push_back(std::make_shared<Card>(RESOURCE_DIR "/Background/Card/card6.png",6)); // iceshooter
        allCards.push_back(std::make_shared<Card>(RESOURCE_DIR "/Background/Card/card7.png",7)); // chomper
        allCards.push_back(std::make_shared<Card>(RESOURCE_DIR "/Background/Card/card8.png",8)); // fastshooter
    }

    std::vector<std::shared_ptr<Card>> SetCards(int level) {
        std::vector<std::shared_ptr<Card>> result;

        for (int i = 0; i < level && i < allCards.size(); ++i) {
            allCards[i]-> SetVisible(true);
            allCards[i]-> m_Transform.scale ={0.45,0.45};

            // std::cout << "true"<<i << std::endl;
            result.push_back(allCards[i]);
        }

        return result;
    }

private:
    std::vector<std::shared_ptr<Card>> allCards;
};


#endif //CARDMANAGER_HPP
