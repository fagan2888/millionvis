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
#ifndef TREEMAP2_LITESCATTERPLOT_HPP
#define TREEMAP2_LITESCATTERPLOT_HPP

#include <infovis/drawing/drawing.hpp>
#include <infovis/drawing/SaveUnder.hpp>
#include <infovis/drawing/lite/LiteGroup.hpp>
#include <infovis/drawing/inter/Interactor3States.hpp>
#include <infovis/drawing/notifiers/BoundedRange.hpp>
#include <infovis/drawing/notifiers/BeginEnd.hpp>
#include <infovis/drawing/Animate.hpp>
#include <infovis/tree/property_tree.hpp>

#include <infovis/tree/treemap/drawing/numeric_prop_color_drawer.hpp>
#include <infovis/tree/treemap/drawing/weight_interpolator.hpp>

#include <types.hpp>
#include <FastDrawer.hpp>

namespace infovis {
class Font;

class LiteScatterPlot : public LiteGroup,
			public Interactor3States,
			public BoundedRangeObserver,
			public BeginEndObserver
{
public:
  enum  TexAction {
    no_texture,
    save_texture,
    use_texture
  };

  LiteScatterPlot(const Box& b,
		  SaveUnder& save_under,
		  FastDrawer& drawer,
		  Font * lab,
		  Tree& t,
		  const string& name_prop,
		  const string& x_axis_prop,
		  const string& y_axis_prop,
		  const string& color_prop,
		  const string& size_prop,
		  BoundedRangeObservable& param
		  );
  virtual ~LiteScatterPlot();

  void disableSaveUnder();
  void enableSaveUnder(bool reuse_cache = false);

  Interactor * interactor(const string& name, int tool_id);
  void doRender(const RenderContext& c);
  void doPassiveMotion(int x, int y);
  // Interactor3States
  void doMove(const Point& pos);
  void doStart(const Point& pos);
  void doDrag(const Point& pos);
  void doFinish(const Point& pos);

  // BoundedRangeObserver
  virtual void valueDragged(BoundedRangeObservable * obs);
  virtual void rangeDragged(BoundedRangeObservable * obs);
  virtual void updateBoundedRange(BoundedRangeObservable * obs);

  // BeginEndObserver
  virtual void begin(BeginEndObservable *);
  virtual void end(BeginEndObservable *);

  virtual const string& getNameProp() const { return name_prop_; }
  virtual void setNameProp(const string& name_prop);
  virtual const string& getXAxisProp() const { return x_axis_prop_; }
  virtual void setXAxisProp(const string& x_axis_prop);
  virtual const string& getYaxisProp() const { return y_axis_prop_; }
  virtual void setYAxisProp(const string& y_axis_prop);
  virtual const string& getColorProp() const { return color_prop_; }
  virtual void setColorProp(const string& prop);
  virtual const string& getSizeProp() const { return size_prop_; }
  virtual void setSizeProp(const string& prop);

  float getFps() const {return fps_; }

  virtual void beginAnimation(int duration);
  virtual void endAnimation();
  virtual bool isAnimating() const;
  virtual float animationParam(int time = 0);
  
  virtual void setAnimate(Animate *, bool reversed = true);
  virtual const Animate::BoxList computeBoxList(unsigned depth) const;
protected:
  Box computeBox(int i) const;

  TexAction tex_action_;
  SaveUnder& save_under_;
  FastDrawer& drawer_;
  Font * label_font_;
  Tree& tree_;
  std::string name_prop_;
  std::string x_axis_prop_;
  std::string y_axis_prop_;
  std::string color_prop_;
  std::string size_prop_;

  const Tree::string_prop * name_;
  const Tree::numeric_prop * x_axis_;
  float x_axis_min_, x_axis_max_;
  const Tree::numeric_prop * y_axis_;
  float y_axis_min_, y_axis_max_;
  const Tree::numeric_prop * color_;
  float color_min_, color_max_;
  const Tree::numeric_prop * size_;
  float size_min_, size_max_;

  BoundedRangeObservable& param_;
  float fps_;
  int animation_start_time_;
  int animation_end_time_;
  Animate * animate_;
  bool animate_reversed_;
};

} // namespace infovis

#endif // TREEMAP2_LITESCATTERPLOT_HPP
