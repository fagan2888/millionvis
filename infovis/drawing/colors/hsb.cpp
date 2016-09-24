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
#include <infovis/drawing/colors/hsb.hpp>

namespace infovis {

void convert(color_rgb<float>& rgb, const color_hsb& c)
{
  typedef color_hsb Color;
  double r = 0;
  double g = 0;
  double b = 0;
  double hue = double(c[Color::hue]);
  double saturation =double(c[Color::saturation]);
  double brightness = double(c[Color::brighness]);
  if (saturation == 0.0) {
    r = g = b = brightness;
  }
  else {
    double h = (hue - floor(hue)) * 6.0;
    double f = h - floor(h);
    double p = brightness * (1.0 - saturation);
    double q = brightness * (1.0 - saturation * f);
    double t = brightness * (1.0 - (saturation * (1.0 - f)));
    switch (int(h)) {
    case 0:
      r = brightness;
      g = t;
      b = p;
      break;
    case 1:
      r = q;
      g = brightness;
      b = p;
      break;
    case 2:
      r = p;
      g = brightness;
      b = t;
      break;
    case 3:
      r = p;
      g = q;
      b = brightness;
      break;
    case 4:
      r = t;
      g = p;
      b = brightness;
      break;
    case 5:
      r = brightness;
      g = p;
      b = q;
      break;
    }
  }
  rgb = color_rgb<float>(r, g, b);
}

void convert(color_hsb& hsb, const color_rgb<float>& c)
{
  typedef color_rgb<float> Color;
  double hue, saturation, brightness;
  double r = double(c[Color::red]) / Color::one();
  double g = double(c[Color::green]) / Color::one();
  double b = double(c[Color::blue]) / Color::one();
  double cmax = (r > g) ? r : g;
  if (b > cmax) cmax = b;
  double cmin = (r < g) ? r : g;
  if (b < cmin) cmin = b;
  brightness = cmax;
  if (cmax != 0)
    saturation = (cmax - cmin) / cmax;
  else
    saturation = 0;
  if (saturation == 0)
    hue = 0;
  else {
    double redc = (cmax - r) / (cmax - cmin);
    double greenc = (cmax - g) / (cmax - cmin);
    double bluec = (cmax - b) / (cmax - cmin);
    if (r == cmax)
      hue = bluec - greenc;
    else if (g == cmax)
      hue = 2.0 + redc - bluec;
    else
      hue = 4.0 + greenc - redc;
    hue = hue / 6.0;
    if (hue < 0)
      hue = hue + 1.0;
  }
  hsb = color_hsb(hue, saturation, brightness);
}

} // namespace infovis
