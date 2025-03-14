//
// Created by bingho on 2025/3/11.
//

#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <string>


class BackgroundImage : public Util::GameObject {

public:


	BackgroundImage():GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Background/open.png"), -10) {

	};
	void NextLevel(const int level) {
		int tmp;
		if (level==0){tmp=0;}
		else if (level==1){tmp=1;}
		else if (level==2){tmp=3;}
		else {tmp=5;}
		auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
		temp -> SetImage(BackgroundImagePath(tmp));

	}






private:

	inline std::string BackgroundImagePath(int level) {
		return RESOURCE_DIR"/Background/bg" + std::to_string(level) + ".jpg";
	}
	std::string  m_BackGround;


};



#endif //BACKGROUND_HPP
