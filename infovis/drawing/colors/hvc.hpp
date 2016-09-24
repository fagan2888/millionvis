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
#ifndef INFOVIS_DRAWING_COLORS_HVC_HPP
#define INFOVIS_DRAWING_COLORS_HVC_HPP

#include <infovis/drawing/color.hpp>
#include <infovis/drawing/colors/uvY.hpp>

namespace infovis {

struct color_space_hvc {
  enum channel_name { hue, value, chroma, last_channel };
};

struct color_hvc : public color_type<float, color_space_hvc>
{
  typedef color_type<float, color_space_hvc> super;

  color_hvc();
  color_hvc(float val) : super(val) {}
  color_hvc(const color_hvc& r) : super(r.begin(), r.end()) { }
  template <class ChannelIt>
  color_hvc(ChannelIt start, ChannelIt end) {
    int chan;
    for (chan = 0; chan < last_channel; chan++) {
      if (start != end)
	channel[chan] = *start++;
    }
    while(chan < last_channel)
      channel[chan++] = T(0);
  }
  color_hvc(float h, float v, float c) {
    channel[hue] = h;
    channel[value] = v;
    channel[chroma] = c;
  }
  color_hvc(double h, double v, double c) {
    channel[hue] = h;
    channel[value] = v;
    channel[chroma] = c;
  }

  bool is_valid() const;
  bool check_modify();
  bool clip_chroma();
  bool clip_value();
  bool clip_value_chroma();
  float max_chroma();		// given a hue/value
  float max_value();		// given a hue/chroma
  float min_value();		// given a hue/chroma
  float max_value_chroma();	// given a hue
};

void convert(color_uvY& uvY, const color_hvc& hvc);
void convert(color_hvc& hvc, const color_uvY& uvY);
void convert(color_xyz& xyz, const color_hvc& hvc);
void convert(color_hvc& hvc, const color_xyz& xyz);
void convert(color_rgb<float>& rgb, const color_hvc& hvc);
void convert(color_hvc& hvc, const color_rgb<float>& rgb);

} // namespace infovis

#endif // INFOVIS_DRAWING_COLORS_HVC_HPP
