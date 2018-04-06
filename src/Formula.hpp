/*
 * Formula.h
 *
 *  Created on: May 20, 2014
 *      Author: nicola
 */

#pragma once

#include "common.hpp"

#include <vector>
#include <string>

namespace ctl_sat
{

class Formula {
public:
  Formula();
  virtual ~Formula();

  formula_type getType(){return type;}

  virtual std::string toString(){return string_format;};

  virtual Formula * getSubFormula(){return NULL;};
  virtual Formula * getLeftSubFormula(){return NULL;};
  virtual Formula * getRightSubFormula(){return NULL;};

  virtual Formula * removeDoubleNegations(){return NULL;};

  // returns set of all positive subformulas (i.e. that are not negations)
  virtual std::vector<Formula*> * positiveClosure(){return NULL;};

  inline bool operator<(const Formula & f) const { return string_format.compare(f.string_format)<0; };
  inline bool operator<=(const Formula & f) const { return string_format.compare(f.string_format)<=0; };
  const bool operator>(const Formula & f) const { return string_format.compare(f.string_format)>0; };
  const bool operator==(const Formula & f) const { return string_format.compare(f.string_format)==0; };
  const bool operator!=(const Formula & f) const { return string_format.compare(f.string_format)!=0; };

  std::string string_format;
protected:

  formula_type type;
}; // Formula

class Atom : public Formula
{
public:
  Atom(char c);
  virtual ~Atom();

  Formula * removeDoubleNegations();

  char c;

  std::vector<Formula*> * positiveClosure();
};

class Negation : public Formula
{
public:
  Negation(Formula * f);
  virtual ~Negation();

  Formula * getSubFormula(){return f;};

  Formula * removeDoubleNegations();

  std::vector<Formula*> * positiveClosure();

  Formula * f;
};

class Conjunction : public Formula
{
public:
  Conjunction(Formula * f1, Formula * f2);

  Formula * getLeftSubFormula(){return f1;};
  Formula * getRightSubFormula(){return f2;};

  Formula * removeDoubleNegations();

  std::vector<Formula*> * positiveClosure();

  Formula * f1, * f2;

  virtual ~Conjunction();
};

class AllTomorrow : public Formula
{
public:
  AllTomorrow(Formula * f);
  virtual ~AllTomorrow();

  Formula * getSubFormula(){return f;};
  Formula * removeDoubleNegations();
  std::vector<Formula*> * positiveClosure();

  Formula * f;
};

class AllUntil : public Formula
{
public:
  AllUntil(Formula * f1, Formula * f2);
  virtual ~AllUntil();

  Formula * getLeftSubFormula(){return f1;};
  Formula * getRightSubFormula(){return f2;};

  Formula * removeDoubleNegations();

  std::vector<Formula*> * positiveClosure();

  Formula * f1, * f2;
};

class ExistsTomorrow : public Formula
{
public:
  ExistsTomorrow(Formula * f);
  virtual ~ExistsTomorrow();

  Formula * getSubFormula(){return f;};
  Formula * removeDoubleNegations();

  std::vector<Formula*> * positiveClosure();
  Formula * f;
};

class ExistsUntil : public Formula
{
public:
  ExistsUntil(Formula * f1, Formula * f2);
  virtual ~ExistsUntil();

  Formula * getLeftSubFormula(){return f1;};
  Formula * getRightSubFormula(){return f2;};

  Formula * removeDoubleNegations();

  std::vector<Formula*> * positiveClosure();

  Formula * f1, * f2;
};

} // namespace ctl_sat
