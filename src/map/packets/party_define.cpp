/*
===========================================================================

  Copyright (c) 2010-2012 Darkstar Dev Teams

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see http://www.gnu.org/licenses/

  This file is part of DarkStar-server source code.

===========================================================================
*/

#include "../../common/socket.h"

#include "party_define.h"

#include "../charentity.h"
#include "../party.h"
#include "../alliance.h"


CPartyDefinePacket::CPartyDefinePacket(CParty* PParty) 
{
	this->type = 0xC8;
	this->size = 0x7C;
	int nextPosition = 1;
	

	//party is an alliance do the double loop
	if (PParty != NULL)
	{
		if (PParty->m_PAlliance!= NULL)
		{
			CAlliance* ourAlliance = PParty->m_PAlliance;

			for (int32 a = 0; a < ourAlliance->partyList.size(); ++a)
			{

						for (int32 i = 0; i < ourAlliance->partyList.at(a)->members.size(); ++i) 
						{
							CBattleEntity* PChar = ourAlliance->partyList.at(a)->members.at(i);

							WBUFL(data,12*nextPosition+(0x08)-4) = PChar->id;
							WBUFW(data,12*nextPosition+(0x0C)-4) = PChar->targid;
							WBUFW(data,12*nextPosition+(0x0E)-4) = PChar->PParty->GetMemberFlags(PChar);
							WBUFB(data,12*nextPosition+(0x10)-4) = PChar->getZone();
							nextPosition++;
						}
				
			}
			return;
		}
	}

	


	//regular party
	if (PParty != NULL)
	{
		DSP_DEBUG_BREAK_IF(PParty->members.size() > 6);

		for (int32 i = 0; i < PParty->members.size(); ++i) 
		{
			CBattleEntity* PChar = PParty->members.at(i);

			WBUFL(data,12*i+(0x08)-4) = PChar->id;
			WBUFW(data,12*i+(0x0C)-4) = PChar->targid;
			WBUFW(data,12*i+(0x0E)-4) = PChar->PParty->GetMemberFlags(PChar);
			WBUFB(data,12*i+(0x10)-4) = PChar->getZone();
		}
	}



}