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
#ifndef INFOVIS_DRAWING_LITE_LITETEXTFIELD_HPP
#define INFOVIS_DRAWING_LITE_LITETEXTFIELD_HPP

#include <infovis/drawing/lite/LiteLabel.hpp>
#include <infovis/drawing/inter/Interactor3States.hpp>
#include <infovis/drawing/inter/KeyCodeInteractor.hpp>

namespace infovis {

/**
 * Lite for displaying a text field.
 */
class LiteTextField : public LiteLabel,
		      public Interactor3States,
		      public KeyCodeInteractor
{
public:
  LiteTextField(const string& text,
		float width,
		justification j = just_left,
		Font * font = 0,
		const Color& fg = color_black,
		const Color& bg = color_white,
		const Color& gfg = color_none);

  virtual int getCaretPosition() const;
  virtual void setCaretPosition(unsigned pos);

  virtual void doRender(const RenderContext& c);
  virtual Lite * clone() const;
  virtual Interactor * interactor(const string& name, int toolid);
  
  // Interactor3States
  virtual bool doStart(const Event& ev);
  virtual void doDrag(const Event& ev);
  virtual void doFinish(const Event& ev);

  // KeyCodeInteractor
  virtual void doKeyDown(KeyCode code);
protected:
  int caret_position_;
};

} // namespace infovis


#endif // INFOVIS_DRAWING_LITE_LITETEXTFIELD_HPP
