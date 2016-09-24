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
#ifndef INFOVIS_DRAWING_EVENTCODES_HPP
#define INFOVIS_DRAWING_EVENTCODES_HPP

#include <infovis/drawing/inter/Event.hpp>

namespace infovis {

/**
 * Common methods for storing and retrieving informations in events.
 */
class EventCodes
{
public:
  static const string field_x;	// float field
  static const string field_y;	// float field
  static const string field_mod; // int field
  static const string field_on;	// bool field

  static float getFieldX(const Event& ev) {
    return ev[field_x].getFloatValue();
  }
  static void setFieldX(Event& ev, float v) {
    ev[field_x].setFloatValue(v);
  }
  static float getFieldY(const Event& ev) {
    return ev[field_y].getFloatValue();
  }
  static void setFieldY(Event& ev, float v) {
    ev[field_y].setFloatValue(v);
  }
  static int getFieldMod(const Event& ev) {
    return ev[field_mod].getIntValue();
  }
  static void setFieldMod(Event& ev, int v) {
    ev[field_mod].setIntValue(v);
  }

  static Point getFieldPosition(const Event& ev) {
    return Point(getFieldX(ev), getFieldY(ev));
  }
  static void setFieldPosition(Event& ev, const Point& p) {
    setFieldX(ev, x(p));
    setFieldY(ev, y(p));
  }

  static bool getFieldOn(const Event& ev) {
    return ev[field_on].getBoolValue();
  }

  static void setFieldOn(Event& ev, bool v) {
    ev[field_on].setBoolValue(v);
  }

};
} // namespace infovis 

#endif // INFOVIS_DRAWING_EVENTCODES_HPP
