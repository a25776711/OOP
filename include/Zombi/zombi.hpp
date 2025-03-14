//
// Created by a2577 on 25-3-10.
//
#ifndef ZOMBI_HPP
#define ZOMBI_HPP
#include "Util/GameObject.hpp"
#include "Util/Animation.hpp"

class Zombi:public Util::GameObject {
public:
    explicit Zombi(const std::string& ImagePath);

    Zombi(const Zombi&) = delete;

    Zombi(Zombi&&) = delete;

    Zombi& operator=(const Zombi&) = delete;

    Zombi& operator=(Zombi&&) = delete;

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    // TODO: Implement the collision detection
    [[nodiscard]] bool IfCollides(const std::shared_ptr<Zombi>& other) const {
        (void) other;
        return false;
    }

    // TODO: Add and implement more methods and properties as needed to finish Giraffe Adventure.

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;

};

#endif //ZOMBI_HPP
