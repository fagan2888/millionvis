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
#include <infovis/drawing/box_concepts.hpp>
#include <infovis/drawing/box_io.hpp>
#include <iostream>

using namespace infovis;


#define check(expr) std::cout << "\"" << #expr << "\"\n\t=" << (expr) << std::endl

int main(int argc, char * argv[])
{
  box_min_extent<int,unsigned> b3(1, 2, 1, 2);
  boost::function_requires<BoxConcept<box_min_extent<int, int> > >();
  check(b3);
  
  box_min_max<float> b1(b3), b2(0, 0, 100, 100);
  boost::function_requires<BoxConcept<box_min_max<float> > >();

  check(b1);
  check(b2);
  check(b1 = box_min_max<float>(20, 20, 110, 110));
  check(intersects(b1,b2));

  return 0;
}
