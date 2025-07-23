/***************************************************************************************
#  Copyright (c) 2018
#  All rights reserved
#
#  @author  :
#  @name    :
#  @file    :
#  @date    :
#  @describe:GameServer通信类 游戏与外部的唯一接口实现
#***************************************************************************************/

#include "utils/tarslog.h"
#include "common/macros.h"
//#include "protos/headproto.h"
//#include "protos/dzproto.h"
#include "head.pb.h"
#include "dz.pb.h"
#include "gameroot.h"
#include "gameserver.h"
#include "message/onroommessage.h"
#include "message/onclientmessage.h"

namespace game
{
    namespace gameserver
    {
        GameServer::GameServer(GameRoot *root)
            : _root(root)
            , _pTable(root->sParams.pTable)
            , _strRoomTableId(root->sParams.strRoomTableId)
        {

        }

        GameServer::~GameServer()
        {

        }

        long GameServer::toSoData(const RoomSo::E_ROOM_TO_SO eMsgType, void *p)
        {
            long ret = 0;

            __TRY__;

            ret = message::onRoomMessage(eMsgType, p, _root);

            __CATCH__;

            return ret;
        }

        int GameServer::onGameSoMessage(const long lPlayerID, const vector<char> &vecMsgData)
        {
            int ret = 0;

            __TRY__

            XGameSoProto::TSoMsg somsg = pbToObj<XGameSoProto::TSoMsg>(vecMsgData);

            //校验版本
            if (somsg.nver() != XGameDZProto::iProtoVersion)
            {
                LOG_WARN("client proto version : \"" << somsg.nver() << "\" server proto version : \"" << XGameDZProto::iProtoVersion << "\";");
            }

            //校验命令字
            if (somsg.ncmd() > XGameDZProto::MSG_ID_END || somsg.ncmd() < XGameDZProto::MSG_ID_BEGIN)
            {
                LOG_ERROR("invalid message command type value.");
                return -1;
            }

            //data
            vector<char> vecOutBuffer;
            vecOutBuffer.insert(vecOutBuffer.begin(), somsg.vecmsgdata().begin(), somsg.vecmsgdata().end());
            RLOG_DEBUG << "process game so reqeust, msg size = " << vecOutBuffer.size() << ", msg data len: " << somsg.vecmsgdata().length() << endl;
            message::onClientMessage(lPlayerID, somsg.ncmd(), vecOutBuffer, _root);

            __CATCH__

            return ret;
        }

        int GameServer::toRoomData(const RoomSo::E_SO_TO_ROOM eMSG, void *p)
        {
            RLOG_DEBUG << " test send room data, eMSG: " << etos(eMSG) << endl;
            if(_pTable)
            {
                return _pTable->toRoomData(eMSG, p);
            }
            else
            {
                RLOG_ERROR << "_pTable is nullptr." << endl;
                return 0;
            }
        }

        int GameServer::doSendGameData(const long &pid, int eMSG, const vector<char> &vecData)
        {
            int ret = 0;

            __TRY__

            XGameSoProto::TSoMsg sTSoMsg;
            sTSoMsg.set_nver(XGameDZProto::iProtoVersion);
            sTSoMsg.set_ncmd(eMSG);
            string msgData;
            msgData.assign(vecData.begin(), vecData.end());
            sTSoMsg.set_vecmsgdata(msgData);
            ret = _pTable->doSendGameData(pid, pbTobuffer(sTSoMsg));
            RLOG_DEBUG << "send game data, pid : " << pid << ", eMSG: " << eMSG << ", vecData size : " << vecData.size() << endl;

            __CATCH__

            return ret;
        }

