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

namespace game
{
    class GameRoot;

    namespace message
    {
        long onRoomMessage(const RoomSo::E_ROOM_TO_SO eMsgType, void const *p, GameRoot *root);
    };
};

