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
#include <infovis/drawing/lite/LabelLayout.hpp>

namespace infovis {

LabelLayout::LabelLayout(const Box& box)
  : bounds_(box),
    list_(),
    center_(0, 0),
    radius_(0)
{ }

LabelLayout::~LabelLayout()
{ }

LabelLayout::LayoutResult
LabelLayout::layout(const List& list, const Point& center, float radius)
{
  list_ = list;
  center_ = center;
  radius_ = radius;
  return doLayout();
}

Box
LabelLayout::getBounds() const
{
  return bounds_;
}

void
LabelLayout::setBounds(const Box& box)
{
  bounds_ = box;
}

const LabelLayout::List&
LabelLayout::getList() const { return list_; }

void
LabelLayout::setList(const LabelLayout::List& v) {list_ = v; }

const Point&
LabelLayout::getCenter() const { return center_; }

void
LabelLayout::setCenter(const Point& v) {center_ = v; }

float
LabelLayout::getRadius() const { return radius_; }

void
LabelLayout::setRadius(float v) {radius_ = v; }

LiteDisplacedLabel *
LabelLayout::getLabel(int i) const
{
  if (i < 0 || i > list_.size())
    return 0;
  return list_[i];
}

int
LabelLayout::getLabelCount() const
{
  return list_.size();
}

} // namespace infovis

