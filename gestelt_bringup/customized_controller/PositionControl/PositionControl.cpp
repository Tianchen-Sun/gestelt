/****************************************************************************
 *
 *   Copyright (c) 2018 - 2019 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file PositionControl.cpp
 */

#include "PositionControl.hpp"
#include "ControlMath.hpp"
#include <float.h>
#include <mathlib/mathlib.h>
#include <px4_platform_common/defines.h>
#include <geo/geo.h>

using namespace matrix;

void PositionControl::setVelocityGains(const Vector3f &P, const Vector3f &I, const Vector3f &D)
{
	_gain_vel_p = P;
	_gain_vel_i = I;
	_gain_vel_d = D;
}

void PositionControl::setVelocityLimits(const float vel_horizontal, const float vel_up, const float vel_down)
{
	_lim_vel_horizontal = vel_horizontal;
	_lim_vel_up = vel_up;
	_lim_vel_down = vel_down;
}

void PositionControl::setThrustLimits(const float min, const float max)
{
	// make sure there's always enough thrust vector length to infer the attitude
	_lim_thr_min = math::max(min, 10e-4f);
	_lim_thr_max = max;
}

void PositionControl::setHorizontalThrustMargin(const float margin)
{
	_lim_thr_xy_margin = margin;
}

void PositionControl::updateHoverThrust(const float hover_thrust_new)
{
	// Given that the equation for thrust is T = a_sp * Th / g - Th
	// with a_sp = desired acceleration, Th = hover thrust and g = gravity constant,
	// we want to find the acceleration that needs to be added to the integrator in order obtain
	// the same thrust after replacing the current hover thrust by the new one.
	// T' = T => a_sp' * Th' / g - Th' = a_sp * Th / g - Th
	// so a_sp' = (a_sp - g) * Th / Th' + g
	// we can then add a_sp' - a_sp to the current integrator to absorb the effect of changing Th by Th'
	if (hover_thrust_new > FLT_EPSILON) {
		// _vel_int(2) += (_acc_sp(2) - CONSTANTS_ONE_G) * _hover_thrust / hover_thrust_new + CONSTANTS_ONE_G - _acc_sp(2);

		//_pos_int(2)<0
		_pos_int(2) += (_acc_sp(2) - CONSTANTS_ONE_G) * _hover_thrust / hover_thrust_new + CONSTANTS_ONE_G - _acc_sp(2);

		setHoverThrust(hover_thrust_new);
		// PX4_INFO("new hover thrust: %8.4f", (double)_hover_thrust);
	}
}

void PositionControl::setState(const PositionControlStates &states)
{
	_pos = states.position;
	_vel = states.velocity;
	_yaw = states.yaw;
	_vel_dot = states.acceleration;
}

void PositionControl::setInputSetpoint(const vehicle_local_position_setpoint_s &setpoint)
{
	_pos_sp = Vector3f(setpoint.x, setpoint.y, setpoint.z);
	_vel_sp = Vector3f(setpoint.vx, setpoint.vy, setpoint.vz);
	_acc_sp = Vector3f(setpoint.acceleration);
	_yaw_sp = setpoint.yaw;
	_yawspeed_sp = setpoint.yawspeed;
}

bool PositionControl::update(const float dt)
{
	bool valid = _inputValid();

	if (valid) {
		// _positionControl();
		// _velocityControl(dt);
		_RPTControl(dt);
		_yawspeed_sp = PX4_ISFINITE(_yawspeed_sp) ? _yawspeed_sp : 0.f;
		_yaw_sp = PX4_ISFINITE(_yaw_sp) ? _yaw_sp : _yaw; // TODO: better way to disable yaw control
	}

	// There has to be a valid output accleration and thrust setpoint otherwise something went wrong
	valid = valid && PX4_ISFINITE(_acc_sp(0)) && PX4_ISFINITE(_acc_sp(1)) && PX4_ISFINITE(_acc_sp(2));
	valid = valid && PX4_ISFINITE(_thr_sp(0)) && PX4_ISFINITE(_thr_sp(1)) && PX4_ISFINITE(_thr_sp(2));

	return valid;
}

