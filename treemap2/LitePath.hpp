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
#ifndef TREEMAP2_LITEPATH_HPP
#define TREEMAP2_LITEPATH_HPP

#include <infovis/drawing/Font.hpp>
#include <infovis/drawing/lite/Lite.hpp>
#include <infovis/drawing/lite/Border.hpp>
#include <infovis/drawing/inter/Interactor3States.hpp>
#include <infovis/drawing/notifiers/BoundedRange.hpp>

#include <types.hpp>

namespace infovis {

class LitePath : public Lite,
		 public Interactor3States,
		 public BoundedRange,
		 public AbstractBoundedRangeObservable
{
public:
  LitePath(node_descriptor n,
	   const Tree& tree,
	   const StringColumn& name,
	   Font * font);
  
  // BoundedRange
  virtual float min() const;
  virtual float max() const;
  virtual float value() const;
  virtual float range() const;

  virtual const BoundedRange * getBoundedRange() const;
  void setReference(int i);
  int getReference()			{ return reference_; }
  node_descriptor getPath() const 	{ return node_; }
  void setPath(node_descriptor n);
  void setVisible(bool b);
  Box getBounds() const;
  Box getInBounds() const;
  void setBounds(const Box& b);
  Point getPosition() const		{ return position_; }
  void setPosition(const Point& p)	{ position_ = p; }

  Lite * clone() const;
  void setSelected(int s)		{ selected_ = s; }
  int getSelected() const		{ return selected_; }
  node_descriptor getSelectedRoot() const;
  BoundedRangeObservable& getLeftRight() { return left_right_; }

  Interactor * interactor(const string& name, int tool_id);

  void moveSmart(const Point& pos);
  int selectedFromPos(const Point& pos);

  // Interactor3States
  virtual void doMove(const Event& ev);
  virtual bool doStart(const Event& ev);
  virtual void doDrag(const Event& ev);
  virtual void doFinish(const Event& ev);
  virtual void doAbort(const Event& ev);
  
protected:
  void updateBounds();
  void doRender(const RenderContext& rc);

  const Tree& tree_;
  node_descriptor node_;
  const StringColumn& name_;
  Point position_;
  Font * font_;
  int depth_;
  int selected_;
  Vector size_;
  bool was_inside_;
  bool was_visible_;
  int reference_;
  Border border_;
  DefaultBoundedRangeObservable left_right_;
};

} // namespace infovis

#endif // TREEMAP2_LITEPATH_HPP
