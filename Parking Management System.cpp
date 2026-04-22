#include<iostream>
#include<string>
#include<cmath>
#include<fstream>
using namespace std;
class parking_block
{
private:
	string** slot;
	int* slots_per_row;
	int total_rows;
	float x_coordinate;
	float y_coordinate;
public:
	parking_block()
	{
		slot = nullptr;
		slots_per_row = nullptr;
		total_rows = 0;
		x_coordinate = 0;
		y_coordinate = 0;
	}
	parking_block(int num_rows)
	{
		total_rows = num_rows;
		slots_per_row = new int[total_rows];
		slot = new string * [total_rows];
		for (int i = 0; i < total_rows; i++)
		{
			slot[i] = nullptr;
		}
		x_coordinate = 0;
		y_coordinate = 0;
	}
	parking_block(const parking_block& p)
	{
		total_rows = p.total_rows;
		x_coordinate = p.x_coordinate;
		y_coordinate = p.y_coordinate;
		slots_per_row = new int[total_rows];
		slot = new string * [total_rows];
		for (int i = 0; i < total_rows; i++)
		{
			slots_per_row[i] = p.slots_per_row[i];
			if (p.slot[i] != nullptr)
			{
				slot[i] = new string[slots_per_row[i]];
				for (int j = 0; j < slots_per_row[i]; j++)
				{
					slot[i][j] = p.slot[i][j];
				}
			}
			else slot[i] = nullptr;
		}
	}
	parking_block(parking_block&& p)
	{
		total_rows = p.total_rows;
		slot = p.slot;
		slots_per_row = p.slots_per_row;
		x_coordinate = p.x_coordinate;
		y_coordinate = p.y_coordinate;
		p.slot = nullptr;
		p.slots_per_row = nullptr;
		p.total_rows = 0;
		p.x_coordinate = 0;
		p.y_coordinate = 0;
	}
	parking_block& operator=(const parking_block& p)
	{
		if (this != &p)
		{
			if (slot != nullptr)
			{
				for (int i = 0; i < total_rows; i++)
				{
					delete[]slot[i];
				}
				delete[]slot;
			}
			if (slots_per_row != nullptr)
			{
				delete[] slots_per_row;
			}
			total_rows = p.total_rows;
			x_coordinate = p.x_coordinate;
			y_coordinate = p.y_coordinate;
			slots_per_row = new int[total_rows];
			slot = new string * [total_rows];
			for (int i = 0; i < total_rows; i++)
			{
				slots_per_row[i] = p.slots_per_row[i];
				if (p.slot[i] != nullptr)
				{
					slot[i] = new string[slots_per_row[i]];
					for (int j = 0; j < slots_per_row[i]; j++)
					{
						slot[i][j] = p.slot[i][j];
					}
				}
				else slot[i] = nullptr;
			}
		}
		return *this;
	}
	parking_block& operator=(parking_block&& p)
	{
		if (this != &p)
		{
			if (slot != nullptr)
			{
				for (int i = 0; i < total_rows; i++)
				{
					delete[]slot[i];
				}
				delete[]slot;
			}
			if (slots_per_row != nullptr)
			{
				delete[] slots_per_row;
			}
			total_rows = p.total_rows;
			slot = p.slot;
			slots_per_row = p.slots_per_row;
			x_coordinate = p.x_coordinate;
			y_coordinate = p.y_coordinate;
			p.slot = nullptr;
			p.slots_per_row = nullptr;
			p.total_rows = 0;
			p.x_coordinate = 0;
			p.y_coordinate = 0;
		}
		return*this;
	}
	void add_rows(int n)
	{
		int* temp = new int[total_rows + n];
		for (int i = 0; i < total_rows; i++)
		{
			temp[i] = slots_per_row[i];
		}
		for (int i = total_rows; i < total_rows + n; i++)
		{
			temp[i] = 0;
		}
		delete[] slots_per_row;
		string** new_slot = new string * [total_rows + n];
		for (int i = 0; i < total_rows; i++)
		{
			new_slot[i] = slot[i];
		}
		for (int i = total_rows; i < total_rows + n; i++)
		{
			new_slot[i] = nullptr;
		}
		delete[]slot;
		slots_per_row = temp;
		slot = new_slot;
		total_rows += n;
	}
	//1)
	void add_slots(int row_num, int n)
	{
		slot[row_num] = new string[n];
		for (int i = 0; i < n; i++)
		{
			slot[row_num][i] = "empty";
		}
		slots_per_row[row_num] = n;
	}
	//2)
	void park_car(int row_num, int slot_num, string vehicle_num)
	{
		if (row_num < 0 || row_num >= total_rows)
		{
			cout << "The cark can not be parked at this " << row_num + 1 << " row" << endl;
			return;
		}
		if (slot_num < 0 || slot_num >= slots_per_row[row_num])
		{
			cout << "The cark can not be parked at this " << slot_num + 1 << " slot" << endl;
			return;
		}
		if (slot[row_num][slot_num] != "empty")
		{
			cout << "There is no empty parking" << endl;
			return;
		}
		slot[row_num][slot_num] = vehicle_num;
		cout << "The cark has been sucessfully parked at row " << row_num + 1 << " and slot " << slot_num + 1 << endl;

	}
	//3)
	void remove_car(int row_num, int slot_num)
	{
		if (row_num < 0 || row_num >= total_rows)
		{
			cout << "The cark can not be removed from this " << row_num + 1 << " row" << endl;
			return;
		}
		if (slot_num < 0 || slot_num >= slots_per_row[row_num])
		{
			cout << "The cark can not be removed from this " << slot_num + 1 << " slot" << endl;
			return;
		}
		if (slot[row_num][slot_num] == "empty")
		{
			cout << "The slot is already empty" << endl;
			return;
		}
		slot[row_num][slot_num] = "empty";
		cout << "The cark has been sucessfully removed from row " << row_num + 1 << " and slot " << slot_num + 1 << endl;

	}
	//4)
	void display_block()
	{
		cout << "\nThe block at (" << x_coordinate << " , " << y_coordinate << " )" << endl;
		for (int i = 0; i < total_rows; i++)
		{
			cout << " \nRow: " << i + 1 << ": ";
			for (int j = 0; j < slots_per_row[i]; j++)
			{
				cout << slot[i][j] << " ";
			}
			cout << endl;
		}
	}
	//5)
	void resize_slot(int row_num, int new_size)
	{
		if (row_num < 0 || row_num >= total_rows)
		{
			cout << "The row number is invalid" << endl;
			return;
		}
		if (new_size <= 0)
		{
			cout << "The new size is invalid" << endl;
			return;
		}
		if (new_size > slots_per_row[row_num])
		{
			string* temp = new string[new_size];
			for (int i = 0; i < slots_per_row[row_num]; i++)
			{
				temp[i] = slot[row_num][i];
			}
			for (int i = slots_per_row[row_num]; i < new_size; i++)
			{
				temp[i] = "empty";
			}
			delete[] slot[row_num];
			slot[row_num] = temp;
			slots_per_row[row_num] = new_size;

		}
		else
		{
			string* temp = new string[new_size];
			for (int i = new_size; i < slots_per_row[row_num]; i++)
			{
				if (slot[row_num][i] != "empty")
				{
					cout << "The slots " << i + 1 << " is occupied." << endl;
					delete[] temp;
					return;
				}
			}
			for (int i = 0; i < new_size; i++)
			{
				temp[i] = slot[row_num][i];

			}
			delete[] slot[row_num];
			slot[row_num] = temp;
			slots_per_row[row_num] = new_size;
		}
	}
	//6)
	int* search_vehicle(string vehicle_num)
	{
		for (int i = 0; i < total_rows; i++)
		{
			for (int j = 0; j < slots_per_row[i]; j++)
			{
				if (slot[i][j] == vehicle_num)
				{
					int* result = new int[2];
					result[0] = i;
					result[1] = j;
					return result;
				}
			}
		}
		return nullptr;
	}
	//7)
	void empty_row(int row_num)///no
	{
		if (row_num < 0 || row_num >= total_rows)
		{
			cout << "It is an invalid row" << endl;
			return;
		}
		for (int i = 0; i < slots_per_row[row_num]; i++)
		{
			slot[row_num][i] = "empty";
		}
	}
	//8)
	void empty_block() //no
	{
		for (int i = 0; i < total_rows; i++)
		{
			empty_row(i);
		}
	}
	//9)
	void transfer_vehicles(parking_block& source)
	{
		empty_block();
		if (source.total_rows > total_rows)
		{
			add_rows(source.total_rows - total_rows);
		}
		if (source.total_rows < total_rows)
		{
			for (int i = source.total_rows; i < total_rows; i++)
			{
				delete[] slot[i];
				slot[i] = nullptr;
			}
			total_rows = source.total_rows;
		}
		for (int i = 0; i < total_rows; i++)
		{
			delete[] slot[i];
			slot[i] = nullptr;
		}
		for (int i = 0; i < total_rows; i++)
		{
			add_slots(i, source.slots_per_row[i]);
		}
		for (int i = 0; i < total_rows; i++)
		{
			for (int j = 0; j < slots_per_row[i]; j++)
			{
				slot[i][j] = source.slot[i][j];// copying use ho rahi hai
			}
		}
	}
	float get_x()
	{
		return x_coordinate;
	}
	float get_y()
	{
		return y_coordinate;
	}
	void set_coordinates(float x, float y)
	{
		x_coordinate = x;
		y_coordinate = y;

	}
	int get_total_rows()
	{
		return total_rows;
	}
	int get_slots_per_row(int row)
	{
		return slots_per_row[row];
	}
	string get_slot(int rows, int cols)
	{
		return slot[rows][cols];
	}
	void merge_vehicles(parking_block& source)
	{
		int old_rows = total_rows;
		bool is_empty;
		if (source.total_rows > total_rows)
		{
			add_rows(source.total_rows - total_rows);
			for (int i = old_rows; i < source.total_rows; i++)
			{
				add_slots(i, source.slots_per_row[i]);
			}
		}
		for (int i = 0; i < total_rows; i++)
		{
			for (int j = 0; j < source.slots_per_row[i]; j++)
			{
				if (source.slot[i][j] != "empty")
				{
					is_empty = false;
					for (int k = 0; k < slots_per_row[i]; k++)
						if (slot[i][k] == "empty")
						{
							is_empty = true;
							break;
						}
					if (is_empty == false)
					{
						resize_slot(i, slots_per_row[i] + 1);
					}

					for (int k = 0; k < slots_per_row[i]; k++)
					{
						if (slot[i][k] == "empty")
						{
							slot[i][k] = source.slot[i][j];
							break;
						}
					}
				}
			}

		}
	}
	~parking_block()
	{
		for (int i = 0; i < total_rows; i++)
		{
			delete[] slot[i];
		}
		delete[] slot;
		delete[] slots_per_row;
	}
};
//10)
parking_block* load_ParkingLot(string filename, int& total_blocks)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "File could not be opened!" << endl;
		return nullptr;
	}
	int num_of_rows;
	int num_of_slots;
	file >> total_blocks;
	parking_block* block = new parking_block[total_blocks];//yeh ek array hai parking_block objects ki, har object ek block hai apna data khud manage kerta hai
	for (int i = 0; i < total_blocks; i++)
	{
		file >> num_of_rows;
		block[i].add_rows(num_of_rows);
		for (int j = 0; j < num_of_rows; j++)
		{
			file >> num_of_slots;
			block[i].add_slots(j, num_of_slots);
		}
	}
	file.close();
	return block;
}
//11)
float distance(float xslot, float yslot, float xblock, float yblock) {
	float delta_x = xslot - xblock;
	float delta_y = yslot - yblock;
	return sqrt((delta_x * delta_x) + (delta_y * delta_y));
}
void smart_allocate(string vehicle_num, int desired_block, parking_block* block, int total_blocks)
{
	int min_dist = -1;
	int chosen_block = -1, chosen_row = -1, chosen_slot = -1;
	for (int i = 0; i < total_blocks; i++)
	{
		int rows = block[i].get_total_rows();
		for (int j = 0; j < rows; j++)
		{
			int slots = block[i].get_slots_per_row(j);
			for (int k = 0; k < slots; k++)
			{
				string result = block[i].get_slot(j, k);
				if (result == "empty")
				{
					float x_slot = block[i].get_x() + (k * 8);
					float y_slot = block[i].get_y() + (j * 16);
					float dist = distance(x_slot, y_slot, block[desired_block].get_x(), block[desired_block].get_y());
					if (min_dist == -1 || dist < min_dist)
					{
						min_dist = dist;
						chosen_block = i;
						chosen_row = j;
						chosen_slot = k;
					}
				}
			}
		}
	}
	if (chosen_block != -1)
	{
		block[chosen_block].park_car(chosen_row, chosen_slot, vehicle_num);
		cout << "Vehicle parked at Block " << chosen_block + 1 << " Row " << chosen_row + 1 << " Slot " << chosen_slot + 1 << endl;
	}
	else
		cout << "There is no slot avaliable" << endl;
}
//12)
void load_block_coordinates(string file_name, parking_block* block, int total_blocks)
{
	float x, y;
	ifstream file(file_name);
	if (!file.is_open())
	{
		cout << "Can not open file" << endl;
		return;
	}
	for (int i = 0; i < total_blocks; i++)
	{
		file >> x;
		file >> y;
		block[i].set_coordinates(x, y);
	}
	file.close();
}
int main()
{
	parking_block* blocks = nullptr;
	int total_blocks = 0;
	int choice;
	do
	{
		cout << "\t\t\t\t\t\t PARKING" << endl;
		cout << "\t\t\t\t0) Initialize(manual or from file)" << endl;
		cout << "\t\t\t\t1) Park a vehicle" << endl;
		cout << "\t\t\t\t2) Remove a vehicle" << endl;
		cout << "\t\t\t\t3) Display full parking system" << endl;
		cout << "\t\t\t\t4) Resize slots in a row" << endl;
		cout << "\t\t\t\t5) Search for a vehicle" << endl;
		cout << "\t\t\t\t6) empty a row" << endl;
		cout << "\t\t\t\t7) empty a block " << endl;
		cout << "\t\t\t\t8) Transfer vehicles between blocks" << endl;
		cout << "\t\t\t\t9) Smart allocate a vehicle" << endl;
		cout << "\t\t\t\t10) Load block coordinates from file" << endl;
		cout << "\t\t\t\t11) Merge vehicles" << endl;
		cout << "\t\t\t\t12) Exit " << endl;
		cout << "\t\t\t\t <--------------------------> " << endl;
		while (!(cin >> choice))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input! Enter a number: ";
		}
		if (choice != 0 && choice != 12 && blocks == nullptr)
		{
			cout << "\nPlease initialize the system first. Press 0" << endl;
			continue;
		}
		switch (choice)
		{
		case 0:
		{
			int init_choice;
			cout << "1) Enter manually" << endl;
			cout << "2) Load from file" << endl;
			cout << "Enter choice: ";
			while (!(cin >> init_choice) || (init_choice != 1 && init_choice != 2))
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid! Enter 1 or 2: ";
			}
			if (init_choice == 1)
			{
				cout << "\nEnter number of blocks: ";
				while (!(cin >> total_blocks) || total_blocks <= 0)
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid! Enter positive number: ";
				}
				blocks = new parking_block[total_blocks];
				for (int i = 0; i < total_blocks; i++)
				{
					int num_rows;
					cout << " \nEnter rows for block " << i + 1 << ": ";
					while (!(cin >> num_rows) || num_rows <= 0)
					{
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "Invalid! Enter positive number: ";
					}
					blocks[i].add_rows(num_rows);
					for (int j = 0; j < num_rows; j++)
					{
						int num_slots;
						cout << "  Enter slots for row " << j + 1 << ": ";
						while (!(cin >> num_slots) || num_slots <= 0)
						{
							cin.clear();
							cin.ignore(1000, '\n');
							cout << "Invalid! Enter positive number: ";
						}
						blocks[i].add_slots(j, num_slots);
					}
					float x, y;
					cout << "\nEnter x coordinate for block " << i + 1 << ": ";
					cin >> x;
					cout << "Enter y coordinate for block " << i + 1 << ": ";
					cin >> y;
					blocks[i].set_coordinates(x, y);
				}
				cout << "\nThe system has been initialized" << endl;
			}
			else
			{
				string filename;
				cout << "\nEnter filename: ";
				cin >> filename;
				blocks = load_ParkingLot(filename, total_blocks);
				if (blocks == nullptr)
					cout << "Failed to load file!" << endl;
				else
					cout << "System loaded!" << endl;
			}
			break;
		}
		case 1:
		{
			int b, r, s;
			string v;
			cout << "Enter block number: ";
			while (!(cin >> b) || b < 1 || b > total_blocks)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid block! Enter 1-" << total_blocks << ": ";
			}
			cout << " Enter row number: "; cin >> r;
			cout << "  Enter slot number: "; cin >> s;
			cout << "   Enter vehicle number: "; cin >> v;
			blocks[b - 1].park_car(r - 1, s - 1, v);
			break;
		}

		case 2:
		{
			int b, r, s;
			cout << "Enter block number: ";
			while (!(cin >> b) || b < 1 || b > total_blocks)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid block! Enter 1-" << total_blocks << ": ";
			}
			cout << " Enter row number: "; cin >> r;
			cout << "  Enter slot number: "; cin >> s;
			blocks[b - 1].remove_car(r - 1, s - 1);
			break;
		}

		case 3:
		{
			for (int i = 0; i < total_blocks; i++)
				blocks[i].display_block();
			break;
		}

		case 4:
		{
			int b, r, size;
			cout << "Enter block number: ";
			while (!(cin >> b) || b < 1 || b > total_blocks)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid block! Enter 1-" << total_blocks << ": ";
			}
			cout << " Enter row number: "; cin >> r;
			cout << "  Enter new size: "; cin >> size;
			blocks[b - 1].resize_slot(r - 1, size);
		}
		break;

		case 5:
		{
			string v;
			cout << "Enter vehicle number: "; cin >> v;
			bool found = false;
			for (int i = 0; i < total_blocks; i++)
			{
				int* result = blocks[i].search_vehicle(v);
				if (result != nullptr)
				{
					cout << "Found at Block " << i + 1 << " Row " << result[0] + 1 << " Slot " << result[1] + 1 << endl;
					delete[] result;
					found = true;
					break;
				}
			}
			if (!found)
				cout << "\nThere is no such vehicle" << endl;

			break;
		}

		case 6:
		{
			int b, r;
			cout << "Enter block number: ";
			while (!(cin >> b) || b < 1 || b > total_blocks)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid block! Enter 1-" << total_blocks << ": ";
			}
			cout << " Enter row number: "; cin >> r;
			blocks[b - 1].empty_row(r - 1);
			break;
		}

		case 7:
		{
			int b;
			cout << "Enter block number: ";
			while (!(cin >> b) || b < 1 || b > total_blocks)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid block! Enter 1-" << total_blocks << ": ";
			}
			blocks[b - 1].empty_block();
			break;
		}
		case 8:
		{
			int b1, b2;
			cout << "Enter destination block: ";
			while (!(cin >> b1) || b1 < 1 || b1 > total_blocks)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid block! Enter 1-" << total_blocks << ": ";
			}
			cout << "Enter source block: ";
			while (!(cin >> b2) || b2 < 1 || b2 > total_blocks)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid block! Enter 1-" << total_blocks << ": ";
			}
			blocks[b1 - 1].transfer_vehicles(blocks[b2 - 1]);
			break;
		}

		case 9:
		{
			string v;
			int b;
			cout << "Enter vehicle number: "; cin >> v;
			cout << "Enter desired block: ";
			while (!(cin >> b) || b < 1 || b > total_blocks)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid block! Enter 1-" << total_blocks << ": ";
			}
			smart_allocate(v, b - 1, blocks, total_blocks);
			break;
		}

		case 10:
		{
			string filename;
			cout << "Enter coordinates filename: ";
			cin >> filename;
			load_block_coordinates(filename, blocks, total_blocks);
			break;
		}


		case 11:
		{
			int b1, b2;
			cout << "Enter destination block: ";
			while (!(cin >> b1) || b1 < 1 || b1 > total_blocks)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid block! Enter 1-" << total_blocks << ": ";
			}
			cout << "Enter source block: ";
			while (!(cin >> b2) || b2 < 1 || b2 > total_blocks)
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid block! Enter 1-" << total_blocks << ": ";
			}
			blocks[b1 - 1].merge_vehicles(blocks[b2 - 1]);
			break;
		}

		case 12:
		{
			cout << "The parking has been exited. " << endl;
			break;
		}

		default:
			cout << "Invalid choice!" << endl;
		}
	} while (choice != 12);
	delete[] blocks;
	return 0;
}
//one block use hoga tou member function 
// sab blocks use honge tou free function