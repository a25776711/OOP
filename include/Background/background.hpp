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
<<<<<<< Updated upstream
	Background(std::string BackgroundPath);
=======
	BackgroundImage():GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Background/open.png"), -10) {

	};
	void NextLevel(const int level) {
			auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
			temp -> SetImage(BackgroundImagePath(level));

	}

>>>>>>> Stashed changes



private:

	inline std::string BackgroundImagePath(int level) {
		return RESOURCE_DIR"/Resource/Background/bg" + std::to_string(level) + ".jpg";
	}
	std::string  m_BackGround;


};



#endif //BACKGROUND_HPP
