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
#include <infovis/drawing/lite/Lite.hpp>
#include <infovis/drawing/inter/Interactor.hpp>
#include <infovis/drawing/gl.hpp>
#include <GL/glut.h>
#include <stdexcept>
//#include <iostream>

namespace infovis {

Lite::~Lite()
{
  //std::cerr << "Freeing lite " << this << std::endl;
}

Box
Lite::getMinBounds() const
{
  return getBounds();
}

void
Lite::movePosition(const Vector& v)
{
  setPosition(getPosition()+v);
}

Vector
Lite::getSize() const
{
  return extent(getBounds());
}

void
Lite::setSize(const Vector& v)
{
  setBounds(Box(min(getBounds()), v));
}

bool
Lite::intersects(const Box& b) const
{
  return infovis::intersects(getBounds(), b);
}

bool
Lite::contains(const Box& b) const
{
  return infovis::contains(getBounds(), b);
}

bool
Lite::inside(const Point& p) const
{
  return infovis::inside(getBounds(), x(p), y(p));
}

void
Lite::doRender(const RenderContext& c)
{ }

void
Lite::render(const RenderContext& c)
{
  if (! is_visible)
    return;
  doRender(c);
  if (c.is_picking)
    glPushName(unsigned(-1));
  for (int i = 0; i < childCount(); i++) {
    if (c.is_picking)
      glLoadName(i);
    getChild(i)->render(c);
  }
  if (c.is_picking)
    glPopName();
}

Interactor *
Lite::interactor(const string& name, int toolid)
{
  return 0;
}

int
Lite::childCount() const { return 0; }

Lite *
Lite::getChild(int ) const { return 0; }

void
Lite::setChild(int, Lite* )
{
  throw std::overflow_error("Lite is not a container");
}

int
Lite::indexOf(Lite * l) const
{
  for (int i = 0; i < childCount(); i++) {
    if (getChild(i) == l)
      return i;
  }
  return -1;
}

Lite *
Lite::getPath(const Path& path)
{
  Lite * l = this;
  for (Path::const_iterator i = path.begin()+1;	// we always start with 0
       l != 0 && i != path.end();
       i++)
    l = l->getChild(*i);
  return l;
}

void
Lite::addChild(Lite *)
{
  throw std::overflow_error("Lite is not a container");
}

void
Lite::removeChild(Lite * l)
{
  eraseChild(indexOf(l));
}

void
Lite::insertChild(int, Lite *)
{
  throw std::overflow_error("Lite is not a container");
}

void
Lite::eraseChild(int)
{
  throw std::overflow_error("Lite is not a container");
}

void
Lite::removeAll()
{
  while (childCount() != 0)
    eraseChild(childCount()-1);
}

Lite::iterator
Lite::begin()
{
  return iterator(0);
}

Lite::const_iterator
Lite::begin() const
{
  return iterator(0);
}

Lite::iterator
Lite::end()
{
  return iterator(0);
}

Lite::const_iterator
Lite::end() const
{
  return iterator(0);
}

void
Lite::repaint() const
{
  glutPostRedisplay();
}

void
Lite::setVisible(bool b)
{
  is_visible = b;
}

void
Lite::invalidate()
{
  pack();
}

void
Lite::pack()
{
  for (int i = 0; i < childCount(); i++) {
    getChild(i)->pack();
  }
}

} // namespace infovis
