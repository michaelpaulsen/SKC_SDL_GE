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
			void ApplyForce(double& force, double drag) {
				if (force > drag) {
					force -= drag;
				}
				else if (force < -drag) {
					force += drag;
				}
				else {
					force = 0;
				}
			}
			void ApplyForceAndSetPos(Vector::Vec2d& position, Vector::Vec2d& force, Vector::Vec2d drag ) {
				if (force.m_x) {
					position.m_x += force.m_x;
					ApplyForce(force.m_x, drag.m_x);
				}	
				//maybe imlement this as a function to dry the code? 
				if (force.m_y) {
					position.m_y += force.m_y;
					ApplyForce(force.m_y, drag.m_y);
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