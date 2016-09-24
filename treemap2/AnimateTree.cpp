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
#include <AnimateTree.hpp>
#include <FastDrawer.hpp>

namespace infovis {

AnimateTree::AnimateTree(int size, Tree& tree, FastDrawer& drawer)
  : AnimateBoxList(size),
    tree_(tree),
    drawer_(drawer)
{ }

static inline float
interp(float from, float to, float param)
{
  return (1-param) * from + param * to;
}

static inline Box
interp_box(const Box& from, const Box& to, float param)
{
  return Box(interp(xmin(from), xmin(to), param),
	     interp(ymin(from), ymin(to), param),
	     interp(xmax(from), xmax(to), param),
	     interp(ymax(from), ymax(to), param));
}

static bool
is_null_box(const Box& b)
{
  return
    xmin(b) == 0 &&
    xmax(b) == 0 &&
    ymin(b) == 0 &&
    ymax(b) == 0;
}

void
AnimateTree::render(float param)
{
  if (texture_ != 0) {
    AnimateBoxList::render(param);
    return;
  }
  unsigned last = std::min(start_.size(), end_.size());
  //last = std::min(last, tex_coords_.size());
  glPushAttrib(GL_COLOR_BUFFER_BIT
	       | GL_FOG_BIT 
	       | GL_STENCIL_BUFFER_BIT
	       );

  //glShadeModel(GL_SMOOTH);
  glPushMatrix();
  glScalef(1, 1, -1);
  drawer_.start();
  //glEnable(GL_STENCIL_TEST);
  //glStencilOp(GL_KEEP, GL_INCR, GL_INCR);

  glFogi(GL_FOG_START, 0);
  glFogi(GL_FOG_END, 3);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glColor4f(1.0f, 1.0f, 1.0f, 0.5f);

  for (int i = 0; i < last; i++) {
    const Box& from = start_[i];
    const Box& to = end_[i];
    Box interp;
    if (is_null_box(from)) {
      if (is_null_box(to))
	continue;
      Point p(center(to));
      interp = interp_box(Box(p, p), to, param);
    }
    else if (is_null_box(to)) {
      Point p(center(from));
      interp = interp_box(from, Box(p, p), param);
    }
    else {
      interp = interp_box(from, to, param);
    }
    drawer_.draw_box(interp, i, 1);
  }
  drawer_.finish();
  glPopMatrix();
  glPopAttrib();
}

void
AnimateTree::clear()
{
  std::fill(start_.begin(), start_.end(), Box());
  std::fill(end_.begin(), end_.end(), Box());
  std::fill(tex_coords_.begin(), tex_coords_.end(), Box());
  texture_ = 0;
}


} /// namespace infovis
