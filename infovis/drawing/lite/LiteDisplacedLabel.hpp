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
#ifndef INFOVIS_DRAWING_LITE_LITEDISPLACEDLABEL_HPP
#define INFOVIS_DRAWING_LITE_LITEDISPLACEDLABEL_HPP

#include <infovis/drawing/lite/LiteLabel.hpp>
#include <vector>

namespace infovis {

/**
 * Label with a line.  Used for dynamic labeling.
 */
class LiteDisplacedLabel : public LiteLabel
{
public:
  typedef std::vector<Point, gc_alloc<Point,true> > Path;
  LiteDisplacedLabel(const string& label,
		     const Point& orig,
		     justification j = just_left,
		     Font * font = 0,
		     const Color& fg = color_black,
		     const Color& bg = color_white,
		     const Color& gfg = color_none);

  virtual void doRender(const RenderContext& c);
  virtual Lite * clone() const;

  const Point& getOrig() const { return orig_; }
  const Path& getPath() const { return path_; }
  void addPath(const Point& p) { path_.push_back(p); }
  void setPath(const Path& p) { path_ = p; } // at your own risk
  void setLineAlpha(float alpha);
  float getLineAlpha() const { return line_alpha_; }
protected:
  Point orig_;
  Path path_;
  float line_alpha_;
};

} // namespace infovis

#endif // INFOVIS_DRAWING_LITE_LITEDISPLACEDLABEL_HPP
