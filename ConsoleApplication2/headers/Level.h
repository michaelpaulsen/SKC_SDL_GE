#pragma once
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Vec2d.h"
#include "Defines.h"
#include "ReadFromFile.h"
#include "TileAttr.h"
namespace Skele_lib {
	namespace SKGE {
		namespace Formats {
			static constexpr int SIZEOFMAGICNUMBER = 3; 
			class Level {
				static const int currentV = 1;
				std::string magicNumbers; 
				int version; 
				Vector::Vec2i levelSize;
				std::vector<std::vector<int>> tileIds;
				std::vector<TileAttr> atrTable; 
			public:
				explicit Level(std::string path) {
					std::fstream file(path, std::ios::in | std::ios::binary);
					if (file.fail()) {
						char buffer[1000] = { 0 };
						strerror_s(buffer, errno);
						cerrf("Error: {}\n{}", buffer, path);
						exit(-errno);
					}
					magicNumbers = Utils::ReadNBytes(file, SIZEOFMAGICNUMBER);
					if (strcmp(magicNumbers.c_str(), "LVL") != 0) {
						cerrf("error creating level not a valid file");
						cerrf("\nmagic numbers were {} (expected LVL)", magicNumbers);
						exit(69);
					}
					version = Utils::readInt(file);
					levelSize.m_x = Utils::readInt(file);
					levelSize.m_y = Utils::readInt(file);
					for (size_t y = 0; y < levelSize.m_y; y++) {
						std::vector<int> row; 
						for (size_t x = 0; x < levelSize.m_x; x++) {
							row.push_back(Utils::readInt(file));
						}
						tileIds.push_back(row);
					}
					
				}
				void                   Set(int x, int y, int val) {
					tileIds[y][x] = val;
				}
				const Vector::Vec2i    GetSize() const{
					return levelSize;
				}
				const std::vector<int> At(size_t y) const{
					return tileIds[y]; 
				}
				const int              At(size_t x, size_t y) const {
					return tileIds[y][x]; 
				}
				const std::vector<int>& operator[](size_t y) const {
					return tileIds[y]; 
				}
			};
		}
	}
}