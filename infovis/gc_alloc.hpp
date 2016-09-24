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
#ifndef _gc_alloc_hpp
#define _gc_alloc_hpp

#ifndef USE_GC
#include <memory>
/**
 * Base class for garbage collecting.
 */
struct gc {};

/**
 * Base class for garbage collecting and still calling the destructor.
 */
struct gc_cleanup : virtual public gc {};

template <class T, bool Atomic = false>
class gc_alloc : public std::allocator<T>
{
};

enum GCPlacement {UseGC,
#ifndef GC_NAME_CONFLICT
		  GC=UseGC,
#endif
                  NoGC, PointerFreeGC};

typedef void (* GCCleanUpFunc)();

inline void*
operator new(std::size_t size,
	     GCPlacement gcp,
	     GCCleanUpFunc cleanup = 0,
	     void* clientData = 0)
{
  return ::operator new(size);
}

inline void* operator new[](std::size_t size, 
			    GCPlacement gcp,
			    GCCleanUpFunc cleanup = 0,
			    void* clientData = 0)
{
  return ::operator new(size);
}

#else
#include <gc_cpp.h>

struct GC_true_type {};
struct GC_false_type {};

template <class GC_tp>
struct GC_type_traits {
  GC_false_type GC_is_ptr_free;
};

# define GC_DECLARE_PTRFREE(T) \
template<> struct GC_type_traits<T> { GC_true_type GC_is_ptr_free; }

GC_DECLARE_PTRFREE(signed char);
GC_DECLARE_PTRFREE(unsigned char);
GC_DECLARE_PTRFREE(signed short);
GC_DECLARE_PTRFREE(unsigned short);
GC_DECLARE_PTRFREE(signed int);
GC_DECLARE_PTRFREE(unsigned int);
GC_DECLARE_PTRFREE(signed long);
GC_DECLARE_PTRFREE(unsigned long);
GC_DECLARE_PTRFREE(float);
GC_DECLARE_PTRFREE(double);
/* The client may want to add others.	*/

// In the following GC_Tp is GC_true_type iff we are allocating a
// pointerfree object.
template <class GC_Tp>
inline void * GC_selective_alloc(std::size_t n, GC_Tp) {
    return GC_MALLOC(n);
}

template <>
inline void * GC_selective_alloc<GC_true_type>(std::size_t n, GC_true_type) {
    return GC_MALLOC_ATOMIC(n);
}

template <class T, bool Atomic = false>
class gc_alloc {
public:
  typedef std::size_t	size_type;
  typedef ptrdiff_t	difference_type;
  typedef T		value_type;
  typedef T *		pointer;
  typedef const T*	const_pointer;
  typedef T&		reference;
  typedef const T&	const_reference;

  template <class U> struct rebind { typedef gc_alloc<U> other; };
  
  gc_alloc() throw() {}
  gc_alloc(const gc_alloc&) throw() {}
#ifndef _MSC_VER
  template <class U> gc_alloc(const gc_alloc<U>&) throw() {}
#endif
  ~gc_alloc() throw() {}

  pointer address(reference x) const { return &x; }
  const_pointer address(const_reference x) const { return &x; }

  pointer allocate(std::size_type n, const void * = 0) {
    if (n ==0)
      return 0;
#if 1
    GC_type_traits<T> traits;
    return static_cast<T *>
	    (GC_selective_alloc(n * sizeof(T),
			        traits.GC_is_ptr_free));
#else
    return (pointer)operator new ((size_type)(n * sizeof(value_type)));
#endif
  }
  char *_Charalloc(size_type n) {
      return n == 0 ? 0 :
	(char*)GC_MALLOC_ATOMIC (n);
  }
  void deallocate(pointer p, size_type) {
    deallocate(p);
  }
  void deallocate(pointer p) const {
    if (p != 0)
      operator delete (p);
  }
  void deallocate(void * p, size_type) {
    if (p != 0)
      operator delete (p);
  }

  size_type max_size() const throw()
    { return std::size_t(-1) / sizeof(value_type); }

  void construct(pointer p, const T& val) const {
    new (p) T(val);
  }
  void destroy(pointer p) const {
    p->~T();
  }
  template <class U, bool A>
  bool operator==(const gc_alloc<U, A>& ) const { return false; }

  bool operator==(const gc_alloc<T, Atomic>& ) const { return true; }
};

#endif // USE_GC
#endif // _gc_alloc_hpp
