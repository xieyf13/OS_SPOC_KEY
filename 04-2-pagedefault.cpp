#include <iostream>
#include <cstring>

using namespace std;

#define MAXINDEX 10
#define INTERVALTIME 2

bool pages_in_memory[MAXINDEX];
int lastVisitTime[MAXINDEX];

int current_time = 0;
int last_time = 0;

void restore_page(int index)
{
	if (INTERVALTIME < (current_time - last_time)) {

		for (int i = 0; i < MAXINDEX; i++) {
			if (lastVisitTime[i] < last_time)
				pages_in_memory[i] = false;
		}

	}
	else {
		pages_in_memory[index] = true;
		lastVisitTime[index] = current_time;
	}

	last_time = current_time;
}

void print_page()
{
	cout << "memory : ";
	for (int i = 0; i < MAXINDEX; i++)
		if (pages_in_memory[i])
			cout << i << " ";

	cout << endl;
}

int main()
{
	memset(pages_in_memory, 0, sizeof(pages_in_memory));
	memset(lastVisitTime, 0, sizeof(lastVisitTime));

	while (true)
	{
		int now_page;
		cin >> now_page;

		if (pages_in_memory[now_page]) 
		{		
			lastVisitTime[now_page] = current_time;
			cout << "HIT " << now_page << "  ";			
		}
		else
		{
			restore_page(now_page);
			cout << "MISS " << now_page << "  ";
		}
		
		print_page();
		current_time++;
	}



	return 0;
}
