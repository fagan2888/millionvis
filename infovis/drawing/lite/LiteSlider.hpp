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
#ifndef INFOVIS_DRAWING_LITE_SLIDER_HPP
#define INFOVIS_DRAWING_LITE_SLIDER_HPP

#include <infovis/drawing/direction.hpp>
#include <infovis/drawing/lite/LiteGroup.hpp>
#include <infovis/drawing/lite/Border.hpp>
#include <infovis/drawing/notifiers/BeginEnd.hpp>
#include <infovis/drawing/notifiers/BoundedRange.hpp>

namespace infovis {

class Font;

/**
 * Slider component
 */
class LiteSlider : public LiteGroup,
		   public BoundedRangeObserver,
		   public DefaultBeginEndObservable
{
public:
  enum Zone {
    zone_none = -1,
    zone_min,
    zone_thumb,
    zone_max,
    zone_last
  };
  /**
   * Class for specifying a format value for values
   */
  class LabelFormater {
  public:
    virtual ~LabelFormater();

    virtual string formatLabel(float value) = 0;
  };
  LiteSlider(BoundedRangeObservable * observable,
	     const Box& bounds,
	     direction dir = left_to_right,
	     const Color& fg = color_black,
	     const Color& bg = color_white,
	     Font * font = 0
	     );
  LiteSlider(const Box& bounds,
	     direction dir = left_to_right,
	     const Color& fg = color_black,
	     const Color& bg = color_white,
	     Font * font = 0
	     );


  virtual void render(const RenderContext&);
  virtual void doRender(const RenderContext& rc);
  virtual Lite * clone() const;

  virtual void positionParts();
  virtual void positionMin(const Box&);
  virtual void positionThumb(const Box&);
  virtual void positionMax(const Box&);

  virtual BoundedRangeObservable* getObservable() const;
  virtual void setObservable(BoundedRangeObservable* v);
  
  virtual direction getDirection() const;
  virtual void setDirection(direction v);

  virtual const Color& getForegroundColor() const;
  virtual void setForegroundColor(const Color& color);

  virtual const Color& getBackgroundColor() const;
  virtual void setBackgroundColor(const Color& color);

  virtual Font * getFont() const;
  virtual void setFont(Font * font);

  virtual float getMinSize() const;
  virtual void setMinSize(float v);
  
  virtual float getThumbSize() const;
  virtual void setThumbSize(float v);

  virtual float getMaxSize() const;
  virtual void setMaxSize(float v);
  
  virtual void computeZones(float length, float zones[zone_last]) const;
  virtual Zone getZone(const Point& pos) const;
  virtual float getValue(const Point& pos, Zone z = zone_thumb) const;


  virtual void renderBackground(const Box& b);
#if 0
  virtual void renderMin(const Box& b);
  virtual void renderThumb(const Box& b);
  virtual void renderMax(const Box& b);
#endif
  virtual void renderOverlay(const Box& b);

  virtual void valueDragged(BoundedRangeObservable * obs);
  virtual void rangeDragged(BoundedRangeObservable * obs);
  virtual void updateBoundedRange(BoundedRangeObservable * obs);

  virtual string minLabel();
  virtual string maxLabel();

  virtual string formatLabel(float value);

  virtual void setLabelFormater(LabelFormater * f);
  virtual LabelFormater * getLabelFormater() const;
protected:
  BoundedRangeObservable * observable_;
  direction direction_;
  Color foreground_color_;
  Color background_color_;
  Font * font_;
  float thumb_size_;
  float saved_;
  LabelFormater * formater_;
};


} // namespace infovis

#endif // INFOVIS_DRAWING_LITE_SLIDER_HPP
