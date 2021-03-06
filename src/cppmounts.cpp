#include "cppmounts.hpp"
#include <iostream>
#include <stdexcept>

#define load_mounts if (mounts.empty()) { load(); }

std::vector<cppmounts> cppmounts::mounts;

const cppmounts* cppmounts::for_path(const std::string& absolute_path)
{
	load_mounts;
	dev_t st_dev = 0;
	struct stat file_stat;
	if (stat(absolute_path.c_str(), &file_stat) == 0)
	{
		st_dev = file_stat.st_dev;
	}
	else
	{
		check_stat_errno();
		return 0;
	}
	for (size_t i = 0; i < mounts.size(); i++)
	{
		if (mounts[i].st_dev == st_dev)
		{
			return &mounts[i];
		}
	}
	return 0;
}

const std::vector<cppmounts>& cppmounts::all()
{
	load_mounts;
	return mounts;
}

void cppmounts::load()
{
#ifdef __APPLE__
	MNTENT* entities;
	if (int count = getmntinfo(&entities, MNT_WAIT))
	{
		for (int i = 0; i < count; i++)
		{
			mounts.push_back(cppmounts(&entities[i]));
		}
	}
	else
	{
		switch (errno)
		{
			case ENOMEM:
				throw std::runtime_error("Out of memory");
			case EFAULT:
				throw std::runtime_error("Invalid address");
			case EIO:
				throw std::runtime_error("I/O error");
			default:
				throw std::runtime_error("Unknow error");
		}
	}
#else
	FILE* fh;
	if ((fh = setmntent("/proc/mounts", "r")))
	{
		while (MNTENT* entity = getmntent(fh))
		{
			mounts.push_back(cppmounts(entity));
		}
		endmntent(fh);
	}
	else
	{
		throw std::runtime_error("Unable to open /proc/mounts");
	}
#endif /* __APPLE__ */
}

void cppmounts::check_stat_errno()
{
	switch(errno)
	{
		case EACCES:
			throw std::runtime_error("Access to file denied");
		case EFAULT:
			throw std::runtime_error("Invalid address");
		case EIO:
			throw std::runtime_error("I/O error");
		case ELOOP:
			throw std::runtime_error("Too many symlinks");
		case ENAMETOOLONG:
			throw std::invalid_argument("Path too long (or one of its components)");
		case ENOENT:
			throw std::invalid_argument("Path doesn't correspond to any file");
		case ENOTDIR:
			throw std::invalid_argument("A component of the path is not a directory");
		case EOVERFLOW:
			throw std::runtime_error("Buffer size error");
		default:
			throw std::runtime_error("Unknow error");
	}
}

cppmounts::cppmounts(const MNTENT* entity)
	:st_dev(0)
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
			check_stat_errno();
		}
	}
}

const std::string& cppmounts::getName() const NOEXCEPT
{
	return this->name;
}

const std::string& cppmounts::getPath() const NOEXCEPT
{
	return this->path;
}

const std::string& cppmounts::getType() const NOEXCEPT
{
	return this->type;
}

