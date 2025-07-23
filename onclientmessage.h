/***************************************************************************************
#  Copyright (c) 2019
#  All rights reserved
#
#  @author  :
#  @name    :
#  @file    :
#  @date    :
#  @describe:分发来自client的透传消息
#***************************************************************************************/

#pragma once

#include<vector>

namespace game
{
    class GameRoot;

    namespace message
    {
        void onClientMessage(long uid, int eMSG, const vector<char> &vecMsgData, GameRoot *root);
    };
};
