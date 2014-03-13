/*
 * FATFile.h
 *
 * Copyright (C) 2013 IBR, TU Braunschweig
 *
 * Written-by: David Goltzsche <goltzsch@ibr.cs.tu-bs.de>
 *             Johannes Morgenroth <morgenroth@ibr.cs.tu-bs.de>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  Created on: Sep 23, 2013
 *
 *  This class provides the same methods as ibrcommon::File, but for a file
 *  on a FAT image.
 *  A few methods are not implemented, because not needed;
 */

#ifndef FATFILE_H_
#define FATFILE_H_

#include "config.h"

#include <ibrcommon/data/File.h>
#include <list>
#include <dirent.h>

#ifdef HAVE_LIBTFFS
extern "C" //libtffs does not support c++
{
#include <tffs.h>
}
#endif

namespace io
{
	class FATFile : public ibrcommon::File
	{
	public:
		FATFile(const ibrcommon::File &image_file, const std::string &file_path);
		virtual ~FATFile();

		int getFiles(std::list<FATFile> &files);
		int remove(bool recursive);
		FATFile get(std::string filename);
		FATFile getParent();
		bool exists();
		void update();
		size_t size();
		time_t lastaccess();
		time_t lastmodify();
		time_t laststatchange();

		const ibrcommon::File& getImageFile() const;

	private:
		const ibrcommon::File _image_file;

		//handles
		tffs_handle_t _htffs;
		tdir_handle_t _hdir;
		tfile_handle_t _hfile;

		dirent_t _dirent;

		//tffs methods
		int mount_tffs();
		int umount_tffs();
		int opendir_tffs();
		int closedir_tffs();
		int set_dirent_to_current();
	};
}
#endif /* FATFILE_H_ */
