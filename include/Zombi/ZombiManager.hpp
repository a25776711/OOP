//
// Created by bingho on 2025/3/28.
//

#ifndef ZOMBIMANGER_HPP
#define ZOMBIMANGER_HPP

#include <iostream>
#include "../Background/car.hpp"
#include "zombi.hpp"
#include "normal.hpp"
#include "hat.hpp"
#include "bucket.hpp"
#include "armor.hpp"
#include <glm/glm.hpp>

class ZombiManager{
public:
   ZombiManager() {
     SetZombies();
   };

void SetZombies(){// 關卡 1：教學關，只有普通殭屍
  m_zombies1 = {
      std::make_shared<normal>(),
      std::make_shared<normal>(),
      std::make_shared<normal>(),

  };

  // 關卡 2：普通 + 路障
  m_zombies2 = {
      std::make_shared<normal>(),
      std::make_shared<hat>(),
      std::make_shared<normal>(),
      std::make_shared<hat>(),
      std::make_shared<normal>(),
      std::make_shared<normal>()
  };

  // 關卡 3：增加數量
  m_zombies3 = {
      std::make_shared<normal>(),
      std::make_shared<hat>(),
      std::make_shared<normal>(),
      std::make_shared<armor>(),
      std::make_shared<hat>(),
      std::make_shared<normal>(),
      std::make_shared<normal>()
  };

  // 關卡 4：引入 bucket
  m_zombies4 = {
      std::make_shared<normal>(),
      std::make_shared<bucket>(),
      std::make_shared<hat>(),
      std::make_shared<normal>(),
      std::make_shared<armor>(),
      std::make_shared<bucket>(),
      std::make_shared<hat>(),
      std::make_shared<normal>()
  };

  // 關卡 5：小測驗式混合型（類似 mini-game）
  m_zombies5 = {
      std::make_shared<normal>(),
      std::make_shared<normal>(),
      std::make_shared<hat>(),
      std::make_shared<bucket>(),
      std::make_shared<armor>(),
      std::make_shared<bucket>(),
      std::make_shared<hat>(),
      std::make_shared<armor>(),
      std::make_shared<normal>(),
      std::make_shared<hat>()
  };

  // 關卡 6：敵人更多
  m_zombies6 = {
      std::make_shared<normal>(), std::make_shared<normal>(), std::make_shared<hat>(),
      std::make_shared<armor>(), std::make_shared<bucket>(), std::make_shared<bucket>(),
      std::make_shared<hat>(), std::make_shared<armor>(), std::make_shared<normal>(),
      std::make_shared<hat>(), std::make_shared<bucket>(), std::make_shared<armor>()
  };

  // 關卡 7：分層出現，增加壓力
  m_zombies7 = {
      std::make_shared<normal>(), std::make_shared<hat>(), std::make_shared<bucket>(),
      std::make_shared<armor>(), std::make_shared<hat>(), std::make_shared<normal>(),
      std::make_shared<bucket>(), std::make_shared<hat>(), std::make_shared<armor>(),
      std::make_shared<bucket>(), std::make_shared<normal>(), std::make_shared<hat>()
  };

  // 關卡 8：高強度
  m_zombies8 = {
      std::make_shared<normal>(), std::make_shared<armor>(), std::make_shared<hat>(),
      std::make_shared<bucket>(), std::make_shared<normal>(), std::make_shared<bucket>(),
      std::make_shared<armor>(), std::make_shared<hat>(), std::make_shared<bucket>(),
      std::make_shared<normal>(), std::make_shared<armor>(), std::make_shared<hat>(),
      std::make_shared<normal>()
  };

  // 關卡 9：挑戰關
  m_zombies9 = {
      std::make_shared<bucket>(), std::make_shared<hat>(), std::make_shared<armor>(),
      std::make_shared<normal>(), std::make_shared<bucket>(), std::make_shared<armor>(),
      std::make_shared<hat>(), std::make_shared<normal>(), std::make_shared<bucket>(),
      std::make_shared<hat>(), std::make_shared<armor>(), std::make_shared<normal>(),
      std::make_shared<bucket>(), std::make_shared<hat>()
  };

  // 關卡 10：頭目前的混戰
  m_zombies10 = {
      std::make_shared<normal>(), std::make_shared<hat>(), std::make_shared<armor>(),
      std::make_shared<bucket>(), std::make_shared<armor>(), std::make_shared<hat>(),
      std::make_shared<bucket>(), std::make_shared<normal>(), std::make_shared<bucket>(),
      std::make_shared<hat>(), std::make_shared<armor>(), std::make_shared<normal>(),
      std::make_shared<bucket>(), std::make_shared<armor>(), std::make_shared<hat>(),
      std::make_shared<normal>()
};


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
    case 5:
      m_result = m_zombies5;
      break;
    case 6:
      m_result = m_zombies6;
      break;
    case 7:
      m_result = m_zombies7;
      break;
    case 8:
      m_result = m_zombies8;
      break;
    case 9:
      m_result = m_zombies9;
      break;
    case 10:
      m_result = m_zombies10;
      break;
    default:
      m_result.clear();
      break;
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
    zombi -> SetLooping(true);
  }
}

std::vector<std::shared_ptr<GameObject>> GetZombiesAsGameObjects(std::vector<std::shared_ptr<zombi>> m_zombies) {
  std::vector<std::shared_ptr<GameObject>> result;
  for (const auto& z : m_zombies) {
    result.push_back(std::static_pointer_cast<GameObject>(z));
  }
  return result;
}

void move(std::vector<std::shared_ptr<Car>> cars) {
  
  for (auto zombi : m_result) {
    if(zombi -> GetState() != zombi::zombistate::stand&&zombi -> GetState() != zombi::zombistate::die) {
      zombi -> move(cars);
    }
  }
}

   std::vector<std::shared_ptr<zombi>> &GetZombies() {
  return  m_result;
}

void Startwalk(int CurrtZombi) {
  m_result[CurrtZombi] -> StartWalk();
}

void Die(bool ash) {
  for (auto zombi : m_result) {
    if (zombi) {
        if (ash) zombi -> Ash();
        else zombi -> Die();
    }
  }
};

bool IfAnimationEnds() {
  for (auto zombi : m_result) {
    if (zombi -> GetState() == zombi::zombistate::die && zombi -> IfAnimationEnds()) {
      return true;
    }
    else return false;
  }
};
bool AllDieCheck() {
  bool check = true;
  for (auto zombi : m_result) {
    if (zombi->GetState()!=zombi::zombistate::die&&zombi->GetState()!=zombi::zombistate::ash) {
      check = false;
    }
  }
  return check;
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
