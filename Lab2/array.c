#include "array.h"
#include <limits.h>

int get_index_of(const int numbers[], const size_t element_count, const int num) 
{
	size_t i;
	int index = 0;
	for (i = 0; i < element_count; i++) 
	{
		if (numbers[i] == num) 
		{
			index = i;
			return index;
		}
	}
	return -1;
}

int get_last_index_of(const int numbers[], const size_t element_count, const int num) 
{
	int i;
	int index = 0;
	for (i = (int)element_count - 1; i >= 0; i--) 
	{
		if (numbers[i] == num) 
		{
			index = i;
			return index;
		}
	}
	return -1;
}

int get_max_index(const int numbers[], const size_t element_count) 
{
	size_t i;
	int max_index;
	int max = INT_MIN+1;
	if (element_count == 0) 
	{
		return -1;
	}
	for (i = 0; i < element_count; i++) 
	{
		if (numbers[i] > max) 
		{
			max = numbers[i];
			max_index = i;
		}
	}
	return max_index;
}

int get_min_index(const int numbers[], const size_t element_count) 
{
	size_t i;
	size_t count = 0;
	int min_index;
	int min = INT_MAX-1;
	for (i = 0; i < element_count; i++) 
	{
		if (numbers[i] == INT_MAX || numbers[i] == INT_MIN) 
		{
			count += 1;
		}
	}
	if (count == element_count) 
	{
		return -1;
	}
	for (i = 0; i < element_count; i++) 
	{
		if (numbers[i] < min) 
		{
			min = numbers[i];
			min_index = i;
		}
	}
	return min_index;
}

int is_all_positive(const int numbers[], const size_t element_count) 
{
	size_t i;
	size_t count = 0;
	for (i = 0; i < element_count; i++)
	{
		if (numbers[i] == INT_MIN || numbers[i] == INT_MAX)
		{
			count++;
		}
	}
	if (count == element_count)
	{
		return FALSE;
	}
	else
	{
		count = 0;
	}
	for (i = 0; i < element_count; i++) 
	{
		if (numbers[i] >= 0)
		{
			count++;
		}
		else if (numbers[i] < 0)
		{
			return FALSE;
		}
	}
	if (count == element_count)
	{
		return TRUE;
	}

	return 0;
}

int has_even(const int numbers[], const size_t element_count) 
{
	size_t i;
	for (i = 0; i < element_count; i++) 
	{
		if (numbers[i] % 2 == 0) 
		{
			return TRUE;
		}
		else 
		{
			continue;
		}
	}
	return FALSE;
}

int insert(int numbers[], const size_t element_count, const int num, const size_t pos) 
{
	int i;

	if(pos >= 0 && pos <= element_count)
	{
		for (i = (int)element_count - 1; i >= (int)pos; i--)
		{
			numbers[i + 1] = numbers[i];
		}
		numbers[pos] = num;
		return TRUE;
	}
	else
	{
		return FALSE;
	}

	return 0;
}

int remove_at(int numbers[], const size_t element_count, const size_t index) 
{
	size_t i;
	size_t count = 0;
	if ((int)index > (int)element_count - 1 || index < 0) 
	{
		return FALSE;
	}
	for (i = 0; i < element_count; i++) 
	{
		if (numbers[i] == INT_MIN || numbers[i] == INT_MAX) 
		{
			count += 1;
		}
	}
	if (count == element_count) 
	{
		return FALSE;
	}
	for (i = index + 1; i < element_count; i++) 
	{
		numbers[i - 1] = numbers[i];
	}
	numbers[element_count-1] = INT_MIN;
	return TRUE;
}
