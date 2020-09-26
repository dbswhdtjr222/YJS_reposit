#include <limits.h>
#include "cyber_spaceship.h"

const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length)
{
    if (cab_length == 0) { /* cab의 길이가 0일 때*/
        /* out_longest_safe_area 는 포인터 size_t를 가리키는 */
        *out_longest_safe_area_length = 0; /* 역참조 해서 값을 0으로 설정 */
        return NULL;
    } else if (cluster_count == 0) { /* cluster의 개수가 0일 때*/
        size_t i;
        size_t safe_count = 0;
        cluster_start_locations = NULL;
        cluster_lengths = NULL;

        for (i = 0; i < cab_length; i++) { /*모두 안전 구역 */
            safe_count++;
        }
        *out_longest_safe_area_length = safe_count;
        return cab_start_location;
    } else { /* 클러스터가 있고 cab길이가 0이 아닐 때*/
        size_t i;
        size_t j;
        size_t safe_count = 0; /*안전거리 카운트*/
        size_t overlap_count = 0; /*클러스터 겹침 카운트*/
        int max = INT_MIN;
        size_t index_info = 0;
        for (i = 0; i < cab_length; i++) { /* cab길이 만큼 하나씩 탐색*/
            for (j = 0; j < cluster_count; j++) {
                if (cab_start_location + i >= cluster_start_locations[j] && cab_start_location + i < cluster_start_locations[j] + cluster_lengths[j]) { /* 겹칠 때 */
                    overlap_count++;
                }
            }
            if (overlap_count % 2 == 0) { /* 겹치는게 짝수 개*/
                safe_count++;
                if (max <= (int)safe_count) { /* 안전거리 최댓값 구하기 */
                    max = safe_count;
                    *out_longest_safe_area_length = (size_t)max;
                    index_info = i;
                }
            } else { /*홀수가 나오면 안전거리 카운트 0 */
                safe_count = 0;
            }
            overlap_count = 0; /* 다음 위치의 겹침을 확인 하기 위해 */
        }
        return cab_start_location + (index_info + 1) - max;
    }
}

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
{
    if (cluster_count == 0) {/* 소행성이 없을 때 */
        size_t i;
        size_t safe_count = 0; /*안전구역 카운트*/
        double result = 0; /* double로 계산 */
        for (i = 0; i < cab_length; i++) {
            safe_count++; /*소행성 x 다 안전구역 */
        }
        result = (double)safe_count / 10;
        result = result + 0.5;
        return (int)result;
    } else { /*소행성 있을 때 */
        size_t i;
        size_t j;
        size_t danger_count = 0;
        size_t overlap_count = 0;
        size_t safe_zone_length = 0;
        double result = 0.0;
        for (i = 0; i < cab_length; i++) {
            for (j = 0; j < cluster_count; j++) {
                if (cab_start_location + i >= cluster_start_locations[j] && cab_start_location + i < cluster_start_locations[j] + cluster_lengths[j]) { /* 겹칠 때 */
                    overlap_count++;
                }
            }
            if (overlap_count % 2 == 1) { /*겹치는 게 홀수개*/
                danger_count++; /*위험지역 카운트 */
            }
            overlap_count = 0;
        }
        safe_zone_length = cab_length - danger_count;
        result = (double)safe_zone_length / 10 + (double)danger_count / 5;
        result = result + 0.5; /*반올림 구현*/
        return (int)result;
    }
}

