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
#include <GL/glut.h>
//#include <GL/glu.h>
#include <infovis/tree/tree.hpp>
#include <infovis/tree/treemap/slice_and_dice.hpp>
#include <infovis/tree/treemap/squarified.hpp>
#include <infovis/tree/treemap/drawing/gl_cs_drawer.hpp>
#include <infovis/tree/treemap/drawing/debug_drawer.hpp>
#include <boost/directory.h>
#include <iostream>
#include <cmath>

using namespace infovis;

typedef std::vector<float,gc_alloc<float,true> > WeightMap;
typedef vector_as_tree Tree;
Tree t(1);
std::vector<std::string,gc_alloc<std::string> > names;
WeightMap wm;
WeightMap swm;
int win_width, win_height;
bool changed = true;

static void build_tree(tree_traits< vector_as_tree >::node_descriptor parent,
		       vector_as_tree& tree, const std::string& dirname,
		       std::vector<std::string,gc_alloc<std::string> >& names,
		       WeightMap& wm)
{
  using namespace infovis::filesystem;
  for (dir_it it(dirname); it != dir_it(); ++it) {
    if ((*it)[0] == '.')
      continue;
    tree_traits< vector_as_tree >::node_descriptor n = add_node(parent, tree);
    names.push_back(*it);
    wm.push_back(boost::filesystem::get<size>(it));
    if (boost::filesystem::get<is_directory>(it))
      build_tree(n, tree, dirname+"/"+(*it), names, wm);
  }
}

struct compare_weight {
  typedef tree_traits< vector_as_tree >::node_descriptor node_descriptor;
  const WeightMap& weight;

  compare_weight(const WeightMap& wm)
    : weight(wm) {}

  bool operator()(node_descriptor n1, node_descriptor n2) {
    return weight[n1] < weight[n2];
  }
};

typedef debug_drawer<Tree,Box,gl_cs_drawer<Tree,Box> > Drawer;

static void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  Drawer drawer(t);
#if 0
  treemap_slice_and_dice<Tree,Box,WeightMap, WeightMap, Drawer&>
    tmsd(t, wm, swm, drawer);
  tmsq.start();
  tmsd.visit(left_to_right, Box(0, 0, win_width, win_height), root(t));
#else
  treemap_squarified<Tree,Box,WeightMap, WeightMap, Drawer& >
    tmsq(t, wm, swm, drawer);
  tmsq.start();
  tmsq.visit(Box(0, 0, win_width, win_height), root(t));
#endif
  tmsq.finish();
  glFlush();

}

static void init()
{
  glClearColor (1, 1, 0, 1);
  glShadeModel (GL_FLAT);
  glViewport (0, 0, win_width, win_height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, win_width, 0, win_height);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  changed = true;
}

static void reshape(int w, int h)
{
  win_width = w;
  win_height = h;
  init();
}

int main(int argc, char * argv[])
{

  WeightMap lwm;
  lwm.push_back(0);		// weight of root is 0

  if (argc == 1) {
    names.push_back(".");
    build_tree(root(t), t, ".", names, lwm);
  }
  else {
    names.push_back(argv[1]);
    build_tree(root(t), t, argv[1], names, lwm);
  }
  
  wm.resize(lwm.size());
  for (int i = 0; i < wm.size(); i++) {
    wm[i] = log(lwm[i] + 1.0);
  }
  sum_weights(t, wm);
  sort(t, compare_weight(wm));

  win_height = 768;
  win_width = 1024;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize (win_width, win_height); 
  glutInitWindowPosition (0, 0);
  glutCreateWindow (argv[0]);

  init();
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  
  glutMainLoop();
  return 0;
}
