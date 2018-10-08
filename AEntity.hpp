#ifndef AENTITY_HPP
#define AENTITY_HPP

#include <iostream>
#include <ncurses.h>
#include <unistd.h>

#define GREEN 1
#define SCORE 2
#define TIMER 3
#define MAGENTA 4

typedef struct s_body {
  int offsetX;
  int offsetY;
  const char *str;
  bool collidable;
} t_body;

class AEntity {
public:
  AEntity(void) {}
  virtual ~AEntity(void) {}
  virtual int tryToMove(void) = 0;
  bool collideWith(int x, int y) const;
  virtual int getX(void) const = 0;
  virtual int getY(void) const = 0;
  virtual t_body *getBody(void) const = 0;
  virtual int getBodyParts(void) const = 0;
  void clearItself(void) const;
  void displayItself(void) const;

protected:
  int _x;
  int _y;
  int _speed;
};

#endif