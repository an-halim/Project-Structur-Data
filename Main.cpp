#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <string.h>

using namespace std;
/*
implementasi array -> done
implementasi struct -> done
implementasi pointer -> done
implementasi search -> done
implementasi sorting -> done
implementasi queue -> done
*/

#define MAX 10 // jumlah maksimal untuk antrian (bisa ditambah)

struct guest {
	string nama;
	char nik[17]{};
	string address;
	int umur{};
} person[100];// Implementasi array of struct

struct queue {
	string data[MAX]{};
	int head{}, tail{};
} antrian;

int jumlah = -1; // public

bool login();
bool auth(string username, string password);
void loading();
void mainMenu();
bool regist();
void quisioner();
void rapid();
int cari(char nik[]);
void sorting(int sortMode);
void cetakHasil(string *data);
string saveToTxt(string *data);
void exitConfirm();
void init();
int IsEmpty();
int IsFull();
void push(string data);
string pop();
void Clear();
void Tampil();

int main() {
	SetConsoleTitle(TEXT("Hospital Helper"));
	bool isLogin;
	init();
	
	do
	{
		system("cls");
		isLogin = login();
		if (isLogin)
		{
			cout << "\n\t\t\t\t\t\t   Login berhasil!";
			Sleep(1200);
			loading();
			mainMenu();
		}
	} while (!isLogin);

	return 0;
}

bool login() {
	string username, password;
	cout << "\n\t\t\t\n\t\t\t\t\t\t\tLOGIN" << endl;
	cout << "\n\t\t\t\tUsername  : "; cin >> username;
	cout << "\n\t\t\t\tPasssword : "; cin >> password;
	if (auth(username, password))
		return true;
	else
		return false;

}

bool auth(string username, string password) {
	string db[5][3] = {
		{"anhalim", "admin", "ahmad nur halim"},
		{"indra", "admin", "ade indra yudha pratama"},
		{"Wibisono", "wibiganteng", "satrio wibisono"},
		{"admin", "admin", "full name" }
	};// Implementasi array 2D
	int i = 0;

	do
	{
		if (username == db[i][0] && password == db[i][1]) {
			return true;
		}
		i++;
	} while (i < 5);

	cout << "\n\n\t\t\t\t\t     Password atau username salah!" << endl;
	Sleep(1000);
	return false;
}

void loading() {
	string s = " ";
	for (int i = 0; i < 100; i++) {
		system("cls");
		cout << "\n\n\n\n\n\t\t\t\t\t\t      Loading  " << i << "% " << "\n\t\t\t   Jangan keluarkan program ataupun tekan apapun saat proses sedang berjalan\n";
		s += "=";
		cout << endl;
		cout << "\t" << s;
		cout << "\n\n\n\n\n\t\t\t\t\t\t Hospital Helper @2021";
	}
}

void mainMenu() {
	string uname, pass;
	char nik[17];
	int pilihan, hasil;
	char pilih;
	bool isRegistered;
awal:

	SetConsoleTitle(TEXT("Hospital Helper"));
	system("cls");
	cout << "\n\tSelamat datang di Hospital Helper" << endl;
	cout << "\n\t-------------------------------" << endl;
	cout << "\t\t     Menu";
	cout << "\n\t-------------------------------" << endl;
	cout << "\n\t1. Registrasi pasien" << endl;
	cout << "\n\t2. Screening Covid-19" << endl;
	cout << "\n\t3. Rapid test" << endl;// implementasi queue
	cout << "\n\t4. Cari data pasien" << endl; // implementasi searching
	cout << "\n\t5. Tampilkan data pasien" << endl; // implementasi sorting
	cout << "\n\t6. keluar" << endl;
	cout << "\n\t-------------------------------" << endl;

	cout << "\n\n>\tMasukan pilihan kamu => ";
	cin >> pilihan;
	switch (pilihan)
	{
	case 1:
		isRegistered = regist();
		if (isRegistered)
		{
			system("cls");
			cout << ">\tRegistrasi berhasil!" << endl;
		}
		break;
	case 2:
		cout << "\n>\tApakah pasien sebelumnya sudah terdaftar? [Y/n] -> ";
		cin >> pilih;
		if (pilih == 'Y' || pilih == 'y')
		{
			cout << ">\tSilahkan masukan NIK anda : ";
			cin >> nik;
			hasil = cari(nik);
			if (hasil != -1)
			{
				quisioner();
			}
		}
		else
		{
			isRegistered = regist();
			if (isRegistered)
			{
				system("cls");
				cout << ">\tRegistrasi berhasil!" << endl;
			}
		}
		break;
	case 3:
		system("cls");
		rapid();
		break;
	case 4:
		system("cls");
		cout << ">\tMasukan NIK pasien: ";
		cin >> nik;
		hasil = cari(nik);
		if (hasil != -1)
		{
			cout << "\n\t---------------------------------" << endl;
			cout << "\t       Hasil Pencarian NIK       " << endl;
			cout << "\t---------------------------------" << endl;
			cout << "\n>\tNama: " << person[hasil].nama << endl;
			cout << ">\tUmur: " << person[hasil].umur << endl;
			cout << ">\tNIK: " << person[hasil].nik << endl;
			cout << ">\tAlamat: " << person[hasil].address << endl;
		}
		break;
	case 5:
		system("cls");
		cout << "\n\t---------------------------------" << endl;
		cout << "\t   Pilih tipe pengurutan data    " << endl;
		cout << "\t---------------------------------" << endl;
		cout << "\t1. ascending(menaik)" << endl;
		cout << "\t2. descending(menurun)" << endl;
		cout << "\n>\tMasukan pilihan -> ";
		int k;
		cin >> k;
		sorting(k);
		break;
	case 6:
		exitConfirm();
		break;
	default:
		cout << ">\tPilihan menu tidak tersedia!" << endl;
		break;
	}
	cout << "\n\n>\tKembali ke menu utama? [Y/n] -> ";
	cin >> pilih;
	if (pilih == 'Y' || pilih =='y')
		goto awal;
	else
		exitConfirm();
}

