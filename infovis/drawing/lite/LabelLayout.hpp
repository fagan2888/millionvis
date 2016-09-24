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
#ifndef INFOVIS_DRAWING_LITE_LABELLAYOUT_HPP
#define INFOVIS_DRAWING_LITE_LABELLAYOUT_HPP

#include <infovis/drawing/lite/LiteDisplacedLabel.hpp>

namespace infovis {

/**
 * Layout manager for LiteBox
 */
class LabelLayout : public gc	// no ressources so no need to call destructor
{
public:
  typedef std::vector<LiteDisplacedLabel*,gc_alloc<LiteDisplacedLabel*> > List;

  enum LayoutResult {
    layout_dont_know,
    layout_dont_overlap,
    layout_overlap
  };

  LabelLayout(const Box& box);
  virtual ~LabelLayout();

  LayoutResult layout(const List& list, const Point& center, float radius); // not virtual

  virtual LayoutResult doLayout() = 0;

  virtual Box getBounds() const;
  virtual void setBounds(const Box& box);
  
  virtual const List& getList() const;
  virtual void setList(const List& v);

  virtual const Point& getCenter() const;
  virtual void setCenter(const Point& v);
  
  virtual float getRadius() const;
  virtual void setRadius(float v);

  virtual LiteDisplacedLabel * getLabel(int i) const;
  virtual int getLabelCount() const;

  
protected:
  Box bounds_;
  List list_;
  Point center_;
  float radius_;
};  

} // namespace infovis

#endif // INFOVIS_DRAWING_LITE_LABELLAYOUT_HPP
