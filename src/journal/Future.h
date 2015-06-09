// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*-
// vim: ts=8 sw=2 smarttab

#ifndef CEPH_JOURNAL_FUTURE_H
#define CEPH_JOURNAL_FUTURE_H

#include "include/int_types.h"
#include <string>
#include <iosfwd>
#include <boost/intrusive_ptr.hpp>
#include "include/assert.h"

class Context;

namespace journal {

class FutureImpl;

class Future {
public:
  typedef boost::intrusive_ptr<FutureImpl> FutureImplPtr;

  Future(const FutureImplPtr &future_impl) : m_future_impl(future_impl) {}

  void flush(Context *on_safe);
  void wait(Context *on_safe);

  bool is_complete() const;
  int get_return_value() const;

private:
  friend std::ostream& operator<<(std::ostream&, const Future&);

  FutureImplPtr m_future_impl;
};

void intrusive_ptr_add_ref(FutureImpl *p);
void intrusive_ptr_release(FutureImpl *p);

std::ostream &operator<<(std::ostream &os, const Future &future);

} // namespace journal

using journal::intrusive_ptr_add_ref;
using journal::intrusive_ptr_release;
using journal::operator<<;

#endif // CEPH_JOURNAL_FUTURE_H
