#pragma once
#include <iostream>
#include <string>

class Item {
private:
	std::string name_;
	int price_;
public:
	
	Item() : name_("noName"), price_(0) {}
	Item(const std::string name, int price) : name_(name), price_(price){}

	void PrintInfo() const {
		std::cout << "[이름: " << name_ << ", 가격: " << price_ << "]" << std::endl;
	}
	
	const std::string& GetName() const { return name_; }
	//const 멤버 함수 안에서는 name_가 const std::string 으로 취급되는데,
	//이를 std::string& (non-const 참조) 로 반환하려 하면 타입이 안 맞음 (const 객체 수정 가능성 생김)
	//반환 타입도 const.

	//아니면 복사 비용 있더라도 이렇게 반환 가능
	//std::string GetName() const { return name_; }

	int GetPrice() const { return price_; } //값 반환은 복사본 반환

};