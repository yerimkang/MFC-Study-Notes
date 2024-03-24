﻿// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//


#include <iostream>
#include <string.h>

using namespace std;
typedef unsigned int HANDLE;

struct HandleData {
	HANDLE h;
	char *p_string; //문자열을 관리할 포인터
};


//문자열을 관리하는 핸들
class HandleManager { // 핸들값만 보내줌
private:
	unsigned int m_max_count, m_gen_value;
	HandleData *mp_data;

public:
	HandleManager(unsigned int a_max_count = 50) {//매개변수를 안적으면 50으로 됨
		m_gen_value = 1; //핸들 생성 기준 값을 1로 설정
		m_max_count = a_max_count;
		mp_data = new HandleData[m_max_count];
		memset(mp_data, 0, sizeof(HandleData)*m_max_count);//0으로 채운다 (사용하고 있는지 아닌지 확인)
		cout << "핸들 관리자가 생성되었습니다!" << endl;//확인
	}

	~HandleManager() { //객체 파괴자
		HandleData *p = mp_data; //모두 삭제를 해야함

		for (unsigned int i = 0; i < m_max_count; i++) {
			if (p->h) delete[] p->p_string; //0이 아닌경우에만 할당
			p++;
		}
		delete[] mp_data; //할당했던 핸들 데이터도 삭제
		cout << "핸들 관리자 관리하던 문자열을 모두 제거했습니다!" << endl;
	}

	HANDLE InsertString(const char *ap_string) { //문자열을 추가할 수 있게 하기
		HandleData *p = mp_data;//시작 주소를 p가 받았다
		unsigned int i;
		//아직 핸들 값이 사용되지 않은 공간을 찾는다
		for (i = 0; i < m_max_count; i++) {
			if (p->h == 0) break;
			p++;
		}
		if (i < m_max_count) {
			p->h = m_gen_value++; //자동으로 증가하면서 일반 번호를 하나씩 줌
			int len = strlen(ap_string) + 1;
			p->p_string = new char[len];
			memcpy(p->p_string, ap_string, len); //문자열 복사
			cout << p->p_string << ":문자열 추가!!" << endl;
			return p->h; //핸들값
		}
		//핸들 저장공간이 부족한 경우!
		cout << "더 이상 문자열을 추가할 수 없습니다!" << endl;
		return 0xFFFFFFFF;
	}

	void PrintString(HANDLE ah_string) {

		HandleData *p = mp_data;

		for (unsigned int i = 0; i < m_max_count; i++) {
			if (p->h == ah_string) {
				//일치하는 핸들이 있으면 출력!
				cout << p->p_string << endl;
				return;
			}
			p++;
		}
		cout << "유효하지 않은 핸들 값을 사용했습니다!" << endl;
	}

	void DeleteString(HANDLE ah_string) {
		HandleData *p = mp_data;

		for (unsigned int i = 0; i < m_max_count; i++) {
			if (p->h == ah_string) {
				cout << p->p_string << ":삭제!!" << endl;
				delete[] p->p_string;
				p->h = 0;
				return;
			}
			p++;
		}
		cout << "유효하지 않은 핸들 값을 사용했습니다!" << endl;
	}
};


int main()
{
	HandleManager str_list;//인자를 안적으면 50 

	HANDLE h_str = str_list.InsertString("Hello~ tipsware!!");
	if (h_str != 0xFFFFFFFF) {
		str_list.PrintString(h_str);
		str_list.DeleteString(h_str);
	}
	//제거 확인!
	str_list.PrintString(h_str);

	return 0;
}