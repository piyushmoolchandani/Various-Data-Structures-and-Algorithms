#include<stdio.h>
#include<stdlib.h>

int N = 0;
struct process
{
    int id;
    int arrival_time;
    int burst_time;
    int remaining_burst_time;
    int turnaround_time;
    int waiting_time;
    int completion_time;
    float penalty_ratio;
};

typedef struct process process;

void print_process(process* temp)
{
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%.2f\n", temp -> id, temp -> arrival_time, \
                 temp -> burst_time, temp -> turnaround_time, temp -> waiting_time, \
                    temp -> completion_time, temp -> penalty_ratio);
}

void print_queue(process * ready_queue[])
{
    printf("%s\n", "ID\tAT\tBT\tTA\tWT\tCT\tPR");
    for (int i = 0; i < N; i++)
        print_process(ready_queue[i]);
    printf("\n");
}

process * create_process(int id, int arrival_time, int burst_time)
{
    process * temp = (process *)malloc(sizeof(process));
    temp -> id = id;
    temp -> arrival_time = arrival_time;
    temp -> burst_time = burst_time;
    temp -> remaining_burst_time= burst_time;
    temp -> turnaround_time = 0;
    temp -> waiting_time = 0;
    temp -> penalty_ratio = 0;
    temp -> completion_time = 0;
    return temp;
}

int for_arrival_time_sorting(const void *p, const void *q)
{
    process * p1 = *(process **)p;
    process * p2 = *(process **)q;
    int l = p1 -> arrival_time;
    int r = p2 -> arrival_time;
    if (l != r)
        return (l - r);
    else
        return (p1 -> id - p2 -> id);    
}

int for_burst_time_sorting(const void *p, const void *q)
{
    process * p1 = *(process **)p;
    process * p2 = *(process **)q;
    int l = p1 -> burst_time;
    int r = p2 -> burst_time;
    if (l != r)
        return (l - r);
    else
        return (p1 -> id - p2 -> id);
}

int for_completion_time_sorting(const void *p, const void *q)
{
    process * p1 = *(process **)p;
    process * p2 = *(process **)q;
    int l = p1 -> completion_time;
    int r = p2 -> completion_time;
    if (l != r)
        return (l - r);
    else
        return (p1 -> id - p2 -> id);
}

void fcfs(process * ready_queue[]);
void sjf_non_pre_emptive(process * ready_queue[]);
void sjf_pre_emptive(process * ready_queue[]);
void round_robin(process * ready_queue[]);

void fcfs(process * ready_queue[])
{
    printf("Before FCFS: \n");
    print_queue(ready_queue);

    qsort(ready_queue, N, sizeof(ready_queue[0]), for_arrival_time_sorting);
    int present_time = 0;
    for (int i = 0; i < N; i++)
    {
        present_time += ready_queue[i] -> burst_time;
        ready_queue[i] -> turnaround_time = present_time - ready_queue[i] -> arrival_time;
        ready_queue[i] -> waiting_time = ready_queue[i] -> turnaround_time - ready_queue[i] -> burst_time;
        ready_queue[i] -> penalty_ratio = (float)(ready_queue[i] -> turnaround_time / ready_queue[i] -> burst_time);
        ready_queue[i] -> completion_time = present_time;
    }

    printf("After FCFS: \n");
    qsort(ready_queue, N, sizeof(ready_queue[0]), for_completion_time_sorting);
    print_queue(ready_queue);
    printf("\n");
}

int min_burst_from_sorted(process * ready_queue[], int current_time)
{
    int min = 65550;
    int min_index = N - 1;
    for (int i = 0; i < N; i++)
    {
        if (ready_queue[i] -> arrival_time > current_time)
            break;
        else if (!(ready_queue[i] -> completion_time))
        {
            if (ready_queue[i] -> remaining_burst_time < min)
            {
                min = ready_queue[i] -> remaining_burst_time;
                min_index = i;
            }
        }
    }
    return min_index;
}

