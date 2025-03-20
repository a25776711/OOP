//
// Created by bingho on 2025/3/20.
//

#ifndef BUTTOM_HPP
#define BUTTOM_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <string>


class adventure : public Util::GameObject{
    public:
        explicit  adventure():GameObject(std::make_unique<Util::Image>(RESOURCE_DIR"/Background/Adventure_1.png"), -10){

        }

        // [[nodiscard]] void onclick(bool pause){
        //     if (pause == true){
        //         auto temp = std::dynamic_pointer_cast<Util::Image>(m_Drawable);
        //         temp -> SetImage(RESOURCE_DIR"/Background/Adventure.png");
        //     }
        // };


        // [[nodiscard]] std::shared_ptr<Util::GameObject> GetChild() const {
        //     return m_buttom;
        // }
    private:
        //std::shared_ptr<adventure> m_buttom;

};

#endif //BUTTOM_HPP
