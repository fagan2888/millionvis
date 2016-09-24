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
#ifndef INFOVIS_DRAWING_COLORS_UVY_HPP
#define INFOVIS_DRAWING_COLORS_UVY_HPP

#include <infovis/drawing/color.hpp>
#include <infovis/drawing/colors/xyz.hpp>

namespace infovis {

struct color_space_uvY {
  enum channel_name { u_prime, v_prime, Y, last_channel };
};

struct color_uvY : public color_type<float, color_space_uvY>
{
  typedef color_type<float, color_space_uvY> super;

  color_uvY();
  color_uvY(float val) : super(val) {}
  color_uvY(const color_uvY& r) {
    for (int chan = 0; chan < last_channel; chan++) {
      channel[chan] = r.channel[chan];
    }
  }
  template <class ChannelIt>
  color_uvY(ChannelIt start, ChannelIt end) {
    int chan;
    for (chan = 0; chan < last_channel; chan++) {
      if (start != end)
	channel[chan] = *start++;
    }
    while(chan < last_channel)
      channel[chan++] = float(0);
  }
  color_uvY(const float& u, const float& v, const float& y) {
    channel[u_prime] = u;
    channel[v_prime] = v;
    channel[Y] = y;
  }
  color_uvY(double u, double v, double y) {
    detail::round(channel[u_prime], u * super::one());
    detail::round(channel[v_prime], v * super::one());
    detail::round(channel[Y], y * super::one());
  }
};

void convert(color_xyz& xyz, const color_uvY& uvY);
void convert(color_uvY& uvY, const color_xyz& xyz);

} // namespace infovis

#endif // INFOVIS_DRAWING_COLORS_UVY_HPP
