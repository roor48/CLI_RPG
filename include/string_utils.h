#pragma once

#define INT_FORMAT_SIZE 15

/* 
 * @brief 문자열을 소문자로 변환
 * 
 * @param *str 변환할 문자열 포인터
 */
void toLowerCase(char* str);

/* 
 * @brief 숫자 문자열인지 확인
 * 
 * @param *str 확인할 문자열 포인터
 * 
 * @return 숫자 문자열이면 1 아니면 0
 */
int isDigitString(char* str);

/* 
 * @brief 숫자에 천 단위 구분 기호 추가
 * 
 * 한 번에 최대 4번 호출
 * static한 변수 이므로 free() 불필요
 * 
 * @param num 변환할 숫자
 * 
 * @return 포맷된 문자열
 */
char* formatNum(int num);
