	#include "jrb.h"
#include "jval.h"
#include "MAP.h"

#ifndef _graphNode_
#define _graphNode_

#define MAX 50
#define INF 1e6

typedef struct GRAPH
{
	struct graphNode* node;	//đỉnh đồ thị
	int* id;
	int size;	//số đỉnh có trong đồ thị
	int edge;
}GRAPH;

typedef struct graphNode //một đỉnh của đồ thị
{
	int id;	//id do chương trình đặt tự động, chỉ chương trình dùng
	char* key;	//tên đỉnh
	int in_degree;
	int out_degree;

	JRB Adjcency;	//danh sách các đỉnh kề
	struct graphNode* next; 

	//tùy vào yêu cầu đề bài
	struct PAIR* product;
	int walk;
}graphNode;

typedef struct PAIR //cấu trúc lưu giá trị theo khóa tùy ý
{
	int key;
	int value;

	struct PAIR* next;
}PAIR;

typedef struct QUEUE
{
	int value;

	struct QUEUE* next;
}QUEUE;

typedef struct STACK
{
	int value;

	struct STACK* next;
}STACK;

//hàm thêm đỉnh vào đồ thị
void addVertex(char* _key, int _id, GRAPH** graph);

//hàm thêm cạnh vào đồ thị (có hướng)
void addEdge(int _id1, int _id2, int weight, GRAPH** graph);
void addEdge_str(char* _key1, char* _key2, int weight, GRAPH** graph);

//trả về trọng số của cạnh
int edgeValue(int _id1, int _id2, GRAPH* graph);

//hàm trả về ma trận 2 x (số đỉnh), trong đó hàng 1 là khoảng cách, hàng 2 là truy vết
int** dijkstra(int _begin, GRAPH** graph);
void find_path(int _end, int** path, GRAPH* graph);

//In ra topo của đồ thị
int topo(GRAPH* graph);

//Duyệt đồ thị từ 1 đỉnh cho trước
void DFS(int _begin, GRAPH** graph);
void BFS(int _begin, GRAPH** graph);

//trả về đỉnh trong đồ thị có id = _id
graphNode* findVertex(int _id, GRAPH** graph);

//trả về cấu trúc PAIR có key = _key
PAIR* findPair(int _key, PAIR** pair);

//tùy vào yêu cầu đề bài mà bổ sung thêm hàm
void addInfor(int _store_id, int _product_id, int quantity, GRAPH** graph);
int return_id(char* _key, GRAPH* graph);

#endif