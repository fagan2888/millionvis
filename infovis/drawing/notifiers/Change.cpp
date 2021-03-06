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
#include <infovis/drawing/notifiers/Change.hpp>
#include <algorithm>

namespace infovis {

ChangeObserver::~ChangeObserver()
{ }

void
ChangeObserver::changed(ChangeObservable *)
{ }

ChangeObservable::~ChangeObservable()
{ }

void
DefaultChangeObservable::addChangeObserver(ChangeObserver * obs)
{
  push_back(obs);
}

void
DefaultChangeObservable::removeChangeObserver(ChangeObserver * obs)
{
  iterator i = std::find(begin(), end(), obs);
  if (i != end())
    erase(i);
}

void
DefaultChangeObservable::notifyChanged()
{
  for (const_iterator i = begin(); i != end(); i++) {
    (*i)->changed(this);
  }
}

} // namespace infovis
