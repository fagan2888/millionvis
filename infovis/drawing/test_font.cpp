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
#include <infovis/drawing/lite/LiteWindow.hpp>
#include <infovis/drawing/lite/LiteLabel.hpp>
#include <infovis/drawing/Font.hpp>

#include <iostream>

using namespace infovis;

int main(int argc, char * argv[])
{
  LiteWindow::init(argc, argv);
  if (argc < 3) {
    std::cerr << "syntax: " << argv[0] << " Font Text ...\n";
    return 1;
  }

  LiteWindow win(argv[0], Box(0, 0, 800, 600));
  win.setColor(color_red);
  Font * font = Font::create(argv[1], Font::style_plain, 20);
  if (font == 0) {
    std::cerr << "cannot create font " << argv[1] << std::endl;
    return 1;
  }
  string text = argv[2];
  for (int i = 3; i < argc; i++)
    text.append(string(" ")+argv[i]);

  LiteLabel lab(text, LiteLabel::just_left, font,
		color_yellow, color_red, color_black);
  lab.setPosition(Point(10, 10));
  win.addChild(&lab);
  win.run();
  return 0;
}
