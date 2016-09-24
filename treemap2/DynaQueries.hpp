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
#ifndef TREEMAP_DYNAQUERIES_HPP
#define TREEMAP_DYNAQUERIES_HPP

#include <infovis/drawing/lite/LayoutTable.hpp>
#include <infovis/drawing/lite/LiteBackground.hpp>
#include <infovis/drawing/lite/LiteBox.hpp>
#include <infovis/drawing/lite/LiteLabel.hpp>
#include <infovis/drawing/lite/LiteRangeSlider.hpp>
#include <infovis/drawing/lite/LiteWindow.hpp>
#include <infovis/drawing/notifiers/BeginEnd.hpp>
#include <infovis/drawing/notifiers/Change.hpp>
#include <infovis/drawing/notifiers/BoundedRange.hpp>

#include <types.hpp>
#include <LiteTreemap.hpp>

namespace infovis {

class DynamicQueries : public LiteBox,
		       public BoundedRangeObserver,
		       public BeginEndObserver
{
protected:
  LiteTreemap * tm_;
  const Tree& tree_;
  std::vector<LiteRangeSlider*> slider_;
  std::vector<const column*> column_;
  Font * label_font_;
  LiteBackground background_;
  FilterColumn * filter_;
public:
  DynamicQueries(LiteTreemap * tm, FilterColumn * col, Font * label_font);

  Lite * clone() const;

  void create_numeric(const FloatColumn * col);
  void create_string(const StringColumn * col);
  void filter(int i, const BoundedRange * range);
  void applyFilters();

  // BoundedRangeObserver
  virtual void valueDragged(BoundedRangeObservable * obs);  
  virtual void rangeDragged(BoundedRangeObservable * obs);  
  virtual void updateBoundedRange(BoundedRangeObservable * obs);

  // BeginEndObserver
  virtual void begin(BeginEndObservable *);
  virtual void end(BeginEndObservable *);

  virtual bool isVisible() const;
  virtual void setVisible(bool);

  LiteBackground * getBackground() { return &background_; }
};

} // namespace infovis

#endif // TREEMAP_DYNAQUERIES_HPP
