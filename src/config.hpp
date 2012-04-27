#ifndef CPPMOUNTS_CONFIG_HPP
#define CPPMOUNTS_CONFIG_HPP

#ifndef __cplusplus
#error __cplusplus macro is not defined.
#endif

#ifndef NOEXCEPT
#	if __cplusplus > 199711L /* C++11 */
#		define NOEXCEPT noexcept (true)
#	else
#		define NOEXCEPT throw ()
#	endif
#endif /* NOEXCEPT */

extern "C"
{

#include <sys/stat.h>
#ifndef __APPLE__
#	include <sys/types.h>
#	include <unistd.h>
#endif

#ifndef MNTENT
#	ifdef __APPLE__
#		include <sys/param.h>
#		include <sys/ucred.h>
#		include <sys/mount.h>
#		define MNTENT struct statfs
#	else
#		include <cstdio>
#		include <mntent.h>
#		define MNTENT struct mntent
#	endif /* __APPLE__ */
#endif /* MNTENT */

} /* extern "C" */

#endif /* CPPMOUNTS_CONFIG_HPP */

