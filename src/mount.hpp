#ifndef CPPMOUNTS_MOUNT_HPP
#define CPPMOUNTS_MOUNT_HPP

#include "config.hpp"

#include <string>

class mount
{
public:
	mount(const MNTENT* entity);

	const std::string& getName() const NOEXCEPT;
	const std::string& getPath() const NOEXCEPT;
	const std::string& getType() const NOEXCEPT;
private:
	std::string name;
	std::string path;
	std::string type;
};

#endif /* CPPMOUNTS_MOUNT_HPP */

