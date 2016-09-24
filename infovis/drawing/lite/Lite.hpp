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
#ifndef INFOVIS_DRAWING_LITE_LITE_HPP
#define INFOVIS_DRAWING_LITE_LITE_HPP

#include <infovis/drawing/drawing.hpp>
#include <vector>

namespace infovis {
class Interactor;

enum {
  mouse_id,
  keyboard_id
};

/**
 * A Lite is the root class for all retained graphics objects.
 *
 * Lite objects form a tree.
 */
class Lite : public virtual gc
{
public:
  typedef std::vector<Lite*, gc_alloc<Lite*> > List;
  typedef std::vector<int, gc_alloc<int,true> > Path;
  typedef List::iterator iterator;
  typedef List::const_iterator const_iterator;

  /**
   * Context for rendering and picking in OpenGL
   */ 
  struct RenderContext {
    bool is_picking;
    float quality;
    RenderContext()
      : is_picking(false), quality(1.0f) { }
    RenderContext(bool p, float q = 1.0f)
      : is_picking(p), quality(q) {}
  };

  Lite() : is_visible(true) {}
  virtual ~Lite();

  virtual Box getBounds() const = 0;
  virtual void setBounds(const Box& b) = 0;
  virtual Box getMinBounds() const;
  virtual Point getPosition() const = 0;
  virtual void setPosition(const Point& p) = 0;
  virtual void movePosition(const Vector& v);
  virtual Vector getSize() const;
  virtual void setSize(const Vector& s);
  virtual bool intersects(const Box& b) const;
  virtual bool contains(const Box& b) const;
  virtual bool inside(const Point& p) const;
  virtual void render(const RenderContext&);
  virtual Lite * clone() const = 0;
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
  bool isVisible() const { return is_visible; }

  virtual void invalidate();
  virtual void pack();
protected:
  virtual void doRender(const RenderContext&);
  bool is_visible;
};

} // namespace infovis

#endif // INFOVIS_DRAWING_LITE_LITE_HPP
