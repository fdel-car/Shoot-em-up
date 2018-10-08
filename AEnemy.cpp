#include "AEnemy.hpp"

int AEnemy::tryToMove(void) {
  this->clearItself();
  for (int k = 0; k < _speed; k++) {
    _y--;
    if (_y + this->getMaxOffsetY() < 0)
      return -1;
    for (int i = 0; i < this->getBodyParts(); i++) {
      if ((this->getBody())[i].collidable)
        if (_player->collideWith(_x + (this->getBody())[i].offsetX,
                                 _y + (this->getBody())[i].offsetY)) {
          _player->hit();
          return -1;
        }
    }
    for (int i = 0; i < (_player->getProjectiles())->getCount(); i++) {
      AEntity *projectile = (_player->getProjectiles())->getUnit(i);
      for (int j = 0; j < this->getBodyParts(); j++) {
        if ((this->getBody())[j].collidable)
          if (projectile->collideWith(_x + (this->getBody())[j].offsetX,
                                      _y + (this->getBody())[j].offsetY)) {
            (_player->getProjectiles())->remove(i);
            _player->updateScorePoints(this->getValue());
            return -1;
          }
      }
    }
  }
  this->tryToShoot();
  this->displayItself();
  return 0;
}