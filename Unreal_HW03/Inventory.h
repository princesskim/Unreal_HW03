//Inventory.h

#pragma once
#include <iostream>
#include <algorithm>
#include "Item.h"


//아이템, 무기, 포션 등 어떤 타입이든 담을 수 있도록 템플릿 클래스 선언
template <typename T>
class Inventory
{
private:
	T* pItems_;
	int capacity_;
	int size_;
	
public:
	Inventory(int capacity = 10) : capacity_((capacity <= 0) ? 1 : capacity), size_(0) {
		//초기화 리스트에서는 이름이 같아도 this-> 없어도 됨.
		//함수 안에서 지역 변수와 멤버 변수 이름이 겹칠 때는 this-> 필요

		pItems_ = new T[capacity_]; //배열 생성 시 [] 사용 //힙 메모리 할당
		//new T[n] 은 n개의 객체를 즉시 생성하므로 각 원소마다 기본 생성자가 필요
		//사용자 정의 생성자를 하나라도 만들면 기본 생성자는 자동 생성되지 않음
		//따라서 기본 생성자를 직접 정의해야 함
		//=> T 자리에 들어갈 아이템 클래스로 가서 추가해주자.
	} 
	
	// 복사 생성자 (컴파일러가 자동으로 만드는 암시적 복사 생성자는 얕은 복사를 함)
	// 깊은 복사를 위해 pItems_를 하나씩 옮겨담아야 함.
	Inventory(const Inventory<T>& other) {
		capacity_ = other.capacity_;
		size_ = other.size_;
		pItems_ = new T[capacity_];
		for (int i = 0; i < size_; ++i) {
			pItems_[i] = other.pItems_[i];
		}
		std::cout << "인벤토리 복사 완료" << std::endl;
	}

	~Inventory() {
		delete[] pItems_; //힙 메모리 해제
		pItems_ = nullptr;
	}
	
	void AddItem(const T& item);

	void RemoveLastItem();

	int GetSize() const { return size_; }

	int GetCapacity() const { return capacity_; }

	void PrintAllItems() const;

	void Assign(const Inventory<T>& other);

	void Resize(int newCapacity);

	void SortItems();

};


template <typename T>
void Inventory<T>::AddItem(const T& item) {
	if (capacity_ == size_) {
		Resize(capacity_*2);
	}
	pItems_[size_] = item; //pItems_은 포인터
	++size_;
}


template <typename T>
void Inventory<T>::RemoveLastItem() {
	if (size_ == 0) {
		std::cout << "인벤토리가 비어있습니다." << std::endl;
	}
	else {
		--size_;
	}
}


template <typename T>
void Inventory<T>::PrintAllItems() const {
	if (size_ == 0) {
		std::cout << "인벤토리가 비어있습니다." << std::endl;
	}
	else {
		for (int i = 0;i<size_;++i) {
			(pItems_[i]).PrintInfo();
		}
	}
}

template <typename T>
void Inventory<T>::Assign(const Inventory<T>& other) { //self-assign에 대한 대비 추가
	
	if (&other != this) { //객체 other의 주소가 self의 주소인지(== 포인터 this)
		delete[] pItems_; //기존꺼 해제

		capacity_ = other.capacity_;
		size_ = other.size_;
		pItems_ = new T[capacity_];
		for (int i = 0; i < size_; ++i) {
			pItems_[i] = other.pItems_[i];
		}
		std::cout << "인벤토리 복사 완료" << std::endl;
	
	}
	
}

template <typename T>
void Inventory<T>::Resize(int newCapacity) {
	std::cout << "capacity: " << capacity_ <<" -> " << newCapacity << std::endl;
	capacity_ = newCapacity;
	T* temp = new T[capacity_]; //temp는 지역 포인터 변수
	for (int i = 0; i < size_; ++i) {
		temp[i] = pItems_[i];
	}
	delete[] pItems_;
	pItems_ = temp; //함수 종료 후에는 temp가 사라지고, pItems_만 힙 메모리를 가리킴
}


//전역 템플릿 함수
//일반 전역 함수라면 함수 구현은 .cpp파일에서 해야하지만
//템플릿 함수이기 때문에 헤더파일에서 구현까지 다 해야 함.
template <typename T>
bool compareItemsByPrice(const T& a, const T& b) {//오름차순 비교함수
	//함수 안에서 a는 const로 취급되기 때문에 
	//함수 안에서 a를 통해 호출하는 함수는 const 멤버 함수여야 함. (const 함수 아니면 에러)
	//const가 아닌 멤버 함수는 객체를 수정할 가능성이 있다고 간주되어 호출 불가.
	return a.GetPrice() < b.GetPrice();
}


template <typename T>
void Inventory<T>::SortItems() {
	std::sort(pItems_, pItems_ + size_, compareItemsByPrice<T>);
}
