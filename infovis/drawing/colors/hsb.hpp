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
#ifndef INFOVIS_DRAWING_COLORS_HSB_HPP
#define INFOVIS_DRAWING_COLORS_HSB_HPP

#include <infovis/drawing/color.hpp>

namespace infovis {

struct color_space_hsb {
  enum channel_name { hue, saturation, brighness, last_channel };
  static const char * name() { return "hsb"; }
};

struct color_hsb : public color_type<float, color_space_hsb>
{
  typedef color_type<float, color_space_hsb> super;
  color_hsb() {
    channel[hue] = float(0);
    channel[saturation] = float(0);
    channel[brighness] = float(1);
  }
  color_hsb(float val) : super(val) {}
  color_hsb(const color_hsb& r) {
    for (int chan = 0; chan < last_channel; chan++) {
      channel[chan] = r.channel[chan];
    }
  }
  template <class ChannelIt>
  color_hsb(ChannelIt start, ChannelIt end) {
    int chan;
    for (chan = 0; chan < last_channel; chan++) {
      if (start != end)
	channel[chan] = *start++;
    }
    while(chan < last_channel)
      channel[chan++] = float(0);
  }
  color_hsb(float h, float s, float b) {
    channel[hue] = h;
    channel[saturation] = s;
    channel[brighness] = b;
  }
  color_hsb(double h, double s, double b) {
    detail::round(channel[hue], h * super::one());
    detail::round(channel[saturation], s * super::one());
    detail::round(channel[brighness], b * super::one());
  }
};

void convert(color_rgb<float>& rgb, const color_hsb& c);
void convert(color_hsb& hsb, const color_rgb<float>& c);

} // namespace infovis

#endif // INFOVIS_DRAWING_COLORS_HSB_HPP
