#include <limits.h>

#include "cyber_spaceship.h"

#define NULL ((void *)0) /* 포인터 초기화 */

const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length) 
{ 
	/* 안전 지역 중 가장 긴 것 중 마지막 것의 시작 주소를 반환
	   cab_length 값이 0이면 null을 반환하고 out_longest_safe area_length 0설정
	   가장 긴 안전지역 길이를 out_longest_area_length를 통해 반환 길이 단위 바이트
	   cluster_count가 0일 경우 cluster_start_location와 cluster_lengths의 값으로 null 전달 */
	if (cab_length == 0) {
		*out_longest_safe_area_length = 0;
		return NULL;
	} else if (cluster_count == 0) {
		size_t i;
		size_t safe_count = 0;
		cluster_start_locations = NULL;
		cluster_lengths = NULL;
		for (i = 0; i < cab_length; i++) {
			safe_count += 1;
		}
		*out_longest_safe_area_length = safe_count;
		return cab_start_location;
	} else {
		size_t i, j;
		int max = INT_MIN;
		char* longest_safe_location = NULL;
		char* longest_safe_zone_start_location = NULL;
		int safe_count = 0; /* 안전지역 카운트*/
		size_t overlap_count = 0; /* 겹침 카운트 */
		for (i = 0; i < cab_length; i++) { 
			for (j = 0; j < cluster_count; j++) { 
				if (cab_start_location + i < cluster_start_locations[j] || cab_start_location + i > cluster_start_locations[j] + cluster_lengths[j]) { /* 안 겹칠 때*/
					safe_count++;
					overlap_count = 0;
				} else { /* 겹칠 때 */
					overlap_count += 1;
				}
			}
			if (overlap_count % 2 == 0) { /* 겹치는 것이 짝수일 때 안전구역 + 1 연속된 짝수 가장 길었던 세이프존의 마지막 주소가 남음 */
				safe_count++;
				if (max < safe_count) {
					max = safe_count;
					longest_safe_location = (char *)cab_start_location + i;
				}
			} else { /* 홀수일 때 안전구역 길이 초기화 */
				safe_count = 0;
			}
		}
		longest_safe_zone_start_location = longest_safe_location - safe_count; /* 가장 긴 세이프존의 마지막 주소에서 가장 긴 안전거리를 빼면 세이프존 시작주소가 나옴 */
		return longest_safe_zone_start_location;
	}
	
}

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
{
	if (cluster_count == 0) {
		size_t i;
		size_t safe_zone_count = 0;
		double result = 0.0;
		cluster_lengths = NULL;
		cluster_start_locations = NULL;
		for (i = 0; i < cab_length; i++){
			safe_zone_count++;
		}
		result = (double)safe_zone_count / 10;
		return (int)result;
	} else { /* 소행성대를 항해하는데 걸리는 시간 위험지역 1분에 5바이트, 안전지역 1분에 10바이트 전체에서 위험지역만을 빼면 -> 안전지역을 이용*/
		size_t i, j;
		size_t danger_zone_length = 0;
		size_t overlap_count = 0;
		double result = 0.0;
		int safe_zone_length = 0;
		for (i = 0; i < cab_length; i++) {
			for (j = 0; j < cluster_count; j++) {
				if (cab_start_location + i < cluster_start_locations[j] || cab_start_location + i > cluster_start_locations[j] + cluster_lengths[j]) { /* 겹치지 않을 때*/
					overlap_count = 0; /* 안전지역 */
				} else { 
					overlap_count++;
				}
			}
			if (overlap_count % 2 == 1) { /* 홀수일 경우 */
				danger_zone_length++; /*위험지역 ++ */
			}
		}
		safe_zone_length = cab_length - danger_zone_length;
		result = (double)safe_zone_length / 10 + (double)danger_zone_length / 5;
		return (int)result;
	}
}

