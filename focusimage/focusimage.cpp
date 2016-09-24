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
#include <infovis/drawing/Image.hpp>
#include <infovis/drawing/gl_support.hpp>
#include <infovis/drawing/inter/Interactor3States.hpp>
#include <infovis/drawing/inter/KeyCodes.hpp>
#include <infovis/drawing/inter/KeyboardHandler.hpp>
#include <infovis/drawing/inter/MouseHandler.hpp>
#include <infovis/drawing/inter/MouseCodes.hpp>
#include <infovis/drawing/lite/LiteWindow.hpp>

#include <cstdlib>
#include <iostream>

using namespace infovis;

#undef DBG
#ifndef NDEBUG
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

class FocusImageWindow : public LiteWindow,
	 		 public Interactor3States,
	 		 public MouseHandler,
			 public KeyboardHandler
{
  Image * img_;

public:
  FocusImageWindow(const string& name,
		   const Box& b)
    : LiteWindow(name, b, cap_double | cap_rgb)
  {
    img_ = Image::load(name);
    if (img_ == 0) {
      std::cerr << "Cannot load file " << name << std::endl;
      exit(1);
    }
    
  }

  virtual void doRender(const RenderContext&);

  void doKeyboard(int key, bool down, int x, int y) {
    static bool is_saving = false;

    switch(key) {
    case 27:			// escape
      exit(0);
    }
  }

  virtual void doMouse(int button, bool down, int x, int y) {
  }

 
};

void
FocusImageWindow::doRender(const RenderContext& ctx)
{
}

int main(int argc, char * argv[])
{
  LiteWindow::init(argc, argv);
  const char * toload = 0;
  bool fullscreen = true;
  int width = 720, height = 480;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      switch(argv[i][1]) {
      case 'f':
	fullscreen = ! fullscreen;
	break;
      case 'w':
	i++;
	if (i < argc) {
	  width = atoi(argv[i]);
	}
	break;
      case 'h':
	i++;
	if (i < argc) {
	  height = atoi(argv[i]);
	}
	break;
      default:
	std::cerr << "syntax: " << argv[0]
		  << "[-f] [-w <width>] [-h height] imagefile\n";
	exit(1);
      }
    }
    else {
      toload = argv[i];
    }
  }

  if (toload == 0) {
    std::cerr << "syntax: " << argv[0]
	      << "[-f] [-w <width>] [-h height] imagefile\n";
    exit(1);
  }

  FocusImageWindow win(toload, Box(0, 0, width, height));

  if (fullscreen)
    win.setFullscreen();
  try {
    win.run();
  }
  catch(...) {
    return 1;
  }
  return 0;
}  
