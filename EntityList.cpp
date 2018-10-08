#include "EntityList.hpp"

EntityList::EntityList(void) : _count(0), _list(NULL) {}

EntityList::EntityList(EntityList const &src)
    : _count(src.getCount()), _list(NULL) {
  // Unused
}

EntityList::~EntityList(void) {
  for (int i = this->_count - 1; i >= 0; i--) {
    this->remove(i);
  }
}

EntityList &EntityList::operator=(EntityList const &rhs) {
  // Unused
  return *this;
  (void)rhs;
}

int EntityList::getCount() const { return this->_count; }

int EntityList::push(AEntity *newEnemy) {
  if (newEnemy == NULL)
    return _count;
  if (_list == NULL) {
    _list = new (t_list);
    _list->instance = newEnemy;
    _list->next = NULL;
  } else {
    t_list *it = _list;
    while (it->next) {
      if (it->instance == newEnemy)
        return _count;
      it = it->next;
    }
    it->next = new (t_list);
    (it->next)->instance = newEnemy;
    (it->next)->next = NULL;
  }
  _count++;
  return _count;
}

int EntityList::remove(int index) {
  if (index < 0 || index >= _count)
    return _count;
  _count--;
  t_list *tmp;
  if (index == 0) {
    tmp = _list;
    delete _list->instance;
    _list = _list->next;
    delete tmp;
  } else {
    t_list *it = _list;
    for (int i = 0; i < index - 1; i++)
      it = it->next;
    tmp = it->next;
    delete it->next->instance;
    it->next = (it->next)->next;
    delete tmp;
  }
  if (_count == 0)
    this->_list = NULL;
  return _count;
}

AEntity *EntityList::getUnit(int index) const {
  if (index < 0 || index >= _count)
    return NULL;
  t_list *it = _list;
  for (int i = 0; i < index; i++)
    it = it->next;
  return it->instance;
}