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
#include <infovis/drawing/lite/LiteColorChooser.hpp>
#include <infovis/drawing/lite/LiteFrame.hpp>
#include <infovis/drawing/lite/LiteWindow.hpp>
#include <iostream>

using namespace infovis;

class MyLiteWindow : public LiteWindow
{
  Interactor3States * inter_;
  ColorScheme scheme_;
  LiteColorSlider slider_;
  LiteColorSurface surface_;
  
public:
  MyLiteWindow(const string& name, const Box& box)
    : LiteWindow(name, box),
      inter_(0),
      slider_(&scheme_,
	      Box(100, 100, 120, 200),
	      top_to_bottom, color_red),
      surface_(&scheme_,
	       Box(0, 100, 100, 200))
  {
    addChild(&surface_);
    addChild(&slider_);
  }

#if 0
  virtual void doMouse(Button button, ButtonState state, int x, int y) {
    if (inter_ == 0) {
      PathList pl;
      pick(Box(x-1, y-1, x+1, y+1), pl);
      List l;
      sortPathList(pl, l);
      for (List::reverse_iterator i = l.rbegin(); i != l.rend(); i++) {
	inter_ =
	  dynamic_cast<Interactor3States*>((*i)->interactor("3States",
							    mouse_id));
	if (inter_ != 0) {
	  break;
	}
      }
      if (inter_ == 0)
	inter_ =
	  dynamic_cast<Interactor3States*>(slider_.interactor("3States",
							      mouse_id));
    }
    if (inter_ != 0) {
      if (state == button_down) {
	inter_->start(Point(x, y));
      }
      else {
	inter_->finish(Point(x, y));
	inter_ = 0;
      }
      repaint();
    }
  }
  void doMotion(int x, int y) {
    if (inter_ != 0) {
      inter_->drag(Point(x, y));
      repaint();
    }
  }  
#endif
};

int main(int argc, char *argv[])
{
  LiteWindow::init(argc, argv);
  MyLiteWindow win("test color", Box(0, 0, 640, 400));

  win.run();
  return 0;
}
