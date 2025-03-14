//
// Created by bingho on 2025/3/14.
//

#ifndef UPDATEBACKGROUND_HPP
#define UPDATEBACKGROUND_HPP

#include "Background/background.hpp"
#include "Util/GameObject.hpp"

class UpdateBackground{
    public:
        UpdateBackground ();

		void NextLevel();

        [[nodiscard]] std::shared_ptr<Util::GameObject> GetChild() const {
            return m_Background;
        }
        void SetScale(const glm::vec2& scale) {
            m_Background ->GetScaledSize() = scale;
        }
    private:
        std::shared_ptr<BackgroundImage> m_Background;
        int m_level = 0;
};


#endif //UPDATEBACKGROUND_HPP