void sjf_non_pre_emptive(process * ready_queue[])
{
    printf("Before SJF non pre emptive: \n");
    print_queue(ready_queue);

    qsort(ready_queue, N, sizeof(ready_queue[0]), for_arrival_time_sorting);
    int present_time = 0;
    for (int j = 0; j < N; j++)
    {
        int i = min_burst_from_sorted(ready_queue, present_time);
        present_time += ready_queue[i] -> burst_time;
        ready_queue[i] -> turnaround_time = present_time - ready_queue[i] -> arrival_time;
        ready_queue[i] -> waiting_time = ready_queue[i] -> turnaround_time - ready_queue[i] -> burst_time;
        ready_queue[i] -> penalty_ratio = (float)(ready_queue[i] -> turnaround_time / ready_queue[i] -> burst_time);
        ready_queue[i] -> completion_time = present_time;
    }

    printf("After SJF non pre-emptive: \n");
    qsort(ready_queue, N, sizeof(ready_queue[0]), for_completion_time_sorting);
    print_queue(ready_queue);
    printf("\n");
}

void sjf_pre_emptive(process * ready_queue[])
{
    printf("Before SJF pre emptive: \n");
    print_queue(ready_queue);

    qsort(ready_queue, N, sizeof(ready_queue[0]), for_arrival_time_sorting);
    int total_time = 0;
    for (int i = 0; i < N; i++)
    {
        total_time += ready_queue[i] -> burst_time;
    }

    for (int present_time = 1; present_time <= total_time; present_time++)
    {
        int i = min_burst_from_sorted(ready_queue, present_time - 1);
        ready_queue[i] -> remaining_burst_time -= 1;
        if (ready_queue[i] -> remaining_burst_time == 0)
        {
            ready_queue[i] -> turnaround_time = present_time - ready_queue[i] -> arrival_time;
            ready_queue[i] -> waiting_time = ready_queue[i] -> turnaround_time - ready_queue[i] -> burst_time;
            ready_queue[i] -> penalty_ratio = (float)ready_queue[i] -> turnaround_time / ready_queue[i] -> burst_time;
            ready_queue[i] -> completion_time = present_time;
        }
    }
    
    printf("After SJF pre-emptive: \n");
    qsort(ready_queue, N, sizeof(ready_queue[0]), for_completion_time_sorting);
    print_queue(ready_queue);
    printf("\n");
}

int provide_next_burst(int total)
{
    if (total < 5)
        return total;
    else
        return 5;
}

void round_robin(process * ready_queue[])
{
    printf("Before Round Robin: \n");
    print_queue(ready_queue);

    qsort(ready_queue, N, sizeof(ready_queue[0]), for_arrival_time_sorting);
    int total_time = 0;
    for (int i = 0; i < N; i++)
    {
        total_time += ready_queue[i] -> burst_time;
    }

    int i = 0;
    int flag[N];
    for (int i = 0; i < N; i++)
    {
        flag[i] = 0;
    }
    for (int present_time = 5; present_time <= total_time; present_time += provide_next_burst(ready_queue[i] -> remaining_burst_time))
    {

        ready_queue[i] -> remaining_burst_time -= provide_next_burst(ready_queue[i] -> remaining_burst_time);
        if (ready_queue[i] -> remaining_burst_time == 0 && !flag[i])
        {
            ready_queue[i] -> turnaround_time = present_time - ready_queue[i] -> arrival_time;
            ready_queue[i] -> waiting_time = ready_queue[i] -> turnaround_time - ready_queue[i] -> burst_time;
            ready_queue[i] -> penalty_ratio = (float)ready_queue[i] -> turnaround_time / ready_queue[i] -> burst_time;
            ready_queue[i] -> completion_time = present_time;
            flag[i] = 1;
        }
        
        i = (i + 1) % N;
        if (total_time == present_time)
            break;
    }

    printf("After Round Robin: \n");
    qsort(ready_queue, N, sizeof(ready_queue[0]), for_completion_time_sorting);
    print_queue(ready_queue);
    printf("\n");
}

