//
// Created by bingho on 2025/3/20.
//

#ifndef BUTTOM_HPP
#define BUTTOM_HPP

#include "GameObject.hpp"
#include "Util/Image.hpp"
#include <string>


class adventure : public GameObject{
    public:
        explicit  adventure():GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Background/Adventure_1.png"), -5){

        }
        void ChangeImage() {
            auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
                return temp -> SetImage(RESOURCE_DIR"/Background/Adventure.png");
        }
        void NextLevel(int level){
            auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
            if (level==0) {
                temp -> SetImage(RESOURCE_DIR"/Background/Adventure_1.png");
            }
            else {
                temp -> SetImage(RESOURCE_DIR"/Background/list.png");
            }
        }
    private:



};

#endif //BUTTOM_HPP
