/* -*- C++ -*-
 *
 * Copyright (C) 2002 Jean-Daniel Fekete
 * 
 * This file is part of MillionVis.
 * 
 * MillionVis is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 * 
 * MillionVis is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with MillionVis; see the file COPYING.  If not, write to the
 * Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA. 
 */
#include <infovis/table/column.hpp>
#include <iostream>

using namespace infovis;

int main()
{
  IntColumn c("int");
  FloatColumn f("float");

  c.add_value("10");
  c.add_value("20");
  c.add_value("15");

  f.add_value("10.2");
  f.add_value("20.3");
  f.add_value("14.3");

  std::cout << "c=" << c;
  std::cout << "min(c) = " << c.get_min() << std::endl;
  std::cout << "max(c) = " << c.get_max() << std::endl;
  std::cout << "f=" << f;
  std::cout << "min(f) = " << f.get_min() << std::endl;
  std::cout << "max(f) = " << f.get_max() << std::endl;

  std::cout << "resizing c to 10\n";
  c.resize(10);
  for (int i = 0; i < c.size(); i++) {
    std::cout << "c.defined(" << i << ") = " <<
      (c.defined(i) ? "yes" : "no" );
    if (c.defined(i))
      std::cout << " = " << c[i];
    std::cout << std::endl;
  }
  
  return 0;
}
