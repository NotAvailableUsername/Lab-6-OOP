#include "App.h"

Menu::Menu(){
	this->adminRepo = AdminRepo();
	this->userRepo = UserRepo();
}

void Menu::startMenu(){
	bool run = true;

	while (run){
		int mode;
		cout << "1.Administrator mode   2.User mode   3.Exit" << endl;
		cout << "Choose your mode: ";
		cin >> mode;
		if (mode == 1){
			int adminMode = 0;
			while (adminMode != 6){
				cout << "Administrator:" << endl;
				cout << "1. Add film" << endl;
				cout << "2. Delete film" << endl;
				cout << "3. Update film" << endl;
				cout << "4. Display filme" << endl;
				cout << "5. Deschidere fisier" << endl;
				cout << "6. Exit" << endl;
				cout << "Option: " << endl;
				cin >> adminMode;
				if (adminMode == 1){
					string title, genre, year, likes, link, blank;
					cout << "Title: ";
					getline(cin, blank);
					getline(cin, title);
					cout << "Genre: ";
					getline(cin, genre);
					cout << "Year: ";
					cin >> year;
					cout << "Likes: ";
					cin >> likes;
					cout << "Trailer link: ";
					getline(cin, blank);
					getline(cin, link);

					Movie m(title, genre, year, likes, link);
					adminRepo.create_csv(m);
				}
				else if (adminMode == 2){
					adminRepo.delete_csv();
				}
				else if (adminMode == 3){
					adminRepo.update_csv();
				}
				else if (adminMode == 4){
					adminRepo.read_csv();
				}
				else if (adminMode == 5){
					adminRepo.open_csv();
				}
				else if (adminMode == 6){
					break;
				}
				else{
					cout << "Invalid.";
				}
			}
		}
		else if (mode == 2){
			int userMode = 0;
			while (userMode != 5){
				cout << "User:" << endl;
				cout << "1. After genre" << endl;
				cout << "2. Add film" << endl;
				cout << "3. Delete film" << endl;
				cout << "4. Display lista filme" << endl;
				cout << "5. Deschidere fisier" << endl;
				cout << "6. Exit" << endl;
				cout << "Option: ";
				cin >> userMode;
				if (userMode == 1){
					string genre, link, line;
					int adaugare, continuare;
					fstream fin;

					cout << "Genre: ";
					cin >> genre;

					if (adminRepo.search_genre(genre) == 0){
						fin.open("AdminRepo.txt", ios::in);

						while (!fin.eof()){
							getline(fin, line);
							cout << line << endl;
							cout << endl;
							getline(fin, link);

							// Redarea filmului
							system(std::string("start " + link).c_str());

							cout << "Add?" << endl;
							cout << "1->YES     2-> NO" << endl;
							cin >> adaugare;
							if (adaugare == 1){
								userRepo.create_csv(line, link);
								cout << "Succes." << endl;

								cout << "Next trailer?" << endl;
								cout << "1->YES     2->NO" << endl;
								cin >> continuare;
								if (continuare == 2){
									break;
								}
							}
							else{
								cout << "Next trailer?" << endl;
								cout << "1->YES     2->NO" << endl;
								cin >> continuare;
								if (continuare == 2){
									break;
								}
							}
						}
					}
				}
				else if (userMode == 2){
					string title, blank, line, l1, l2;
					fstream fin;
					int pos;
					bool exista;
					cout << "Film Title: ";
					getline(cin, blank);
					getline(cin, title);

					fin.open("AdminRepo.txt", ios::in);

					exista = false;
					while (!fin.eof()){

						getline(fin, line);
						pos = line.find(title);
						if (pos != string::npos){
							l1 = line;
							getline(fin, line);
							l2 = line;
							exista = true;
						}
					}

					if (exista){
						userRepo.create_csv(l1, l2);
						cout << "Succes." << endl;
					}
				}
				else if (userMode == 3){
					userRepo.delete_csv();
				}
				else if (userMode == 4){
					userRepo.read_csv();
				}
				else if (userMode == 5){
					userRepo.open_csv();
				}
				else if (userMode == 6){
					break;
				}
				else{
					cout << "Invalid";
				}
			}
		}
		else if (mode == 3){
			run = false;
		}
		else{
			cout << "Invalid" << endl;
		}
	}
}

int main(){
	Menu menu = Menu();

	menu.startMenu();



	return 0;
}