#include "Player.hpp"
#include "Bullet.hpp"
#include <math.h>

void Player::clearItself(void) const {
  for (int i = 0; i < Player::_bodyParts; i++) {
    ::mvprintw(_x + _body[i].offsetX, _y + _body[i].offsetY, " ");
  }
}

void Player::displayItself(void) const {
  for (int i = 0; i < Player::_bodyParts; i++) {
    ::mvprintw(_x + _body[i].offsetX, _y + _body[i].offsetY, _body[i].str);
  }
}

Player::Player(EntityList *enemys)
    : _x(LINES / 2), _y(Player::_minOffsetY * -1), _bulletHeat(0),
      _enemys(enemys), _alive(true), _score(0), _lives(3), _multiplier(1),
      _killsInSuccession(0) {
  this->_projectiles = new EntityList();
  this->displayItself();
}

Player::Player(Player const &src) { *this = src; }

Player::~Player(void) { delete this->_projectiles; }

Player &Player::operator=(Player const &rhs) {
  return *this;
  (void)rhs;
}

EntityList *Player::getProjectiles(void) const { return this->_projectiles; }

void Player::resetMultiplier(void) {
  _multiplier = 1;
  _killsInSuccession = 0;
}

void Player::handleInput(int key) {
  if (key == KEY_UP && _x > 0)
    this->moveUp();
  else if (key == KEY_DOWN && _x < LINES - 1)
    this->moveDown();
  else if (key == KEY_LEFT && _y > (Player::_minOffsetY * -1))
    this->moveLeft();
  else if (key == KEY_RIGHT && _y < COLS - 1)
    this->moveRight();
  else if (key == 32 && _bulletHeat == 0) {
    this->shoot(new Bullet(_x, _y, _enemys, this, 1, 1));
    _bulletHeat = Bullet::getHeatProduced();
  }
}

void Player::moveUp(void) {
  this->clearItself();
  _x--;
  this->displayItself();
}

void Player::moveDown(void) {
  this->clearItself();
  _x++;
  this->displayItself();
}

void Player::moveLeft(void) {
  this->clearItself();
  _y--;
  this->displayItself();
}
void Player::moveRight(void) {
  this->clearItself();
  _y++;
  this->displayItself();
}

void Player::coolDownWeapons(void) { _bulletHeat -= _bulletHeat > 0 ? 1 : 0; }

int Player::tryToMove(void) { // Unused
  return 0;
}

void Player::updateScorePoints(int amount) {
  this->_score += amount * _multiplier;
  _killsInSuccession++;
  int n = _killsInSuccession;
  n--;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  _multiplier = fmin(sqrt(n + 1), 8);
}

void Player::shoot(AEntity *projectile) { _projectiles->push(projectile); }

void Player::hit(void) {
  _lives--;
  if (_lives > 0) {
    this->resetMultiplier();
    return;
  }
  this->_alive = false;
  std::string array[] = {
      "  _____                                            ",
      " / ____|                                           ",
      "| |  __  __ _ _ __ ___   ___    _____   _____ _ __ ",
      "| | |_ |/ _` | '_ ` _ \\ / _ \\  / _ \\ \\ / / _ \\ '__|",
      "| |__| | (_| | | | | | |  __/ | (_) \\ V /  __/ |   ",
      " \\_____|\\__,_|_| |_| |_|\\___|  \\___/ \\_/ \\___|_|   ",
  };
  std::string str = "Your final score: ";
  std::string value = std::to_string(_score);
  ::attron(A_BOLD);
  ::mvprintw(LINES / 2 - 5, COLS / 2 - array[0].length() / 2, array[0].c_str());
  ::mvprintw(LINES / 2 - 4, COLS / 2 - array[1].length() / 2, array[1].c_str());
  ::mvprintw(LINES / 2 - 3, COLS / 2 - array[2].length() / 2, array[2].c_str());
  ::mvprintw(LINES / 2 - 2, COLS / 2 - array[3].length() / 2, array[3].c_str());
  ::mvprintw(LINES / 2 - 1, COLS / 2 - array[4].length() / 2, array[4].c_str());
  ::mvprintw(LINES / 2, COLS / 2 - array[5].length() / 2, array[5].c_str());
  ::mvprintw(LINES / 2 + 2, COLS / 2 - (str.length() + value.length()) / 2,
             str.c_str());
  ::attron(COLOR_PAIR(SCORE));
  ::printw(value.c_str());
  ::attroff(COLOR_PAIR(SCORE));
  ::attroff(A_BOLD);
}

bool Player::collideWith(int x, int y) const {
  for (int i = 0; i < Player::_bodyParts; i++) {
    if (_body[i].collidable)
      if (x == _x + _body[i].offsetX && y == _y + _body[i].offsetY)
        return true;
  }
  return false;
}

int Player::_bodyParts = 25;

