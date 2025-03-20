//
// Created by bingho on 2025/3/14.
//

#ifndef UPDATEBACKGROUND_HPP
#define UPDATEBACKGROUND_HPP

#include "Adventure.hpp"
#include "Background/background.hpp"
#include "Util/GameObject.hpp"

class UpdateBackground{
    public:
        UpdateBackground ();

		void NextLevel();

        [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() const {
            return {m_Background,m_Adventure};
        }

        int GetLevel() {return m_level;}
    private:
        std::shared_ptr<BackgroundImage> m_Background;
        std::shared_ptr<adventure> m_Adventure;
        int m_level = 0;
};


#endif //UPDATEBACKGROUND_HPP
