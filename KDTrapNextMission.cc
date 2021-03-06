/******************************************************************************
 *  KDTrapNextMission.cc
 *
 *  Copyright (C) 2013 Kevin Daughtridge <kevin@kdau.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************/

#include "KDTrapNextMission.hh"

KDTrapNextMission::KDTrapNextMission (const String& _name, const Object& _host)
	: TrapTrigger (_name, _host),
	  THIEF_PARAMETER (next_mission_on, 0),
	  THIEF_PARAMETER (next_mission_off, 0)
{}

Message::Result
KDTrapNextMission::on_trap (bool on, Message&)
{
	int next_mission = on ? next_mission_on : next_mission_off;
	if (next_mission < 1) return Message::HALT;

#ifdef IS_THIEF2
	log (Log::NORMAL, "Setting next mission to %||.", next_mission);
	Mission::set_next (next_mission);
	return Message::HALT;
#else // !IS_THIEF2
	log (Log::ERROR, "This script is not available for this game.");
	return Message::ERROR;
#endif // IS_THIEF2
}

