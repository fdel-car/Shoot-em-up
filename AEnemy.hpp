#ifndef AENEMY_HPP
#define AENEMY_HPP

#include "Player.hpp"

class AEnemy : public AEntity {
public:
  AEnemy(void) {}
  virtual ~AEnemy(void) {}
  virtual int getValue(void) const = 0;
  virtual int getMaxOffsetY(void) const = 0;
  virtual void tryToShoot(void) = 0;
  int tryToMove(void);
  bool collideWith(int x, int y) const;

protected:
  Player *_player;
  static int _value;
};

#endif