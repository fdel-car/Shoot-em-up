#include "Bullet.hpp"

Bullet::Bullet(int x, int y, EntityList *enemys, Player *player, int direction,
               int speed)
    : _enemys(enemys), _player(player), _direction(direction), _speed(speed) {
  _x = x;
  _y = y + (_direction * 2); // Bullet width => 2
  this->displayItself();
}

Bullet::Bullet(Bullet const &src) { *this = src; }

void Bullet::displayItself(void) const {
  attron(A_BOLD);
  attron(COLOR_PAIR(_enemys ? GREEN : MAGENTA));
  for (int i = 0; i < Bullet::_bodyParts; i++) {

    ::mvprintw(_x + _body[i].offsetX, _y + _body[i].offsetY, _body[i].str);
  }
  attroff(COLOR_PAIR(_enemys ? GREEN : MAGENTA));
  attroff(A_BOLD);
}

Bullet::~Bullet(void) { this->clearItself(); }

Bullet &Bullet::operator=(Bullet const &rhs) {
  return *this;
  (void)rhs;
}

int Bullet::tryToMove(void) {
  this->clearItself();
  for (int k = 0; k < _speed; k++) {
    _y += _direction;
    if ((_y + _minOffsetY >= COLS && _direction == 1) ||
        (_y - _minOffsetY < 0 && _direction == -1)) {
      if (_enemys)
        _player->resetMultiplier();
      return -1;
    }
    if (_enemys != NULL)
      for (int i = 0; i < _enemys->getCount(); i++) {
        AEntity *enemy = _enemys->getUnit(i);
        for (int j = 0; j < Bullet::_bodyParts; j++) {
          if (_body[j].collidable)
            if (enemy->collideWith(_x + _body[j].offsetX,
                                   _y + _body[j].offsetY)) {
              _player->updateScorePoints(
                  static_cast<AEnemy *>(enemy)->getValue());
              _enemys->remove(i);
              return -1;
            }
        }
      }
    else
      for (int j = 0; j < Bullet::_bodyParts; j++) {
        if (_body[j].collidable)
          if (_player->collideWith(_x + _body[j].offsetX,
                                   _y + _body[j].offsetY)) {
            _player->hit();
            return -1;
          }
      }
  }
  this->displayItself();
  return 0;
}

int Bullet::_bodyParts = 2;

t_body *Bullet::instantiateShape(void) {
  t_body bodyPart;
  t_body *shape = new t_body[Bullet::_bodyParts];

  bodyPart.str = "-";
  bodyPart.offsetX = 0;
  bodyPart.offsetY = 0;
  bodyPart.collidable = true;
  shape[0] = bodyPart;

  bodyPart.str = "-";
  bodyPart.offsetX = 0;
  bodyPart.offsetY = -1;
  bodyPart.collidable = true;
  shape[1] = bodyPart;
  return shape;
}

void Bullet::freeBody(void) { delete[] _body; }
t_body *Bullet::getBody(void) const { return this->_body; }
int Bullet::getBodyParts(void) const { return this->_bodyParts; }

int Bullet::_heatPerShot = 6;
int Bullet::_minOffsetY = 1;

int Bullet::getX(void) const { return this->_x; }
int Bullet::getY(void) const { return this->_y; }
int Bullet::getHeatProduced(void) { return Bullet::_heatPerShot; }
t_body *Bullet::_body = Bullet::instantiateShape();