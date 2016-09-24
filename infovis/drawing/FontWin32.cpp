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
#include <infovis/drawing/FontWin32.hpp>

#if defined(WIN32) || defined(_WIN32)

#include <windows.h>
#include <GL/gl.h>
#include <wingdi.h>

namespace infovis {

FontWin32::FontWin32(void * h,
		     const string& n, Style s, float sz)
  : Font(n, s, sz),
    hfont(h),
    base(0),
    ascent(0),
    descent(0)
{
  HWND hwnd = GetDesktopWindow();
  HDC hdc = GetDC(hwnd);

  HFONT prevfnt = (HFONT)SelectObject(hdc, h);

  base = glGenLists(256);
  if (wglUseFontBitmaps (hdc, 0, 255, base) == FALSE) {
    throw false;
  }
  TEXTMETRIC tm;
  GetTextMetrics(hdc, &tm);
  ascent = tm.tmAscent;
  descent = tm.tmDescent;
  GetCharWidth32(hdc, 0, 255, widths);
  SelectObject(hdc, prevfnt);
  ReleaseDC(hwnd, hdc);
}

FontWin32::~FontWin32()
{
  if (base != 0)
    glDeleteLists(base, 255);
}

bool
FontWin32::install()
{
  return true;
}

void
FontWin32::finish() {}

Font::Format
FontWin32::getFormat() const
{
  return format_bitmap;
}

bool
FontWin32::isFixedWidth() const
{
  return false;			// +++FIXME
}

void
FontWin32::paint(const string& str, float x, float y)
{
  HWND hwnd = GetDesktopWindow();
  HDC hdc = GetDC(hwnd);

  glListBase(base);
  glRasterPos2f(x, y);
  glCallLists (str.length(), GL_UNSIGNED_BYTE, str.c_str());
  ReleaseDC(hwnd, hdc);
}

float
FontWin32::getLeading() const
{
  return 0;
}

float
FontWin32::getAscent() const
{
  return ascent;
}

float
FontWin32::getDescent() const
{
  return descent;
}

float
FontWin32::charWidth(int ch) const
{
  if (ch < 0 || ch > 255)
    return 0;
  return widths[ch];
}

float
FontWin32::stringWidth(const string& str)
{
  float w = 0;
  for (string::const_iterator i = str.begin();
       i != str.end(); i++) {
    w += charWidth(*i);
  }
  return w;
}

Box
FontWin32::getStringBounds(const string& str)
{
  return Box(0, -descent,
	     stringWidth(str), ascent);
}


Font *
FontWin32Creator::create(const string& name, Font::Style style, float size)
{
  if (name == "default" ||
      name == "SYSTEM_FONT" ||
      name == "system_font" ||
      name == "SYSTEM FONT" ||
      name == "system font") {
    static Font * def;
    if (def == 0)
      def = new FontWin32(GetStockObject(SYSTEM_FONT),
			  name, style, size);
    return def;
  }
  LOGFONT log;

  log.lfHeight	= -int(size);
  log.lfWidth	= 0;
  log.lfEscapement 	= 0 ;
  log.lfOrientation 	= 0 ;
  log.lfWeight 		=
    (style == Font::style_bold ||
     style == Font::style_bold_italic) ? FW_BOLD : FW_NORMAL ;
  log.lfItalic 		=
    (style == Font::style_italic ||
     style == Font::style_bold_italic) ? TRUE : FALSE ;
  log.lfUnderline 	= FALSE ;
  log.lfStrikeOut 	= FALSE ;
  log.lfCharSet		= ANSI_CHARSET ;
  log.lfOutPrecision = OUT_DEFAULT_PRECIS ;
  log.lfClipPrecision= CLIP_DEFAULT_PRECIS ;
  log.lfQuality 		= PROOF_QUALITY ;
  log.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE ;
  strncpy(log.lfFaceName, name.c_str(), 32) ;  
  HFONT fnt = CreateFontIndirect(&log);
  if (fnt == 0)
    return 0;
  FontWin32 * f = 0;
  try {
    f = new FontWin32(fnt, name, style, size);
  }
  catch(...) {}
  return f;
}

FontWin32Creator * font_win32_creator;

void installFontWin32()
{
  font_win32_creator = new FontWin32Creator;
}

} // namespace infovis
#else
namespace infovis {
void installFontWin32()
{
}
} // namespace infovis
#endif // defined(WIN32) || defined(_WIN32)

