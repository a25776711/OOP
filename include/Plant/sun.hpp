//
// Created by bingho on 2025/3/11.
//

#ifndef SUN_HPP
#define SUN_HPP
#include  "Plant/plant.hpp"
#include <glm/glm.hpp>
class Sun : public Plant {
    public:
    explicit  Sun(std::vector<std::string>& Path,int interval=100):Plant(Path,interval) {

    }
    void CollectAndMove(glm::vec2 click,glm::vec2& des);
    float CrossProduct(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3) {
        return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    }
    bool CheckHit(const glm::vec2& point) {
        // 計算點與每個邊的叉積
        bool b1 = CrossProduct(p1, p2, point) >= 0;
        bool b2 = CrossProduct(p2, p3, point) >= 0;
        bool b3 = CrossProduct(p3, p4, point) >= 0;
        bool b4 = CrossProduct(p4, p1, point) >= 0;
        // 檢查四個叉積是否都為正或都為負，這意味著點在四邊形內

        return (b1 == b2) && (b2 == b3) && (b3 == b4);
    }
    private:
    glm::vec2 p1={m_Transform.translation.x+10,m_Transform.translation.y+10};
    glm::vec2 p2={m_Transform.translation.x-10,m_Transform.translation.y+10};
    glm::vec2 p3={m_Transform.translation.x-10,m_Transform.translation.y-10};
    glm::vec2 p4={m_Transform.translation.x+10,m_Transform.translation.y-10};

};
#endif //SUN_HPP