bool regist() {
	char pilihan;

	SetConsoleTitle(TEXT("Registrasi pasien"));
	system("cls");
	cout << "\n>\tSebelum melanjutkan apakah data diri pasien bersedia tersimpan dalam database? [Y/n] -> ";
	cin >> pilihan;
	
	if (pilihan == 'y' || pilihan == 'Y') {
		jumlah++;
		cout << "\n\tData diri pasien" << endl;
		cout << "\t--------------------" << endl;
		cout << ">\tNama : ";
		cin.ignore();
		getline(cin, person[jumlah].nama);
		cout << "\n>\tUmur : ";
		cin >> person[jumlah].umur;
		cout << "\n>\tNIK  : ";
		cin >> person[jumlah].nik;
		cout << "\n>\tAlamat : ";
		cin.ignore();
		getline(cin, person[jumlah].address);
		return true;
	}
	else
	{
		cout << ">\tRegistrasi gagal!" << endl;
		Sleep(1000);
		return false;
	}
}

void quisioner() {
	system("cls");
	string pilihan, hasil;
	int yes = 0;
	string question[5] = {
		"\n\tApakah pasien demam?",
		"\n\tApakah pasien batuk/pilek?",
		"\n\tApakah Anda pernah kontak dengan pasien positif COVID-19 atau berada satu ruangan yang sama atau kontak dalam \n\t1 meter pada 14 hari terakhir ?",
		"\n\tApakah Anda pernah berkunjung atau tinggal ke negara atau daerah endemis COVID-19 dalam 14 hari Terakhir?",
		"\n\tApakah Anda mengalami Diare pada 14 hari terakhir ?"
	};

	string answer[3] = {
		"Lakukan perawatan mandiri di rumah dengan beristirahat jika seminggu tidak ada perubahan segera datang ke klinik terdekta",
		"Kondisi anda kurang fit, segera periksa dokter terdekat!",
		"Segera lakukan rapid test di Fasilitas Kesehatan terdekat atau Hubungi segera layanan 119 Ext 9."
	};

	cout << "\n\tSilahkan isi quisioner berikut\n" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << question[i] << endl;
		cout << "\n>\tya/tidak?\n\t->";
		cin >> pilihan;
		if (pilihan == "ya" || pilihan == "Ya" || pilihan == "YA" || pilihan == "Y" || pilihan == "y")
			yes++;
		cout << "\t---------------------------------------------\n";
	}

	if (yes <= 2) {
		hasil = answer[0];
		cetakHasil(&hasil);
	}
	else if (yes == 3) {
		hasil = answer[1];
		cetakHasil(&hasil);
	}
	else {
		hasil = answer[2];
		cetakHasil(&hasil);
	}
	
	cout << "\n>\tSimpan hasil tes kedalam file? [Y/n] -> ";
	cin >> pilihan;
	if (pilihan == "ya" || pilihan == "YA" || pilihan == "y" || pilihan == "Y") {
		string save = saveToTxt(&hasil);
		cout << save << endl;
	}

	cout << "\n>\tApakah anda ingin melakukan rapid test? [Y/n] -> ";
	cin >> pilihan;
	if (pilihan == "ya" || pilihan == "YA" || pilihan == "y" || pilihan == "Y")
		rapid();
	else
		mainMenu();
}

