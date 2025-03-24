#ifndef CARD_HPP
#define CARD_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <string>
#include <memory>

class Card : public Util::GameObject {
public:
      Card(const std::string& imagePath) {
            auto image = std::make_shared<Util::Image>(imagePath);
            SetDrawable(image);
      }
};

#endif // CARD_HPP
