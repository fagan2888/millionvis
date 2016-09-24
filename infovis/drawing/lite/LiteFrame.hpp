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
#ifndef INFOVIS_DRAWING_LITEFRAME_HPP
#define INFOVIS_DRAWING_LITEFRAME_HPP

#include <infovis/drawing/lite/LiteProxy.hpp>
#include <infovis/drawing/lite/Border.hpp>
#include <infovis/drawing/inter/InteractorEnterLeave.hpp>

namespace infovis {

/**
 * Lite that draws a border around it.
 */
class LiteFrame : public LiteProxy,
		  public InteractorEnterLeave
{
public:
  LiteFrame(Lite * l, const Color& c, float width);

  virtual Box getBounds() const;
  virtual void setBounds(const Box& b);
  virtual void doRender(const RenderContext&);
  virtual Lite * clone() const;
  virtual Interactor * interactor(const string& name, int toolid);

  // InteractorEnterLeave
  virtual bool doEnter(const Event&);
  virtual void doLeave(const Event&);
  
protected:
  Color color_;
  Border border_;
  float width_;
};

} // namespace infovis

#endif // INFOVIS_DRAWING_LITEFRAME_HPP