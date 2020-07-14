#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GRAPH.h"

int main()
{
	FILE* fp = fopen("dothi.txt", "r");
	int edge, vertex;

	fscanf(fp, "%d", &vertex);
	fscanf(fp, "%d", &edge);

	int id1, id2, time;

	GRAPH* graph = (GRAPH*)calloc(1, sizeof(GRAPH));

	for (int i = 0; i < edge; ++i)
	{
		fscanf(fp, "%d", &id1);
		fscanf(fp, "%d", &id2);
		fscanf(fp, "%d", &time);

		addVertex("#", id1, &graph);
		addVertex("#", id2, &graph);

		addEdge(id1, id2, time, &graph);
		addEdge(id2, id1, time, &graph);
	}

	int option = 0;

	while(option != 6)
	{
		scanf("%d", &option);

		switch(option)
		{
			case 1:
			{
				int** ad_matrix = (int**)calloc(vertex, sizeof(int*));
				for (int i = 0; i < vertex; ++i)
					*(ad_matrix + i) = (int*)calloc(vertex, sizeof(int));

				graphNode* tmp = graph -> node;
				JRB a;
				while(tmp != NULL)
				{
					jrb_traverse(a, tmp -> Adjcency)
					{
						ad_matrix[graph -> id[tmp -> id - 1] - 1][graph -> id[a -> key.i - 1] - 1] = a -> val.i;
						ad_matrix[graph -> id[a -> key.i - 1] - 1][graph -> id[tmp -> id - 1] - 1] = a -> val.i;
					}

					tmp = tmp -> next;
				}
				
				for (int i = 0; i < vertex; ++i)
				{
					for (int j = 0; j < vertex; ++j)
					{
						printf("%-5d", ad_matrix[i][j]);
					}
					printf("\n");
				}

				break;
			}

			case 2:
			{
				graphNode* tmp = graph -> node;
				JRB a;

				while(tmp != NULL)
				{
					printf("Castle%d:", tmp -> id);

					jrb_traverse(a, tmp -> Adjcency)
					{
						printf("%d\t", a -> key.i);
					}
					printf("\n");

					tmp = tmp -> next;
				}

				break;
			}

			case 3:
			{
				graphNode* tmp = graph -> node;
				int max_way = 0;

				while(tmp != NULL)
				{
					if(max_way < tmp -> in_degree)
						max_way = tmp -> in_degree;

					if(tmp -> walk == tmp -> in_degree)
						printf("%d\t", graph -> id[tmp -> id - 1]);
					
					tmp = tmp -> next;
				}
				printf("\n");

				tmp = graph -> node;

				while(tmp != NULL)
				{
					if(tmp -> in_degree == max_way)
					{
						printf("%d\t", graph -> id[tmp -> id - 1]);
					}
					tmp = tmp -> next;
				}
				printf("\n");

				break;
			}

			case 4:
			{
				int s, t;
				scanf("%d", &s);
				scanf("%d", &t);

				int** res = dijkstra(s, &graph);
				find_path(t, res, graph);
				break;
			}
		}
	}
}