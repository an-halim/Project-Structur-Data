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

#define MAX 10

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
	cout << "\n\tSelamat datang diHospital Helper" << endl;
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

	cout << "\n\n\tMasukan pilihan kamu => ";
	cin >> pilihan;
	switch (pilihan)
	{
	case 1:
		isRegistered = regist();
		if (isRegistered)
		{
			system("cls");
			cout << "\tRegistrasi berhasil!" << endl;
		}
		break;
	case 2:
		cout << "\n\tApakah pasien sebelumnya sudah terdaftar? [Y/n] -> ";
		cin >> pilih;
		if (pilih == 'Y' || pilih == 'y')
		{
			cout << "\tSilahkan masukan NIK anda : ";
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
				cout << "\tRegistrasi berhasil!" << endl;
			}
		}
		break;
	case 3:
		system("cls");
		rapid();
		break;
	case 4:
		system("cls");
		cout << "Masukan NIK pasien: ";
		cin >> nik;
		hasil = cari(nik);
		if (hasil != -1)
		{
			cout << "Nama: " << person[hasil].nama << endl;
			cout << "Umur: " << person[hasil].umur << endl;
			cout << "NIK: " << person[hasil].nik << endl;
			cout << "Alamat: " << person[hasil].address << endl;
		}
		break;
	case 5:
		system("cls");
		cout << "Pilih tipe pengurutan data" << endl;
		cout << "1. ascending(menaik)" << endl;
		cout << "2. descending(menurun)" << endl;
		cout << "Masukan pilihan -> ";
		int k;
		cin >> k;
		sorting(k);
		break;
	case 6:
		exitConfirm();
		break;
	default:
		cout << "Pilihan menu tidak tersedia!" << endl;
		break;
	}
	cout << "\nKembali ke menu utama? [Y/n] -> ";
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
		cout << ">\n\tUmur : ";
		cin >> person[jumlah].umur;
		cout << ">\n\tNIK  : ";
		cin >> person[jumlah].nik;
		cout << ">\n\tAlamat : ";
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
		"Apakah pasien demam?",
		"Apakah pasien batuk/pilek?",
		"Apakah Anda pernah kontak dengan pasien positif COVID-19 atau berada satu ruangan yang sama atau kontak dalam 1 meter pada 14 hari terakhir ?",
		"Apakah Anda pernah berkunjung atau tinggal ke negara atau daerah endemis COVID-19 dalam 14 hari Terakhir?",
		"Apakah Anda mengalami Diare pada 14 hari terakhir ?"
	};

	string answer[3] = {
		"Lakukan perawatan mandiri di rumah dengan beristirahat jika seminggu tidak ada perubahan segera datang ke klinik terdekta",
		"Kondisi anda kurang fit, segera periksa dokter terdekat!",
		"Segera lakukan rapid test di Fasilitas Kesehatan terdekat atau Hubungi segera layanan 119 Ext 9."
	};

	cout << "Silahkan isi quisioner berikut\n" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << question[i] << endl;
		cout << "ya/tidak?\n->";
		cin >> pilihan;
		if (pilihan == "ya" || pilihan == "Ya" || pilihan == "YA" || pilihan == "Y" || pilihan == "y")
			yes++;
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
	
	cout << "Simpan hasil tes kedalam file? [Y/n] -> ";
	cin >> pilihan;
	if (pilihan == "ya" || pilihan == "YA" || pilihan == "y" || pilihan == "Y") {
		string save = saveToTxt(&hasil);
		cout << save << endl;
	}

	cout << "Apakah anda ingin melakukan rapid test? [Y/n] -> ";
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

		cout << "Apakah pasien sebelumnya sudah terdaftar? [Y/n] -> ";
		cin >> pilih;
		if (pilih == 'Y' || pilih == 'y')
		{
			system("cls");
			Tampil();
			cout << "Menu" << endl;
			cout << "1. Ambil antrian" << endl;
			cout << "2. Panggil antrian" << endl;
			cout << "3. Reset antrian" << endl;
			cout << "Silahkan masukan antrian yang akan diambil -> ";
			cin >> pilihan;
			if (pilihan == 1 )
			{
				cout << "Silahkan masukan NIK pasien : ";
				cin >> nik;
				hasil = cari(nik);
				if (hasil != -1)
				{
					push(person[hasil].nama);
				}
				
			}
			else if (pilihan == 2)
			{
				if (IsEmpty())
					cout << "Antrian kosong!" << endl;
				else {
					string pasienName = pop();
					cout << "Silahkan panggil pasien " << pasienName << " untuk melakukan tes rapid!" << endl;
				}
			}
		}
		else
		{
			regist();
		}
		Sleep(1000);

}

int cari(char nik[]) { //implementasi squential search
	int posisi = -1;
	for (int i = 0; i < 100; i++)
	{
		if (strcmp(nik, person[i].nik) == 0) {
			posisi = i;
			cout << "Data ditemukan!!" << endl;
		}
	}
	
	if (posisi == -1)
	{
		cout << "Data tidak ditemukan!!" << endl;
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
		cout << "Data pasien kosong!" << endl;
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
	cout << "===========Hasil periksa============" << endl;
	cout << "Nama: " << person[jumlah].nama << endl;
	cout << "Umur: " << person[jumlah].umur << endl;
	cout << "NIK: " << person[jumlah].nik << endl;
	cout << "Alamat: " << person[jumlah].address << endl;
	cout << "Hasil: " << *data << endl;
	cout << "====================================" << endl;
}

string saveToTxt(string *data) {
	string charToString = person[jumlah].nik;
	string fileName = charToString + "_HASILSCREENING.txt";
	ofstream myfile(fileName);
	if (myfile.is_open())
	{
		myfile << "===========Hasil periksa============" << endl;
		myfile << "Nama: " << person[jumlah].nama << endl;
		myfile << "Umur: " << person[jumlah].umur << endl;
		myfile << "NIK: " << person[jumlah].nik << endl;
		myfile << "Alamat: " << person[jumlah].address << endl;
		myfile << "Hasil: " << *data << endl;
		myfile << "===================================" << endl;
		myfile.close();
		return "Hasil tersimpan dalam " + fileName;
	}
	else
	{
		return "Gagal menyimpan file!";
	}
}

void exitConfirm() {
	string konfir, username, password;

	SetConsoleTitle(TEXT("LOGOUT"));
	system("cls");
	cout << "Semua data pasien yang tersimpan akan terhapus!" << endl;
	cout << "Apakah anda yakin keluar? [Y/n] -> ";
	cin >> konfir;
	if (konfir == "Y" || konfir == "y")
	{
		cout << endl;
		cout << "Sebagai konfirmasi akhir silahkan masukan username dan password anda" << endl;
		cout << "Username : ";
		cin >> username;
		cout << "Password : ";
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
	if (IsEmpty() == 1)
	{
		antrian.head = antrian.tail = 0;
		antrian.data[antrian.tail] = data;
		cout << antrian.data[antrian.tail] << " Berhasil mendapat antrian!" << endl;
	}
	else if (IsFull() == 0)
	{
			antrian.tail++;
			antrian.data[antrian.tail] = data;
			cout << antrian.data[antrian.tail] << " Berhasil mendapat antrian!" << endl;
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
		cout << "Daftar antrian" << endl;
		cout << "No.\tNama" << endl;
		for (int i = antrian.head; i <= antrian.tail; i++)
		{
			cout << i + 1 << "\t" << antrian.data[i] << endl;
		}
	}
	else
		cout << "Tidak ada antrian rapid test!" << endl;

	cout << endl;
}