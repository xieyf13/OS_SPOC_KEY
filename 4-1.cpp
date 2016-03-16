#include <cstdio>
#include <cstdlib>
#include <cstdlib>

using namespace std;

int data[] = {0x6653, 0x1c13, 0x6890, 0x0af6, 0x1e6f};

int memory[4096];
int disk[4096];

void solve(int x) {
	
	printf("Virtual Address: %x\n", x);
	int pde_idx = (x >> 10) & 31;
	int pte_idx = (x >> 5) & 31;
	int offset = x & 31;

	int pde_ctx = memory[0xd80 + pde_idx];

	printf("	->pde_idx: %x, pde_cxt: (Valid: %d, pfn: %x)\n", pde_idx, pde_ctx >> 7, pde_ctx & 0x7f);

	if ((pde_ctx >> 7) == 0) 
	{
		printf("		-> Fault, pde invalid\n");
		return;
	}

	int pte_ctx = memory[(pde_ctx & 0x7f) * 32 + pte_idx];

	printf("		->pte_idx: %x, pte_cxt: (Valid: %d, pfn: %x)\n", pte_idx, pte_ctx >> 7, pte_ctx & 0x7f);

	if ((pte_ctx >> 7) == 1) 
	{
		printf("			-> To Physical Address %x -> Value: %x\n", ((pte_ctx & 0x7f) << 5) + offset, memory[((pte_ctx & 0x7f) << 5) + offset]);
	}
	else 
	{
		if ((pte_ctx & 0x7f) == 0x7f)
			printf("			-> Fault, can not find!\n");
		else
			printf("			-> To disk Address %x -> Value: %x\n", ((pte_ctx & 0x7f) << 5) + offset, disk[((pte_ctx & 0x7f) << 5) + offset]);

	}
}

int main()
{
	freopen("input.txt", "r", stdin);

	for (int i = 0; i < 0x80; i++) 
	{
		int tmp;
		scanf("page %x:", &tmp);

		for (int j = 0; j < 32; j++)
			scanf("%x", &memory[i * 32 + j]);

		scanf("\n");
	}

	for (int i = 0; i < 0x80; i++) 
	{
		int tmp;
		scanf("disk %x:", &tmp);

		for (int j = 0; j < 32; j++)
			scanf("%x", &disk[i * 32 + j]);

		scanf("\n");
	}
	
	for(int i = 0; i < sizeof(data)/sizeof(data[0]); i++)
		solve(data[i]);
		
	return 0;
	
}
