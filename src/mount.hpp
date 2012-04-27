#ifndef CPPMOUNTS_MOUNT_HPP
#define CPPMOUNTS_MOUNT_HPP

#include "config.hpp"

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

#endif /* CPPMOUNTS_MOUNT_HPP */

