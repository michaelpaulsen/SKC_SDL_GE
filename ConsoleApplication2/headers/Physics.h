#pragma once
#include "./Vec2d.h"
namespace Skele_lib {
	namespace SKGE {
		namespace Physics {
			
			void BounceHorizontal(Vector::Vec2d& m_force) {
				m_force.m_x = -m_force.m_x;
			}
			void BounceVirtical(Vector::Vec2d& m_force) {
				m_force.m_y = -m_force.m_y;
			}
			void ApplyForceAndSetPos(Vector::Vec2d& position, Vector::Vec2d& force, Vector::Vec2d drag ) {
				if (force.m_x) { position.m_x += force.m_x; if (force.m_x > 0) { force.m_x -= drag.m_x;} if (force.m_x < 0) { force.m_x += drag.m_x; }}
				if (force.m_y) {position.m_y += force.m_y; if (force.m_y > 0) { force.m_y -= drag.m_y; } if (force.m_y < 0) { force.m_y += drag.m_y; }}
			}
			void AddForce(Vector::Vec2d& m_force, Vector::Vec2d force) {
				m_force += force;
			}
			void SetForce(Vector::Vec2d& m_force, Vector::Vec2d force) {
				m_force = force;
			}
			void SetDragForce(Vector::Vec2d& m_drag, double drag) {
				m_drag = drag;
			};
		}
	}
}