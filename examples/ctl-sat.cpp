/*
 * main.cpp
 *
 *  Created on: May 20, 2014
 *      Author: nicola
 */

#include "CTLParser.hpp"
#include "Tableau.hpp"
#include <iostream>

using namespace ctl_sat;

int main(int argc,char** argv){
  if( argc != 2 )
  {
    std::cout << "*** CTL-sat solver ***\n";
    std::cout << "Usage: ctl-sat formula\n";
    return 0;
  }

  CTLParser *parser = new CTLParser();
  Formula *f = parser->parse( std::string(argv[1]) );
  delete parser;

  Tableau *tableau = new Tableau(f);
  const auto sat = tableau->isSatisfiable();
  delete tableau;

  if( sat )
  {
    std::cout << "SAT" << std::endl;
    return 10;
  }
  else
  {
    std::cout << "UNSAT" << std::endl; 
    return 20;
  }
}

