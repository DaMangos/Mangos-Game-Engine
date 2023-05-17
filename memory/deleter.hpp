#pragma once

namespace handles
{
template <class deleting_type>
class deleter final
{
  public:
    typedef deleting_type value_type;

    deleter() = delete;
};
}