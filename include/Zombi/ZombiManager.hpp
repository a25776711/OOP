//
// Created by bingho on 2025/3/28.
//

#ifndef ZOMBIMANGER_HPP
#define ZOMBIMANGER_HPP
#include <iostream>

#include "zombi.hpp"
#include "normal.hpp"
#include "hat.hpp"
#include "bucket.hpp"
#include "armor.hpp"
class ZombiManager{
public:
   ZombiManager() {
     SetZombies();
   };

void SetZombies(){
  m_zombies1.push_back(std::make_shared<armor>());
  m_zombies1.push_back(std::make_shared<armor>());

  m_zombies2.push_back(std::make_shared<hat>());
  m_zombies2.push_back(std::make_shared<hat>());

  m_zombies3.push_back(std::make_shared<normal>());
  m_zombies3.push_back(std::make_shared<normal>());
  m_zombies3.push_back(std::make_shared<normal>());

  m_zombies4.push_back(std::make_shared<bucket>());
  m_zombies4.push_back(std::make_shared<bucket>());
  m_zombies4.push_back(std::make_shared<bucket>());
  m_zombies4.push_back(std::make_shared<bucket>());

  m_zombies5.push_back(std::make_shared<normal>());
  m_zombies5.push_back(std::make_shared<armor>());
  m_zombies5.push_back(std::make_shared<hat>());
  m_zombies5.push_back(std::make_shared<bucket>());
  m_zombies5.push_back(std::make_shared<normal>());
  m_zombies5.push_back(std::make_shared<armor>());
  m_zombies5.push_back(std::make_shared<hat>());
  m_zombies5.push_back(std::make_shared<bucket>());

  m_zombies6.push_back(std::make_shared<normal>());
  m_zombies6.push_back(std::make_shared<armor>());
  m_zombies6.push_back(std::make_shared<hat>());
  m_zombies6.push_back(std::make_shared<bucket>());
  m_zombies6.push_back(std::make_shared<normal>());
  m_zombies6.push_back(std::make_shared<armor>());
  m_zombies6.push_back(std::make_shared<hat>());
  m_zombies6.push_back(std::make_shared<bucket>());
  m_zombies6.push_back(std::make_shared<normal>());
  m_zombies6.push_back(std::make_shared<armor>());
  m_zombies6.push_back(std::make_shared<hat>());


};

std::vector<std::shared_ptr<zombi>> GetZombi(int level) {
  switch (level) {
    case 1:
      m_result = m_zombies1;
      break;
    case 2:
      m_result = m_zombies2;
      break;
    case 3:
      m_result = m_zombies3;
      break;
    case 4:
      m_result = m_zombies4;
      break;
    default:
      m_result.clear();
  }
  for (auto zombi : m_result) {
    zombi -> SetPiov(level);
  }
  return m_result;
}

void Getice(bool ice) {
  for (auto zombi : m_result) {
    if ((zombi -> GetState() == zombi::zombistate::coldeat) ||(zombi -> GetState() == zombi::zombistate::coldwalk)) {
      return;}
    zombi -> Gotice(true);
  }
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
    if (zombi -> GetState() != zombi::zombistate::stand) {
      zombi -> move();
    }
  }
}
std::vector<std::shared_ptr<zombi>> GetZombies() {
  return  m_result;
}

void SetLoop(int CurrtZombi) {
  m_result[CurrtZombi] -> SetLooping(true);
  // std::cout << CurrtZombi << std::endl;
}

void Die() {
  for (auto zombi : m_result) {
    if (zombi) {
      zombi -> Die();
    }
  }
}

bool IfAnimationEnds() {
  for (auto zombi : m_result) {
    if (zombi -> GetState() == zombi::zombistate::die && zombi -> IfAnimationEnds()) {
      return true;
    }
    else return false;
  }

}
private:
  std::vector<std::shared_ptr<zombi>> m_result;
  std::vector<std::shared_ptr<zombi>> m_zombies1;
  std::vector<std::shared_ptr<zombi>> m_zombies2;
  std::vector<std::shared_ptr<zombi>> m_zombies3;
  std::vector<std::shared_ptr<zombi>> m_zombies4;
  std::vector<std::shared_ptr<zombi>> m_zombies5;
  std::vector<std::shared_ptr<zombi>> m_zombies6;
  std::vector<std::shared_ptr<zombi>> m_zombies7;
  std::vector<std::shared_ptr<zombi>> m_zombies8;
  std::vector<std::shared_ptr<zombi>> m_zombies9;
  std::vector<std::shared_ptr<zombi>> m_zombies10;



};
#endif //ZOMBIMANGER_HPP