void rapid() {//implementasi queue
	SetConsoleTitle(TEXT("RAPID TEST"));
	char pilih;
	int pilihan;
	char nik[17];
	int hasil, i = 0;

		cout << "\n>\tApakah pasien sebelumnya sudah terdaftar? [Y/n] -> ";
		cin >> pilih;
		if (pilih == 'Y' || pilih == 'y')
		{
			do
			{
				system("cls");
				Tampil();
				cout << "\n\t-------------------------------" << endl;
				cout << "\t\t     Menu";
				cout << "\n\t-------------------------------" << endl;
				cout << "\n\t1. Ambil antrian" << endl;
				cout << "\t2. Panggil antrian" << endl;
				cout << "\t3. Reset antrian" << endl;
				cout << "\n\t-------------------------------" << endl;
				cout << "\n\tSilahkan masukan antrian yang akan diambil -> ";
				cin >> pilihan;
				if (pilihan == 1)
				{
					cout << "\n>\tSilahkan masukan NIK pasien : ";
					cin >> nik;
					hasil = cari(nik);
					if (hasil != -1)
					{
						push(person[hasil].nama);
					}
					else
					{
						cout << "\n>\tData pasien dengan NIK " << nik << " tidak ditemukan, silahkan mendaftar terlebih dahulu!" << endl;
						return;
					}

				}
				else if (pilihan == 2)
				{
					if (IsEmpty())
						cout << "Antrian kosong!" << endl;
					else {
						string pasienName = pop();
						cout << "\n\tSilahkan panggil pasien " << pasienName << " untuk melakukan tes rapid!" << endl;
					}
				}
				Sleep(2000);
			} while (true);
		}
		else
		{
			regist();
		}
		

}

int cari(char nik[]) { //implementasi squential search
	int posisi = -1;
	for (int i = 0; i < 100; i++)
	{
		if (strcmp(nik, person[i].nik) == 0) {
			posisi = i;
			cout << "\t+----------------------------+";
			cout << "\n\t|Data ditemukan!!            |"<< endl;
			cout << "\t+----------------------------+\n";
		}
	}
	
	if (posisi == -1)
	{
		cout << "\t+----------------------------+";
		cout << "\n\t|Data Tidak ditemukan!!      |"<< endl;
		cout << "\t+----------------------------+\n";
	}
	return posisi;
}

void sorting(int sortMode) { //implemetasi bubble sort
	bool tukar;
	int tempUmur, j, i;
	char tempNIK[17];
	string tempAdd, tempNama;
	int total = jumlah + 1;

	system("cls");
	if (jumlah == -1) {
		cout << "\t+----------------------------+";
		cout << "\n\t|Data pasien kosong!         |" << endl;
		cout << "\t+----------------------------+";
		return;
	} 
	else if (sortMode == 1)// ascending
	{
		i = 0;
		tukar = true;
		while ((i <= total - 2) && (tukar))
		{
			tukar = false;
			for (j = total - 1; j >= i + 1; j--)
			{
				if (person[j].umur < person[j - 1].umur)
				{
					{
						tempUmur = person[j].umur;
						person[j].umur = person[j - 1].umur;
						person[j - 1].umur = tempUmur;

						for (int i = 0; i < 17; i++) {
							tempNIK[i] = person[j].nik[i];
							person[j].nik[i] = person[j - 1].nik[i];
							person[j - 1].nik[i] = tempNIK[i];
						}

						tempNama = person[j].nama;
						person[j].nama = person[j - 1].nama;
						person[j - 1].nama = tempNama;

						tempAdd = person[j].address;
						person[j].address = person[j - 1].address;
						person[j - 1].address = tempAdd;
						tukar = true;
					}
				}
				i++;
			}
		}
	}
	else if(sortMode == 2)// descending
	{
		i = 0;
		tukar = true;
		while ((i <= total - 2) && (tukar))
		{
			tukar = false;
			for (j = total - 1; j >= i + 1; j--)
			{
				if (person[j].umur > person[j - 1].umur)
				{
					tempUmur = person[j].umur;
					person[j].umur = person[j - 1].umur;
					person[j - 1].umur = tempUmur;

					for (int i = 0; i < 17; i++) {
						tempNIK[i] = person[j].nik[i];
						person[j].nik[i] = person[j - 1].nik[i];
						person[j - 1].nik[i] = tempNIK[i];
					}

					tempNama = person[j].nama;
					person[j].nama = person[j - 1].nama;
					person[j - 1].nama = tempNama;

					tempAdd = person[j].address;
					person[j].address = person[j - 1].address;
					person[j - 1].address = tempAdd;
					tukar = true;
				}
			}
			i++;
		}
	}
	else {
		cout << "Maaf sepertinya menu nomor " << sortMode << " tidak tersedia!" << endl;
		Sleep(2000);
		return;
	}

	if (sortMode == 1)
		cout << "Data pasien berdasarkan umur termuda" << endl;
	else
		cout << "Data pasien berdasarkan umur tertua" << endl;

	for (i = 0; i <= jumlah; i++) {
		int no = i + 1;
		cout <<
			no << ".\tNama : " << person[i].nama
			<< "\n\tUmur : " << person[i].umur
			<< "\n\tNIK  : " << person[i].nik
			<< "\n\tAlamat : " << person[i].address << endl;
	}
		
}

