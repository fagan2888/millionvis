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
#include <infovis/tree/ObservableTree.hpp>

namespace infovis {

ObservableTree::ObservableTree()
{ }

tree::node_descriptor
ObservableTree::add_node(node_descriptor n)
{
  node_descriptor ret = tree::add_node(n);
  notifyBoundedRange();
  return ret;
}

void
ObservableTree::clear()
{
  tree::clear();
  notifyBoundedRange();
}

const BoundedRange *
ObservableTree::getBoundedRange() const 
{
  return this;
}

float 
ObservableTree::min() const
{
  return 0;
}

float 
ObservableTree::max() const
{
  return num_nodes();
}

float 
ObservableTree::value() const
{
  return num_nodes();
}

float 
ObservableTree::range() const
{
  return 0;
}

} // namespace infovis
