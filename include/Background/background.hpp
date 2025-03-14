//
// Created by bingho on 2025/3/11.
//

#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <string>

class Background : public Util::GameObject {

public:
	Background() : GameObject(
            std::make_unique<Util::Image>(RESOURCE_DIR"/Resources//Background/open.png"), -10) {
    }



private:
	std::string BackgroundPath;

};



#endif //BACKGROUND_HPP
