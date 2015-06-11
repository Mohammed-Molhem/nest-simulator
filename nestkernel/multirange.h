/*
 *  multirange.h
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MULTIRANGE_H
#define MULTIRANGE_H

#include <vector>
#include <utility>
#include "nest.h"

namespace nest
{

/**
 * Class for sequences of ranges acting like a compressed vector.
 */
class Multirange
{
public:
  typedef std::pair< index, index > Range;
  typedef std::vector< Range > RangeVector;

  class iterator
  {
  public:
    iterator( RangeVector::const_iterator iter, index n );
    index operator*() const;
    bool operator!=( const iterator& other ) const;
    iterator& operator++();
    iterator operator++( int );

  private:
    RangeVector::const_iterator pair_iter_;
    index n_;
  };

  Multirange();
  void push_back( index x );
  void clear();
  index operator[]( index n ) const;
  index size() const;
  bool empty() const;
  iterator begin() const;
  iterator end() const;
  bool contains( index x ) const;

private:
  RangeVector ranges_;
  index size_;
};

inline Multirange::Multirange()
  : ranges_()
  , size_( 0 )
{
}

inline void
Multirange::push_back( index x )
{
  if ( ( not ranges_.empty() ) && ( ranges_.back().second + 1 == x ) )
  {
    ++ranges_.back().second;
  }
  else
  {
    ranges_.push_back( Range( x, x ) );
  }
  ++size_;
}

inline void
Multirange::clear()
{
  ranges_.clear();
  size_ = 0;
}

inline index
Multirange::size() const
{
  return size_;
}

inline bool
Multirange::empty() const
{
  return size_ == 0;
}

inline Multirange::iterator::iterator( RangeVector::const_iterator iter, index n )
  : pair_iter_( iter )
  , n_( n )
{
}

inline bool Multirange::iterator::operator!=( const iterator& other ) const
{
  return ( other.pair_iter_ != pair_iter_ ) || ( other.n_ != n_ );
}

inline index Multirange::iterator::operator*() const
{
  return pair_iter_->first + n_;
}

inline Multirange::iterator& Multirange::iterator::operator++()
{
  ++n_;
  if ( n_ > pair_iter_->second - pair_iter_->first )
  {
    ++pair_iter_;
    n_ = 0;
  }
  return *this;
}

inline Multirange::iterator Multirange::iterator::operator++( int )
{
  iterator tmp = *this;
  ++( *this );
  return tmp;
}

inline Multirange::iterator
Multirange::begin() const
{
  return Multirange::iterator( ranges_.begin(), 0 );
}

inline Multirange::iterator
Multirange::end() const
{
  return Multirange::iterator( ranges_.end(), 0 );
}

inline bool
Multirange::contains( index x ) const
{
  for ( RangeVector::const_iterator it = ranges_.begin(); it != ranges_.end(); ++it )
  {
    if ( ( x >= it->first ) && ( x <= it->second ) )
    {
      return true;
    }
  }
  return *this;
}

inline Multirange::iterator Multirange::iterator::operator++( int )
{
  iterator tmp = *this;
  ++( *this );
  return tmp;
}

inline Multirange::iterator
Multirange::begin() const
{
  return Multirange::iterator( ranges_.begin(), 0 );
}

inline Multirange::iterator
Multirange::end() const
{
  return Multirange::iterator( ranges_.end(), 0 );
}

  return false;
}

} // namespace

#endif
