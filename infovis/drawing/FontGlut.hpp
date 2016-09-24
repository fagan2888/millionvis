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
#ifndef INFOVIS_DRAWING_FONTGLUT_HPP
#define INFOVIS_DRAWING_FONTGLUT_HPP

#include <infovis/drawing/Font.hpp>

namespace infovis {

/**
 * Implementation of Glut based stroked fonts.
 */
class FontGlutStroke : public Font
{
protected:
  void * type;
public:

  FontGlutStroke(void * t,
		 const string& name, Style style, float size);

  virtual bool install();
  virtual void finish();

  virtual Format getFormat() const;
  virtual bool isFixedWidth() const;
  virtual void paint(const string& str, float x, float y);
  virtual float getLeading() const;
  virtual float getAscent() const;
  virtual float getDescent() const;
  virtual float charWidth(int ch) const;
  virtual float stringWidth(const string& str);
  virtual Box getStringBounds(const string& str);
};

/**
 * Implementation of Glut based bitmap fonts.
 */
class FontGlutBitmap : public FontGlutStroke
{
protected:
  float ascent;
  float descent;
public:

  FontGlutBitmap(void * t,
		 float ascent, float descent,
		 const string& name, Style style, float size);

  virtual Format getFormat() const;
  virtual bool isFixedWidth() const;
  virtual void paint(const string& str, float x, float y);
  virtual float getLeading() const;
  virtual float getAscent() const;
  virtual float getDescent() const;
  virtual float charWidth(int ch) const;
  virtual float stringWidth(const string& str);
  virtual Box getStringBounds(const string& str);
};

/**
 * Creator or Glut based fonts.
 */
class FontGlutCreator : public Font::Creator {
public:
  FontGlutCreator() {}
  Font * create(const string& name, Font::Style style, float size);
};

extern void installFontGlut();



} // namespace infovis

#endif // INFOVIS_DRAWING_FONTGLUT_HPP
