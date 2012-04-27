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
		static mount& for_path(const std::string& path);
		static const std::vector<mount>& all();

		const std::string& getName() const NOEXCEPT;
		const std::string& getPath() const NOEXCEPT;
		const std::string& getType() const NOEXCEPT;

	private:
		static void load();
		mount(const MNTENT* entity) NOEXCEPT;

		static std::vector<mount> mounts;

		std::string name;
		std::string path;
		std::string type;
	};
}

#endif /* CPPMOUNTS_MOUNT_HPP */