        int GameServer::doSendGameData(const long &pid, vector<int> &eMSG, const std::vector<vector<char> > &vecData)
        {
            int ret = 0;

            __TRY__

            if (eMSG.size() == 0 || vecData.size() == 0 || eMSG.size() != vecData.size())
            {
                return -1;
            }

            std::vector<vector<char> > vecSendData;
            for (size_t i = 0; i < vecData.size(); ++i)
            {
                XGameSoProto::TSoMsg sTSoMsg;
                sTSoMsg.set_nver(XGameDZProto::iProtoVersion);
                sTSoMsg.set_ncmd(eMSG[i]);
                string msgData;
                msgData.assign(vecData[i].begin(), vecData[i].end());
                sTSoMsg.set_vecmsgdata(msgData);
                vecSendData.push_back(pbTobuffer(sTSoMsg));
            }

            ret = _pTable->doSendGameData(pid, vecSendData);
            RLOG_DEBUG << "send game data, pid : " << pid << ", vecData size : " << vecData.size() << endl;

            __CATCH__

            return ret;
        }

        int GameServer::doSendAllGameData(int eMSG, const std::vector<char> &vecData)
        {
            int ret = 0;

            __TRY__

            XGameSoProto::TSoMsg sTSoMsg;
            sTSoMsg.set_nver(XGameDZProto::iProtoVersion);
            sTSoMsg.set_ncmd(eMSG);
            string msgData;
            msgData.assign(vecData.begin(), vecData.end());
            sTSoMsg.set_vecmsgdata(msgData);
            ret = _pTable->doSendAllGameData(pbTobuffer(sTSoMsg));
            RLOG_DEBUG << "send all game data, eMSG: " << eMSG << ", vecData size : " << vecData.size() << endl;

            __CATCH__

            return ret;
        }

        int GameServer::doSendAllGameData(vector<int> &eMSG, const std::vector<vector<char> > &vecData)
        {
            int ret = 0;

            __TRY__

            if (eMSG.size() == 0 || vecData.size() == 0 || eMSG.size() != vecData.size())
            {
                return -1;
            }

            std::vector<vector<char> > vecSendData;
            for (size_t i = 0; i < vecData.size(); ++i)
            {
                XGameSoProto::TSoMsg sTSoMsg;
                sTSoMsg.set_nver(XGameDZProto::iProtoVersion);
                sTSoMsg.set_ncmd(eMSG[i]);
                string msgData;
                msgData.assign(vecData[i].begin(), vecData[i].end());
                sTSoMsg.set_vecmsgdata(msgData);
                vecSendData.push_back(pbTobuffer(sTSoMsg));
            }

            ret = _pTable->doSendAllGameData(vecSendData);
            RLOG_DEBUG << "send all game data, vecData size : " << vecData.size() << endl;

            __CATCH__

            return ret;
        }

        int GameServer::doSendWatchGameData(int eMSG, const std::vector<char> &vecData)
        {
            int ret = 0;

            __TRY__

            XGameSoProto::TSoMsg sTSoMsg;
            sTSoMsg.set_nver(XGameDZProto::iProtoVersion);
            sTSoMsg.set_ncmd(eMSG);
            string msgData;
            msgData.assign(vecData.begin(), vecData.end());
            sTSoMsg.set_vecmsgdata(msgData);
            ret = _pTable->doSendWatchGameData(pbTobuffer(sTSoMsg));
            RLOG_DEBUG << "send watch game data, eMSG: " << eMSG << ", vecData size : " << vecData.size() << endl;

            __CATCH__

            return ret;
        }

        int GameServer::doSendWatchGameData(vector<int> &eMSG, const std::vector<vector<char> > &vecData)
        {
            int ret = 0;

            __TRY__

            if (eMSG.size() == 0 || vecData.size() == 0 || eMSG.size() != vecData.size())
            {
                return -1;
            }

            std::vector<vector<char> > vecSendData;
            for (size_t i = 0; i < vecData.size(); ++i)
            {
                XGameSoProto::TSoMsg sTSoMsg;
                sTSoMsg.set_nver(XGameDZProto::iProtoVersion);
                sTSoMsg.set_ncmd(eMSG[i]);
                string msgData;
                msgData.assign(vecData[i].begin(), vecData[i].end());
                sTSoMsg.set_vecmsgdata(msgData);

                vecSendData.push_back(pbTobuffer(sTSoMsg));
            }

            ret = _pTable->doSendWatchGameData(vecSendData);
            RLOG_DEBUG << "send watch game data, vecData size : " << vecData.size() << endl;

            __CATCH__

            return ret;
        }
    }
};
