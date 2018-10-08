#ifndef ENTITYLIST_HPP
#define ENTITYLIST_HPP

#include "AEntity.hpp"

typedef struct s_list {
  AEntity *instance;
  s_list *next;
} t_list;

class EntityList {
public:
  EntityList(void);
  EntityList(EntityList const &src);
  ~EntityList(void);

  EntityList &operator=(EntityList const &rhs);

  int getCount() const;
  int push(AEntity *);
  int remove(int index);
  AEntity *getUnit(int) const;

private:
  int _count;
  t_list *_list;
};

#endif