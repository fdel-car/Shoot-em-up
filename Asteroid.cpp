#include "Asteroid.hpp"

Asteroid::Asteroid(Player *player) {
  _x = rand() % LINES;
  _y = COLS - 1;
  _speed = rand() % 3 ? 1 : 2;
  _player = player;
  this->displayItself();
}

Asteroid::Asteroid(Asteroid const &src) { *this = src; }

Asteroid::~Asteroid(void) { this->clearItself(); }

Asteroid &Asteroid::operator=(Asteroid const &rhs) {
  return *this;
  (void)rhs;
}

int Asteroid::_bodyParts = 2;

t_body *Asteroid::instantiateShape(void) {
  t_body bodyPart;
  t_body *shape = new t_body[Asteroid::_bodyParts];

  bodyPart.str = "(";
  bodyPart.offsetX = 0;
  bodyPart.offsetY = 0;
  bodyPart.collidable = true;
  shape[0] = bodyPart;

  bodyPart.str = ")";
  bodyPart.offsetX = 0;
  bodyPart.offsetY = 1;
  bodyPart.collidable = true;
  shape[1] = bodyPart;
  return shape;
}

void Asteroid::freeBody(void) { delete[] _body; }
t_body *Asteroid::getBody(void) const { return this->_body; }
int Asteroid::getBodyParts(void) const { return this->_bodyParts; }
int Asteroid::getMaxOffsetY(void) const { return this->_maxOffsetY; }

int Asteroid::getValue(void) const { return Asteroid::_value; }
int Asteroid::getX(void) const { return this->_x; }
int Asteroid::getY(void) const { return this->_y; }

int Asteroid::_value = 70;
int Asteroid::_maxOffsetY = 1;
t_body *Asteroid::_body = Asteroid::instantiateShape();
