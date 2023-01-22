#pragma once
#include <functional> 
namespace Skele_lib {
	namespace SKGE {
		namespace Formats {
			struct TileAttr {
				int m_x, m_y, m_action_type;
				TileAttr(int x, int y, int actionType) {
					m_x = x; 
					m_y = y; 
					m_action_type = actionType; 
				}
			};
		}
	}
}