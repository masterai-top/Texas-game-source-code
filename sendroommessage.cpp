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

#include "utils/tarslog.h"
#include "message/sendroommessage.h"

namespace game
{
    namespace message
    {
        int sendRoomMessage(const RoomSo::E_SO_TO_ROOM eMsgType, void *p, GameRoot *root)
        {
            //DLOG_TRACE("sendRoomMessage, eMsgType = " << etos(eMsgType));
            if(root->gs)
            {
            	return root->gs->toRoomData(eMsgType, p);
            }
            else
            {
            	//DLOG_TRACE("sendRoomMessage, root->gs is nullprt.");
            	return 0;
            }
        }
    };
};

