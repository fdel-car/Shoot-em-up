#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "AEnemy.hpp"

class Asteroid : public AEnemy {
public:
  Asteroid(Player *player);
  Asteroid(Asteroid const &src);
  ~Asteroid(void);

  Asteroid &operator=(Asteroid const &rhs);

  int getX(void) const;
  int getY(void) const;
  int getValue(void) const;
  static void freeBody(void);
  t_body *getBody(void) const;
  int getBodyParts(void) const;
  int getMaxOffsetY(void) const;
  void tryToShoot(void) {}

private:
  static int _value;
  static t_body *_body;
  static int _bodyParts;
  static int _maxOffsetY;

  static t_body *instantiateShape(void);
};

#endif