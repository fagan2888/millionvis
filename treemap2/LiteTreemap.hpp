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
#ifndef TREEMAP2_LITETREEMAP_HPP
#define TREEMAP2_LITETREEMAP_HPP

#include <infovis/drawing/SaveUnder.hpp>
#include <infovis/drawing/lite/LiteGroup.hpp>
#include <infovis/drawing/inter/InteractorEnterLeave.hpp>
#include <infovis/drawing/inter/Interactor3States.hpp>
#include <infovis/drawing/inter/InteractorIdle.hpp>
#include <infovis/drawing/notifiers/BoundedRange.hpp>
#include <infovis/drawing/notifiers/BeginEnd.hpp>
#include <infovis/drawing/notifiers/Change.hpp>
//#include <infovis/tree/property_tree.hpp>

#include <FastDrawer.hpp>
#include <FastPicker.hpp>
#include <LitePath.hpp>
#include <AnimateTree.hpp>

namespace infovis {

class Image;
typedef FastDrawer Drawer;
typedef FastPicker Picker;
class LiteTreemap;
class LabelTreemap;

class LayoutVisu;

class LiteTreemap : public LiteGroup,
		    public BoundedRangeObserver,
		    public BeginEndObserver,
		    public ChangeObserver,
		    public Interactor3States,
		    public InteractorEnterLeave,
		    public InteractorIdle
{
public:
  enum  TexAction {
    no_texture,
    save_texture,
    use_texture
  };
  enum Layout {
    layout_squarified,
    layout_strip,
    layout_slice_and_dice,
    layout_scatter_plot,
    layout_max
  };

  LiteTreemap(const Box& b,
	      SaveUnder& save_under,
	      Drawer& drawer,
	      Font * lab,
	      Tree& t,
	      const string& name_prop,
	      const string& weight_prop,
	      const string& weight2_prop,
	      const string& color_prop,
	      BoundedRangeObservable& param,
	      BoundedRangeObservable& transparency,
	      BoundedRangeObservable& plot_range
	      );
  virtual ~LiteTreemap();

  void disableSaveUnder();
  void enableSaveUnder(bool reuse_cache = false);
  void update_root(node_descriptor n);

  Interactor * interactor(const string& name, int tool_id);
  void doRender(const RenderContext& c);

  // InteractorIdle
  bool doIdle(const Event& ev);
  void doActive(const Event& ev);

  // InteractorEnterLeave
  void doMove(const Event& ev);

  // BoundedRangeObserver
  virtual void valueDragged(BoundedRangeObservable * obs);
  virtual void rangeDragged(BoundedRangeObservable * obs);
  virtual void updateBoundedRange(BoundedRangeObservable * obs);

  // BeginEndObserver
  virtual void begin(BeginEndObservable *);
  virtual void end(BeginEndObservable *);

  // ChangeObserver
  virtual void changed(ChangeObservable * o);

  const Tree& getTree() const { return tree_; }
  void setCurrentRoot(node_descriptor n);
  node_descriptor getCurrentRoot() const { return current_root_; }
  const string& getNameProp() const { return name_prop_; }
  const string& getWeightProp() const { return weight_prop_; }
  const string& getWeight2Prop() const { return weight2_prop_; }
  const string& getColorProp() const { return color_prop_; }
  void setColorProp(const string& prop);
  
  const string& getXAxisProp() const { return x_axis_prop_; }
  void setXAxisProp(const string& prop);
  const string& getYAxisProp() const { return y_axis_prop_; }
  void setYAxisProp(const string& prop);
  void setWeightProp(const string& prop);
  void updateMinMax();

  Drawer& getDrawer() { return drawer_; }

  float getFps() const {return fps_; }
  int getDisplayedItems() const { return displayed_items_; }
  node_descriptor getCurrentPath() const { return current_path_; }
  node_descriptor getMenuPath() const { return menu_.getPath(); }
  const StringColumn& getNames() const;

  void setStrip(bool b = true);
  bool getStrip() const { return orient_.get_strip(); }
  void setLayout(Layout l);
  Layout getLayout() const { return layout_; }

  virtual void beginAnimation(int duration);
  virtual void endAnimation();
  virtual bool isAnimating() const;
  virtual float animationParam(int time = 0);

  virtual void setAnimate(Animate *);
  virtual void computeBoxList(float param, unsigned depth,
			      AnimateTree::BoxList& bl) const;

  unsigned int getTexture() const { return save_under_.get_texture(); }
  Box getTextureSize() const {
    return Box(min(getBounds()),
	       Vector(save_under_.get_tex_width(),
		      save_under_.get_tex_height()));
  }
  void doKeyboard(int key, bool down, int x, int y);
  Vector beginScatterPlot(float max_plot_size);
  void renderScatterPlot(const Vector& one, float max_plot_size, bool);
  void renderFastScatterPlot(const Vector& one, float max_plot_size);
  void endScatterPlot();

  void enableDynamicLabels();
  void disableDynamicLabels(bool inhibit = false);
  //protected:
  struct orient_choser
  {
    orient_choser() : strip(false) { }

    void set_strip(bool s = true) { strip = s; }
    bool get_strip() const { return strip; }
    
    bool operator()(const Box& b,
		    node_descriptor n,
		    unsigned depth) const {
      return (!strip) && width(b) > height(b);
    }
    bool strip;
  };

  TexAction tex_action_;
  SaveUnder save_under_;
  Font * label_font_;
  Tree& tree_;
  std::string name_prop_;
  std::string weight_prop_;
  std::string weight2_prop_;
  std::string color_prop_;
  std::string x_axis_prop_;
  std::string y_axis_prop_;

  const FloatColumn * weight_;
  float weight_min_, weight_max_;
  const FloatColumn * color_;
  float color_min_, color_max_;
  const FloatColumn * x_axis_;
  float x_axis_min_, x_axis_max_;
  const FloatColumn * y_axis_;
  float y_axis_min_, y_axis_max_;

  Drawer& drawer_;
  orient_choser orient_;
  Picker picker_;

  node_descriptor current_root_;
  PathBoxes current_boxes_;
  node_descriptor current_path_;
  Box hilite_box_;
  LitePath menu_;
  LabelTreemap * labels_;
  BoundedRangeObservable& param_;
  BoundedRangeObservable& transparency_;
  BoundedRangeObservable& plot_range_;

  float fps_;
  int displayed_items_;
  Layout layout_;
  LayoutVisu * visu_;
  int animation_start_time_;
  int animation_end_time_;
  int animation_current_time_;
  Animate * animate_;
  Image * overlaps_;
  bool show_overlaps_;
  unsigned int list_;

  bool shift_;
  bool inhibit_dynamic_labels_;
};

} // namespace infovis

#endif // TREEMAP2_LITETREEMAP_HPP
