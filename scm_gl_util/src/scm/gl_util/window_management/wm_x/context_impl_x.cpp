
#include "context_impl_x.h"

#if SCM_PLATFORM == SCM_PLATFORM_LINUX

#include <exception>
#include <stdexcept>
#include <sstream>
#include <vector>

#include <scm/log.h>
#include <scm/gl_core/constants.h>

#include <scm/gl_util/window_management/display.h>

namespace scm {
namespace gl {
namespace wm {

context::context_impl::context_impl(const surface_ptr&     in_surface,
                                    const attribute_desc&  in_attributes,
                                    const context_ptr&     in_share_ctx)
{
    try {
    }
    catch(...) {
        cleanup();
        throw;
    }
}

context::context_impl::~context_impl()
{
    cleanup();
}
bool
context::context_impl::make_current(const surface_ptr& in_surface, bool current) const
{
    return (false);
}

void
context::context_impl::cleanup()
{
}

} // namespace wm
} // namepspace gl
} // namepspace scm

#endif // SCM_PLATFORM == SCM_PLATFORM_WINDOWS