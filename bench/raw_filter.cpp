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
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <functional>
#include <vector>

static inline bool
in_range(float value, float min, float max)
{
  return value >= min && value < max;
}

static void
do_filter(int n,
	  unsigned long * filter,
	  const char * defined,
	  const float * value,
	  int col,
	  float min_value, float max_value)
{
  std::cout << "Starting filtering\n";
  clock_t time = clock();
  unsigned filtered = 0;

  unsigned long mask = 1 << col; // assume we are filtering on this column

  for (int i = 0; i < n; i++) {
    if (! defined[i] 
	|| ! in_range(value[i], min_value, max_value)
	)
      filter[i] |= mask;
    else {
      filter[i] &= ~mask;
      filtered++;
    }
  }
  time = clock() - time;
  std::cout << "Filtered " << filtered << " out of " << n << std::endl;
  std::cout << "Time to filter: "
	    << time / float(CLOCKS_PER_SEC) << "s for "
	    << n << " items = "
	    << n * float(CLOCKS_PER_SEC) / time << "items/s\n";
}

struct indirect_sort : public std::binary_function<int,int,bool>
{
  const float * values;

  indirect_sort(const float * v) : values(v) { }
  bool operator()(int a, int b) const {
    return values[a] < values[b];
  }
};

struct indirect_compare : public std::binary_function<int,float,bool>
{
  const float * values;

  indirect_compare(const float * v) : values(v) { }
  bool operator()(int a, float b) const {
    return values[a] < b;
  }
  bool operator()(float a, int  b) const {
    return a < values[b];
  }
};

static void
create_sorted_table(int n,
		    unsigned long * filter,
		    const char * defined,
		    const float * value,
		    std::vector<int>& sorted,
		    std::vector<int>& invalid)
{
  sorted.reserve(n);
  for (int i = 0; i < n; i++) {
    if (defined[i]) {
      sorted.push_back(i);
    }
    else {
      invalid.push_back(i);
    }
  }
  std::sort(sorted.begin(), sorted.end(), indirect_sort(value));
}

static void
do_filter_sorted(int n,
		 unsigned long * filter,
		 const std::vector<int>& sorted,
		 const std::vector<int>& invalid,
		 const float * value,
		 int col,
		 float min_value, float max_value)
{
  std::cout << "Starting sorted filtering\n";
  clock_t time = clock();
  unsigned filtered = 0;

  unsigned long mask = 1 << col; // assume we are filtering on this column
  unsigned long not_mask = ~mask;

  int lower, upper;

  lower = std::lower_bound(sorted.begin(), sorted.end(),
			   min_value, indirect_compare(value))
    - sorted.begin();
  upper = std::upper_bound(sorted.begin(), sorted.end(),
			   max_value, indirect_compare(value))
    - sorted.begin();
  int i;
  filtered = n - (lower + (sorted.size() - upper) + invalid.size());

  for (i = 0; i < lower; i++) {
    filter[sorted[i]] |= mask;
  }
  for (i = upper; i < sorted.size(); i++) {
    filter[sorted[i]] |= mask;
  }
  for (i = 0; i < invalid.size(); i++) {
    filter[invalid[i]] |= mask;
  }

  for (i = lower; i < upper; i++) {
    filter[sorted[i]] &= not_mask;
  }
  time = clock() - time;
  std::cout << "Filtered " << filtered << " out of " << n << std::endl;
  std::cout << "Time to filter sorted: "
	    << time / float(CLOCKS_PER_SEC) << "s for "
	    << n << " items = "
	    << n * float(CLOCKS_PER_SEC) / time << "items/s\n";
}

static void
do_filter_sorted_raw(int n,
		     unsigned long * filter,
		     const std::vector<int>& sorted,
		     const std::vector<int>& invalid,
		     const float * value,
		     int col,
		     float min_value, float max_value)
{
  std::cout << "Starting sorted filtering raw\n";
  clock_t time = clock();
  unsigned filtered = 0;
  unsigned sorted_size = sorted.size();
  const int * sorted_data = &(*sorted.begin());
  unsigned invalid_size = invalid.size();
  const int * invalid_data = &(*invalid.begin());

  unsigned long mask = 1 << col; // assume we are filtering on this column
  unsigned long not_mask = ~mask;

  int lower, upper;

  lower = std::lower_bound(sorted_data, sorted_data + sorted_size,
			   min_value, indirect_compare(value))
    - sorted_data;
  upper = std::upper_bound(sorted_data, sorted_data + sorted_size,
			   max_value, indirect_compare(value))
    - sorted_data;
  int i;
  filtered = n - (lower + (sorted_size - upper) + invalid_size);

  for (i = 0; i < lower; i++) {
    filter[sorted_data[i]] |= mask;
  }
  for (i = upper; i < sorted_size; i++) {
    filter[sorted_data[i]] |= mask;
  }
  for (i = 0; i < invalid_size; i++) {
    filter[invalid_data[i]] |= mask;
  }

  for (i = lower; i < upper; i++) {
    filter[sorted_data[i]] &= not_mask;
  }
  time = clock() - time;
  std::cout << "Filtered " << filtered << " out of " << n << std::endl;
  std::cout << "Time to filter sorted raw: "
	    << time / float(CLOCKS_PER_SEC) << "s for "
	    << n << " items = "
	    << n * float(CLOCKS_PER_SEC) / time << "items/s\n";
}

int main(int argc, char * argv[])
{
  if (argc == 1) {
    std::cerr << "syntax: " << argv[0] << " <# of values>\n";
    return 1;
  }
  int n = atoi(argv[1]);
  if (n <= 0) {
    std::cerr << "syntax: " << argv[0] << " <positive # of values>\n";
    return 1;
  }

  int i;

  std::cout << "Initializing table with " << n << " random items\n";
  float * value = new float[n];
  for (i = 0; i < n; i++) {
    value[i] = float(rand());
  }

  clock_t time = clock();
  std::cout << "Initializing filter with " << n << " items\n";
  unsigned long * filter = new unsigned long[n];
  char * defined = new char[n];
  
  for (i = 0; i < n; i++) {
    filter[i] = 0;
    defined[i] = (int(value[i]) &  16) ? 0 : 1; // define out randomly 
  }
  std::cout << "Time to initialize: "
	    << (clock() - time) / float(CLOCKS_PER_SEC) << std::endl;

  for (i = 0; i < 10; i++) {
    do_filter(n, filter, defined, value, i, 300, 10000);
  }

  std::vector<int> sorted, invalid;
  std::cout << "Initializing sorted filter with " << n << " items\n";
  time = clock();
  create_sorted_table(n, filter, defined, value, sorted, invalid);
  std::cout << "Time to initialize sorted filter: "
	    << (clock() - time) / float(CLOCKS_PER_SEC) << std::endl;
  
  for (i = 0; i < 10; i++) {
    do_filter_sorted(n, filter, sorted, invalid, value, i, 300, 10000);
  }

  for (i = 0; i < 10; i++) {
    do_filter_sorted_raw(n, filter, sorted, invalid, value, i, 300, 10000);
  }
  
  return 0;
}


