#ifndef CPPMOUNTS_HPP
#define CPPMOUNTS_HPP

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
#include <errno.h>

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

#include <string>
#include <vector>

namespace filesystem
{
	class mount
	{
	public:
		static mount* for_path(const std::string& absolute_path);
		static const std::vector<mount>& all();

		const std::string& getName() const NOEXCEPT;
		const std::string& getPath() const NOEXCEPT;
		const std::string& getType() const NOEXCEPT;

	private:
		static void load();
		static void check_stat_errno();
		mount(const MNTENT* entity);

		static std::vector<mount> mounts;

		std::string name;
		std::string path;
		std::string type;
		dev_t st_dev;
	};
}

#endif /* CPPMOUNTS_HPP */

