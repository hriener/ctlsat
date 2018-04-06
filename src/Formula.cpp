/*
 * Formula.cpp
 *
 *  Created on: May 20, 2014
 *      Author: nicola
 */

#include "Formula.hpp"

#include <sstream>

namespace ctl_sat {

/***************************************************************************
 formula
 ***************************************************************************/

Formula::Formula()
{}

Formula::~Formula()
{}

/***************************************************************************
 atom
 ***************************************************************************/

Atom::Atom(char c)
{
  this->c = c;
  type=ATOMIC;

  std::stringstream ss;
  ss<<c;

  string_format = ss.str();
}

Atom::~Atom()
{}

Formula * Atom::removeDoubleNegations()
{
  return this;
}

std::vector<Formula*> * Atom::positiveClosure()
{
  std::vector<Formula*> * closure = new std::vector<Formula*>();
  closure->push_back(this);

  return closure;
}

/***************************************************************************
 negation
 ***************************************************************************/

Negation::Negation(Formula * f)
{
  this->f=f;
  type=NEGATION;

  string_format = (std::string("~(").append(f->toString())).append(")");
}

Negation::~Negation() {}

Formula * Negation::removeDoubleNegations(){
  switch(getSubFormula()->getType())
  {
  case NEGATION:
    return getSubFormula()->getSubFormula()->removeDoubleNegations();
  default:
    return new Negation( getSubFormula()->removeDoubleNegations() );
  }
}

std::vector<Formula*> * Negation::positiveClosure()
{
  return getSubFormula()->positiveClosure();
}

/***************************************************************************
 conjunction
 ***************************************************************************/

Conjunction::Conjunction(Formula * f1, Formula * f2)
{
  //normalize: first formula is the lexicographically smallest
  this->f1 = (*f1<=*f2 ? f1 : f2) ;
  this->f2 = (*f1<=*f2 ? f2 : f1) ;

  type=CONJUNCTION;

  string_format = std::string("(").append(this->f1->toString()).append(")^(").append(this->f2->toString()).append(")");
}

Conjunction::~Conjunction() {}

Formula * Conjunction::removeDoubleNegations()
{
  return new Conjunction(
    getLeftSubFormula()->removeDoubleNegations(),
    getRightSubFormula()->removeDoubleNegations()
  );
}

std::vector<Formula*> * Conjunction::positiveClosure()
{
  std::vector<Formula*> * closure1 = getLeftSubFormula()->positiveClosure();
  std::vector<Formula*> * closure2 = getRightSubFormula()->positiveClosure();

  closure1->insert(closure1->end(), closure2->begin(), closure2->end());
  closure1->push_back(this);

  return closure1;
}

/***************************************************************************
 all_tomorrow
 ***************************************************************************/

AllTomorrow::AllTomorrow(Formula * f)
{
  this->f=f;
  type=ALL_TOMORROW;

  string_format = (std::string("AX(").append(f->toString())).append(")");
}

AllTomorrow::~AllTomorrow()
{
}

Formula * AllTomorrow::removeDoubleNegations()
{
  return new AllTomorrow( getSubFormula()->removeDoubleNegations() );
}

std::vector<Formula*> * AllTomorrow::positiveClosure()
{
  std::vector<Formula*> * closure = getSubFormula()->positiveClosure();
  closure->push_back(this);

  return closure;
}

/***************************************************************************
 all_until
 ***************************************************************************/

AllUntil::AllUntil(Formula * f1, Formula * f2)
{
  this->f1 = f1 ;
  this->f2 = f2 ;

  type=ALL_UNTIL;

  string_format = std::string("A(").append(this->f1->toString()).append("U").append(this->f2->toString()).append(")");
}

AllUntil::~AllUntil() {}

Formula * AllUntil::removeDoubleNegations()
{
  return new AllUntil(
    getLeftSubFormula()->removeDoubleNegations(),
    getRightSubFormula()->removeDoubleNegations()
  );
}

std::vector<Formula*> * AllUntil::positiveClosure()
{
  std::vector<Formula*> * closure1 = getLeftSubFormula()->positiveClosure();
  std::vector<Formula*> * closure2 = getRightSubFormula()->positiveClosure();

  closure1->insert(closure1->end(), closure2->begin(), closure2->end());
  closure1->push_back(this);

  return closure1;
}

/***************************************************************************
 exists_tomorrow
 ***************************************************************************/

ExistsTomorrow::ExistsTomorrow(Formula * f)
{
  this->f=f;
  type=EXISTS_TOMORROW;

  string_format = (std::string("EX(").append(f->toString())).append(")");
}

ExistsTomorrow::~ExistsTomorrow() {}

Formula * ExistsTomorrow::removeDoubleNegations(){
  return new ExistsTomorrow( getSubFormula()->removeDoubleNegations() );
}

std::vector<Formula*> * ExistsTomorrow::positiveClosure()
{
  std::vector<Formula*> * closure = getSubFormula()->positiveClosure();
  closure->push_back(this);

  return closure;
}

/***************************************************************************
 exists_until
 ***************************************************************************/

ExistsUntil::ExistsUntil(Formula * f1, Formula * f2)
{
  this->f1 = f1 ;
  this->f2 = f2 ;

  type=EXISTS_UNTIL;

  string_format = std::string("E(").append(this->f1->toString()).append("U").append(this->f2->toString()).append(")");
}

ExistsUntil::~ExistsUntil() {}

Formula * ExistsUntil::removeDoubleNegations()
{
  return new ExistsUntil(
    getLeftSubFormula()->removeDoubleNegations(),
    getRightSubFormula()->removeDoubleNegations()
  );
}

std::vector<Formula*> * ExistsUntil::positiveClosure()
{
  std::vector<Formula*> * closure1 = getLeftSubFormula()->positiveClosure();
  std::vector<Formula*> * closure2 = getRightSubFormula()->positiveClosure();

  closure1->insert(closure1->end(), closure2->begin(), closure2->end());
  closure1->push_back(this);

  return closure1;
}

} // namespace ctl_sat
