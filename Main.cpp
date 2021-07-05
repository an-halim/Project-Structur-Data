#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <cstdlib>

using namespace std;
/*
implementasi array -> done
implementasi struct -> done
implementasi pointer
implementasi search -> done
implementasi sorting -> done
implementasi queue

*/
struct guest {
	string nama;
	long int nik;
	string address;
	int umur;
} person[100];// Implementasi array of struct

int jumlah = -1; // public

void mainMenu();
void quisioner();
bool regist();
bool auth(string username, string password);
bool login();
int cari(long int nik);
void rapid();
void cetakHasil(string data);
void sorting(int sortMode);
bool sync();


int main() {
	SetConsoleTitle(TEXT("Hospital Helper"));
	bool isLogin = false;
	do
	{
		system("cls");
		isLogin = login();
		if (isLogin)
		{
			cout << "Sedang singkronisasi data..." << endl;
			bool sin = sync();
			if (sin)
				cout << "BERHASIL sinkronisasi data!" << endl;
			else
				cout << "GAGAL sinkronisasi data!" << endl;
			Sleep(5000);
			mainMenu();
		}
	} while (!isLogin);

	return 0;
}


void mainMenu() {
	string uname, pass;
	long int nik;
	int pilihan, hasil;
	char pilih;
	awal:

	system("cls");
	cout << "Menu" << endl;
	cout << "--------------------------" << endl;
	cout << "1. Screening Covid-19" << endl;
	cout << "2. Rapid test" << endl;// implementasi queue
	cout << "3. Cek data vaksinasi" << endl;
	cout << "4. Pengajuan vaksinasi" << endl;
	cout << "5. Cari data pasien" << endl;
	cout << "e. keluar" << endl;

	cout << "Masukan pilihan kamu => ";
	cin >> pilihan;
	switch (pilihan)
	{
	case 1:
		if (regist())
			quisioner();
		break;
	case 2:
		rapid();
		break;
	case 5:
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
	case 6:
		system("cls");
		cout << "Pilih tipe pengurutan data" << endl;
		cout << "1. ascending(menaik)" << endl;
		cout << "2. descending(menurun)" << endl;
		cout << "Masukan pilihan -> ";
		int k;
		cin >> k;
		sorting(k);
		break;
	default:
		cout << "Terimakasih" << endl;
		exit(0);
		break;
	}
	cout << "Ingin kembali ke menu utama? y/n -> ";
	cin >> pilih;
	if (pilih == 'y')
		goto awal;
	else
		exit(0);
}

bool regist() {
	char pilihan;
	system("cls");
	cout << "Sebelum melanjutkan apakah data diri pasien bersedia tersimpan dalam database?" << endl;
	cout << "Y/n? -> ";
	cin >> pilihan;
	
	if (pilihan == 'y' || pilihan == 'Y') {
		jumlah++;
		cout << "Data diri pasien" << endl;
		cout << "Nama : ";
		cin.ignore();
		getline(cin, person[jumlah].nama);
		cout << "Umur : ";
		cin >> person[jumlah].umur;
		cout << "NIK  : ";
		cin >> person[jumlah].nik;
		cout << "Alamat : ";
		cin.ignore();
		getline(cin, person[jumlah].address);
		return true;
	}
	else
	{
		cout << "Mohon maaf kamu tidak dapat melakukan deteksi mandiri." << endl;
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
		"Segera lakukan rapid test, Datang ke Fasilitas Kesehatan terdekat atau Hubungi segera layanan 119 Ext 9."
	};

	cout << "Silahkan isi quisioner berikut\n" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << question[i] << endl;
		cout << "ya/tidak?\n->";
		cin >> pilihan;
		if (pilihan == "ya" || pilihan == "Ya")
			yes++;
	}

	if (yes <= 2) {
		hasil = answer[0];
		cetakHasil(hasil);
	}
	else if (yes == 3) {
		hasil = answer[1];
		cetakHasil(hasil);
	}
	else {
		hasil = answer[2];
		cetakHasil(hasil);
	}
		

	cout << "Apakah anda ingin melakukan rapid test? y/n -> ";
	cin >> pilihan;
	if (pilihan == "ya" || pilihan == "YA" || pilihan == "y" || pilihan == "Y")
		rapid();
	else
		mainMenu();
}

