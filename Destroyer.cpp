#include "Destroyer.hpp"
#include "Bullet.hpp"

Destroyer::Destroyer(Player *player, EntityList *projectiles)
    : _projectiles(projectiles), _heat(Bullet::getHeatProduced()) {
  _x = rand() % LINES;
  _y = COLS - 1;
  _speed = rand() % 10 ? 1 : 2;
  _player = player;
  this->displayItself();
}

Destroyer::Destroyer(Destroyer const &src) { *this = src; }

Destroyer::~Destroyer(void) { this->clearItself(); }

Destroyer &Destroyer::operator=(Destroyer const &rhs) {
  return *this;
  (void)rhs;
}

void Destroyer::tryToShoot(void) {
  _heat--;
  if (_heat == 0) {
    _projectiles->push(new Bullet(_x, _y, NULL, _player, -1, _speed + 1));
    _heat = Bullet::getHeatProduced() * 12;
  }
}

int Destroyer::_bodyParts = 8;

t_body *Destroyer::instantiateShape(void) {
  t_body bodyPart;
  t_body *shape = new t_body[Destroyer::_bodyParts];
  bodyPart.str = "_";
  bodyPart.offsetX = -2;
  bodyPart.offsetY = -1;
  bodyPart.collidable = false;
  shape[0] = bodyPart;

  bodyPart.str = "_";
  bodyPart.offsetX = -2;
  bodyPart.offsetY = 0;
  bodyPart.collidable = false;
  shape[1] = bodyPart;

  bodyPart.str = "_";
  bodyPart.offsetX = -2;
  bodyPart.offsetY = 1;
  bodyPart.collidable = false;
  shape[2] = bodyPart;

  bodyPart.str = "|";
  bodyPart.offsetX = -1;
  bodyPart.offsetY = 0;
  bodyPart.collidable = true;
  shape[3] = bodyPart;

  bodyPart.str = "O";
  bodyPart.offsetX = 0;
  bodyPart.offsetY = 0;
  bodyPart.collidable = true;
  shape[4] = bodyPart;

  bodyPart.str = "_";
  bodyPart.offsetX = 1;
  bodyPart.offsetY = -1;
  bodyPart.collidable = true;
  shape[5] = bodyPart;

  bodyPart.str = "|";
  bodyPart.offsetX = 1;
  bodyPart.offsetY = 0;
  bodyPart.collidable = true;
  shape[6] = bodyPart;

  bodyPart.str = "_";
  bodyPart.offsetX = 1;
  bodyPart.offsetY = 1;
  bodyPart.collidable = true;
  shape[7] = bodyPart;
  return shape;
}

void Destroyer::freeBody(void) { delete[] _body; }
t_body *Destroyer::getBody(void) const { return this->_body; }
int Destroyer::getBodyParts(void) const { return this->_bodyParts; }
int Destroyer::getMaxOffsetY(void) const { return this->_maxOffsetY; }

int Destroyer::getValue(void) const { return Destroyer::_value; }
int Destroyer::getX(void) const { return this->_x; }
int Destroyer::getY(void) const { return this->_y; }

int Destroyer::_value = 50;
int Destroyer::_maxOffsetY = 1;
t_body *Destroyer::_body = Destroyer::instantiateShape();
