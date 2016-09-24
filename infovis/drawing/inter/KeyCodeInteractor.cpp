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
#include <infovis/drawing/inter/KeyCodeInteractor.hpp>

namespace infovis {

KeyCodeInteractor::KeyCodeInteractor()
  : Interactor("KeyCode")
{ }

bool
KeyCodeInteractor::activate()
{
  return true;
}
void
KeyCodeInteractor::desactivate()
{ }

void
KeyCodeInteractor::abort()
{ }

void
KeyCodeInteractor::key_down(KeyCode code)
{
  doKeyDown(code);
}

void
KeyCodeInteractor::key_up(KeyCode code)
{
  doKeyUp(code);
}

void
KeyCodeInteractor::doKeyDown(KeyCode code)
{ }

void
KeyCodeInteractor::doKeyUp(KeyCode code)
{ }


} // namespace infovis 
