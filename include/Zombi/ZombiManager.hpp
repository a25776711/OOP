//
// Created by bingho on 2025/3/28.
//

#ifndef ZOMBIMANGER_HPP
#define ZOMBIMANGER_HPP
#include "zombi.hpp"
#include "normal.hpp"
class ZombiManager{
public:
   ZombiManager() {
     SetZombies();
   };

void SetZombies(){
  m_zombies1.push_back(std::make_shared<normal>());
  m_zombies1.push_back(std::make_shared<normal>());

  m_zombies2.push_back(std::make_shared<normal>());
  m_zombies2.push_back(std::make_shared<normal>());
  m_zombies3.push_back(std::make_shared<normal>());
};

std::vector<std::shared_ptr<zombi>> GetZombi(int level) {
  switch (level) {
    case 1:
      m_result = m_zombies1;
      break;
    case 2:
      m_result = m_zombies2;
      break;
    default:
      break;
  }
  for (auto zombi : m_result) {
    zombi -> SetLoopingandPlay(true);
    zombi -> SetZIndex(51);
  }
    return m_result;
}

std::vector<std::shared_ptr<Util::GameObject>> GetZombiesAsGameObjects(std::vector<std::shared_ptr<zombi>> m_zombies) {
  std::vector<std::shared_ptr<Util::GameObject>> result;
  for (const auto& z : m_zombies) {
    result.push_back(std::static_pointer_cast<Util::GameObject>(z));
  }
  return result;
}

void move() {
  for (auto zombi : m_result) {
    zombi -> move();
  }
}


  private:
    std::vector<std::shared_ptr<zombi>> m_result;
    std::vector<std::shared_ptr<zombi>> m_zombies1;
    std::vector<std::shared_ptr<zombi>> m_zombies2;
    std::vector<std::shared_ptr<zombi>> m_zombies3;


};
#endif //ZOMBIMANGER_HPP
