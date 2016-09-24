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
#ifndef INFOVIS_DRAWING_LITE_LITEINTER_HPP
#define INFOVIS_DRAWING_LITE_LITEINTER_HPP

#include <infovis/drawing/inter/Interactor3States.hpp>
#include <infovis/drawing/lite/Lite.hpp>

namespace infovis {

/**
 * Lite that manages positional interaction following the
 * Interactor3States protocol.
 */
class LiteMoveInteractor : public Interactor3States
{
public:
  LiteMoveInteractor(Lite * l);

  virtual Interactor * interactor(const string& name, int toolid);

  virtual bool doStart(const Event& ev);
  virtual void doDrag(const Event& ev);
  virtual void doFinish(const Event& ev);
    
protected:
  Lite * lite_;
  Point lite_start_pos_;
};

} // namespace infovis


#endif // INFOVIS_DRAWING_LITE_LITEINTER_HPP
