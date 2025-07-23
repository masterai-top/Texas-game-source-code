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

#include "gameroot.h"
#include "config/gameconfig.h"
#include "config/pluginconfig.h"
#include "context/context.h"
#include "process/process.h"
#include "gameserver.h"

namespace game
{
    using namespace config;
    using namespace context;
    using namespace process;
    using namespace gameserver;

    GameRoot::GameRoot(int iInitMode, GameInitParam const &sInitParams)
        : sParams(sInitParams)
        , cfg(NULL)
        , plg(NULL)
        , con(NULL)
        , pro(NULL)
        , gs(NULL)
    {
        if (cfg == NULL)
        {
            cfg = config::GameConfig::Create();
        }

        if (plg == NULL)
        {
            plg = config::PluginConfig::Create();
        }

        if (con == NULL)
        {
            con = Context::Create(this);
        }

        if (pro == NULL)
        {
            pro = Process::Create(this);
        }

        if (gs == NULL)
        {
            gs = GameServer::Create(this);
        }

        //
        std::string cfgPath = sInitParams.strConfigPath + "lib" + sInitParams.strConfigParam + ".cfg";
        if (!cfg->loadConfigFile(cfgPath.c_str()))
        {
            DLOG_TRACE("error cfgPath, cfgPath = " << cfgPath);
        }
        else
        {
            cfg->printConfigFile(sInitParams);
            con->setRewardJackpotWealth(cfg->getRewardInit());
            con->setSysJackpotWealth(cfg->getSysInit());
        }

        if (this->roomid().size() > 4)
        {
            int room_type = this->roomid()[0] - '0';
            int index =  0;
            if (room_type == 3 || room_type == 9)
            {
                index = this->roomid()[3] - '1';
            }
            cfg->setInitBetTime(room_type, index);
        }
    }

    GameRoot::~GameRoot()
    {
        if (cfg != NULL)
        {
            delete cfg;
            cfg = NULL;
        }

        if (plg != NULL)
        {
            delete plg;
            plg = NULL;
        }

        if (con != NULL)
        {
            delete con;
            con = NULL;
        }

        if (pro != NULL)
        {
            delete pro;
            pro = NULL;
        }

        if (gs != NULL)
        {
            delete gs;
            gs = NULL;
        }
    }
}

