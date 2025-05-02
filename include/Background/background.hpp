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


	BackgroundImage():GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Background/bg0.png"), -10) {
		m_Name="background";
		m_Transform.scale=glm::vec2(1.2f,1.2f);
	};
	void SetScale(float scale){
		m_Transform.scale=glm::vec2(scale,scale);
	}
	void SetPosition(glm::vec2 pos){
		m_Transform.translation=glm::vec3(pos.x,pos.y,0);
	}


	void NextLevel(int level) {
		int tmp;

		if (level==1){tmp=1;}
		else if (level==2){tmp=3;}
		else {tmp=5;}
		auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
		temp -> SetImage(BackgroundImagePath(tmp));
	}

private:

	inline std::string BackgroundImagePath(int level) {
		return RESOURCE_DIR"/Background/bg" + std::to_string(level) + ".jpg";
	}


};



#endif //BACKGROUND_HPP
