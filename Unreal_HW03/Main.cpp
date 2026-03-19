#include "Inventory.h"


int main(void)
{
	Inventory<Item>* itemInventory = new Inventory<Item>();
	std::cout << "ItemCapacity : " << itemInventory->GetCapacity() << std::endl;
	std::cout << "Add 11 items" << std::endl;


	for (int i = 0; i < 11; ++i)
	{
		itemInventory->AddItem(Item("Item" + std::to_string(i), i * 100));
	}

	itemInventory->PrintAllItems();

	itemInventory->Resize(25);

	std::cout << "Add 15 items" << std::endl;


	for (int i = 0; i < 14; ++i)
	{
		itemInventory->AddItem(Item("Item" + std::to_string(i), i * 100+5));
	}

	itemInventory->PrintAllItems();
	
	std::cout << "Sorting " << itemInventory->GetSize() << " items" << std::endl;

	itemInventory->SortItems();
	itemInventory->PrintAllItems();

	Inventory<Item>* itemInventory2 = new Inventory<Item>(*itemInventory);
	itemInventory2->PrintAllItems();

	delete itemInventory;
	delete itemInventory2;
	itemInventory = nullptr;
	itemInventory2 = nullptr;

	return 0;
}