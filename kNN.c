#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct
{
	float property_1;
	float property_2;
	char type;
}dataObj;

typedef struct
{
	dataObj *base;
	int size;
	int length;
}dataSet;

void initDataSet(dataSet *p_DS,int size)
{
	p_DS->base = (dataObj*)malloc(sizeof(dataObj) * size);
	if(NULL == p_DS->base)
	{
		printf("Malloc Failed\n");
		return;
	}
	p_DS->size = size;
	p_DS->length = 0;
}

void appendTestData(dataSet *p_DS)
{
	if(p_DS->size <= 0 || p_DS->length < 0)
	{
		printf("DATASET ERROR\n");
		return;
	}
	p_DS->base[0].property_1 = 1;
	p_DS->base[0].property_2 = 1.1;
	p_DS->base[0].type = 'A';	
	p_DS->base[1].property_1 = 1;
	p_DS->base[1].property_2 = 1;
	p_DS->base[1].type = 'A';
	p_DS->base[2].property_1 = 0;
	p_DS->base[2].property_2 = 0;
	p_DS->base[2].type = 'B';
	p_DS->base[3].property_1 = 0;
	p_DS->base[3].property_2 = 0.1;
	p_DS->base[3].type = 'B';
	p_DS->length = 4;
}

void quickSort(float *arr, dataObj *dataArr, int low, int high)
{
	int i = low;
	int j = high;
	float x = arr[i];
	dataObj tempObj = dataArr[i];
	if(i < j)
	{
		while(i < j)
		{
			while(i < j && arr[j] > x)
			{
				j--;
			}
			if(i < j)
			{
				arr[i] = arr[j];
				dataArr[i] = dataArr[j];
				i++;
			}

			while(i < j && arr[i] < x)
			{
				i++;
			}
			if(i < j)
			{
				arr[j] = arr[i];
				dataArr[j] = dataArr[i];
				j--;
			}
		}
		arr[i] = x;
		dataArr[i] = tempObj;
		quickSort(arr,dataArr,low,i-1);
		quickSort(arr,dataArr,i+1,high);
	}
}

float *calculateDist(dataSet *p_DS,dataObj inX)
{
	float *result = (float *)malloc(sizeof(float) * p_DS->length);
	float proValue_1 = inX.property_1;
	float proValue_2 = inX.property_2;
	float tempSum = 0;
	int i;
	
	for(i = 0;i < p_DS->length;i++)
	{
		proValue_1 = inX.property_1 - p_DS->base[i].property_1;
		proValue_2 = inX.property_2 - p_DS->base[i].property_2;
		proValue_1 *= proValue_1;
		proValue_2 *= proValue_2;
		result[i] = proValue_1 + proValue_2;
		result[i] = (float)sqrt(result[i]);
	}
	return result;
}

char classify(dataObj *arr, int k)
{
	char alphaSet[26] = {0};
	int max = 0;
	int mark = 0;
	int i;
	for(i = 0;i < k;i++)
	{
		alphaSet[arr[i].type - 'A']++;
	}

	for(i = 0;i < 26;i++)
	{
		if(max <= alphaSet[i])
		{
			max = alphaSet[i];
			mark = i;
		}
	}
	return ('A'+mark);
}

int main()
{
	float *result = NULL;
	char type = 'Z';
	int i;
	dataObj inX;
	dataSet *p_DS = (dataSet*)malloc(sizeof(dataSet));
	initDataSet(p_DS,4);
	appendTestData(p_DS);

	printf("Enter 2 properties (num1,num2) : ");
	scanf("%f,%f",&inX.property_1, &inX.property_2);
	result = calculateDist(p_DS,inX);
	for(i = 0;i < 4;i++)
	{
		printf("%f ",result[i]);
	}
	quickSort(result,p_DS->base,0,p_DS->length);
	type = classify(p_DS->base,3);
	for(i = 0;i < 4;i++)
	{
		printf("%c ",p_DS->base[i].type);
	}
	printf("The type is : %c\n",type);
	return 0;
}
