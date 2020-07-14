#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GRAPH.h"

int convert(char* num)
{
	int res = 0;

	for (int i = 0; i < strlen(num); ++i)
	{
		res *= 10;
		res += num[i] - '0';
	}

	return res;
}

int min_time(graphNode* node, GRAPH* graph)
{
	if(node == NULL)
		return 0;

	int max = 0;

	JRB a;

	jrb_traverse(a, node -> Adjcency)
	{
		graphNode* _node = findVertex(a -> key.i, &graph);
		int time = min_time(_node, graph);
		if(max < time + a -> val.i)
			max = time + a -> val.i;
	}

	return max;
}

int main()
{
	FILE* fp = fopen("K55.txt", "r");
	char* str = (char*)calloc(100, sizeof(char));
	char* s1 = (char*)calloc(100, sizeof(char));
	char* s2 = (char*)calloc(100, sizeof(char));

	GRAPH* graph = (GRAPH*)calloc(1, sizeof(GRAPH));
	GRAPH* topo_graph = (GRAPH*)calloc(1, sizeof(GRAPH));

	while(fgets(str, 100, fp))
	{
		if(feof(fp) == 0)
			str[strlen(str) - 1] = '\0';
		
		strcpy(s1, str);
		int i = 0;

		while(s1[i] != ' ')
			++i;
		s1[i] = '\0';

		addVertex(s1, 0, &graph);
		addVertex(s1, 0, &topo_graph);
		int id1 = graph -> id[return_id(s1, graph) - 1];

		if(strlen(str) >= i + 1)
		{
			i = i + 3;
			int j = i + 1;

			int node = 1;
			int num = 0;
			int id2;
			char key = '-';
			char* tmp = (char*)calloc(100, sizeof(char));

			while(str[j - 1] != '\0')
			{
				strcpy(s2, str + i);
				if(node)
					key = '-';
				else
					key = ' ';

				if(str[j] == key || str[j] == '\0')
				{
					s2[j - i] = '\0';

					if(node)
					{
						// printf("%s: ", s2);
						addVertex(s2, 0, &graph);
						addVertex(s2, 0, &topo_graph);
						strcpy(tmp, s2);
						id2 = graph -> id[return_id(s2, graph) - 1];
						key = ' ';
						node = 0;
						num = 1;
					}else{
						addEdge_str(s1, tmp, convert(s2), &graph);
						addEdge_str(tmp, s1, convert(s2), &topo_graph);
						// printf("%s\n", s2);
						key = '-';
						node = 1;
						num = 0;
					}

					i = j + 1;
					++j;
				}
				++j;
			}
		}
	}

	int option = 0;

	while(option != 7)
	{
		scanf("%d", &option);

		switch(option)
		{
			case 1:
			{
				printf("Tong nut: %d\n", graph -> size);
				break;
			}

			case 2:
			{
				char y = 'y';

				while(y != 'n')
				{
					char* cv = (char*)calloc(100, sizeof(char));

					scanf("%s", cv);
					while(getchar() != '\n');
					graphNode* tmp = graph -> node;

					while(tmp != NULL)
					{
						if(strcmp(tmp -> key, cv) == 0)
						{
							printf("Truoc cong viec %s co %d cong viec\n", cv, tmp -> out_degree);

							JRB a;

							if(tmp -> Adjcency != NULL)
								printf("null\n");

							jrb_traverse(a, tmp -> Adjcency)
							{
								printf("%d\t", a -> key.i);
							}
							printf("\n");

							break;
						}

						tmp = tmp -> next;
					}

					if(tmp == NULL)
					{
						printf("Cong viec khong co trong chuong trinh\n");
					}

					printf("Co thuc hien tiep khong [y/n]\n");
					scanf("%c", &y);
				}
			}

			case 4:
			{
				topo(topo_graph);
				break;
			}

			case 5:
			{
				char* cv = (char*)calloc(100, sizeof(char));
				scanf("%s", cv);

				graphNode* tmp = graph -> node;

				while(tmp != NULL)
				{
					if(strcmp(tmp -> key, cv) == 0)
					{
						printf("%d\n", min_time(tmp, graph));
						break;
					}

					tmp = tmp -> next;
				}
				break;
			}

			case 6:
			{
				if(topo(topo_graph))
					printf("Khong co chu trinh\n");
				else
					printf("Co chu trinh\n");
				break;
			}
		}
	}
}