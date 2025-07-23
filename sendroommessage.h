/***************************************************************************************
#  Copyright (c) 2019
#  All rights reserved
#
#  @author  :
#  @name    :
#  @file    :
#  @date    :
#  @describe:
#***************************************************************************************/

#pragma once

#include "Comm/ITableGame.h"

#include "gameroot.h"
#include "gameserver.h"

namespace game
{
    namespace message
    {
        int sendRoomMessage(const RoomSo::E_SO_TO_ROOM eMsgType, void *p, GameRoot *root);

        template<class T>
        int sendRoomMessage(const RoomSo::E_SO_TO_ROOM eMsgType, T const &TMsg, GameRoot *root)
        {
            return sendRoomMessage(eMsgType, const_cast<void *>(static_cast<void const *>(&TMsg)), root);
        }
    };
};

