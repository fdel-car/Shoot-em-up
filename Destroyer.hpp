#ifndef DESTROYER_HPP
#define DESTROYER_HPP

#include "AEnemy.hpp"

class Destroyer : public AEnemy {
public:
  Destroyer(Player *player, EntityList *projectiles);
  Destroyer(Destroyer const &src);
  ~Destroyer(void);

  Destroyer &operator=(Destroyer const &rhs);

  int getX(void) const;
  int getY(void) const;
  int getValue(void) const;
  static void freeBody(void);
  t_body *getBody(void) const;
  int getBodyParts(void) const;
  int getMaxOffsetY(void) const;
  void tryToShoot(void);

private:
  static int _value;
  static t_body *_body;
  static int _bodyParts;
  static int _maxOffsetY;
  EntityList *_projectiles;
  int _heat;

  static t_body *instantiateShape(void);
};

#endif