t_body *Player::instantiateShape(void) {
  t_body bodyPart;
  t_body *shape = new t_body[Player::_bodyParts];

  bodyPart.str = "_";
  bodyPart.offsetX = -2;
  bodyPart.offsetY = -8;
  bodyPart.collidable = false;
  shape[0] = bodyPart;

  bodyPart.str = "_";
  bodyPart.offsetX = -2;
  bodyPart.offsetY = -7;
  bodyPart.collidable = false;
  shape[1] = bodyPart;

  bodyPart.str = "\\";
  bodyPart.offsetX = -1;
  bodyPart.offsetY = -8;
  bodyPart.collidable = true;
  shape[2] = bodyPart;

  bodyPart.str = "\\";
  bodyPart.offsetX = -1;
  bodyPart.offsetY = -6;
  bodyPart.collidable = true;
  shape[3] = bodyPart;

  bodyPart.str = "_";
  bodyPart.offsetX = -1;
  bodyPart.offsetY = -5;
  bodyPart.collidable = false;
  shape[4] = bodyPart;

  bodyPart.str = "_";
  bodyPart.offsetX = -1;
  bodyPart.offsetY = -4;
  bodyPart.collidable = false;
  shape[5] = bodyPart;

  bodyPart.str = "_";
  bodyPart.offsetX = -1;
  bodyPart.offsetY = -3;
  bodyPart.collidable = false;
  shape[6] = bodyPart;

  bodyPart.str = "_";
  bodyPart.offsetX = -1;
  bodyPart.offsetY = -2;
  bodyPart.collidable = false;
  shape[7] = bodyPart;

  bodyPart.str = "_";
  bodyPart.offsetX = -1;
  bodyPart.offsetY = -1;
  bodyPart.collidable = false;
  shape[8] = bodyPart;

  bodyPart.str = "#";
  bodyPart.offsetX = 0;
  bodyPart.offsetY = -11;
  bodyPart.collidable = false;
  shape[9] = bodyPart;

  bodyPart.str = "#";
  bodyPart.offsetX = 0;
  bodyPart.offsetY = -10;
  bodyPart.collidable = false;
  shape[10] = bodyPart;

  bodyPart.str = "#";
  bodyPart.offsetX = 0;
  bodyPart.offsetY = -9;
  bodyPart.collidable = false;
  shape[11] = bodyPart;

  bodyPart.str = "[";
  bodyPart.offsetX = 0;
  bodyPart.offsetY = -8;
  bodyPart.collidable = true;
  shape[12] = bodyPart;

  bodyPart.str = "=";
  bodyPart.offsetX = 0;
  bodyPart.offsetY = -7;
  bodyPart.collidable = true;
  shape[13] = bodyPart;

  bodyPart.str = "=";
  bodyPart.offsetX = 0;
  bodyPart.offsetY = -6;
  bodyPart.collidable = true;
  shape[14] = bodyPart;

  bodyPart.str = "_";
  bodyPart.offsetX = 0;
  bodyPart.offsetY = -5;
  bodyPart.collidable = true;
  shape[15] = bodyPart;

  bodyPart.str = "_";
  bodyPart.offsetX = 0;
  bodyPart.offsetY = -5;
  bodyPart.collidable = true;
  shape[16] = bodyPart;

  bodyPart.str = "_";
  bodyPart.offsetX = 0;
  bodyPart.offsetY = -4;
  bodyPart.collidable = true;
  shape[17] = bodyPart;

  bodyPart.str = "_";
  bodyPart.offsetX = 0;
  bodyPart.offsetY = -3;
  bodyPart.collidable = true;
  shape[18] = bodyPart;

  bodyPart.str = "_";
  bodyPart.offsetX = 0;
  bodyPart.offsetY = -2;
  bodyPart.collidable = true;
  shape[19] = bodyPart;

  bodyPart.str = "_";
  bodyPart.offsetX = 0;
  bodyPart.offsetY = -1;
  bodyPart.collidable = true;
  shape[20] = bodyPart;

  bodyPart.str = ">";
  bodyPart.offsetX = 0;
  bodyPart.offsetY = 0;
  bodyPart.collidable = true;
  shape[21] = bodyPart;

  bodyPart.str = "/";
  bodyPart.offsetX = 1;
  bodyPart.offsetY = -8;
  bodyPart.collidable = true;
  shape[22] = bodyPart;

  bodyPart.str = "_";
  bodyPart.offsetX = 1;
  bodyPart.offsetY = -7;
  bodyPart.collidable = true;
  shape[23] = bodyPart;

  bodyPart.str = "/";
  bodyPart.offsetX = 1;
  bodyPart.offsetY = -6;
  bodyPart.collidable = true;
  shape[24] = bodyPart;
  return shape;
}

int Player::_minOffsetY = -8;

void Player::freeBody(void) { delete[] _body; }
t_body *Player::getBody(void) const { return this->_body; }
int Player::getBodyParts(void) const { return this->_bodyParts; }

bool Player::isAlive(void) const { return this->_alive; }
int Player::getX(void) const { return this->_x; }
int Player::getY(void) const { return this->_y; }
int Player::getLives(void) const { return this->_lives; }
int Player::getScore(void) const { return this->_score; }
int Player::getMultiplier(void) const { return this->_multiplier; }

t_body *Player::_body = Player::instantiateShape();