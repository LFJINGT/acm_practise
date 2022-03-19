// W-1 Saving James Bond - Easy Version（深度优先搜索）
#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <math.h>

using namespace std;

int mark[100];  //用于记录各结点（鳄鱼）是否跳到过，默认没有被跳到过，为 0
int n;          //用于记录结点（鳄鱼）的总数
int jumpsize;   //用于记录每次可以跳出的距离
double R = 7.5; //用于保存中心小岛的半径
int set;        //用于标记最终结果

struct Node //把每个鳄鱼当作一个节点
{
    int x;
    int y;
};

// 用于判断node1和node2能不能互相跳过去
bool canJump(struct Node *node1, struct Node *node2)
{
    double nodeDistance = sqrt(pow((node1->x - node2->x), 2) + pow((node1->y - node2->y), 2));
    if (nodeDistance <= jumpsize)
        return true;
    return false;
}

// 判断能否从当前节点直接跳上岸
bool rightNode(struct Node *node)
{
    int up = 50 - node->y;
    int down = 50 + node->y;
    int left = 50 + node->x;
    int right = 50 - node->x;
    if (left <= jumpsize || right <= jumpsize || up <= jumpsize || down <= jumpsize)
        return true;
    return false;
}

// 深度优先搜索，判断从当前的第x个节点起跳，最终能否跳上岸
bool DFS(struct Node *nodeList, int x)
{
    if (rightNode(&nodeList[x]))
        return true;
    mark[x] = 1;
    for (int i = 0; i < n; i++)
    {
        if (!mark[i] && canJump(&nodeList[i], &nodeList[x]))
        {
            bool ans = DFS(nodeList, i);
            if (ans)
                return true;
        }
    }
    return false;
}

// 判断是否能从中心小岛跳到本结点（判断当前节点能否作为DFS搜索的第一个节点)
bool firstStep(struct Node *node)
{
    double zeroSize = sqrt(pow(node->x, 2) + pow(node->y, 2));
    if (zeroSize <= (R + jumpsize))
        return true;
    return false;
}

int main()
{
    scanf("%d%d", &n, &jumpsize);
    struct Node *nodeList = (struct Node *)malloc(sizeof(struct Node) * n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &(nodeList[i].x), &(nodeList[i].y));
    }
    for (int i = 0; i < n; i++)
    {
        if (firstStep(&nodeList[i]) && !mark[i])
        {
            bool ans = DFS(nodeList, i);
            if (ans)
            {
                set = 1;
                break;
            }
        }
    }
    if (set)
        printf("Yes");
    else
        printf("No");

    return 0;
}