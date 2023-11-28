#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
    int n;  
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

int in_degree[MAX_VERTICES];  
int removed[MAX_VERTICES];    

void graph_init(GraphType* g) {
    int v;
    g->n = 0;
    for (v = 0; v < MAX_VERTICES; v++)
        g->adj_list[v] = NULL;
}

void insert_vertex(GraphType* g, int v) {
    if ((g->n + 1) > MAX_VERTICES) {
        fprintf(stderr, "�׷���: ������ ���� �ʰ�\n");
        return;
    }
    g->n++;
}

void insert_edge(GraphType* g, int u, int v) {
    GraphNode* node;
    if (u >= g->n || v >= g->n) {
        fprintf(stderr, "�׷���: ���� ��ȣ ����\n");
        return;
    }
    node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
}

int remove_zero_vertex(GraphType* g) {
    int i;

    for (i = 0; i < g->n; i++) {
        if (in_degree[i] == 0 && !removed[i]) {
            
            GraphNode* node = g->adj_list[i];
            while (node != NULL) {
                in_degree[node->vertex]--;
                node = node->link;
            }
            removed[i] = TRUE;
            return i;
        }
    }

    return -1;  
}

int topo_sort(GraphType* g) {
    int index;

    while ((index = remove_zero_vertex(g)) != -1) {
        printf("���� %d -> ", index);
    }

    for (int i = 0; i < g->n; i++) {
        if (in_degree[i] != 0) {
            return FALSE;
        }
    }

    for (int i = 0; i < g->n; i++) {
        if (removed[i] != 1) {
            return FALSE;
        }
    }

    return TRUE;
}


int main(void) {
    GraphType g;
    graph_init(&g);
    insert_vertex(&g, 0);
    insert_vertex(&g, 1);
    insert_vertex(&g, 2);
    insert_vertex(&g, 3);
    insert_vertex(&g, 4);
    insert_vertex(&g, 5);

    //���� 0 ��������Ʈ
    insert_edge(&g, 0, 2);
    insert_edge(&g, 0, 3);
    //���� 1 ��������Ʈ
    insert_edge(&g, 1, 3);
    insert_edge(&g, 1, 4);
    //���� 2 ��������Ʈ
    insert_edge(&g, 2, 3);
    insert_edge(&g, 2, 5);
    //���� 3 ��������Ʈ
    insert_edge(&g, 3, 5);
    //���� 4 ��������Ʈ
    insert_edge(&g, 4, 5);

   

    if (topo_sort(&g))
        printf("���� ������ �ֽ��ϴ�.\n");
    else
        printf("���� ������ �������� �ʽ��ϴ�.\n");

    return 0;
}
