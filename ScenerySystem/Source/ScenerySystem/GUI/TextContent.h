#include <string>

using namespace std;

//
const string HEADER_TEXT =
"\
=====================================\n\
	 ������Ϣ����ϵͳ\n\
=====================================\n\
";

//
const string INPUT_TIP =
"��ѡ����Ҫ���еĲ����� ";

//
const string MAIN_PAGE_TEXT = HEADER_TEXT +
"\
1. ������������ֲ�ͼ\n\
2. ���Ӿ��������·��\n\
3. �����������ֲ�ͼ\n\
4. ������������·ͼ\n\
5. �������������·ͼ\n\
6. ������������·��\n\
7. �����������Ϣ��ѯ\n\
8. ͣ��������������¼\n\
9. �˳�ϵͳ\n\n\
" + INPUT_TIP;

//
const string ADD_SCENERY_PAGE_TEXT = HEADER_TEXT +
"\
1. ���һ����������\n\
2. ���һ������·��\n\
3. �������˵�\n\n\
" + INPUT_TIP;

//
const string OUTPUT_SCENERY_PAGE_TEXT = HEADER_TEXT +
"\
1. �ڽӾ�����ʽ���\n\
2. �ڽӱ���ʽ���\n\
3. �������˵�\n\n\
" + INPUT_TIP;

//
const string CAL_MIN_DISTANCE_PAGE_TEXT = HEADER_TEXT +
"\
1. Floyd����������С·��\n\
2. Dijkstra����������С·��\n\
3. �������˵�\n\n\
" + INPUT_TIP;

//
const string SCENERY_INFO_PAGE_TEXT = HEADER_TEXT +
"\
1. ���㰴�ȶ�����\n\
2. ��ѯ������\n\
3. �������˵�\n\n\
" + INPUT_TIP;

//
const string PARKING_PAGE_TEXT = HEADER_TEXT +
"\
1. ��������ͣ����\n\
2. �����뿪ͣ����\n\
3. �鿴����״̬\n\
4. �������˵�\n\n\
" + INPUT_TIP;