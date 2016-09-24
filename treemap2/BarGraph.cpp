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
#include <BarGraph.hpp>
#include <infovis/drawing/gl_support.hpp>
#include <infovis/tree/numeric_prop_min_max.hpp>
#include <algorithm>

namespace infovis {


BarGraph::BarGraph(unsigned bars)
  : bars_(bars)
{
  reset();
}

void
BarGraph::reset(float val)
{
  min_ = 0;
  max_ = 0;
  std::fill(bars_.begin(), bars_.end(), val);
}

void
BarGraph::setValue(unsigned index, float value)
{
  bars_[index] = value;
  if (value < min_)
    min_ = value;
  else if (value > max_)
    max_ = value;
}

float
BarGraph::getValue(unsigned index) const
{
  return bars_[index];
}

void
BarGraph::computeDistribution(const FloatColumn& values)
{
#ifdef VECTOR_AS_TREE
  float min_val, max_val;
  numeric_prop_min_max(values, min_val, max_val);
  computeDistribution(values, min_val, max_val);
#else
  computeDistribution(values, values.min(), values.max());
#endif
}

void
BarGraph::computeDistribution(const FloatColumn& values,
			      float min_val, float max_val)
{
  float step = (max_val - min_val + 1) / bars_.size();
  float gap = bars_.size() / (max_val - min_val + 1);
  FloatColumn::const_iterator i;

  reset(0);

  for (i = values.begin(); i != values.end(); i++) {
    if (*i < min_val || *i > max_val)
      continue;
    int index = int((*i - min_val) / step);
    for (int j = index; j <= int(index + gap); j++)
      bars_[j]++;
  }
  max_ = min_ = bars_[0];
  for (i = bars_.begin()+1; i != bars_.end(); i++) {
    float v = *i;
    if (v < min_)
      min_ = v;
    else if (v > max_)
      max_ = v;
  }
}


void
BarGraph::updateMinMax()
{
  if (min_ < max_ || bars_.empty())
    return;

  max_ = min_ = bars_[0];
  for (List::const_iterator i = bars_.begin()+1; i != bars_.end(); i++) {
    float v = *i;
    if (v < min_)
      min_ = v;
    else if (v > max_)
      max_ = v;
  }
}

void
BarGraph::render(const Box& box, direction dir) const
{
  glPushMatrix();
  switch(dir) {
  case left_to_right:
    glTranslatef(xmin(box), ymin(box), 0);
    glScalef(width(box), height(box), 1);
    break;
  case right_to_left:
    glScalef(-width(box), height(box), 1);
    glTranslatef(xmax(box), ymin(box), 0);
    break;
  case top_to_bottom:
  case bottom_to_top:
    glRotatef(90, 0, 0, 1);
    glScalef(width(box), height(box), 1);
    glTranslatef(xmin(box), ymax(box), 0);
    break;
  }
  glScalef(1.0f/(bars_.size()+1), 1.0f/(max_ - min_ + 1), 1);
  glBegin(GL_QUAD_STRIP);
  glVertex2f(0, 0);
  glVertex2f(1, bars_[1]-min_);
  for (int i = 0; i < bars_.size(); i++) {
    glVertex2f(i, 0);
    glVertex2f(i, bars_[i]-min_);
  }
  glEnd();
  glPopMatrix();
}

} // namespace infovis
