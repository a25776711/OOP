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
      Card():GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Background/Adventure_1.png"),0) {

      };



protected:

};


#endif //CARD_HPP
