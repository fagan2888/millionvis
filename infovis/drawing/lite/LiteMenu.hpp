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
#ifndef INFOVIS_DRAWING_LITE_MENU_HPP
#define INFOVIS_DRAWING_LITE_MENU_HPP

#include <infovis/drawing/lite/LiteBox.hpp>
#include <infovis/drawing/lite/Border.hpp>
#include <infovis/drawing/notifiers/BeginEnd.hpp>
#include <infovis/drawing/notifiers/BoundedRange.hpp>
#include <infovis/drawing/inter/Interactor3States.hpp>

namespace infovis {

/**
 * Lite menu
 */
class LiteMenu : public LiteBox,
		 public Interactor3States,
		 public BoundedRange,
		 public AbstractBoundedRangeObservable,
		 public DefaultBeginEndObservable
{
public:
  LiteMenu(const Color& c = color_white);
  LiteMenu(const Color& c, float max_width, float max_height = 0);

  Lite * clone() const;

  virtual Box getBounds() const;
  virtual Box getInBounds() const;
  
  virtual Interactor * interactor(const string& name, int tool_id);
  virtual void render(const RenderContext& c);

  // BoundedRange
  virtual float min() const;
  virtual float max() const;
  virtual float value() const;
  virtual float range() const;

  // AbstractBoundedRangeObservable
  virtual const BoundedRange * getBoundedRange() const;

  // Interactor3States
  virtual void doMove(const Event& ev);
  virtual bool doStart(const Event& ev);
  virtual void doDrag(const Event& ev);
  virtual void doFinish(const Event& ev);

  // Interactor
  virtual void doAbort(const Event& ev);

  virtual void setSelected(int s);
  virtual int getSelected() const;

  virtual const Color& getColor() const;
  virtual void setColor(const Color& c);

  const Vector& getMaxSize() const { return max_size_; }
protected:
  virtual void doRender(const RenderContext&);
  virtual int selectedFromPos(const Point& pos);
  Vector max_size_;
  Color color_;
  int selected_;
  bool was_visible_;
  Border border_;
};

} // namespace infovis

#endif // INFOVIS_DRAWING_LITE_MENU_HPP
