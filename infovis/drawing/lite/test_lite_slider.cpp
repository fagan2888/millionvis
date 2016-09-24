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
#include <infovis/drawing/lite/LiteSliderExt.hpp>
#include <infovis/drawing/lite/LiteFrame.hpp>
#include <infovis/drawing/lite/LiteWindow.hpp>
#include <iostream>

using namespace infovis;

class MyLiteWindow : public LiteWindow
{
  LiteSliderExt slider_;
  
public:
  MyLiteWindow(const string& name, const Box& box)
    : LiteWindow(name, box),
      slider_(Box(100, 100, 120, 200),
	      box,
	      top_to_bottom, color_red)
  {
    addChild(new LiteFrame(&slider_, color_white, 10));
  }

  void doReshape(int w, int h) {
    slider_.setMaxBounds(getBounds());
  }
};

int main(int argc, char *argv[])
{
  LiteWindow::init(argc, argv);
  MyLiteWindow win("test lite box", Box(0, 0, 640, 400));

  win.run();
  return 0;
}
