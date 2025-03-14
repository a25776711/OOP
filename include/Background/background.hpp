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
	Background(std::string BackgroundPath);



private:
	std::string BackgroundPath;

};



#endif //BACKGROUND_HPP
