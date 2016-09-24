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
#ifndef INFOVIS_DRAWING_SAVEUNDER_HPP
#define INFOVIS_DRAWING_SAVEUNDER_HPP

#include <infovis/alloc.hpp>

namespace infovis {

/**
 * Class for saving the frame buffer in memory of texture memory
 */
class SaveUnder : public gc_cleanup
{
public:
  SaveUnder(bool use_texture = false);
  SaveUnder(unsigned int max_width, unsigned int max_height,
	    bool use_texture = false);
  ~SaveUnder();

  void save(int x, int y, unsigned int width, unsigned int height);
  void restore();
  void restore(int x, int y);
  void resize(unsigned int max_width, unsigned int max_height);

  unsigned int get_texture() const { return use_texture ? data[0] : 0; }
  unsigned int get_tex_width() const { return use_texture ? tile_width : 0; }
  unsigned int get_tex_height() const { return use_texture ? tile_height : 0; }
  // Utility function useful for others
  static unsigned int next_power_of_2(unsigned int n);
protected:
  bool use_texture;
  unsigned int *data;		// pixels or texture objecte
  unsigned int data_size;	// allocated pixels of texture objects
  unsigned int tile_width;
  unsigned int tile_height;
  unsigned int max_width;
  unsigned int max_height;
  int x;
  int y;
  unsigned int width;
  unsigned int height;

  void allocate_ressources();
  void free_ressources();
};

} // namespace infovis

#endif // INFOVIS_DRAWING_SAVEUNDER_HPP