void cetakHasil(string *data) {
	system("cls");
	cout << "\n\t===========Hasil periksa============" << endl;
	cout << "\n\tNama   : " << person[jumlah].nama << endl;
	cout << "\tUmur   : " << person[jumlah].umur << endl;
	cout << "\tNIK    : " << person[jumlah].nik << endl;
	cout << "\tAlamat : " << person[jumlah].address << endl;
	cout << "\tHasil  : " << *data << endl;
	cout << "\n\t====================================" << endl;
}

string saveToTxt(string *data) {
	string charToString = person[jumlah].nik;
	string fileName = charToString + "_HASILSCREENING.txt";
	ofstream myfile(fileName);
	if (myfile.is_open())
	{
		myfile << "\n\t===========Hasil periksa============" << endl;
		myfile << "\n\tNama   : " << person[jumlah].nama << endl;
		myfile << "\tUmur   : " << person[jumlah].umur << endl;
		myfile << "\tNIK    : " << person[jumlah].nik << endl;
		myfile << "\tAlamat : " << person[jumlah].address << endl;
		myfile << "\tHasil  : " << *data << endl;
		myfile << "\n\t===================================" << endl;
		myfile.close();
		return "\n\tHasil tersimpan dalam " + fileName;
	}
	else
	{
		return "\n\tGagal menyimpan file!";
	}
}

void exitConfirm() {
	string konfir, username, password;

	SetConsoleTitle(TEXT("LOGOUT"));
	system("cls");
	cout << "\n\tSemua data pasien yang tersimpan akan terhapus!" << endl;
	cout << "\tApakah anda yakin keluar? [Y/n] -> ";
	cin >> konfir;
	if (konfir == "Y" || konfir == "y")
	{
		cout << endl;
		cout << "\tSebagai konfirmasi akhir silahkan masukan username dan password anda" << endl;
		cout << "\tUsername : ";
		cin >> username;
		cout << "\tPassword : ";
		cin >> password;
		if (auth(username, password))
		{
			exit(0);
		}
	}
	else
		mainMenu();
}


void init() {
	antrian.head = antrian.tail = -1;
}
int IsEmpty() {
	if (antrian.tail == -1)
		return 1;
	else
		return 0;
}
int IsFull() {
	if (antrian.tail == MAX - 1)
		return 1;
	else
		return 0;
}

void push(string data)
{
	system("cls");
	if (IsEmpty() == 1)
	{
		for (int i = 0; i < MAX; i++) { // cek apakah sebelumnya pasien sudah mengambil antrian
			if (data == antrian.data[i])
			{
				cout << "\n\tGagal mengambil antrian!" << endl;
				cout << "\n\t " << data << " sudah mengambil antrian sebelumnya" << endl;
				return;
			}
		}
		antrian.head = antrian.tail = 0;
		antrian.data[antrian.tail] = data;
		cout << "\n\t" << antrian.data[antrian.tail] << " Berhasil mendapat antrian!" << endl;
	}
	else if (IsFull() == 0)
	{		
		for (int i = 0; i < MAX; i++) { // cek apakah sebelumnya pasien sudah mengambil antrian
			if (data == antrian.data[i])
			{
				cout << "\n\tGagal mengambil antrian!" << endl;
				cout << "\n\t" << data << " sudah mengambil antrian sebelumnya" << endl;
				return;
			}
		}
		antrian.tail++;
		antrian.data[antrian.tail] = data;
		cout << "\n\t " << antrian.data[antrian.tail] << " Berhasil mendapat antrian!" << endl;
	}
	else {
		cout << "Antrian penuh" << endl;
	}
}

string pop()
{
	string e = antrian.data[antrian.head];
	for (int i = antrian.head; i <= antrian.tail - 1; i++)
	{
		antrian.data[i] = antrian.data[i + 1];
	}
	antrian.tail--;
	return e;
}

void Clear()
{
	antrian.head = antrian.tail = -1;
	cout << "Antrian berhasil direset!" << endl;
}

void Tampil()
{
	
	if (IsEmpty() == 0)
	{
		cout << "\n\tDaftar antrian" << endl;
		cout << "\t------------------------" << endl;
		cout << "\tNo.\tNama" << endl;
		for (int i = antrian.head; i <= antrian.tail; i++)
		{
			cout << "\t" << i + 1 << "\t" << antrian.data[i] << endl;
			cout << "\t------------------------" << endl;
		}
	}
	else
		cout << "\n\tTidak ada antrian rapid test!" << endl;

	cout << endl;
}