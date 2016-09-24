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
#ifndef INFOVIS_DRAWING_LITE_LITEPROXY_HPP
#define INFOVIS_DRAWING_LITE_LITEPROXY_HPP

#include <infovis/drawing/lite/Lite.hpp>

namespace infovis {

/**
 * Lite the forwards everything to a child.  Implements the Proxy design pattern.
 */
class LiteProxy : public Lite
{
public:
  LiteProxy(Lite * l) : lite_(l) {}
  ~LiteProxy();

  virtual void setLite(Lite * l);
  virtual Lite * getLite() const;

  virtual Box getBounds() const;
  virtual void setBounds(const Box& b);
  virtual Box getMinBounds() const;
  virtual Point getPosition() const;
  virtual void setPosition(const Point& p);
  virtual Vector getSize() const;
  virtual void setSize(const Vector& s);
  virtual bool intersects(const Box& b) const;
  virtual bool contains(const Box& b) const;
  virtual bool inside(const Point& p) const;
  virtual void doRender(const RenderContext& c);
  virtual Lite * clone() const;
  virtual Interactor * interactor(const string& name, int toolid);
  virtual int childCount() const;
  virtual Lite * getChild(int index) const;
  virtual void setChild(int index, Lite *);
  virtual int indexOf(Lite *) const;
  virtual Lite * getPath(const Path& p);
  virtual void addChild(Lite *);
  virtual void removeChild(Lite *);
  virtual void insertChild(int pos, Lite *);
  virtual void eraseChild(int pos);
  virtual void removeAll();
  virtual iterator begin();
  virtual const_iterator begin() const;
  virtual iterator end();
  virtual const_iterator end() const;
  virtual void repaint() const;
  virtual void setVisible(bool b);
  virtual void invalidate();
  virtual void pack();
protected:
  Lite * lite_;
};
} // namespace infovis
#endif // INFOVIS_DRAWING_LITE_LITEPROXY_HPP
