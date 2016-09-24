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
#ifndef INFOVIS_DRAWING_FONTFT_HPP
#define INFOVIS_DRAWING_FONTFT_HPP

#include <infovis/drawing/Font.hpp>

namespace infovis {

/**
 * Implementation of FreeType based fonts.
 */
class FontFTOutline : public Font
{
protected:
  unsigned int list_base;
  float ascent;
  float descent;
  int widths[256];
  FontFTOutline(const string& name, Style style, float size)
    : Font(name, style, size) { }
public:
  FontFTOutline(void * t,
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
 * Bitmap Font using FreeType
 */
class FontFTBitmap : public FontFTOutline
{
protected:
  unsigned int texture;
  int tex_width, tex_height;
  unsigned int gtexture;
  int gtex_width, gtex_height;
  int char_width, char_height;
  bool is_bitmap;
  struct CharInfo {
    int xmin, xmax, ymin, ymax, advance, xbearing, ybearing;
    unsigned char * pixmap;
  };
  CharInfo info[256];
  void fill_texture(unsigned char * tex,
		    int tex_width, int tex_height,
		    int from_x, int from_y,
		    const CharInfo& info);
  void dilate_and_fill_texture(unsigned char * tex,
			       int tex_width, int tex_height,
			       int from_x, int from_y,
			       const CharInfo& info);
  void create_textures();
public:

  FontFTBitmap(void * t,
	       const string& name, Style style, float size);

  virtual Format getFormat() const;
  virtual void paint(const string& str, float x, float y);
  virtual void paintGrown(const string& str, float x, float y);
};

extern void installFontFT();

/**
 * Creator of FreeType fonts
 */
class FontFTCreator : public Font::Creator {
protected:
  FontFTCreator();
  ~FontFTCreator();
  friend void installFontFT();
public:
  Font * create(const string& name, Font::Style style, float size);
  FontFTOutline * createOutline(const string& name, Font::Style style);
  FontFTBitmap * createBitmap(const string& name, Font::Style style, float size);
};


} // namespace infovis

#endif // INFOVIS_DRAWING_FONTFT_HPP
