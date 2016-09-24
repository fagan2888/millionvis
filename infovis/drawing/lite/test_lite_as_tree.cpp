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
#include <infovis/drawing/lite/Lite_as_tree.hpp>
#include <infovis/drawing/box_io.hpp>
#include <infovis/drawing/point_vec_io.hpp>
#include <infovis/drawing/lite/LiteWindow.hpp>
#include <infovis/drawing/lite/LiteLabel.hpp>
#include <infovis/tree/visitor.hpp>
#include <iostream>

using namespace infovis;

struct PrintVisitor
{
  int indent;

  PrintVisitor() : indent(0) {}

  static void tab(int i) {
    while (i-- != 0)
      std::cout << ' ';
  }
  void preorder(tree_traits< const Lite*>::node_descriptor n) {
    tab(indent++);
    std::cout << n << n->getPosition() << std::endl;
  }
  void inorder(tree_traits< const Lite*>::node_descriptor n) {
  }
  void postorder(tree_traits< const Lite*>::node_descriptor n) {
    indent--;
  }
};


int main(int argc, char * argv[])
{
  LiteWindow::init(argc, argv);
  LiteWindow win("test_lite_as_tree", Box(0, 0, 800, 600));
  LiteLabel hello("hello");
  hello.setPosition(Point(10, 10));
  LiteLabel world("world");
  world.setPosition(Point(20, 20));
  win.addChild(&hello);
  win.addChild(&world);

  PrintVisitor vis;
  traverse_tree<const Lite *,PrintVisitor>(&win, &win, vis);
  win.run();
  return 0;
}
