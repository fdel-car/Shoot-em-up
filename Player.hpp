#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "EntityList.hpp"

class Player : public AEntity {
public:
  Player(EntityList *enemys);
  Player(Player const &src);
  ~Player(void);

  Player &operator=(Player const &rhs);
  void handleInput(int key);
  void shoot(AEntity *projectile);
  EntityList *getProjectiles(void) const;
  void hit(void);
  bool isAlive(void) const;
  void updateScorePoints(int amount);
  void clearItself(void) const;
  void displayItself(void) const;
  int tryToMove(void);
  bool collideWith(int x, int y) const;
  int getX(void) const;
  int getY(void) const;
  static void freeBody(void);
  void coolDownWeapons(void);
  int getLives(void) const;
  int getScore(void) const;
  t_body *getBody(void) const;
  int getBodyParts(void) const;
  int getMultiplier(void) const;
  void resetMultiplier(void);

private:
  int _x;
  int _y;
  int _bulletHeat;
  EntityList *_projectiles;
  EntityList *_enemys;
  bool _alive;
  int _score;
  static t_body *_body;
  static int _bodyParts;
  static int _minOffsetY;
  int _lives;
  int _multiplier;
  int _killsInSuccession;

  Player(void) {}

  void moveUp(void);
  void moveDown(void);
  void moveLeft(void);
  void moveRight(void);
  static t_body *instantiateShape(void);
};

#endif