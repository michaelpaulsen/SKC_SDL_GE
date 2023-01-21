#pragma once
#include <string>
#include <iomanip>
#include <fstream>

namespace Skele_lib {
	namespace SKGE {
		namespace Utils {
			std::string ReadNBytes(std::fstream& fs, size_t bytes) {
				std::string retval = "";
				for (size_t i = 0; i < bytes; i++) {
					char t = 0;
					if (fs.get(t)) {
						retval += t;
					}
				}
				retval += '\0';
				return retval;
			}
			int readInt(std::fstream& fs) {
				int* buffer = new int;
				fs.read((char*)buffer, sizeof(int));
				int ret = *buffer;
				delete buffer;
				return ret;
			}
		}
	}
}