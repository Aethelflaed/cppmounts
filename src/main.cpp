#include "cppmounts.hpp"
#include <iostream>

int main(int argc, const char** argv)
{
	std::vector<filesystem::mount> mounts = filesystem::mount::all();

	for (size_t i = 0; i < mounts.size(); i++)
	{
		std::cout <<
			mounts[i].getName() << "\t" <<
			mounts[i].getPath() << "\t" <<
			mounts[i].getType() << "\t" <<
			std::endl;
	}
	return 0;
}

