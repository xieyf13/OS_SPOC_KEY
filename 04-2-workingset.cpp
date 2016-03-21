#include <cstdio>
#include <cstring>
#define NUMBERS 100

struct member
{
	int own_time;
	bool if_in_table;
} members[NUMBERS];

int main()
{
	memset(members,0,sizeof(members));
	
	int curtime = 0;
	int total_time;
	printf("Please input total_time:\n");
	scanf("%d",&total_time);
	
	int members_num;
	printf("Please input total number:\n");
	scanf("%d",&members_num);
	
	printf("Please input own_time and whether it has been in work table :\n");
	for(int i = 0; i < members_num; i++)
	{
		scanf("%d", &members[i].own_time);
		scanf("%d", &members[i].if_in_table);
	}

	int visit_num;
	
	while(true)
	{
		printf("Please input which page to visit(if you want to exit, input -1):\n");
		scanf("%d",&visit_num);
		
		if (visit_num == -1)
			break;
			
		curtime++;
		members[visit_num].own_time = curtime;
		members[visit_num].if_in_table = 1;
		for (int i = 0; i < members_num; i++)
		{
			if (curtime - members[i].own_time >= total_time)
				members[i].if_in_table = 0;
			if (members[i].if_in_table == 1)
				printf("page %d\n", i);
		}
	}

	return 0;
}
