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
#ifndef INFOVIS_DRAWING_LITE_LITESAVEUNDER_HPP
#define INFOVIS_DRAWING_LITE_LITESAVEUNDER_HPP

#include <infovis/drawing/lite/LiteProxy.hpp>


namespace infovis {

/**
 * Lite that caches its image
 */
class LiteSaveUnder : public LiteProxy
{
public:
  LiteSaveUnder(Lite * l)
    : LiteProxy(l), save_under(0), save_under_size(0) { }
  ~LiteSaveUnder();

  virtual void doRender(const RenderContext& c);
  virtual Lite * clone();

  virtual void repaint();

protected:
  typedef box_min_extent<int> IntBox;
  void save(const IntBox&);
  void restore();
  void refresh();
  IntBox saved;
  unsigned char * save_under;
  int save_under_size;
};
} // namespace infovis 


#endif
