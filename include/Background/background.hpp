//
// Created by bingho on 2025/3/11.
//

#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"


class BackgroundImage : public Util::GameObject {

public:
    BackgroundImage() : GameObject(
            std::make_unique<Util::Image>(GA_RESOURCE_DIR"/Resources/Background/bg0.png"), -10) {
    };



private:

  inline std::string ImagePath(const int phase) {
        return GA_RESOURCE_DIR"/Resources/Background/" + std::to_string(phase) + ".png";
    }
};



#endif //BACKGROUND_HPP
