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
#include <infovis/drawing/Font.hpp>
#include <infovis/drawing/lite/LiteButton.hpp>
#include <infovis/drawing/lite/LiteFrame.hpp>
#include <infovis/drawing/lite/LiteLabel.hpp>
#include <infovis/drawing/inter/KeyCodes.hpp>
#include <infovis/drawing/gl_support.hpp>

#include <LabelTreemap.hpp>

#include <iostream>

namespace infovis {

LabelTreemap::LabelTreemap(LiteTreemap * treemap,
			   const string& name,
			   Font * font)
  : treemap_(treemap),
    tree_(treemap->tree_),
    name_(name),
    font_(font),
    hit_(root(tree_))
{ }

Lite *
LabelTreemap::clone() const
{
  return new LabelTreemap(treemap_, name_, font_);
}

void
LabelTreemap::doRender(const RenderContext& rc)
{
  if (boxes_.empty()) return;

  set_color(color_white);
  int i;
  for (i = 0; i != boxes_.size(); i++) {
    const Box& b = boxes_[i];
    stroke_box(b);
  }
}

bool
LabelTreemap::isLabelOver(const Box& box) const
{
  for (PathBoxes::const_iterator i = label_boxes_.begin();
       i != label_boxes_.end(); i++) {
    const Box& b = *i;
    if (infovis::intersects(b, box))
      return true;
  }
  return false;
}

bool
LabelTreemap::addLabel(const Box& box)
{
  if (! infovis::contains(boxes_[0], box)) // not inside treemap
    return false;
  if (isLabelOver(box))
    return false;
  label_boxes_.push_back(box);
  return true;
}

bool
LabelTreemap::layoutLabel(const string& label, const Box& box)
{
  Box bounds(font_->getStringBounds(label));
  Vector size(width(bounds), height(bounds));

  // Try to put it top-right, bottom-right, top-left, bottom-left in
  // that order
  const Point top_right_min(xmax(box), ymax(box)-height(bounds));
  const Box top_right(top_right_min, size);
  const Point top_left_min(xmin(box), ymax(box)-height(bounds));
  const Box top_left(top_left_min, size);
  const Point bottom_right_min(xmax(box), ymin(box));
  const Box bottom_right(bottom_right_min, size);
  const Point bottom_left_min(xmin(box), ymin(box));
  const Box bottom_left(bottom_left_min, size);

  if (width(bounds) <= width(box) &&
      height(bounds) <= height(box)) {
    return (addLabel(top_left) ||
	    addLabel(bottom_left) ||
	    addLabel(top_right) ||
	    addLabel(bottom_right));
  }
  return (addLabel(top_right) ||
	  addLabel(bottom_right) ||
	  addLabel(top_left) ||
	  addLabel(bottom_left));
}

void
LabelTreemap::changed(ChangeObservable * obs)
{
  std::cout << "changed called\n";
  for (int j = 0; j < childCount(); j++) {
    LiteButton * but = dynamic_cast<LiteButton*>(getChild(j));
    if (obs == but) {
      std::cout << "found root=" << labels_[j] << std::endl;
      treemap_->update_root(labels_[j]);
      repaint();
      return;
    }
  }
  std::cout << "found no root" << std::endl;
}

void
LabelTreemap::clear()
{
  label_boxes_.clear();
  labels_.clear();
  
  for (int j = 0; j < childCount(); j++) {
    Lite * l = getChild(j);
    delete l;
  }
  group_.clear();		// +++ FIXME
}

void
LabelTreemap::layoutLabels() 
{
  StringColumn * col = StringColumn::cast(tree_.find_column(name_));
  if (col == 0 || boxes_.empty()) return;

  clear();
  
  int i = boxes_.size()-1;
  for (node_descriptor n = hit_;
       n != root(tree_) && i >= 0;
       n = parent(n, tree_), i--) {
    const string& label = (*col)[n];
    if (layoutLabel(label, boxes_[i])) {
      LiteLabel * lab = new LiteLabel(label,
				      LiteLabel::just_left,
				      font_,
				      color_black,
				      color_none,
				      color_white);
      LiteFrame * frame = new LiteFrame(lab, color_black, 2);
      frame->setPosition(min(label_boxes_[label_boxes_.size()-1]));
      LiteButton * but = new LiteButton(frame);
      but->addChangeObserver(this);
      labels_.push_back(n);
      addChild(but);
    }
  }
}


} // namespace infovis
