#pragma once
namespace Skele_lib {
	namespace SKGE {
		struct Vec3d {
			union {
				int r, x;
			};
			union {
				int g, y;
			};
			union {
				int b, z;
			};
			Vec3d(int m, int e, int q) {
				x = m; 
				y = e; 
				z = q;
			}
		};
	}
}