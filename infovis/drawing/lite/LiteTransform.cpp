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
#include <infovis/drawing/lite/LiteTransform.hpp>
#include <infovis/drawing/gl.hpp>

namespace infovis {

  LiteTransform::LiteTransform() { }
  LiteTransform::LiteTransform(const Transform& t) : trans(t) { }

  Box
  LiteTransform::getBounds() const
  {
    Transform::Matrix m;
    trans.apply(m);
    Box b(m * min(bounds), m * max(bounds));
    normalize(b);
    return b;
  }

  void
  LiteTransform::render(const RenderContext& c)
  {
    glPushMatrix();
    trans.apply();
    LiteGroup::render(c);
    glPopMatrix();
  }

  Lite *
  LiteTransform::clone() const
  {
    LiteTransform * ret = new LiteTransform(trans);
    for (List::const_iterator i = group_.begin(); i != group_.end(); i++)
      ret->addChild((*i)->clone());
    return ret;
  }
} // namespace infovis 
