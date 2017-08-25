#include <string>

using namespace std;

//
const string HEADER_TEXT =
"\
=====================================\n\
	 景区信息管理系统\n\
=====================================\n\
";

//
const string INPUT_TIP =
"请选择需要进行的操作： ";

//
const string MAIN_PAGE_TEXT = HEADER_TEXT +
"\
1. 创建景区景点分布图\n\
2. 增加景区景点和路径\n\
3. 输出景区景点分布图\n\
4. 输出景区景点回路图\n\
5. 输出景区导游线路图\n\
6. 两个景点间最短路径\n\
7. 景区景点的信息查询\n\
8. 停车场车辆进出记录\n\
9. 退出系统\n\n\
" + INPUT_TIP;

//
const string ADD_SCENERY_PAGE_TEXT = HEADER_TEXT +
"\
1. 添加一个景区景点\n\
2. 添加一条景区路径\n\
3. 返回主菜单\n\n\
" + INPUT_TIP;

//
const string OUTPUT_SCENERY_PAGE_TEXT = HEADER_TEXT +
"\
1. 邻接矩阵形式输出\n\
2. 邻接表形式输出\n\
3. 返回主菜单\n\n\
" + INPUT_TIP;

//
const string CAL_MIN_DISTANCE_PAGE_TEXT = HEADER_TEXT +
"\
1. Floyd方法计算最小路径\n\
2. Dijkstra方法计算最小路径\n\
3. 返回主菜单\n\n\
" + INPUT_TIP;

//
const string SCENERY_INFO_PAGE_TEXT = HEADER_TEXT +
"\
1. 景点按热度排序\n\
2. 查询景点简介\n\
3. 返回主菜单\n\n\
" + INPUT_TIP;

//
const string PARKING_PAGE_TEXT = HEADER_TEXT +
"\
1. 车辆进入停车场\n\
2. 车辆离开停车场\n\
3. 查看车辆状态\n\
4. 返回主菜单\n\n\
" + INPUT_TIP;