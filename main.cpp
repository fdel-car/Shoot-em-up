#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Destroyer.hpp"
#include "EntityList.hpp"
#include "Player.hpp"
#include <chrono>
#include <ctime>
#include <unistd.h>

int framePerSecond = 30;
float frameTimeInMs = 1000.0f / (float)framePerSecond;

void padTo(std::string &str, const size_t num, const char paddingChar = ' ') {
  if (num > str.size())
    str.insert(0, num - str.size(), paddingChar);
}

void displayEnv(Player *player, time_t beginning) {
  std::string str;
  std::string value;

  attron(A_BOLD);
  str = "Lifes left: ";
  value = std::to_string(player->getLives());
  ::mvprintw(LINES - 2, COLS - str.length() - value.length() - 2, str.c_str());
  attron(COLOR_PAIR(GREEN));
  ::printw(value.c_str());
  attroff(COLOR_PAIR(GREEN));
  str = "Score: ";
  value = std::to_string(player->getScore());
  ::mvprintw(1, COLS - str.length() - value.length() - 2, str.c_str());
  attron(COLOR_PAIR(SCORE));
  ::printw(value.c_str());
  attroff(COLOR_PAIR(SCORE));
  str = "Multiplier: ";
  value = "x" + std::to_string(player->getMultiplier());
  ::mvprintw(2, COLS - str.length() - value.length() - 2, str.c_str());
  attron(COLOR_PAIR(SCORE));
  ::printw(value.c_str());
  attroff(COLOR_PAIR(SCORE));
  int s = difftime(time(NULL), beginning);
  std::string minutes = std::to_string(s / 60);
  std::string seconds = std::to_string(s % 60);
  padTo(minutes, 2, '0');
  padTo(seconds, 2, '0');
  str = "Timer: ";
  value = minutes + ":" + seconds;
  ::mvprintw(4, COLS - str.length() - value.length() - 2, str.c_str());
  attron(COLOR_PAIR(TIMER));
  ::printw(value.c_str());
  attroff(COLOR_PAIR(TIMER));
  attroff(A_BOLD);
}

void gameLoop(Player *player, EntityList *enemys, int key, time_t beginning,
              EntityList *enemysProjectiles) {
  player->coolDownWeapons();
  for (int i = 0; i < (player->getProjectiles())->getCount(); i++) {
    AEntity *projectile = (player->getProjectiles())->getUnit(i);
    if (projectile->tryToMove() == ERR)
      (player->getProjectiles())->remove(i--);
  }
  if (key != ERR)
    player->handleInput(key);
  else
    player->displayItself();
  for (int i = 0; i < enemysProjectiles->getCount(); i++) {
    AEntity *projectile = enemysProjectiles->getUnit(i);
    if (projectile->tryToMove() == ERR)
      enemysProjectiles->remove(i--);
  }
  for (int i = 0; i < enemys->getCount(); i++) {
    AEntity *unit = enemys->getUnit(i);
    // No need to check collision with player using unit current position
    if (unit->tryToMove() == ERR)
      enemys->remove(i--);
  }
  if (rand() % 20 == 0)
    enemys->push(new Asteroid(player));
  if (rand() % 40 == 0)
    enemys->push(new Destroyer(player, enemysProjectiles));
  displayEnv(player, beginning);
}

int main(void) {
  int key;
  bool windowShouldClose = FALSE;
  time_t beginning;

  initscr();
  keypad(stdscr, TRUE);
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  srand(time(&beginning));
  start_color();
  init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
  init_pair(SCORE, COLOR_YELLOW, COLOR_BLACK);
  init_pair(TIMER, COLOR_CYAN, COLOR_BLACK);
  init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
  curs_set(0);
  set_escdelay(100); // Set the delay waited by ncurses when an escape character
  // is pressed (shouldn't be too low).
  EntityList *enemys = new EntityList();
  EntityList *enemysProjectiles = new EntityList();
  Player *player = new Player(enemys);
  clock_t t;
  while (!windowShouldClose) {
    t = clock();
    key = getch();
    if (key == 27 || key == KEY_RESIZE) {
      windowShouldClose = TRUE;
      clear();
    } else if (player->isAlive())
      gameLoop(player, enemys, key, beginning, enemysProjectiles);
    refresh();
    t = clock() - t;
    float ms = (float)t / CLOCKS_PER_SEC * 1000;
    if (ms < frameTimeInMs) {
      float toWait = (frameTimeInMs - ms) * 1000.0f;
      usleep(toWait);
    }
  }
  endwin();
  delete enemys;
  delete player;
  delete enemysProjectiles;
  Player::freeBody();
  Bullet::freeBody();
  Asteroid::freeBody();
  Destroyer::freeBody();
  if (key == KEY_RESIZE)
    std::cout << "The game closed because you resized the terminal. You can "
                 "now launch it again if you wish!"
              << std::endl;
  return 0;
}