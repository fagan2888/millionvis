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
#include <infovis/drawing/lite/LiteSaveUnder.hpp>
#include <infovis/drawing/gl.hpp>
#include <GL/glut.h>

namespace infovis {

LiteSaveUnder::~LiteSaveUnder()
{
  delete save_under;
  save_under = 0;
}

void
LiteSaveUnder::doRender(const RenderContext& c)
{
  box_min_extent<int> ibounds(getBounds()); // warns but OK
  save(ibounds);
  LiteProxy::render(c);
}

void
LiteSaveUnder::repaint()
{
  if (save_under == 0)
    return;
  box_min_extent<int> ibounds(getBounds()); // warns but OK
  restore();
  if (saved != ibounds) {
    save(ibounds);
  }
  LiteProxy::render(RenderContext());
}

void
LiteSaveUnder::save(const IntBox& b)
{
  saved = b;
  int size = width(saved) * height(saved) * 4;
  if (size > save_under_size) {
    save_under_size = size;
    delete save_under;
    save_under = new unsigned char [save_under_size];
  }
  glReadPixels(xmin(saved), ymin(saved),
	       width(saved), height(saved),
	       GL_RGB, GL_UNSIGNED_BYTE, save_under);
}

void
LiteSaveUnder::restore()
{
  glRasterPos2d(xmin(saved), ymin(saved));
  glDrawPixels(width(saved), height(saved),
	       GL_RGB, GL_UNSIGNED_BYTE, save_under);
}

void
LiteSaveUnder::refresh()
{
  GLint drawBuffer;
  glGetIntegerv(GL_DRAW_BUFFER, &drawBuffer);
  if (drawBuffer == GL_BACK ||
      drawBuffer == GL_BACK_LEFT ||
      drawBuffer == GL_BACK_RIGHT) {
    glDrawBuffer(GL_FRONT);
    glutSetCursor(GLUT_CURSOR_NONE);
    glRasterPos2d(xmin(saved), ymin(saved));
    glCopyPixels(xmin(saved), ymin(saved),
		 width(saved), height(saved),
		 GL_COLOR);
    glDrawBuffer(GL_BACK);
    glutSetCursor(GLUT_CURSOR_INHERIT);
  }
  glFlush();
}
} // namespace infovis
