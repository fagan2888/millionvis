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
#include <infovis/drawing/Texture.hpp>
#
#include <GL/glu.h>
#include <iostream>

namespace infovis {

  static int next_pow2(int s)
  {
    int p = 0;
    while (s != 0) {
      p++;
      s >>= 1;
    }
    return 1 << p;
  }

  Texture::Texture() { }

  Texture::Texture(unsigned w, unsigned h,
		   gl::PixelFormat format,
		   gl::PixelType type)
    : Image(next_pow2(w), next_pow2(h), format, type)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, format_, 
		 width_, height_, 0, format_, type_, 0);
  }

  Texture::Texture(const Image * img)
    : Image(next_pow2(img->getWidth()),
	    next_pow2(img->getHeight()),
	    img->getFormat(), img->getType())
  {
    unsigned char * out = new unsigned char[width_ * height_ *
					   size(format_, type_)];
    if (gluScaleImage(format_,
		      img->getWidth(), img->getHeight(),
		      type_, img->getPixels(),
		      width_, height_, type_, out) != 0)
      std::cerr << "Error scaling image\n";
    pixels_ = out;
    glTexImage2D(GL_TEXTURE_2D, 0, format_, 
		 width_, height_, 0, format_, type_, pixels_);
  }


} // namespace infovis

