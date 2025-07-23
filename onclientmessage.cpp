#include "dz.pb.h"
#include "gameroot.h"
#include "utils/tarslog.h"
#include "common/macros.h"
#include "message/onclientmessage.h"
#include "logic/clientlogic/head.h"

namespace game
{
    namespace message
    {
        void onClientMessage(long uid, int eMSG, const vector<char> &vecMsgData, GameRoot *root)
        {
            using namespace logic;

            try
            {
                switch(static_cast<unsigned char>(eMSG))
                {
                //房间发起sitdown后，发该消息，类似于举手，只有命令字，无消息内容
                case XGameDZProto::NN_msg2cTestBegin_E:
                {
                    // DLOG_TRACE("Recived NN_msg2cTestBegin_E msg, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::TestBegin(uid, vecMsgData, root);
                }
                break;

                //站起
                case XGameDZProto::NN_msg2cStand_E:
                {
                    // DLOG_TRACE("Recived NN_msg2cStand_E msg, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::stand(uid, vecMsgData, root);
                }
                break;

                //坐下
                case XGameDZProto::NN_msg2cSit_E:
                {
                    // DLOG_TRACE("Recived NN_msg2cSit_E msg, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::sit(uid, vecMsgData, root);
                }
                break;

                //下注请求及应答
                case XGameDZProto::NN_msg2csTokenBet_E:
                {
                    // DLOG_TRACE("Recived NN_msg2csTokenBet_E msg, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::TokenBet(uid, vecMsgData, root);
                }
                break;
                case XGameDZProto::NN_msg2csGameStation_E:
                {
                    // DLOG_TRACE("Recived NN_msg2csGameStation_E msg, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::GameStation(uid, vecMsgData, root);
                }
                break;
                //游戏记录
                case XGameDZProto::NN_msg2csGetRecord_E:
                {
                    clientlogic::GetRecord(uid, vecMsgData, root);
                }
                break;
                //收藏游戏记录
                case XGameDZProto::NN_msg2csCollectRecord_E:
                {
                    clientlogic::CollectRecord(uid, vecMsgData, root);
                }
                break;
                //
                case XGameDZProto::NN_msg2csTuoGuan_E:
                {
                    // DLOG_TRACE("Recived NN_msg2csTuoGuan_E, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::TuoGuan(uid, vecMsgData, root);
                }
                break;
                case XGameDZProto::NN_msg2csSneakCard_E:
                {
                    // DLOG_TRACE("Recived NN_msg2csTuoGuan_E, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::SneakCard(uid, vecMsgData, root);
                }
                break;
                //
                default:
                {
                    LOG_ERROR("undefined network message from remote user, uid : " << uid << ", eMSG: " << eMSG);
                }
                break;
                }
            }
            catch (const TarsDecodeException &e)
            {
                ERROR(string("catch tars decode exception : ") + e.what());
            }
            catch (const TarsEncodeException &e)
            {
                ERROR(string("catch tars encode exception : ") + e.what());
            }
            catch (const TarsProtoException &e)
            {
                ERROR(string("catch proto exception : ") + e.what());
            }
            catch (const TC_Exception &e)
            {
                ERROR(string("catch tc exception : ") + e.what());
            }
            catch (const std::exception &e)
            {
                ERROR(string("catch std exception : ") + e.what());
            }
            catch (...)
            {
                ERROR("catch unknown exception.");
            }
        }
    };
};


