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
#ifndef INFOVIS_DRAWING_IMAGE_HPP
#define INFOVIS_DRAWING_IMAGE_HPP

#include <infovis/drawing/drawing.hpp>
#include <infovis/drawing/gl.hpp>
#include <string>

namespace infovis {

/**
 * Loading and saving of images to and from OpenGL.
 */
class Image : public gc_cleanup
{
public:
  Image();
  Image(unsigned w, unsigned h, 
	gl::PixelFormat format = gl::pf_rgb,
	gl::PixelType type = gl::pt_unsigned_byte);
  virtual ~Image();
  virtual int getWidth() const;
  virtual int getHeight() const;
  virtual gl::PixelFormat getFormat() const;
  virtual gl::PixelType getType() const;
    
  virtual void * getPixels() const;
  virtual void render(float x, float y);
  virtual void render();
  virtual void read(int x, int y);
  virtual void read(int x, int y, gl::PixelFormat format);

  static Image * load(const std::string& filename);
  static Image * read(int x, int y, unsigned w, unsigned h,
		      gl::PixelFormat format = gl::pf_rgb,
		      gl::PixelType type = gl::pt_unsigned_byte);
  static int size(gl::PixelFormat format, gl::PixelType type);
protected:
  unsigned width_, height_;
  gl::PixelFormat format_;
  gl::PixelType type_;
  unsigned char * pixels_;
    
public:
  /**
   * Loader class for images
   */
  class Loader {
  protected:
    static Loader * first;
    Loader * next;

    Loader();
    virtual ~Loader();
    friend class Image;
  public:
    virtual Image * load(const std::string& name) = 0;
  };

};

} // namespace infovis

#endif // INFOVIS_DRAWING_IMAGE_HPP