void PositionControl::_positionControl()
{
	// P-position controller
	Vector3f vel_sp_position = (_pos_sp - _pos).emult(_gain_pos_p);
	PX4_INFO("desired position, %8.4f %8.4f %8.4f", (double)_pos_sp(0), (double)_pos_sp(1), (double)_pos_sp(2));
	PX4_INFO("velocity control, %8.4f %8.4f %8.4f", (double)_vel_sp(0), (double)_vel_sp(1), (double)_vel_sp(2));
	PX4_INFO("POSITION control: POS_error: %8.4f %8.4f %8.4f", (double)vel_sp_position(0), (double)vel_sp_position(1), (double)vel_sp_position(2));

	// Position and feed-forward velocity setpoints or position states being NAN results in them not having an influence
	ControlMath::addIfNotNanVector3f(_vel_sp, vel_sp_position);
	// make sure there are no NAN elements for further reference while constraining
	ControlMath::setZeroIfNanVector3f(vel_sp_position);

	// Constrain horizontal velocity by prioritizing the velocity component along the
	// the desired position setpoint over the feed-forward term.
	_vel_sp.xy() = ControlMath::constrainXY(vel_sp_position.xy(), (_vel_sp - vel_sp_position).xy(), _lim_vel_horizontal);
	// Constrain velocity in z-direction.
	_vel_sp(2) = math::constrain(_vel_sp(2), -_lim_vel_up, _lim_vel_down);
}

