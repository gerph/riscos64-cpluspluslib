// RISC OS-specific fallback exception runtime for no-exceptions builds.

#include <cstdio>

namespace std {

static constinit std::terminate_handler  __terminate_handler = nullptr;
static constinit std::unexpected_handler __unexpected_handler = nullptr;

unexpected_handler
set_unexpected(unexpected_handler func) noexcept
{
  return __libcpp_atomic_exchange(&__unexpected_handler, func);
}

unexpected_handler
get_unexpected() noexcept
{
  return __libcpp_atomic_load(&__unexpected_handler);
}

_LIBCPP_NORETURN
void unexpected()
{
    (*get_unexpected())();
    terminate();
}

terminate_handler
set_terminate(terminate_handler func) noexcept
{
  return __libcpp_atomic_exchange(&__terminate_handler, func);
}

terminate_handler
get_terminate() noexcept
{
  return __libcpp_atomic_load(&__terminate_handler);
}

_LIBCPP_NORETURN
void
terminate() noexcept
{
#ifndef _LIBCPP_HAS_NO_EXCEPTIONS
    try
    {
#endif
        (*get_terminate())();
        fprintf(stderr, "terminate_handler unexpectedly returned\n");
        ::abort();
#ifndef _LIBCPP_HAS_NO_EXCEPTIONS
    }
    catch (...)
    {
        fprintf(stderr, "terminate_handler unexpectedly threw an exception\n");
        ::abort();
    }
#endif
}

bool uncaught_exception() noexcept { return false; }

int uncaught_exceptions() noexcept
{
  return 0;
}

exception::~exception() noexcept
{
}

const char* exception::what() const noexcept
{
  return "std::exception";
}

bad_exception::~bad_exception() noexcept
{
}

const char* bad_exception::what() const noexcept
{
  return "std::bad_exception";
}

bad_alloc::bad_alloc() noexcept
{
}

bad_alloc::~bad_alloc() noexcept
{
}

const char*
bad_alloc::what() const noexcept
{
    return "std::bad_alloc";
}

bad_array_new_length::bad_array_new_length() noexcept
{
}

bad_array_new_length::~bad_array_new_length() noexcept
{
}

const char*
bad_array_new_length::what() const noexcept
{
    return "bad_array_new_length";
}

bad_cast::bad_cast() noexcept
{
}

bad_typeid::bad_typeid() noexcept
{
}

bad_cast::~bad_cast() noexcept
{
}

const char*
bad_cast::what() const noexcept
{
  return "std::bad_cast";
}

bad_typeid::~bad_typeid() noexcept
{
}

const char*
bad_typeid::what() const noexcept
{
  return "std::bad_typeid";
}

} // namespace std
