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
#ifndef TREEMAP2_LABELTREEMAP_HPP
#define TREEMAP2_LABELTREEMAP_HPP

#include <infovis/drawing/drawing.hpp>
#include <infovis/drawing/lite/LiteGroup.hpp>
#include <infovis/drawing/notifiers/Change.hpp>
#include <types.hpp>
#include <LiteTreemap.hpp>

namespace infovis {

class Font;
class LiteButton;

class LabelTreemap : public LiteGroup,
		     public ChangeObserver
{
public:
  LabelTreemap(LiteTreemap *, const string& name, Font * font);

  Lite * clone() const;
  void doRender(const RenderContext& );

  void setBoxes(const PathBoxes& boxes) {
    boxes_ = boxes;
  }
  const PathBoxes& getBoxes() const { return boxes_; }

  void setHit(node_descriptor hit) { hit_ = hit; }
  node_descriptor getHit() const { return hit_; }
  bool isLabelOver(const Box& box) const;
  bool addLabel(const Box& box);

  void clear();
  bool layoutLabel(const string& label, const Box& box);
  void layoutLabels();
    
  // ChangeObserver
  virtual void changed(ChangeObservable *);

protected:
  LiteTreemap * treemap_;
  const Tree& tree_;
  string name_;
  Font * font_;
  PathBoxes boxes_;
  PathBoxes label_boxes_;
  typedef std::vector<node_descriptor> Labels;
  Labels labels_;
  node_descriptor hit_;
};

} // namespace infovis

#endif // TREEMAP2_LABELTREEMAP_HPP