int main()
{
    
    process * ready_queue[N];
    /*
    ready_queue[0] = create_process(0, 0, 60);
    ready_queue[1] = create_process(0, 2, 18);
    ready_queue[2] = create_process(0, 3, 25);
    fcfs(ready_queue);
    
    ready_queue[0] = create_process(0, 0, 60);
    ready_queue[1] = create_process(0, 2, 18);
    ready_queue[2] = create_process(0, 3, 25);
    sjf_non_pre_emptive(ready_queue);

    ready_queue[0] = create_process(0, 0, 60);
    ready_queue[1] = create_process(0, 2, 18);
    ready_queue[2] = create_process(0, 3, 25);
    sjf_pre_emptive(ready_queue);
    
    ready_queue[0] = create_process(0, 0, 60);
    ready_queue[1] = create_process(0, 2, 18);
    ready_queue[2] = create_process(0, 3, 25);
    round_robin(ready_queue);
    
    qsort(ready_queue, N, sizeof(ready_queue[0]), for_arrival_time_sorting);*/

    FILE * fp;
    fp = fopen("data.txt", "r");
    char ch;

    if (fp == NULL)
        printf("Cannot open file.\n");

    int i, j, k, sum, sum_1;
    int t_count=0;

	while((ch = getc(fp)) != EOF)
	{
		if(ch == '\n')
		    N = N + 1;
	}
	fseek(fp, 0, SEEK_SET);
	k = 0;
	j = N;
	while(j--)
	{
		i = 0;
		sum = 0;
		sum_1 = 0;

		while((ch = getc(fp)) != '\n' )
    	{
			if(i <= 2)
			{
      			if(i == 1 && ch!=';')
				{
					ch = ch - '0';
					sum = sum * 10 + ch;
				}
			
				if(i == 2 && ch!=';')
				{
					ch = ch - '0';
					sum_1 = sum_1 * 10 + ch;
				}
				
				if(ch == ';')
				i++;
			}
		}
        ready_queue[k] = create_process(k, sum, sum_1);
		k++;
	}
    fcfs(ready_queue);


    fseek(fp, 0, SEEK_SET);
	k = 0;
	j = N;
	while(j--)
	{
		i = 0;
		sum = 0;
		sum_1 = 0;

		while((ch = getc(fp)) != '\n' )
    	{
			if(i <= 2)
			{
      			if(i == 1 && ch!=';')
				{
					ch = ch - '0';
					sum = sum * 10 + ch;
				}
			
				if(i == 2 && ch!=';')
				{
					ch = ch - '0';
					sum_1 = sum_1 * 10 + ch;
				}
				
				if(ch == ';')
				i++;
			}
		}
        ready_queue[k] = create_process(k, sum, sum_1);
		k++;
	}
    sjf_non_pre_emptive(ready_queue);

    fseek(fp, 0, SEEK_SET);
	k = 0;
	j = N;
	while(j--)
	{
		i = 0;
		sum = 0;
		sum_1 = 0;

		while((ch = getc(fp)) != '\n' )
    	{
			if(i <= 2)
			{
      			if(i == 1 && ch!=';')
				{
					ch = ch - '0';
					sum = sum * 10 + ch;
				}
			
				if(i == 2 && ch!=';')
				{
					ch = ch - '0';
					sum_1 = sum_1 * 10 + ch;
				}
				
				if(ch == ';')
				i++;
			}
		}
        ready_queue[k] = create_process(k, sum, sum_1);
		k++;
	}
    sjf_pre_emptive(ready_queue);

    fseek(fp, 0, SEEK_SET);
	k = 0;
	j = N;
	while(j--)
	{
		i = 0;
		sum = 0;
		sum_1 = 0;

		while((ch = getc(fp)) != '\n' )
    	{
			if(i <= 2)
			{
      			if(i == 1 && ch!=';')
				{
					ch = ch - '0';
					sum = sum * 10 + ch;
				}
			
				if(i == 2 && ch!=';')
				{
					ch = ch - '0';
					sum_1 = sum_1 * 10 + ch;
				}
				
				if(ch == ';')
				i++;
			}
		}
        ready_queue[k] = create_process(k, sum, sum_1);
		k++;
	}
    round_robin(ready_queue);
}