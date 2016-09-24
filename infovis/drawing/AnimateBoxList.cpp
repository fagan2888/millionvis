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
#include <infovis/drawing/AnimateBoxList.hpp>
#include <infovis/drawing/gl_support.hpp>
#include <algorithm>

namespace infovis {

AnimateBoxList::AnimateBoxList(int size)
  : start_(size), end_(size), tex_coords_(size), texture_(0)
{ }


void
AnimateBoxList::setStartList(const BoxList& bl)
{
  start_ = bl;
}

void
AnimateBoxList::setEndList(const BoxList& el)
{
  end_ = el;
}

void
AnimateBoxList::setTexCoords(const BoxList& tc)
{
  tex_coords_ = tc;
}

void
AnimateBoxList::setTexture(unsigned int tex)
{
  texture_ = tex;
}

static float
interp(float from, float to, float param)
{
  return (1-param) * from + param * to;
}

static Box
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
AnimateBoxList::render(float param)
{
  unsigned last = std::min(start_.size(), end_.size());
  last = std::min(last, tex_coords_.size());
  glPushAttrib(GL_COLOR_BUFFER_BIT | GL_ENABLE_BIT);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBindTexture(GL_TEXTURE_2D, texture_);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
  std::vector<Point> boxes(last*4);
  std::vector<Point> tex_coords(last*4);
  //glBegin(GL_QUADS);
  int j = 0;
  for (int i = 0; i < last; i++) {
    const Box& from = start_[i];
    const Box& to = end_[i];
    const Box& tex = tex_coords_[i];
    if (is_null_box(tex))
      continue;

    Box interp = interp_box(from, to, param);

    tex_coords[j] = Point(xmin(tex), ymin(tex));
    boxes[j] = Point(xmin(interp), ymin(interp));
    j++;
    tex_coords[j] = Point(xmax(tex), ymin(tex));
    boxes[j] = Point(xmax(interp), ymin(interp));
    j++;
    tex_coords[j] = Point(xmax(tex), ymax(tex));
    boxes[j] = Point(xmax(interp), ymax(interp));
    j++;
    tex_coords[j] = Point(xmin(tex), ymax(tex));
    boxes[j] = Point(xmin(interp), ymax(interp));
    j++;
  }
  //glEnd();
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, &(*boxes.begin()));
  glTexCoordPointer(2, GL_FLOAT, 0, &(*tex_coords.begin()));
  glDrawArrays(GL_QUADS, 0, j);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glPopAttrib();
  glBindTexture(GL_TEXTURE_2D, 0);
}

void
AnimateBoxList::computeTexCoords(const Box& tex_bounds)
{
  tex_coords_.resize(start_.size());
  for (int i = 0; i < start_.size(); i++) {
    Box& from = start_[i];
    Box& to = end_[i];
    Box& b = tex_coords_[i];
    if (is_null_box(from)) {
      if (is_null_box(to))
	continue;
      Point p = center(to);
      from = Box(p,p);
    }
    else if (is_null_box(to)) {
      Point p = center(from);
      to = Box(p,p);
    }

    set_xmin(b, (xmin(from)-xmin(tex_bounds))/width(tex_bounds));
    set_ymin(b, (ymin(from)-ymin(tex_bounds))/height(tex_bounds));
    set_xmax(b, (xmax(from)-xmin(tex_bounds))/width(tex_bounds));
    set_ymax(b, (ymax(from)-ymin(tex_bounds))/height(tex_bounds));
  }
}

void
AnimateBoxList::swap()
{
  start_.swap(end_);
}

} /// namespace infovis
