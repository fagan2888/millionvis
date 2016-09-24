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
#include <infovis/drawing/lite/LiteLabel.hpp>
#include <infovis/drawing/lite/LiteMover.hpp>
#include <infovis/drawing/lite/LiteWindow.hpp>
#include <GL/glut.h>
#include <iostream>

using namespace infovis;

#if 0
class MyWindow : public LiteWindow
{
public:
  MyWindow(const string& name, const Box& box)
    : LiteWindow(name, box), target(0) { }

  Lite * target;
  Vector delta;


  virtual void doMotion(int x, int y) {
    if (target == 0)
      return;
    target->setPosition(Point(x, y) + delta);
    repaint();
  }
  virtual void doMouse(i button, ButtonState state, int x, int y) {
    //std::cout << "Button\n";
    if (button != button_left)
      return;
    if (state == button_down) {
      target = pick(x, y);
      //std::cout << "Target = " << target << std::endl;
      if (target != 0) {
	Point start(x, y);
	delta = target->getPosition() - start;
      }
    }
    else {
      target = 0;
    }
  }
  Lite * pick(int x, int y) {
    Box box(x-3, y-3, x+3, y+3);
    PathList hit;
    if (LiteWindow::pick(box, hit) != 0) {
      return getPath(hit.back());
    }
    return 0;
  }
};
#endif  

int main(int argc, char *argv[])
{
  LiteWindow::init(argc, argv);
  LiteWindow win("test lite", Box(0, 0, 640, 400));

  LiteLabel * lab = new LiteLabel("Label test");
  lab->setPosition(Point(100, 100));
  win.addChild(new LiteMover(lab, lab));
  win.run();
  return 0;
}
