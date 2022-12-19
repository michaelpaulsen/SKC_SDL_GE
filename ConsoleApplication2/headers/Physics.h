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
				if (force.m_x) {
					position.m_x += force.m_x;
					if (force.m_x > drag.m_x) {
						force.m_x -= drag.m_x;
					}else if (force.m_x < -drag.m_x) {
						force.m_x += drag.m_x;
					}
					else {
						force.m_x = 0; 
					}
				}	
				//maybe imlement this as a function to dry the code? 
				if (force.m_y) {
					position.m_y += force.m_y;
					if (force.m_y > drag.m_y) {
						force.m_y -= drag.m_y;
					}else if (force.m_y < -drag.m_y) {
						force.m_y += drag.m_y;
					}
					else {
						force.m_y = 0; 
					}
				}
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
			void CaculateAndAddSpringForce(Vector::Vec2d actingObjectPos, Vector::Vec2d idleObjectPos,Vector::Vec2d& actingForce, double springValue) {
				auto displacement = actingObjectPos - idleObjectPos; 
				auto force = displacement * -springValue; 
				AddForce(actingForce, force);
			};
		
		}
	}
}