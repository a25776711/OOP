//
// Created by bingho on 2025/3/11.
//

#ifndef SUN_HPP
#define SUN_HPP
#include  "Plant/plant.hpp"
#include <glm/glm.hpp>
enum MoveState {
    Droping,
    Collectable,
    CollectMoving,
    MoveOver
};

class Sun : public Plant {
    public:
    bool CheckHit(const glm::vec2& point) {
        // 計算點與每個邊的叉積
        bool b1 = CrossProduct(p1, p2, point) >= 0;
        bool b2 = CrossProduct(p2, p3, point) >= 0;
        bool b3 = CrossProduct(p3, p4, point) >= 0;
        bool b4 = CrossProduct(p4, p1, point) >= 0;
        // 檢查四個叉積是否都為正或都為負，這意味著點在四邊形內

        return (b1 == b2) && (b2 == b3) && (b3 == b4);
    }
    float CrossProduct(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3) {
        return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    }
    explicit  Sun(bool flower,glm::vec2 pos);
    void CollectAndMove(glm::vec2 click);
    void Move();
    MoveState GetMoveState() {return m_state;}

    private:
    MoveState m_state=MoveState::Collectable;
    bool m_click=false;
    glm::vec2 m_drop;
    bool m_flower;
    glm::vec2 m_des={-600,260};
    glm::vec2 p1={m_Transform.translation.x+20,m_Transform.translation.y+20};
    glm::vec2 p2={m_Transform.translation.x-20,m_Transform.translation.y+20};
    glm::vec2 p3={m_Transform.translation.x-20,m_Transform.translation.y-20};
    glm::vec2 p4={m_Transform.translation.x+20,m_Transform.translation.y-20};

};
#endif //SUN_HPP
