#include "utils/tarslog.h"
#include "gameroot.h"
#include "common/macros.h"
#include "message/onroommessage.h"
#include "logic/roomlogic/head.h"

namespace game
{
    namespace message
    {
        long onRoomMessage(const RoomSo::E_ROOM_TO_SO eMsgType, void const *p, GameRoot *root)
        {
            using namespace logic;

            long ret = 0;

            try
            {
                //// DLOG_TRACE("Room command message type is : " << (RoomSo::E_ROOM_TO_SO)eMsgType);

                //
                switch (eMsgType)
                {
                //加载游戏配置
                case RoomSo::TGAME_GameConfig_E:
                {
                    //// DLOG_TRACE("TGAME_GameConfig_E ");
                    roomlogic::GameConfig(p, root);
                }
                break;

                //设置玩家游戏配置
                case RoomSo::TGAME_UserConfig_E:
                {
                    //// DLOG_TRACE("TGAME_UserConfig_E ");
                    roomlogic::UserConfig(p, root);
                }
                break;

                //游戏参数
                case RoomSo::TGAME_GameParameter_E:
                {
                    //// DLOG_TRACE("TGAME_GameParameter_E ");
                    roomlogic::GameParameter(p, root);
                }
                break;

                //常量配置
                case RoomSo::TGAME_ConstConfig_E:
                {
                    DLOG_TRACE("TGAME_ConstConfig_E ");
                    roomlogic::ConstConfig(p, root);
                }
                break;

                //增值服务配置
                case RoomSo::TGAME_ServiceConfig_E:
                {
                    //// DLOG_TRACE("TGAME_ServiceConfig_E ");
                    roomlogic::BaseServiceConfig(p, root);
                }
                break;

                //用户离线
                case RoomSo::TGAME_UserOffline_E:
                {
                    //// DLOG_TRACE("TGAME_UserOffline_E");
                    roomlogic::UserOffline(p, root);
                }
                break;

                //用户进入房间
                case RoomSo::TGAME_UserEnter_E:
                {
                    //// DLOG_TRACE("TGAME_UserEnter_E");
                    ret = roomlogic::UserEnter(p, root);
                }
                break;

                //用户坐桌
                case RoomSo::TGAME_UserSitDown_E:
                {
                    //// DLOG_TRACE("TGAME_UserSitDown_E");
                    roomlogic::UserSitDown(p, root);
                }
                break;

                //站起
                case RoomSo::TGAME_StandUp_E:
                {
                    //// DLOG_TRACE("TGAME_StandUp_E");
                    roomlogic::StandUp(p, root);
                }
                break;

                //坐下
                case RoomSo::TGAME_SitDown_E:
                {
                    //// DLOG_TRACE("TGAME_SitDown_E");
                    roomlogic::SitDown(p, root);
                }
                break;

                //用户离桌
                case RoomSo::TGAME_UserLeftTable_E:
                {
                    //// DLOG_TRACE("TGAME_UserLeftTable_E");
                    roomlogic::UserLeftTable(p, root);
                }
                break;

                //玩家信息
                case RoomSo::TGAME_UserInfo_E:
                {
                    //// DLOG_TRACE("TGAME_UserInfo_E");
                    roomlogic::UserInfo(p, root);
                }
                break;

                //取玩家信息
                case RoomSo::TGAME_GetUserInfo_E:
                {
                    //// DLOG_TRACE("TGAME_GetUserInfo_E");
                    ret = roomlogic::GetUserInfo(p, root);
                }
                break;

                //玩家财富信息
                case RoomSo::TGAME_AddWealth_E:
                {
                    //// DLOG_TRACE("TGAME_AddWealth_E");
                    roomlogic::AddWealth(p, root);
                }
                break;

                //玩家信息@房卡场
                case RoomSo::TGAME_UserInfoMapPrivate_E:
                {
                    //// DLOG_TRACE("TGAME_UserInfoMapPrivate_E");
                    roomlogic::UserInfoMapPrivate(p, root);
                }
                break;
                //用户重回消息
                case RoomSo::TGAME_UserReCome_E:
                {
                    //// DLOG_TRACE("TGAME_UserReCome_E");
                    roomlogic::UserRecome(p, root);
                }
                break;
                //暂停游戏
                case RoomSo::TGAME_Pause_E:
                {
                    roomlogic::Pause(p, root);
                }
                break;

                //获取玩家游戏状态
                case RoomSo::TGAME_UserStatue_E:
                {
                    ret = roomlogic::GetUserStatue(p, root);
                }
                break;
                //清理游戏
                case RoomSo::TGAME_CLEAN_E:
                {
                    ret = roomlogic::CleanGame(p, root);
                }
                break;

                case RoomSo::TGAME_DebugCard_E:
                {
                    roomlogic::DebugCard(p, root);
                }
                break;

                case RoomSo::TGAME_OpenLog_E:
                {
                    roomlogic::OpenLog(p, root);
                }
                break;

                case RoomSo::TGAME_AIDecide_E:
                {
                    roomlogic::AIDecide(p, root);
                }
                break;
                default:
                {
                    ret = -1;
                    LOG_ERROR("unkown Room command message type is : " << (RoomSo::E_ROOM_TO_SO)eMsgType);
                }
                break;
                }
            }
            catch (const std::exception &e)
            {
                ERROR(string("catch std exception : ") + e.what());
            }
            catch (...)
            {
                ERROR("catch unknown exception.");
            };

            return ret;
        }
    };
};

