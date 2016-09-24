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
#include <infovis/drawing/gl_support.hpp>
#include <infovis/drawing/lite/LabelLayoutRect.hpp>
#include <infovis/drawing/lite/LabelLayoutSimple.hpp>

#include <FastPicker.hpp>

namespace infovis {

FastPicker::FastPicker(const Tree& tree, const BorderDrawer& b)
  : x_pos(-1),
    y_pos(-1),
    hit_(root(tree)),
    label_level(1),
    border(b),
    show_all_labels_(false)
{ }

void
FastPicker::start()
{
  hit_ = tree_traits<Tree>::nil();
  path_boxes.clear();
  labels.clear();
  label_centers.clear();
}

void
FastPicker::set_pos(int x, int y)
{
  x_pos = x;
  y_pos = y;
  labels.clear();
  label_centers.clear();
}


void
FastPicker::set_label_level(int l)
{
  label_level = l;
}

void
FastPicker::set_labels_clip(Box b)
{
  labels_clip = b;
}


void
FastPicker::finish(const Box& bounds,
		   Font * font,
		   float line_alpha,
		   const StringColumn& name)
{
#if 1
  LabelLayoutRect::List disp_labels;
  for(int i = 0; i < label_centers.size(); i++) {
    LiteDisplacedLabel * ld = new LiteDisplacedLabel(name[labels[i]],
						     label_centers[i],
						     LiteLabel::just_center,
						     font,
						     color_black,
						     color_none,
						     color_white
						     );
    ld->setLineAlpha(line_alpha);
    disp_labels.push_back(ld);
  }
  if (empty(labels_clip)) {
    LabelLayoutSimple simple_layout(bounds);
    simple_layout.layout(disp_labels, center(labels_clip), width(labels_clip)/2);
  }
  else {
    LabelLayoutRect rect_layout(bounds);
    rect_layout.layout(disp_labels, center(labels_clip), width(labels_clip)/2);
  }
  Lite::RenderContext rc;
  glPushAttrib(GL_COLOR_BUFFER_BIT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  for (LabelLayoutRect::List::const_iterator j = disp_labels.begin();
       j != disp_labels.end(); j++) {
    (*j)->render(rc);
    delete *j;
  }
  glPopAttrib();
#else
  float desc = font->getDescent();
  for(int i = 0; i < label_centers.size(); i++) {
    const string& str = name[labels[i]];
    float w = font->stringWidth(str);
    set_color(color_white);
    font->paintGrown(str,
		     x(label_centers[i]) - w/2,
		     y(label_centers[i])+desc);
    set_color(color_black);
    font->paint(str,
		x(label_centers[i]) - w/2,
		y(label_centers[i])+desc);
  }
#endif
}

} // namespace infovis
