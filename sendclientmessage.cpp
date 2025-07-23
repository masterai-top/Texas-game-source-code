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
#include "message/sendclientmessage.h"

namespace game
{
    namespace message
    {
        int sendClientMessage(const long &pid, int eMSG, const std::vector<char> &vecData, GameRoot *root)
        {
            //// DLOG_TRACE("sendClientMessage, pid = " << pid << ", eMSG: " << eMSG << ", vecData size: " << vecData.size());
            return root->gs->doSendGameData(pid, eMSG, vecData);
        }

        int sendClientMessage(const long &pid, vector<int> &eMSG, const std::vector<vector<char> > &vecData, GameRoot *root)
        {
            return root->gs->doSendGameData(pid, eMSG, vecData);
        }

        int sendAllClientMessage(int eMSG, const std::vector<char> &vecData, GameRoot *root)
        {
            //// DLOG_TRACE("sendAllClientMessage, eMSG: " << eMSG << ", " << "vecData size: " << vecData.size());
            return root->gs->doSendAllGameData(eMSG, vecData);
        }

        int sendAllClientMessage(vector<int> &eMSG, const std::vector<vector<char> > &vecData, GameRoot *root)
        {
            return root->gs->doSendAllGameData(eMSG, vecData);
        }

        int sendClientWatchGameData(int eMSG, const std::vector<char> &vecData, GameRoot *root)
        {
            //// DLOG_TRACE("sendClientWatchGameData, eMSG: " << eMSG << ", vecData size: " << vecData.size());
            return root->gs->doSendWatchGameData(eMSG, vecData);
        }

        int sendClientWatchGameData(vector<int> &eMSG, const std::vector<vector<char> > &vecData, GameRoot *root)
        {
            return root->gs->doSendWatchGameData(eMSG, vecData);
        }
    };
};

