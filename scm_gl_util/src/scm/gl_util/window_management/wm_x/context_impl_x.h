
#ifndef SCM_GL_UTIL_WM_WIN32_CONTEXT_IMPL_X_H_INCLUDED
#define SCM_GL_UTIL_WM_WIN32_CONTEXT_IMPL_X_H_INCLUDED

#include <scm/core/platform/platform.h>

#if SCM_PLATFORM == SCM_PLATFORM_LINUX

#include <scm/core/platform/windows.h>

#include <scm/core/pointer_types.h>

#include <scm/gl_util/window_management/context.h>

namespace scm {
namespace gl {
namespace wm {

struct context::context_impl
{
    context_impl(const surface_ptr&     in_surface,
                 const attribute_desc&  in_attributes,
                 const context_ptr&     in_share_ctx);
    virtual ~context_impl();

    bool                    make_current(const surface_ptr& in_surface, bool current) const;
    void                    cleanup();

}; // class context_impl

} // namespace wm
} // namepspace gl
} // namepspace scm

#endif // SCM_PLATFORM == SCM_PLATFORM_WINDOWS
#endif // SCM_GL_UTIL_WM_WIN32_CONTEXT_IMPL_X_H_INCLUDED