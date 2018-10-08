#ifndef BULLET_HPP
#define BULLET_HPP

#include "AEnemy.hpp"

class Bullet : public AEntity {
public:
  Bullet(int x, int y, EntityList *enemys, Player *player, int direction,
         int speed);
  Bullet(Bullet const &src);
  ~Bullet(void);

  Bullet &operator=(Bullet const &rhs);

  int tryToMove(void);
  int getX(void) const;
  int getY(void) const;
  void displayItself(void) const;
  static int getHeatProduced(void);
  static void freeBody(void);
  t_body *getBody(void) const;
  int getBodyParts(void) const;

private:
  Bullet(void) {}
  EntityList *_enemys;
  Player *_player;
  static int _heatPerShot;
  static t_body *_body;
  static int _bodyParts;
  static int _minOffsetY;
  int _direction;
  int _speed;

  static t_body *instantiateShape(void);
};

#endif