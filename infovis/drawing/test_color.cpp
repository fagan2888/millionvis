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
#include <infovis/drawing/color.hpp>
#include <infovis/drawing/color_io.hpp>
#include <infovis/drawing/colors/hsb.hpp>
#include <infovis/drawing/colors/xyz.hpp>
#include <infovis/drawing/drawing.hpp>
#include <iostream>
#include <typeinfo>

using namespace infovis;


typedef unsigned char uchar;
int main()
{
  color_rgb<float> rgb(1.0f, 0.0f, 0.0f);
  color_rgba<unsigned char> rgba(0U, 255U, 0U);
  color_hsb hsb(0.0f, 1.0f, 1.0f);
  color_xyz xyz;

  std::cout << rgb << std::endl;
  std::cout << rgba << std::endl;
  std::cout << hsb << std::endl;

  infovis::color_rgba<float> rgba2(rgb);
  std::cout << rgba2 << std::endl;

  infovis::convert(rgb, hsb);
  std::cout << rgb << std::endl;

  infovis::convert(hsb, rgb);
  std::cout << hsb << std::endl;

#define PRINT_CONVERT(color) \
  infovis::convert(rgb, color_##color); \
  infovis::convert(hsb, rgb); \
  std::cout << #color " rgba=" << color_##color << " hsb=" << hsb << std::endl

  PRINT_CONVERT(none);
  PRINT_CONVERT(white);
  PRINT_CONVERT(black);
  PRINT_CONVERT(red);
  PRINT_CONVERT(green);
  PRINT_CONVERT(blue);
  PRINT_CONVERT(cyan);
  PRINT_CONVERT(magenta);
  PRINT_CONVERT(yellow);
  PRINT_CONVERT(half_grey);
  
#undef PRINT_CONVERT
#define PRINT_CONVERT(color) \
  infovis::convert(rgb, color_##color); \
  infovis::convert<float>(xyz, rgb); \
  std::cout << #color " rgb=" << color_##color << " xyz=" << xyz << std::endl

  PRINT_CONVERT(none);
  PRINT_CONVERT(white);
  PRINT_CONVERT(black);
  PRINT_CONVERT(red);
  PRINT_CONVERT(green);
  PRINT_CONVERT(blue);
  PRINT_CONVERT(cyan);
  PRINT_CONVERT(magenta);
  PRINT_CONVERT(yellow);
  PRINT_CONVERT(half_grey);

  return 0;
}
