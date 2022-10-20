#pragma once
#include <string>

#define InitFundTip std::string("设置玩家初始资金，范围1000～50000（默认10000）")
#define ChoosePlayerTip std::string("请选择2～4位不重复玩家，输入编号即可（1、钱夫人；2、阿土伯；3、孙小美；4、金贝贝）：")
#define GameOverStr std::string("游戏结束")
#define WinStr std::string("胜利")

#define CmdErrorStr std::string("命令错误")
#define SetUserFirstStr std::string("请先设置玩家")
#define QueryBuyEmptyTip std::string("是否购买空地？y:是 n:否")
#define BuyEmptyY std::string("购买了空地")
#define QueryUpdateBulidingTip std::string("是否升级建筑？y:是 n:否")
#define UpdateBulidingY std::string("升级了建筑")
#define BankruptcyStr std::string("破产了")
#define MagicHouseTip std::string("请选择要陷害的人 1、钱夫人；2、阿土伯；3、孙小美；4、金贝贝；0、退出")
#define FrameStr std::string("陷害了")
#define ToolHouseTip std::string("欢迎光临道具屋，请选择您所需要的道具：1:路障  2:机器娃娃  F:退出")
#define CreditNotEnoughStr std::string("点数不足")
#define BagFullStr std::string("道具背包满了")
#define ExitToolHouseTip std::string("退出道具屋")
#define BuyBarrierStr std::string("购买了一个路障")
#define BuyRobotStr std::string("购买了一个机器娃娃")
#define RollStr std::string("掷骰子")
#define NoBarrierStr std::string("没有路障")
#define SellStr std::string("成功卖了地")
#define CantPlaceBarrier std::string("不能放路障")
#define NoRobotStr std::string("没有机器娃娃")
#define CantPlaceRobot std::string("不能放机器娃娃")
#define FundStr std::string("资金")
#define CreditStr std::string("点数")
#define BarrierStr std::string("路障数")
#define RobotStr std::string("机器娃娃数")
#define GodStr std::string("财神剩余天数")
#define GiftHouseTip std::string("欢迎光临礼品屋，请选择一件您喜欢的礼品：1:2000资金  2:200点数  3:5回合财神  其他:退出")
#define GetCreditStr std::string("获得点数")
#define GetFundStr std::string("获得资金")
#define GetGodStr std::string("获得财神")
#define GodOnBodyStr std::string("财神附身，可免过路费")

#define LandTypeStr std::string("地段")
#define LandEmptyStr std::string("空地")
#define LandLevel1Str std::string("茅屋")
#define LandLevel2Str std::string("洋房")
#define LandLevel3Str std::string("摩天楼")
#define NoLandEmptyStr std::string("无空地")
#define NoLandLevel1Str std::string("无茅屋")
#define NoLandLevel2Str std::string("无洋房")
#define NoLandLevel3Str std::string("无摩天楼")
#define AtStr std::string("在")
#define TotalStr std::string("总计")
#define QueryTitleStr std::string("位置\t地段\t房屋等级")

#define HELPStr "Roll: 掷骰子，行走1~6步。\nSell n: 售出自己在地图上位置为n的房产。\nBlock n: 将路障放在前后n格（-10 <= n <= 10）的位置，n为正表示向前，为负表示向后，路过路障被拦截\nRobot: 使用机器人清空前方10格的任何道具\nQuery: 查询自家资产\nHelp: 显示帮助\nQuit: 退出游戏\n"

std::string get_name(char c);
int get_clour(char c);
std::string get_level_str(int level);