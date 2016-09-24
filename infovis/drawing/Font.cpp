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
#include <infovis/drawing/Font.hpp>
//#include <infovis/drawing/FontGlut.hpp>
//#include <infovis/drawing/FontWin32.hpp>
//#include <infovis/drawing/FontFT.hpp>

//#define PRINT
#ifdef PRINT
#include <iostream>
#endif

namespace infovis {

Font::Font(const string& n, Style s, float sz)
  : name(n),
    style(s),
    size(sz) {}

Font::~Font() {}

void
Font::paintGrown(const string& str, float x, float y)
{
  paint(str, x, y);
}

float
Font::getHeight() const
{
  return getLeading() + getAscent() + getDescent();
}

Font::Creator::Creator()
{
  next = first;
  first = this;
}

extern void installFontGlut();
extern void installFontWin32();
extern void installFontFT();

Font *
Font::create(const string& name, Style style, float size)
{
  static bool inited;
  if (! inited) {
    installFontGlut();
    installFontWin32();
    installFontFT();
	inited = true;
  }
  if (size < 0) {
    size = -size;
  }
  else {
    size *= point_size;
  }
  static Font * deflt;
  if (deflt && name == "default")
    return deflt;

  Font * f = 0;
  for (Creator * c = Creator::first; c != 0; c = c->next) {
    if ((f = c->create(name, style, size)) != 0) {
#ifdef PRINT
      std::cout << "Font " << name << " Size " << size << " created by "
		<< typeid(*c).name() << std::endl;
#endif
      break;
    }
  }
  if (deflt == 0 && name == "default")
    deflt = f;
  return f;
}

Font *
Font::create(const string& name, const string& style, float size)
{
  if (style == "plain")
    return create(name, style_plain, size);
  else if (style == "bold")
    return create(name, style_bold, size);
  else if (style == "italic")
    return create(name, style_italic, size);
  else if (style == "bold italic")
    return create(name, style_bold_italic, size);
  return create(name, style_plain, size);
}

float Font::point_size = 1.0f;

void
Font::setPointSize(float ptsz) { point_size = ptsz; }
float
Font::getPointSize() { return point_size; }


Font::Creator::~Creator() {}

Font::Creator * Font::Creator::first;

void
Font::center(const string& str, float x, float y)
{
  float w = stringWidth(str);
  paint(str, x - w / 2, y);
}

void
Font::rightJustify(const string& str, float x, float y)
{
  float w = stringWidth(str);
  paint(str, x - w, y);
}

} // namespace infovis
