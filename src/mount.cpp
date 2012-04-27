#include "mount.hpp"

mount::mount(const MNTENT* entity)
{
#ifdef __APPLE__
	name = entity->f_mntfromname;
	path = entity->f_mntonname;
	type = entity->f_fstypename;
#else
	name = entity->mnt_fsname;
	path = entity->mnt_dir;
	type = entity->mnt_type;
#endif /* __APPLE__ */
}

const std::string& mount::getName() const NOEXCEPT
{
	return this->name;
}

const std::string& mount::getPath() const NOEXCEPT
{
	return this->path;
}

const std::string& mount::getType() const NOEXCEPT
{
	return this->type;
}

