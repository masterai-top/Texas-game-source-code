/***************************************************************************************
#  Copyright (c) 2018
#  All rights reserved
#
#  @author  :
#  @name    :
#  @file    :
#  @date    :
#  @describe: GameServer通信类 游戏与外部的唯一接口实现
#***************************************************************************************/

#pragma once

//
#include "Comm/ITableGame.h"
#include "common/macros.h"

///
// Function:游戏服务器接口实现
// Describe:1.接收游戏外部传入的消息,并调用分发命令分发消息
//          2.压入透传包头并向客户端发送透传消息
//          3.向RoomServer发送消息结构体
///
namespace game
{
    class GameRoot;

    namespace gameserver
    {
        class GameServer : public IGame
        {
            DISALLOW_COPY_AND_ASSIGN(GameServer)

        private:
            explicit GameServer(GameRoot *root);

        public:
            static GameServer *Create(GameRoot *root)
            {
                return new GameServer(root);
            }

            ~GameServer();

        public:
            long toSoData(const RoomSo::E_ROOM_TO_SO eMsgType, void *p);
            int onGameSoMessage(const long lPlayerID, const std::vector<char> &vecMsgData);

        public:
            int toRoomData(const RoomSo::E_SO_TO_ROOM eMSG, void *p);
            int doSendGameData(const long &pid, int eMSG, const std::vector<char> &vecData);
            int doSendGameData(const long &pid, vector<int> &eMSG, const std::vector<vector<char> > &vecData);
            int doSendAllGameData(int eMSG, const std::vector<char> &vecData);
            int doSendAllGameData(vector<int> &eMSG, const std::vector<vector<char> > &vecData);
            int doSendWatchGameData(int eMSG, const std::vector<char> &vecData);
            int doSendWatchGameData(vector<int> &eMSG, const std::vector<vector<char> > &vecData);

        public:
            inline std::string const &getRoomTableId() const
            {
                return _strRoomTableId;
            }

        private:
            GameRoot *_root;
            ITable *const _pTable;
            string const &_strRoomTableId;
        };
    }
}

