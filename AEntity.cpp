#include "AEntity.hpp"

void AEntity::clearItself(void) const {
  for (int i = 0; i < this->getBodyParts(); i++) {
    ::mvprintw(_x + (this->getBody())[i].offsetX,
               _y + (this->getBody())[i].offsetY, " ");
  }
}

void AEntity::displayItself(void) const {
  for (int i = 0; i < this->getBodyParts(); i++) {
    ::mvprintw(_x + (this->getBody())[i].offsetX,
               _y + (this->getBody())[i].offsetY, (this->getBody())[i].str);
  }
}

bool AEntity::collideWith(int x, int y) const {
  for (int i = 0; i < this->getBodyParts(); i++) {
    if ((this->getBody())[i].collidable)
      if (x == _x + (this->getBody())[i].offsetX &&
          y == _y + (this->getBody())[i].offsetY)
        return true;
  }
  return false;
}