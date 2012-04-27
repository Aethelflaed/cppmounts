#include "mount.hpp"
#include <iostream>

#define load_mounts if (mounts.empty()) { load(); }

std::vector<filesystem::mount> filesystem::mount::mounts;

filesystem::mount& filesystem::mount::for_path(const std::string& path)
{
	load_mounts;
	return mounts[0];
}

const std::vector<filesystem::mount>& filesystem::mount::all()
{
	load_mounts;
	return mounts;
}

void filesystem::mount::load()
{
#ifdef __APPLE__
	MNTENT* entities;
	if (int count = getmntinfo(&entities, MNT_WAIT))
	{
		for (int i = 0; i < count; i++)
		{
			mounts.push_back(filesystem::mount(&entities[i]));
		}
	}
	else
	{
		//TODO
	}
#else
	FILE* fh;
	if (fh = setmntent("/proc/mounts", "r"))
	{
		while (MNTENT* entity = getmntent(fh))
		{
			mounts.push_back(filesystem::mount(entity));
		}
		endmntent(fh);
	}
	else
	{
		//TODO
	}
#endif /* __APPLE__ */
}

filesystem::mount::mount(const MNTENT* entity) NOEXCEPT
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

	if (path.empty() == false)
	{
		struct stat file_stat;
		if (stat(path.c_str(), &file_stat) == 0)
		{
			st_dev = file_stat.st_dev;
		}
		else
		{
			//TODO
		}
	}
}

const std::string& filesystem::mount::getName() const NOEXCEPT
{
	return this->name;
}

const std::string& filesystem::mount::getPath() const NOEXCEPT
{
	return this->path;
}

const std::string& filesystem::mount::getType() const NOEXCEPT
{
	return this->type;
}

