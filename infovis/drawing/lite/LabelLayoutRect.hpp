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
#ifndef INFOVIS_DRAWING_LITE_LABELLAYOUTRECT_HPP
#define INFOVIS_DRAWING_LITE_LABELLAYOUTRECT_HPP

#include <infovis/drawing/lite/LabelLayout.hpp>

namespace infovis {

/**
 * Dynamic labeling inside a rectangle
 */
class LabelLayoutRect : public LabelLayout
{
public:
  LabelLayoutRect(const Box& box, bool x_stable = false);

  virtual LayoutResult doLayout();

  
  virtual bool isXStable() const;
  virtual void setXStable(bool v);
  
protected:
  typedef std::vector<int> Stack;
  typedef std::vector<float> Pos;
  void record_offsets();
  Point nearest_point(const Point& from) const;
  void move_labels_initially();
  LayoutResult compute_left_right();
  void align_left(float max_width) const;
  void align_right(float max_width) const;
  float compute_max_width(const Stack& s);
  void optimize_origin(const Stack&, float height, Pos& y_pos) const;
  float compute_offset(float dy0, float dy1) const;

  bool x_stable_;
  std::vector<float> x_offsets_;
  Stack left_;
  Stack right_;
};

} // namespace infovis

#endif // INFOVIS_DRAWING_LITE_LABELLAYOUTRECT_HPP