void PositionControl::_velocityControl(const float dt)
{
	// PID velocity control
	Vector3f vel_error = _vel_sp - _vel;
	// PX4_INFO("desired velocity, %8.4f %8.4f %8.4f", (double)_vel_sp(0), (double)_vel_sp(1), (double)_vel_sp(2));
	// PX4_INFO("velocity control: vel_error: %8.4f %8.4f %8.4f", (double)vel_error(0), (double)vel_error(1), (double)vel_error(2));
	Vector3f acc_sp_velocity = vel_error.emult(_gain_vel_p) + _vel_int - _vel_dot.emult(_gain_vel_d);

	// No control input from setpoints or corresponding states which are NAN
	ControlMath::addIfNotNanVector3f(_acc_sp, acc_sp_velocity);

	_accelerationControl();

	// Integrator anti-windup in vertical direction
	if ((_thr_sp(2) >= -_lim_thr_min && vel_error(2) >= 0.0f) ||
	    (_thr_sp(2) <= -_lim_thr_max && vel_error(2) <= 0.0f)) {
		vel_error(2) = 0.f;
	}

	// Prioritize vertical control while keeping a horizontal margin
	const Vector2f thrust_sp_xy(_thr_sp);
	const float thrust_sp_xy_norm = thrust_sp_xy.norm();
	const float thrust_max_squared = math::sq(_lim_thr_max);

	// Determine how much vertical thrust is left keeping horizontal margin
	const float allocated_horizontal_thrust = math::min(thrust_sp_xy_norm, _lim_thr_xy_margin);
	const float thrust_z_max_squared = thrust_max_squared - math::sq(allocated_horizontal_thrust);

	// Saturate maximal vertical thrust
	_thr_sp(2) = math::max(_thr_sp(2), -sqrtf(thrust_z_max_squared));

	// Determine how much horizontal thrust is left after prioritizing vertical control
	const float thrust_max_xy_squared = thrust_max_squared - math::sq(_thr_sp(2));
	float thrust_max_xy = 0;

	if (thrust_max_xy_squared > 0) {
		thrust_max_xy = sqrtf(thrust_max_xy_squared);
	}

	// Saturate thrust in horizontal direction
	if (thrust_sp_xy_norm > thrust_max_xy) {
		_thr_sp.xy() = thrust_sp_xy / thrust_sp_xy_norm * thrust_max_xy;
	}

	// Use tracking Anti-Windup for horizontal direction: during saturation, the integrator is used to unsaturate the output
	// see Anti-Reset Windup for PID controllers, L.Rundqwist, 1990
	const Vector2f acc_sp_xy_limited = Vector2f(_thr_sp) * (CONSTANTS_ONE_G / _hover_thrust);
	const float arw_gain = 2.f / _gain_vel_p(0);
	vel_error.xy() = Vector2f(vel_error) - (arw_gain * (Vector2f(_acc_sp) - acc_sp_xy_limited));

	// Make sure integral doesn't get NAN
	ControlMath::setZeroIfNanVector3f(vel_error);
	// Update integral part of velocity control
	_vel_int += vel_error.emult(_gain_vel_i) * dt;

	// limit thrust integral
	_vel_int(2) = math::min(fabsf(_vel_int(2)), CONSTANTS_ONE_G) * sign(_vel_int(2));
}
void PositionControl::_RPTControl(const float dt)
{
	// desired system responds parameters
	// xy outer-loop controller
	float wn_xy = 0.4f; 		// natural frequency
	float sigma_xy = 1.1f * 1.5f ; 	// settling time
	float ki_xy = 0.8f * 1.5f; 	// pole placement
	float eps_xy = 1.0f * 0.4f; 	// damping ratio
	float F_xy[5];

	// xy outer-loop controller
	F_xy[0] = (wn_xy * wn_xy + 2 * sigma_xy * wn_xy * ki_xy) / (eps_xy * eps_xy);
	F_xy[1] = (2 * sigma_xy * wn_xy + ki_xy) / eps_xy;
	F_xy[2] = ki_xy * wn_xy * wn_xy / (eps_xy * eps_xy * eps_xy);
	F_xy[3] = -(wn_xy * wn_xy + 2 * sigma_xy * wn_xy * ki_xy) / (eps_xy * eps_xy);
	F_xy[4] = -(2 * sigma_xy * wn_xy + ki_xy) / eps_xy;

	// F_xy[0]=10.9f;
	// F_xy[1]=6.3f;
	// F_xy[2]=3.0f;
	// F_xy[3]=-10.9f;
	// F_xy[4]=-6.3f;

	// z outer-loop controller
	float wn_z = 0.5f;		// natural frequency
	float sigma_z = 1.1f * 1.5f;	// settling time
	float ki_z = 0.8f * 1.5f;	// pole placement
	float eps_z = 1.0f * 0.3f;	// damping ratio

	float F_z[5];

	// z outer-loop controller
	F_z[0] = (wn_z * wn_z + 2 * sigma_z * wn_z * ki_z) / (eps_z * eps_z);
	F_z[1] = (2 * sigma_z * wn_z + ki_z) / eps_z;
	F_z[2] = ki_z * wn_z * wn_z / (eps_z * eps_z * eps_z);
	F_z[3] = -(wn_z * wn_z + 2 * sigma_z * wn_z * ki_z) / (eps_z * eps_z);
	F_z[4] = -(2 * sigma_z * wn_z + ki_z) / eps_z;
	// F_z[0]=24.78f;
	// F_z[1]=9.5f;
	// F_z[2]=11.11f;
	// F_z[3]=-24.78f;
	// F_z[4]=-9.5f;

	// Constrain velocity in z-direction.
	ControlMath::setZeroIfNanVector3f(_vel_sp);
	ControlMath::setZeroIfNanVector3f(_acc_sp);
	_vel_sp(2) = math::constrain(_vel_sp(2), -_lim_vel_up, _lim_vel_down);

	// xy RPT controller
	// error between desired and actual position
	Vector3f pos_error = _pos_sp - _pos;
	Vector3f vel_error = _vel_sp - _vel;
	ControlMath::setZeroIfNanVector3f(pos_error);
	ControlMath::setZeroIfNanVector3f(vel_error);


	// PX4_INFO("pos_error: %8.4f %8.4f %8.4f", (double)pos_error(0), (double)pos_error(1), (double)pos_error(2));
	// PX4_INFO("vel_error: %8.4f %8.4f %8.4f", (double)vel_error(0), (double)vel_error(1), (double)vel_error(2));
	//p+d
	Vector3f pos_gain = Vector3f(F_xy[0], F_xy[0], F_z[0]);
	Vector3f vel_gain = Vector3f(F_xy[1], F_xy[1], F_z[1]);

	Vector3f u_pos_error = pos_error.emult(pos_gain);
	Vector3f u_vel_error = vel_error.emult(vel_gain);


	//i
	Vector3f inte_pos_gain = Vector3f(F_xy[2], F_xy[2], F_z[2]);
	Vector3f u_pos_int = _pos_int;

	// No control input from setpoints or corresponding states which are NAN
	// desired feed-forward acceleration: _acc_sp
	// PX4_WARN("feedforward acc_sp: %8.4f %8.4f %8.4f", (double)_acc_sp(0), (double)_acc_sp(1), (double)_acc_sp(2));

	ControlMath::addIfNotNanVector3f(_acc_sp, u_pos_error);
	ControlMath::addIfNotNanVector3f(_acc_sp, u_vel_error);
	ControlMath::addIfNotNanVector3f(_acc_sp, u_pos_int);

	// PX4_WARN("output acc_sp: %8.4f %8.4f %8.4f", (double)_acc_sp(0), (double)_acc_sp(1), (double)_acc_sp(2));

	//anti-windup
	_accelerationControl();

	// Integrator anti-windup in vertical direction
	if ((_thr_sp(2) >= -_lim_thr_min && pos_error(2) >= 0.0f) ||
	    (_thr_sp(2) <= -_lim_thr_max && pos_error(2) <= 0.0f)) {
		pos_error(2) = 0.f;
	}

	// Prioritize vertical control while keeping a horizontal margin
	const Vector2f thrust_sp_xy(_thr_sp);
	const float thrust_sp_xy_norm = thrust_sp_xy.norm();
	const float thrust_max_squared = math::sq(_lim_thr_max);

	// Determine how much vertical thrust is left keeping horizontal margin
	const float allocated_horizontal_thrust = math::min(thrust_sp_xy_norm, _lim_thr_xy_margin);
	const float thrust_z_max_squared = thrust_max_squared - math::sq(allocated_horizontal_thrust);

	// Saturate maximal vertical thrust
	_thr_sp(2) = math::max(_thr_sp(2), -sqrtf(thrust_z_max_squared));

	// Determine how much horizontal thrust is left after prioritizing vertical control
	const float thrust_max_xy_squared = thrust_max_squared - math::sq(_thr_sp(2));
	float thrust_max_xy = 0;

	if (thrust_max_xy_squared > 0) {
		thrust_max_xy = sqrtf(thrust_max_xy_squared);
	}

	// Saturate thrust in horizontal direction
	if (thrust_sp_xy_norm > thrust_max_xy) {
		_thr_sp.xy() = thrust_sp_xy / thrust_sp_xy_norm * thrust_max_xy;
	}

	// Use tracking Anti-Windup for horizontal direction: during saturation, the integrator is used to unsaturate the output
	// see Anti-Reset Windup for PID controllers, L.Rundqwist, 1990
	const Vector2f acc_sp_xy_limited = Vector2f(_thr_sp) * (CONSTANTS_ONE_G / _hover_thrust);
	const float arw_gain = 2.f / pos_gain(0);
	pos_error.xy() = Vector2f(pos_error) - (arw_gain * (Vector2f(_acc_sp) - acc_sp_xy_limited));

	// Make sure integral doesn't get NAN
	ControlMath::setZeroIfNanVector3f(pos_error);
	// Update integral part of velocity control
	_pos_int += pos_error.emult(inte_pos_gain) * dt;

	// limit thrust integral
	_pos_int(2) = math::min(fabsf(_pos_int(2)), CONSTANTS_ONE_G) * sign(_pos_int(2));

}
void PositionControl::_accelerationControl()
{
	// Assume standard acceleration due to gravity in vertical direction for attitude generation
	// Vector3f body_z = Vector3f(-_acc_sp(0), -_acc_sp(1), CONSTANTS_ONE_G).normalized();
	Vector3f body_z;
	// PX4_INFO("desired acceleration, %8.4f %8.4f %8.4f", (double)_acc_sp(0), (double)_acc_sp(1), (double)_acc_sp(2));
	if (_acc_sp(2)<CONSTANTS_ONE_G)
	{
		// body z direction is the opposite direction of the desired acceleration
		// but is the same direction of the Gravity since both are in the down frame
		body_z = Vector3f(-_acc_sp(0), -_acc_sp(1), -_acc_sp(2)+CONSTANTS_ONE_G).normalized();
	}
	else if (_acc_sp(2)>=CONSTANTS_ONE_G && _acc_sp(2)<100) //100 is the value for drone does not take off
	{
		body_z = Vector3f(-_acc_sp(0), -_acc_sp(1), -_acc_sp(2)+CONSTANTS_ONE_G).normalized();
		_acc_sp(2) = CONSTANTS_ONE_G;

	}
	else
	{
		body_z = Vector3f(-_acc_sp(0), -_acc_sp(1), CONSTANTS_ONE_G).normalized();
		_acc_sp(2) = CONSTANTS_ONE_G;

	}
	ControlMath::limitTilt(body_z, Vector3f(0, 0, 1), _lim_tilt);
	// Scale thrust assuming hover thrust produces standard gravity
	// float collective_thrust = _acc_sp(2) * (_hover_thrust / CONSTANTS_ONE_G) - _hover_thrust;

	// unlimited the thrust to always produce the standard gravity
	// the thrust magitude is the maginitude of the sum of (the desired acceleration and the standard gravity)
	// the thrust direction is opposite to the sum of (the desired acceleration and the standard gravity)
	float collective_thrust =-(_acc_sp+Vector3f(0, 0, -CONSTANTS_ONE_G)).norm()*( _hover_thrust / CONSTANTS_ONE_G);


	// Project thrust to planned body attitude
	// collective_thrust /= (Vector3f(0, 0, 1).dot(body_z));
	collective_thrust = math::min(collective_thrust, -_lim_thr_min);
	_thr_sp = body_z * collective_thrust;
}

