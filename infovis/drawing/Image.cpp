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
#include <infovis/drawing/Image.hpp>
#include <infovis/drawing/gl.hpp>
#undef DBG
#ifndef NDEBUG
#include <iostream>
#define DBG {						\
  int err = glGetError();				\
  if (err)						\
    std::cerr << __FILE__ << "(" << __LINE__ << ") : "	\
	      << "gl error: " << gl::glErrorString(err)	\
	      << std::endl;				\
}
#else
#define DBG
#endif

namespace infovis {


Image::Image()
  : width_(0), height_(0),
    format_(gl::pf_rgb), type_(gl::pt_unsigned_byte),
    pixels_(0)
{}
int
Image::size(gl::PixelFormat format, gl::PixelType type)
{
  int sz = 0;
  switch(format) {
  case gl::pf_color_index:
  case gl::pf_stencil_index:
  case gl::pf_depth_component:
  case gl::pf_red:
  case gl::pf_green:
  case gl::pf_blue:
  case gl::pf_alpha:
  case gl::pf_luminance:
    sz = 1;
    break;
  case gl::pf_rgb:
    sz = 3;
    break;
  case gl::pf_rgba:
    sz = 4;
    break;
  case gl::pf_luminance_alpha:
    sz = 2;
    break;
  }
  switch(type) {
  case gl::pt_byte:
  case gl::pt_unsigned_byte:
    break;
  case gl::pt_short:
  case gl::pt_unsigned_short:
  case gl::pt_2_bytes:
    sz *= 2;
    break;
  case gl::pt_int:
  case gl::pt_unsigned_int:
  case gl::pt_float:
  case gl::pt_4_bytes:
    sz *= 4;
    break;
  case gl::pt_3_bytes:
    sz *= 3;
    break;
  case gl::pt_double:
    sz *= 8;
    break;
  }
  return sz;
}

Image::Image(unsigned w, unsigned h, 
	     gl::PixelFormat format,
	     gl::PixelType type)
  : width_(w), height_(h),
    format_(format), type_(type)
{
  pixels_ = new unsigned char[w * h * size(format_, type_)];
}
    

Image::~Image() {
  delete pixels_;
}

int
Image::getWidth() const { return width_; }
int
Image::getHeight() const { return height_; }
gl::PixelFormat
Image::getFormat() const { return format_; }
gl::PixelType
Image::getType() const { return type_; }
void *
Image::getPixels() const { return pixels_; }

void
Image::render(float x, float y)
{
  gl::raster_pos(x, y);
  render();
}
void
Image::render()
{
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  gl::draw_pixels(width_, height_, format_, type_, pixels_);
}

extern void installImagePNG();
Image *
Image::load(const std::string& filename)
{
  static bool inited;
  if (! inited) {
    installImagePNG();
  }
  Image * ret = 0;
  for (Loader * l = Loader::first; l != 0; l = l->next) {
    ret = l->load(filename);
    if (ret != 0)
      break;
  }
  return ret;
}

Image *
Image::read(int x, int y, unsigned w, unsigned h,
	    gl::PixelFormat format,
	    gl::PixelType type)
{
  Image * ret = new Image(w, h, format, type);
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  gl::read_pixels(x, y, w, h, format, type, ret->getPixels());
  DBG;
  return ret;
}

void
Image::read(int x, int y)
{
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  gl::read_pixels(x, y, width_, height_, format_, type_, pixels_);
  DBG;
}

void
Image::read(int x, int y, gl::PixelFormat format)
{
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  gl::read_pixels(x, y, width_, height_, format, type_, pixels_);
  DBG;
}

Image::Loader * Image::Loader::first;

Image::Loader::Loader()
{
  next = first;
  first = this;
}

Image::Loader::~Loader()
{
  if (first == this)
    first = next;
  else {
    for (Loader * l = Loader::first; l != 0; l = l->next) {
      if (l->next == this) {
	l->next = next;
	break;
      }
    }
  }
}

} // namespace infovis
