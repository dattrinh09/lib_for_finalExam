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

	printf("%d\n", graph -> size);

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
						ad_matrix[tmp -> id - 1][a -> key.i - 1] = a -> val.i;
						ad_matrix[a -> key.i - 1][tmp -> id - 1] = a -> val.i;
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

				while(tmp != NULL)
				{
					if(tmp -> walk == tmp -> in_degree && tmp -> walk == tmp -> out_degree)
						printf("%d\t", tmp -> id);

					tmp = tmp -> next;
				}

				printf("\n");

				int arr[2][vertex];

				for (int i = 0; i < vertex; ++i)
				{
					arr[0][i] = i + 1;
					arr[1][i] = findVertex(i+1, &graph) -> in_degree;
				}

				for (int i = 0; i < vertex - 1; ++i)
				{
					for (int j = i + 1; j < vertex; ++j)
					{
						if(arr[1][i] < arr[1][j])
						{
							int tmp = arr[1][i];
							arr[1][i] = arr[1][j];
							arr[1][j] = tmp;

							tmp = arr[0][i];
							arr[0][i] = arr[0][j];
							arr[0][j] = tmp;
						}
					}
				}
				printf("%d\t", arr[0][0]);

				for (int i = 1; i < vertex; ++i)
				{
					
						printf("%d\t", arr[0][i]);
				}
				printf("\n");

				break;
			}
		}
	}
}