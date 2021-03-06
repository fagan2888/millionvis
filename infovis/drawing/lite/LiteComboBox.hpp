/* -*- C++ -*-
 *
 * Copyright (C) 2016 Jean-Daniel Fekete
 * 
 * This file is part of MillionVis.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef INFOVIS_DRAWING_LITE_LITECOMBOBOX_HPP
#define INFOVIS_DRAWING_LITE_LITECOMBOBOX_HPP

#include <infovis/drawing/lite/LiteSwitch.hpp>
#include <infovis/drawing/lite/LiteMenu.hpp>

namespace infovis {

/**
 * Combo Box
 */
class LiteComboBox : public LiteSwitch,
		     public Interactor3States,
		     public BoundedRangeObserver
{
public:
  LiteComboBox(LiteMenu * menu, int selected = 0);

  virtual Interactor * interactor(const string& name, int tool_id);
  virtual Lite * clone() const;

  virtual LiteMenu * getMenu() const;
  virtual void setMenu(LiteMenu * menu);
  virtual int getSelectedMenuItem() const;
  virtual void setSelectedMenuItem(int i);

  // Interactor3States
  virtual bool doStart(const Event& ev);
  virtual void doDrag(const Event& ev);
  virtual void doFinish(const Event& ev);

  // BoundedRangeObserver
  virtual void updateBoundedRange(BoundedRangeObservable * obs);
protected:
  LiteMenu * menu_;
  int selected_item_;
};

} // namespace infovis

#endif // INFOVIS_DRAWING_LITE_LITECOMBOBOX_HPP
