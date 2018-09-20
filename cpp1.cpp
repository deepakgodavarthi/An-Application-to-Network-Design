#include <iostream>
#include <algorithm>
using namespace std;

int list[19];
int n=20;
int cost_matrix[20][20];
int traffic_matrix[20][20];


//This is a random number generator
void Random_Number(int z)
{
	int x=0;
	for(int i = 0; i <n; i++)
	{
		if(i==z)	i++;
		
		list[x]=i;
		x++;
	}
random_shuffle(list, list+19);
}


	float Cost_Matrix(int k)
	{
		int count=0;
		for(int i=0;i<n;i++)
		{
			Random_Number(i);
			for(int j=0;j<n;j++)
			{
				cost_matrix[i][j]=100;
				for(int p=0;p<k;p++)
				{
					if(list[p]==j) cost_matrix[i][j]=1;
					
					if(i==j) cost_matrix[i][j]=0;
				}
			}
		}
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				if(cost_matrix[i][j]==1) count=count+1;
			}
		}
	float density = (float)count/(20*19);
	return density;
	}


void Traffic_Matrix()
{
	int d[]={2,0,2,1,3,2,1,9,9,9,2,0,2,1,3,2,1,9,9,9};
	int temp;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			temp = (d[i]-d[j]);
			if(temp>0)
				traffic_matrix[i][j]=temp;
			else
				traffic_matrix[i][j]= -temp;
		}
	}

}

//FloydWarshall Algorithm for shortest path

int FloydWarshallAlgorithm()
{
	int edge_matrix[n][n];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			edge_matrix[i][j]=0;
		}
	}
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			for (int l=0;l<n;l++)
			{
				if ((cost_matrix[j][i]+cost_matrix[i][l]) < cost_matrix[j][l])
				{
					cost_matrix[j][l]=cost_matrix[j][i]+cost_matrix[i][l];
					edge_matrix[j][i]=1;
					edge_matrix[i][l]=1;
				}
				if(j==l)	cost_matrix[j][l]=0;
			}
		}
	}
	cout<<"Shortest Path Cost Matrix: ";
	for(int i=0;i<n;i++)
	{
		cout<<endl;
		for(int j=0;j<n;j++)
		{
			cout<<cost_matrix[i][j]<<" ";
		}
	}
	cout<<"\n\nEdge Matrix : ";
	for(int i=0;i<n;i++)
	{
		cout<<endl;
		for(int j=0;j<n;j++)
		{
			cout<<edge_matrix[i][j]<<" ";
		}
	}
}

int Cost()
{
	int cost=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cost_matrix[i][j]=cost_matrix[i][j]*traffic_matrix[i][j];
			cost += cost_matrix[i][j];
		}
	}
	return cost;
}


main()
{
	int k,cost=0;
	float density=0;
	for(int i=3; i<=14;i++){
		k=i;
		cout<<"\n\nFor k=" <<k;
		cout<<"\n\n";
		Traffic_Matrix();
		density=Cost_Matrix(k);
		FloydWarshallAlgorithm();
		cout<<"\n\nThe Density is : "<<density;
		cout<<"\nThe Cost is : "<<Cost();
		cout<<"\n";
	}

}
