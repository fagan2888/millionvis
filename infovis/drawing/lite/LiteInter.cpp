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
#include <infovis/drawing/lite/LiteInter.hpp>
//#include <infovis/drawing/box_io.hpp>

namespace infovis {

LiteMoveInteractor::LiteMoveInteractor(Lite * l)
  : lite_(l)
{ }

Interactor *
LiteMoveInteractor::interactor(const string& name, int tool_id)
{
  if (isA(name) && tool_id == mouse_id)
    return this;
  return 0;
}

bool
LiteMoveInteractor::doStart(const Event& ev)
{
  lite_start_pos_ = lite_->getPosition();
  return true;
}

void
LiteMoveInteractor::doDrag(const Event& ev)
{
  Vector v(getFieldPosition(ev) - start_pos);
  //  std::cerr << "dragging by " << v << std::endl;
  lite_->setPosition(lite_start_pos_ + v);
  lite_->repaint();
}

void
LiteMoveInteractor::doFinish(const Event& ev)
{
  doDrag(ev);
}

} // namespace infovis
