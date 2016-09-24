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
#ifdef VECTOR_AS_TREE
#include <infovis/tree/vector_as_tree.hpp>
#include <infovis/tree/dir_property_tree.hpp>
#include <infovis/tree/xml_property_tree.hpp>
#else
#include <infovis/tree/tree.hpp>
#include <infovis/tree/dir_tree.hpp>
#include <infovis/tree/xml_tree.hpp>
#endif
#include <infovis/tree/treemap/slice_and_dice.hpp>
#include <infovis/tree/treemap/squarified.hpp>
#include <infovis/tree/treemap/drawing/gl_drawer.hpp>
#include <infovis/tree/treemap/drawing/debug_drawer.hpp>
#include <boost/directory.h>
#include <iostream>
#include <cmath>

using namespace infovis;

#ifdef VECTOR_AS_TREE
typedef std::vector<float,gc_alloc<float,true> > WeightMap;
typedef vector_as_tree Tree;
Tree t(1);
std::vector<std::string,gc_alloc<std::string> > names;
WeightMap wm;
//WeightMap swm;
#else
typedef FloatColumn WeightMap;
typedef tree Tree;
Tree t;
WeightMap * wm;
//WeightMap * swm;
#endif
int win_width, win_height;

struct compare_weight {
  typedef tree_traits< Tree >::node_descriptor node_descriptor;
  const WeightMap& weight;

  compare_weight(const WeightMap& wm)
    : weight(wm) {}

  bool operator()(node_descriptor n1, node_descriptor n2) {
    return weight[n1] < weight[n2];
  }
};

typedef debug_drawer<Tree, Box, gl_drawer<Tree,Box> > Drawer;

static void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
#if 0
  static treemap_slice_and_dice<Tree,Box,WeightMap&, Drawer>
    tmsd(t, *wm);
  tmsd.start();
  tmsd.visit(left_to_right, Box(0, 0, win_width, win_height), root(t));
  tmsd.finish();
#else
  static treemap_squarified<Tree,Box,WeightMap&, Drawer >
    tmsq(t, *wm);
  tmsq.start();
  tmsq.visit(Box(0, 0, win_width, win_height), root(t));
  tmsq.finish();
#endif
  glFlush();
}

static void init()
{
  glViewport (0, 0, win_width, win_height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, win_width, 0, win_height);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

static void reshape(int w, int h)
{
  win_width = w;
  win_height = h;
  init();
}

int main(int argc, char * argv[])
{
  int i;
#ifdef VECTOR_AS_TREE
  if (argc == 1) {
    dir_property_tree(".", t);
  }
  else {
    if (xml_property_tree(argv[1], t) == 1) {
      dir_property_tree(argv[1], t);
    }
  }
#else
  if (argc == 1) {
    dir_tree(".", t);
  }
  else {
    if (xml_tree(argv[1], t) == 1) {
      dir_tree(argv[1], t);
    }
  }
#endif
  wm = 0;
  for (i = 0; i < t.column_count(); i++) {
    wm = FloatColumn::cast(t.get_column(i));
    if (wm != 0)
      break;
  }
  if (wm == 0) {
    std::cerr << "Cannot find a float column\n";
    return 1;
  }
  FloatColumn * lwm = FloatColumn::find("log_weight", t);

  for (i = 0; i < wm->size(); i++) {
    (*lwm)[i] = log((*wm)[i] + 1.0);
  }

  //swm = FloatColumn::find("sum_weight", t);
  sum_weights(t, *lwm);
  sort(t, compare_weight(*lwm));
  wm = lwm;

  win_height = 768;
  win_width = 1024;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize (win_width, win_height); 
  glutInitWindowPosition (0, 0);
  glutCreateWindow (argv[0]);

  glClearColor (1, 1, 0, 1);
  glShadeModel (GL_FLAT);
  glViewport (0, 0, win_width, win_height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, win_width, 0, win_height);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  init();
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  
  glutMainLoop();
  return 0;
}
