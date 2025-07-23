#pragma once

#include "common/macros.h"
#include "gameroot.h"
#include "gameserver.h"
#include "dz.pb.h"

namespace game
{
    namespace message
    {
        int sendClientMessage(const long &pid, int eMSG, const std::vector<char> &vecData, GameRoot *root);
        int sendClientMessage(const long &pid, vector<int> &eMSG, const std::vector<vector<char> > &vecData, GameRoot *root);

        int sendAllClientMessage(int eMSG, const std::vector<char> &vecData, GameRoot *root);
        int sendAllClientMessage(vector<int> &eMSG, const std::vector<vector<char> > &vecData, GameRoot *root);

        int sendClientWatchGameData(int eMSG, const std::vector<char> &vecData, GameRoot *root);
        int sendClientWatchGameData(vector<int> &eMSG, const std::vector<vector<char> > &vecData, GameRoot *root);

        template<class T>
        int sendClientMessage(const long &uid, int eMSG, T const &TMsg, GameRoot *root)
        {
            //vector<char> vecOutBuffer;
            //pbTobuffer(TMsg, vecOutBuffer);
            //// DLOG_TRACE("sendClientMessage, uid = " << uid << ", eMSG: " << eMSG << ", vecData size: " << vecOutBuffer.size() << ", data: " << logPb(TMsg));
            //return sendClientMessage(uid, eMSG, Encoding<T>(TMsg), root);
            //return sendClientMessage(uid, eMSG, vecOutBuffer, root);

            //// DLOG_TRACE("sendClientMessage, uid = " << uid << ", eMSG: " << XGameDZProto::E_msg_ID_Name(eMSG) << ", data: " << logPb(TMsg));
            return sendClientMessage(uid, eMSG, pbTobuffer(TMsg), root);
        }

        template<class T>
        int sendAllClientMessage(int eMSG, T const &TMsg, GameRoot *root)
        {
            //vector<char> vecOutBuffer;
            //pbTobuffer(TMsg, vecOutBuffer);
            //// DLOG_TRACE("sendAllClientMessage, eMSG: " << eMSG << ", " << "vecData size: " << vecOutBuffer.size() << ", data: " << logPb(TMsg));
            //return sendAllClientMessage(eMSG, Encoding<T>(TMsg), root);
            //return sendAllClientMessage(eMSG, vecOutBuffer, root);

            //// DLOG_TRACE("sendAllClientMessage, eMSG: " << XGameDZProto::E_msg_ID_Name(eMSG) << ", data: " << logPb(TMsg));
            return sendAllClientMessage(eMSG, pbTobuffer(TMsg), root);
        }

        template<class T>
        int sendClientWatchGameData(int eMSG, T const &TMsg, GameRoot *root)
        {
            //vector<char> vecOutBuffer;
            //pbTobuffer(TMsg, vecOutBuffer);
            //// DLOG_TRACE("sendClientWatchGameData, eMSG: " << eMSG << ", vecData size: " << vecOutBuffer.size() << ", data: " << logPb(TMsg));
            //return sendClientWatchGameData(eMSG, Encoding<T>(TMsg), root);
            //return sendClientWatchGameData(eMSG, vecOutBuffer, root);

            //// DLOG_TRACE("sendClientWatchGameData, eMSG: " << XGameDZProto::E_msg_ID_Name(eMSG) << ", data: " << logPb(TMsg));
            return sendClientWatchGameData(eMSG, pbTobuffer(TMsg), root);
        }
    };
};