bool PositionControl::_inputValid()
{
	bool valid = true;

	// Every axis x, y, z needs to have some setpoint
	for (int i = 0; i <= 2; i++) {
		valid = valid && (PX4_ISFINITE(_pos_sp(i)) || PX4_ISFINITE(_vel_sp(i)) || PX4_ISFINITE(_acc_sp(i)));
	}

	// x and y input setpoints always have to come in pairs
	valid = valid && (PX4_ISFINITE(_pos_sp(0)) == PX4_ISFINITE(_pos_sp(1)));
	valid = valid && (PX4_ISFINITE(_vel_sp(0)) == PX4_ISFINITE(_vel_sp(1)));
	valid = valid && (PX4_ISFINITE(_acc_sp(0)) == PX4_ISFINITE(_acc_sp(1)));

	// For each controlled state the estimate has to be valid
	for (int i = 0; i <= 2; i++) {
		if (PX4_ISFINITE(_pos_sp(i))) {
			valid = valid && PX4_ISFINITE(_pos(i));
		}

		if (PX4_ISFINITE(_vel_sp(i))) {
			valid = valid && PX4_ISFINITE(_vel(i)) && PX4_ISFINITE(_vel_dot(i));
		}
	}

	return valid;
}

void PositionControl::getLocalPositionSetpoint(vehicle_local_position_setpoint_s &local_position_setpoint) const
{
	local_position_setpoint.x = _pos_sp(0);
	local_position_setpoint.y = _pos_sp(1);
	local_position_setpoint.z = _pos_sp(2);
	local_position_setpoint.yaw = _yaw_sp;
	local_position_setpoint.yawspeed = _yawspeed_sp;
	local_position_setpoint.vx = _vel_sp(0);
	local_position_setpoint.vy = _vel_sp(1);
	local_position_setpoint.vz = _vel_sp(2);
	_acc_sp.copyTo(local_position_setpoint.acceleration);
	_thr_sp.copyTo(local_position_setpoint.thrust);
}

void PositionControl::getAttitudeSetpoint(vehicle_attitude_setpoint_s &attitude_setpoint) const
{
	ControlMath::thrustToAttitude(_thr_sp, _yaw_sp, attitude_setpoint);
	attitude_setpoint.yaw_sp_move_rate = _yawspeed_sp;
}
