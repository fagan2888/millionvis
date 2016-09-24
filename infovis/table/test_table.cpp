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
#include <infovis/table/table.hpp>
#include <infovis/table/column.hpp>
#include <iostream>

using namespace infovis;

int main()
{
  table t;
  
  IntColumn * ic = new IntColumn("int");
  t.add_column(ic);
  FloatColumn * fc = new FloatColumn("float");
  t.add_column(fc);

  ic->add_value("10");
  fc->add_value("20.3");

  ic->resize(4);
  ic->add_value("5");

  std::cout << t;
  return 0;
}
