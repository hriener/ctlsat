/*
 * CTLParser.h
 *
 *  Created on: May 20, 2014
 *      Author: nicola
 */

#pragma once

#include "common.hpp"
#include "Formula.hpp"

#include <stack>

namespace ctl_sat {

class CTLParser {
public:
  CTLParser();
  virtual ~CTLParser();

  Formula * parse(std::string f);

private:
  //shortcuts to build the truth
  static Formula * T();

  //shortcuts to build AF,AG,EF,EG formulas
  static Formula * AF(Formula * f);
  static Formula * AG(Formula * f);
  static Formula * EF(Formula * f);
  static Formula * EG(Formula * f);

  std::string preProcess(std::string f);

  Formula * parseRecursive(std::string f, uint * idx, char nt);

  Formula * applyRule1(std::stack <char> * stck, std::string f, uint * idx);
  Formula * applyRule3(std::stack <char> * stck, std::string f, uint * idx);
  Formula * applyRule4(std::stack <char> * stck, std::string f, uint * idx);
  Formula * applyRule5(std::stack <char> * stck, std::string f, uint * idx);
  Formula * applyRule6(std::stack <char> * stck, std::string f, uint * idx);
  Formula * applyRule7(std::stack <char> * stck, std::string f, uint * idx);
  Formula * applyRule8(std::stack <char> * stck, std::string f, uint * idx);
  Formula * applyRule9(std::stack <char> * stck, std::string f, uint * idx);
  Formula * applyRule10(std::stack <char> * stck, std::string f, uint * idx);
  Formula * applyRule11(std::stack <char> * stck, std::string f, uint * idx);
  Formula * applyRule13(std::stack <char> * stck, Formula * last_formula, std::string f, uint * idx);
  Formula * applyRule14(std::stack <char> * stck, Formula * last_formula, std::string f, uint * idx);
  Formula * applyRule15(std::stack <char> * stck, Formula * last_formula, std::string f, uint * idx);
  Formula * applyRule16(std::stack <char> * stck, std::string f, uint * idx);
  Formula * applyRule18(std::stack <char> * stck, std::string f, uint * idx);
  Formula * applyRule19(std::stack <char> * stck, std::string f, uint * idx);
  Formula * applyRule20(std::stack <char> * stck, std::string f, uint * idx);
  Formula * applyRule21(std::stack <char> * stck, std::string f, uint * idx);
  Formula * applyRule22(std::stack <char> * stck, std::string f, uint * idx);
  Formula * applyRule23(std::stack <char> * stck, std::string f, uint * idx);
  Formula * applyRule24(std::stack <char> * stck, std::string f, uint * idx);
  Formula * applyRule25(std::stack <char> * stck, std::string f, uint * idx);
  Formula * applyRule26(std::stack <char> * stck, std::string f, uint * idx);

  unsigned int ** parsing_table;
  bool * isAtom;

  bool * isTerminal;
};

} // namespace ctl_sat
