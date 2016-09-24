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
#ifndef INFOVIS_DRAWING_ANIMATEBOXLIST_HPP
#define INFOVIS_DRAWING_ANIMATEBOXLIST_HPP

#include <infovis/drawing/Animate.hpp>
#include <vector>

namespace infovis {

/**
 * Animation for interpolating a list of boxes
 */
class AnimateBoxList : public Animate
{
public:
  typedef std::vector<Box, gc_alloc<Box,true> > BoxList;
  AnimateBoxList(int size);

  virtual void setStartList(const BoxList& bl);
  BoxList& getStartList() { return start_; }
  const BoxList& getStartList() const { return start_; }

  virtual void setEndList(const BoxList& el);
  BoxList& getEndList() { return end_; }
  const BoxList& getEndList() const { return end_; }

  virtual void setTexCoords(const BoxList& tc);
  BoxList& getTexCoords() { return tex_coords_; }
  const BoxList& getTexCoords() const { return tex_coords_; }

  virtual void computeTexCoords(const Box& tex_bounds);
  virtual void setTexture(unsigned int t);
  virtual void swap();

  virtual void render(float param = 0.0f);


protected:
  BoxList start_;
  BoxList end_;
  BoxList tex_coords_;
  unsigned int texture_;
};

} // namespace infovis


#endif // INFOVIS_DRAWING_ANIMATEBOXLIST_HPP