bool auth(string username, string password) {
	string db[5][3] = {
		{"anhalim", "admin", "ahmad nur halim"},
		{"indra", "indraadmin077", "full name"},
		{"Wibisono", "wibiganteng", "full name"},
		{"admin", "admin", "full name" }
	};// Implementasi array 2D
	int i = 0;

	do
	{
		if (username == db[i][0] && password == db[i][1]) {
			cout << "Selamat datang " << db[i][2] << endl;
			Sleep(3000);
			return true;
		}
		i++;
	} while (i<5);

	cout << "Password atau username salah!" << endl;
	Sleep(1000);
	return false;
}

bool login() {
	string username, password;
	cout << "LOGIN" << endl;
	cout << "Username : "; cin >> username;
	cout << "Passsword : "; cin >> password;
	if (auth(username, password))
		return true;
	else
		return false;

}


void rapid() {//implementasi queue
	char pilih;
	long int nik;
	int hasil, i = 0;

		cout << "Apakah pasien sebelumnya sudah terdaftar? Y/n : ";
		cin >> pilih;
		if (pilih == 'Y' || pilih == 'y')
		{
			cout << "Silahkan masukan NIK anda : ";
			cin >> nik;
			hasil = cari(nik);
			if (hasil != -1)
			{
				cout << "AMBIL ANTRIAN RAPID" << endl;
				cout << "1. rapid antigen" << endl;
				cout << "2. rapid antibodi" << endl;
				cout << "3. swab pcr" << endl;
				cout << "Silahkan masukan antrian yang akan diambil -> ";

			}
		}
		else
		{
			regist();
		}

}

int cari(long int nik) { //implementasi squential search
	int posisi = -1;
	for (int i = 0; i < 100; i++)
	{
		if (nik == person[i].nik) {
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
	long int tempNIK;
	string tempAdd, tempNama;
	int total = jumlah + 1;
	if (sortMode == 1)// ascending
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

						tempNIK = person[j].nik;
						person[j].nik = person[j - 1].nik;
						person[j - 1].nik = tempNIK;

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

					tempNIK = person[j].nik;
					person[j].nik = person[j - 1].nik;
					person[j - 1].nik = tempNIK;

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

	cout << "\nUmur\tNama\tNIK\tAlamat " << endl;
	for (i = 0; i <= jumlah; i++)
		cout << person[i].umur << "\t" << person[i].nama << "\t" << person[i].nik << "\t" << person[i].address << endl;
}



void cetakHasil(string data) {
	system("cls");
	cout << "===========Hasil periksa============" << endl;
	cout << "Nama: " << person[jumlah].nama << endl;
	cout << "Umur: " << person[jumlah].umur << endl;
	cout << "NIK: " << person[jumlah].nik << endl;
	cout << "Alamat: " << person[jumlah].address << endl;
	cout << "Hasil: " << data << endl;
	cout << "===================================" << endl;
}

bool saveToTxt(string name, string addres, long int nik, int umur) {
	ofstream myfile("DBPASIEN.txt");
	if (myfile.is_open())
	{
		myfile << name << "\n";
		myfile << umur << "\n";
		myfile << nik << "\n";
		myfile << addres << "\n";
		myfile.close();
		return true;
	}
	else
	{
		cout << "Unable to open file";
		return false;
	}
}

bool sync() {
	string line;
	int i = 1;
	int data = 0, ganjil = 1, genap = 1;
	ifstream myfile("DBPASIEN.txt");// belom jadi masih pusing algoritmanya
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			/*if (i % 2 == 1)
			{
				if (ganjil == 2)
				{
					int nik = atoi(line.c_str());
					person[jumlah].nama = nik;
					ganjil = 1;
					data++;
				}
				person[jumlah].nama = line;
				ganjil = 2;
				data++;
			}
			if (i % 2 == 0)
			{
				if (genap == 2)
				{
					person[jumlah].address = line;
					genap = 1;
					data++;
				}
				int umur = atoi(line.c_str());
				person[jumlah].umur = umur;
				genap = 2;
				data++;
			}
			if (data == 4)
			{
				jumlah++;
				data = 0;
			}*/
			cout << line << "\n";
			i++;
			
		}
		cout << i;
		myfile.close();
		Sleep(56565);
		return true;
	}

	else
		return false;
}