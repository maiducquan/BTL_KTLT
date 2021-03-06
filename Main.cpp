﻿#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
#include <cstdlib>
#include<iostream>
using namespace std;
#define GIO_DEN 8
#define PHUT_DEN 30
#define GIO_VE 16
#define PHUT_VE 30

typedef struct thoiGian {
	string ngayThangNam;
	int gioDen;
	int phutDen;
	int gioVe;
	int phutVe;
}ThoiGian;

typedef struct nhanvien {
	string ho;
	string ten;
	string maNhanVien;
	string donVi;
	string chucVu;
	string ngaySinh;
	string queQuan;
	string diaChi;
	string email;
	string sdt;
	string ngayBatDauLamViec;
	vector <ThoiGian> DS_ThoiGianLamViec;
}NhanVien;

typedef struct node_NhanVien {
	NhanVien nhanVien;
	node_NhanVien *next;
}Node_NhanVien;

typedef struct donVi {
	string tenDonVi;
	Node_NhanVien *canBo;
	Node_NhanVien *nhanVien;
	struct donVi *next;
	int soNhanVien;
}DonVi;

//đọc thời gian làm việc của 1 nhân viên, den khi gap ma nhan vien tiep theo thi dung lai
void DocThoiGianLamViec(ifstream &input, ThoiGian &ThoiGianLamViec) {

	getline(input, ThoiGianLamViec.ngayThangNam, ',');
	input >> ThoiGianLamViec.gioDen;
	input.seekg(1, 1); //dich con tro chi vi 1 byte
	input >> ThoiGianLamViec.phutDen;
	input.seekg(1, 1);
	input >> ThoiGianLamViec.gioVe;
	input.seekg(1, 1);
	input >> ThoiGianLamViec.phutVe;
}

// chuyen string sang chu thuong va tra ve chuoi do
string STRLWR(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] = str[i] + 32;
		}
	}
	return str;
}

// so sánh 2 ki tu dau tien cua 2 chuoi chuỗi, tra ve 0 neu 2 chuoi bang nhau, 1 neu str1 > str2, -1 neu str1 < str2.
int nemcmp(string str1, string str2) {
	str1 = STRLWR(str1);
	str2 = STRLWR(str2);
	for (int i = 0; i < 2; i++)
	{
		if (str1[i] > str2[i])
			return 1;
		else if (str1[i] < str2[i])
			return -1;
	}
	return 0;
}

//đọc thông tin 1 nhân viên từ file
void DocThongTinMotNhanVien(ifstream &input, NhanVien &nhanvien) {
	int n = 0, count = 0, vitri;
	getline(input, nhanvien.maNhanVien);
	vitri = input.tellg();
	getline(input, nhanvien.ho);
	if (nemcmp(nhanvien.ho, "NV") == 0) { // kiem tra xem neu dong moi doc vao la ma nhan vien cua nhan vien tiep theo
		nhanvien.ho = "";                 // thi dung lai va set lai vi tri con tro ve truoc dong do
		input.seekg(vitri, ios::beg);
		return;
	}
	vitri = input.tellg();
	getline(input, nhanvien.ten);
	if (nemcmp(nhanvien.ten, "NV") == 0) {
		nhanvien.ten = "";
		input.seekg(vitri, ios::beg);
		return;
	}
	vitri = input.tellg();
	getline(input, nhanvien.donVi);
	if (nemcmp(nhanvien.donVi, "NV") == 0) {
		nhanvien.donVi = "";
		input.seekg(vitri, ios::beg);
		return;
	}
	vitri = input.tellg();
	getline(input, nhanvien.chucVu);
	if (nemcmp(nhanvien.chucVu, "NV") == 0) {
		nhanvien.chucVu = "";
		input.seekg(vitri, ios::beg);
		return;
	}
	vitri = input.tellg();
	getline(input, nhanvien.ngaySinh);
	if (nemcmp(nhanvien.ngaySinh, "NV") == 0) {
		nhanvien.ngaySinh = "";
		input.seekg(vitri, ios::beg);
		return;
	}
	vitri = input.tellg();
	getline(input, nhanvien.queQuan);
	if (nemcmp(nhanvien.queQuan, "NV") == 0) {
		nhanvien.queQuan = "";
		input.seekg(vitri, ios::beg);
		return;
	}
	vitri = input.tellg();
	getline(input, nhanvien.diaChi);
	if (nemcmp(nhanvien.diaChi, "NV") == 0) {
		nhanvien.diaChi = "";
		input.seekg(vitri, ios::beg);
		return;
	}
	vitri = input.tellg();
	getline(input, nhanvien.email);
	if (nemcmp(nhanvien.email, "NV") == 0) {
		nhanvien.email = "";
		input.seekg(vitri, ios::beg);
		return;
	}
	vitri = input.tellg();
	getline(input, nhanvien.sdt);
	if (nemcmp(nhanvien.sdt, "NV") == 0) {
		nhanvien.sdt = "";
		input.seekg(vitri, ios::beg);
		return;
	}
	vitri = input.tellg();
	getline(input, nhanvien.ngayBatDauLamViec);
	if (nemcmp(nhanvien.ngayBatDauLamViec, "NV") == 0) {
		nhanvien.ngayBatDauLamViec = "";
		input.seekg(vitri, ios::beg);
		return;
	}
	string temp;
	vitri = input.tellg();// lay vi tri hien tai cua con tro
	while (true)
	{
		if (input.eof()) break;
		getline(input, temp);
		if (nemcmp(temp, "NV") == 0) break;
		n++;
	}
	input.seekg(vitri, ios::beg); // dich chuyen con tro den vi tri = vitri ke tu dau file
	ThoiGian thoiGianLamViec;
	while (count < n)
	{
		DocThoiGianLamViec(input, thoiGianLamViec);
		getline(input, temp);
		nhanvien.DS_ThoiGianLamViec.push_back(thoiGianLamViec);
		count++;
	}
}

void xuatThoiGian(ThoiGian thoiGian) {
	cout << left << "Ngay : " << thoiGian.ngayThangNam << ","  << thoiGian.gioDen << ":" 
		<< thoiGian.phutDen << ","<< thoiGian.gioVe << ":" << thoiGian.phutVe << endl;
}

void xuatThongTinCoBanMotNhanVien(NhanVien nhanvien) {
	cout << left << setw(15) << nhanvien.ho << setw(7) << nhanvien.ten << setw(8) << nhanvien.maNhanVien << setw(12)
		<< nhanvien.ngaySinh << setw(10) << nhanvien.queQuan << setw(25) << nhanvien.diaChi 
		<< setw(20) << nhanvien.donVi << setw(10) << nhanvien.chucVu << endl;
	/*for (int i = 0; i < nhanvien.DS_ThoiGianLamViec.size(); i++) {
		xuatThoiGian(nhanvien.DS_ThoiGianLamViec[i]);
	}*/
}

// tao mot danh sach lien ket don vong rong de luu tru cac don vi
void create_LinkList_DonVi(DonVi *&ds_DonVi) {
	ds_DonVi = NULL;
}

//tao mot don vi moi co ten tuong ung voi ten don vi cua nhan vien them vao
void creat_DonVi(DonVi *&donVi, Node_NhanVien *nodeNhanVien) {
	donVi->tenDonVi = nodeNhanVien->nhanVien.donVi;
	if (_stricmp(((nodeNhanVien->nhanVien).chucVu).c_str(), "Nhan vien") == 0) { //c_str chuyen ve mang char
		donVi->nhanVien = nodeNhanVien;
		donVi->canBo = NULL;
		donVi->soNhanVien = 1;
	}
	else
	{
		donVi->canBo = nodeNhanVien;
		donVi->nhanVien = NULL;
		donVi->soNhanVien = 0;
	}
	donVi->next = NULL;
}

// tao ra một đơn vị mới nếu trong danh sách các đơn vị chưa có đơn vị la đơn vi làm viêc của nhân viên được thêm vào 
//và thêm nhân viên đó vào đơn vị này
void ThemMotDonVi(DonVi *donVi, DonVi *&ds_DonVi) {
	if (ds_DonVi == NULL) {
		ds_DonVi = donVi;
		ds_DonVi->next = ds_DonVi;
	}
	else {
		DonVi *p = ds_DonVi;
		while (true)
		{
			if (p->next == ds_DonVi) break;
			p = p->next;
		}
		p->next = donVi;
		donVi->next = ds_DonVi;
	}
}

// thêm 1 Node_NhanVien mới vao danh sach cong ty
void Insert(DonVi *&ds_DonVi, Node_NhanVien *nodeNhanVien) {
	int count = 0;
	if (ds_DonVi != NULL) {
		DonVi *p = ds_DonVi;
		while (true)
		{
			if (_stricmp((p->tenDonVi).c_str(), ((nodeNhanVien->nhanVien).donVi).c_str()) == 0) {
				Node_NhanVien *pNode;
				count++;
				if (_stricmp(((nodeNhanVien->nhanVien).chucVu).c_str(), "nhan vien") == 0) {
					p->soNhanVien += 1;
					if (p->nhanVien == NULL) {
						p->nhanVien = nodeNhanVien;
						break;
					}
					else
					{
						pNode = p->nhanVien;
						p->nhanVien = nodeNhanVien;
						nodeNhanVien->next = pNode;
						break;
					}
				}
				else
				{
					if (p->canBo == NULL) {
						p->canBo = nodeNhanVien;
						break;
					}
					else
					{
						pNode = p->canBo;
						p->canBo = nodeNhanVien;
						nodeNhanVien->next = pNode;
						break;
					}
				}
			}
			if (p->next == ds_DonVi) break;
			p = p->next;
		}
	}
	if (count == 0 || ds_DonVi == NULL) {
		DonVi *donVi = new DonVi;
		creat_DonVi(donVi, nodeNhanVien);
		ThemMotDonVi(donVi, ds_DonVi);
	}
}

// đọc thông tin từ file NhanVien.txt tra ve -1 nếu đọc không thành công ngược lại trả về 0
int DocFile(ifstream &input, DonVi *&ds_DonVi) {
	input.seekg(0, ios::end);    // dich chuyen con tro den cuoi file
	if (!input.tellg()) {      // kiem tra file co rong hay khong
		return -1;
	}
	else
	{
		input.seekg(0, ios::beg);      // tra lai con tro ve dau file
		while (input.eof() == false)
		{
			NhanVien nhanvien;
			cin.sync();
			DocThongTinMotNhanVien(input, nhanvien);
			Node_NhanVien *nodeNhanVien = new Node_NhanVien;
			nodeNhanVien->nhanVien = nhanvien;
			nodeNhanVien->next = NULL;
			Insert(ds_DonVi, nodeNhanVien);
		}
		return 0;
	}
}

// xuat toàn bộ thông tin đọc được từ file (Thong tin cong ty BKCorporation)
void Output(DonVi *ds_DonVi) {
	if (ds_DonVi == NULL) {
		cout << "Khong co thong tin de hien thi" << endl;
		return;
	}
	else
	{
		DonVi *pDonVi = ds_DonVi;
		while (true)
		{
			cout << pDonVi->tenDonVi << ": " << endl;
			cout << left << setw(15) << "Ho" << setw(7) << "Ten" << setw(8) << "Ma NV" << setw(12) << "Ngay Sinh"
				<< setw(10) << "Que Quan" << setw(25) << "Dia Chi"  << setw(20)
				<< "Don Vi" << setw(10) << "Chuc Vu" << endl;
			Node_NhanVien *pCanBo = pDonVi->canBo;
			while (true)
			{
				if (pCanBo == NULL) break;
				xuatThongTinCoBanMotNhanVien(pCanBo->nhanVien);
				pCanBo = pCanBo->next;
			}
			Node_NhanVien *pNhanVien = pDonVi->nhanVien;
			while (true)
			{
				if (pNhanVien == NULL) break;
				xuatThongTinCoBanMotNhanVien(pNhanVien->nhanVien);
				pNhanVien = pNhanVien->next;
			}
			if (pDonVi->next == ds_DonVi)
			{
				break;
			}
			pDonVi = pDonVi->next;
		}
	}
}

void xuatThongTinCoBanVeMotDonVi(DonVi *ds_DonVi, string tenDonVi)
{
	if (ds_DonVi == NULL) {
		cout << "Khong co thong tin de hien thi" << endl;
	}
	else
	{
		DonVi *p = ds_DonVi;
		int count = 0;
		cout << left << setw(15) << "Ho" << setw(7) << "Ten" << setw(8) << "Ma NV" << setw(12) << "Ngay Sinh"
			 << setw(10) << "Que Quan" << setw(25) << "Dia Chi" << setw(20) << "Don Vi" << setw(10) << "Chuc Vu" << endl;
		while (true)
		{
			if (_stricmp((p->tenDonVi).c_str(), tenDonVi.c_str()) == 0) {
				count++;
				int n = 0;   //bien dem so can bo
				Node_NhanVien *pCanBo = p->canBo;
				while (true)
				{
					if (pCanBo == NULL) {
						break;
					}
					else
					{
						n++;
						xuatThongTinCoBanMotNhanVien(pCanBo->nhanVien);
						pCanBo = pCanBo->next;
					}
				}
				if (n == 0) cout << "Khong co thong tin can bo!" << endl;
				int m = 0;    //bien dem so nhan vien
				Node_NhanVien *pNhanVien = p->nhanVien;
				while (true)
				{
					if (pNhanVien == NULL) {
						break;
					}
					else
					{
						m++;
						xuatThongTinCoBanMotNhanVien(pNhanVien->nhanVien);
						pNhanVien = pNhanVien->next;
					}
				}
				if (m == 0) cout << "Khong co thong tin nhan vien!" << endl;
			}
			if (p->next == ds_DonVi) break;
			p = p->next;
		}
		if (count == 0) {
			system("cls");
			cout << "Khong co don vi nay trong danh sach!" << endl;
		}
	}
}

void XuatThongTinCoBanVeCongTy(DonVi *ds_DonVi) {
	if (ds_DonVi == NULL) {
		cout << "Khong co thong tin de hien thi" << endl;
		return;
	}
	else
	{
		DonVi *p = ds_DonVi;
		int TongSoNhanVien = 0;
		while (true)
		{
			TongSoNhanVien += p->soNhanVien;
			Node_NhanVien *pCanBo = p->canBo;
			cout << "\n" << p->tenDonVi << " : " << endl;
			cout << left << setw(15) << "Ho" << setw(10) << "Ten" << setw(10) << "Chuc Vu" << endl;
			while (true)
			{
				if (pCanBo == NULL) break;
				cout << left << setw(15) << pCanBo->nhanVien.ho << setw(10) << pCanBo->nhanVien.ten
					<< setw(10) << pCanBo->nhanVien.chucVu << endl;
				pCanBo = pCanBo->next;
			}
			if (p->next == ds_DonVi) break;
			p = p->next;
		}
		cout << "\nTong So Nhan Vien = " << TongSoNhanVien << endl;
	}
}

Node_NhanVien *SaoChepNodeNhanVien(Node_NhanVien *pNhanVien) {
	Node_NhanVien *pNode = new Node_NhanVien();
	pNode->nhanVien.ho = pNhanVien->nhanVien.ho;
	pNode->nhanVien.ten = pNhanVien->nhanVien.ten;
	pNode->nhanVien.diaChi = pNhanVien->nhanVien.diaChi;
	pNode->nhanVien.queQuan = pNhanVien->nhanVien.queQuan;
	pNode->nhanVien.sdt = pNhanVien->nhanVien.sdt;
	pNode->nhanVien.ngaySinh = pNhanVien->nhanVien.ngaySinh;
	pNode->nhanVien.donVi = pNhanVien->nhanVien.donVi;
	pNode->nhanVien.ngayBatDauLamViec = pNhanVien->nhanVien.ngayBatDauLamViec;
	pNode->nhanVien.email = pNhanVien->nhanVien.email;
	pNode->nhanVien.DS_ThoiGianLamViec = pNhanVien->nhanVien.DS_ThoiGianLamViec;
	pNode->nhanVien.maNhanVien = pNhanVien->nhanVien.maNhanVien;
	pNode->nhanVien.chucVu = pNhanVien->nhanVien.chucVu;
	pNode->next = NULL;
	return pNode;
}

//tim kiem gan dung theo thong tin nguoi dung nhap vao tra ve null neu danh sach nhan vien rong, nguoc lai tra ve danh sach tim kiem
Node_NhanVien *Search(DonVi *ds_DonVi, string giaTriTimKiem) {
	if (ds_DonVi == NULL) {
		return NULL;
	}
	else
	{
		Node_NhanVien *ds_TimKiem = NULL;
		DonVi *pDonVi = ds_DonVi;
		while (true)
		{
			Node_NhanVien *pCanBo = pDonVi->canBo;
			while (true)
			{
				if (pCanBo == NULL) break;
				if (strstr((STRLWR(pCanBo->nhanVien.ten)).c_str(), STRLWR(giaTriTimKiem).c_str()) != NULL
					|| strstr((STRLWR(pCanBo->nhanVien.ho)).c_str(), STRLWR(giaTriTimKiem).c_str()) != NULL
					|| strstr((STRLWR(pCanBo->nhanVien.email)).c_str(), STRLWR(giaTriTimKiem).c_str()) != NULL
					|| strstr((STRLWR(pCanBo->nhanVien.ngayBatDauLamViec)).c_str(), STRLWR(giaTriTimKiem).c_str()) != NULL
					|| strstr(STRLWR(giaTriTimKiem).c_str(), (STRLWR(pCanBo->nhanVien.maNhanVien)).c_str()) != NULL
					|| strstr((STRLWR(pCanBo->nhanVien.ngaySinh)).c_str(), STRLWR(giaTriTimKiem).c_str()) != NULL
					|| strstr((STRLWR(pCanBo->nhanVien.chucVu)).c_str(), (STRLWR(giaTriTimKiem)).c_str()) != 0
					|| strstr((STRLWR((pCanBo->nhanVien.ho + " " + pCanBo->nhanVien.ten))).c_str(), STRLWR(giaTriTimKiem).c_str()) != NULL)
				{
					Node_NhanVien *pSaoChep = SaoChepNodeNhanVien(pCanBo);
					if (ds_TimKiem == NULL) {
						ds_TimKiem = pSaoChep;
					}
					else
					{
						Node_NhanVien *pNode = ds_TimKiem;
						ds_TimKiem = pSaoChep;
						pSaoChep->next = pNode;
					}
				}
				pCanBo = pCanBo->next;
			}
			Node_NhanVien *pNhanVien = pDonVi->nhanVien;
			while (true)
			{
				if (pNhanVien == NULL) break;
				if (strstr((STRLWR(pNhanVien->nhanVien.ten)).c_str(), (STRLWR(giaTriTimKiem)).c_str()) != NULL
					|| strstr((pNhanVien->nhanVien.ho).c_str(), (STRLWR(giaTriTimKiem)).c_str()) != NULL
					|| strstr((STRLWR(pNhanVien->nhanVien.email)).c_str(), (STRLWR(giaTriTimKiem)).c_str()) != NULL
					|| strstr((STRLWR(pNhanVien->nhanVien.ngayBatDauLamViec)).c_str(), (STRLWR(giaTriTimKiem)).c_str()) != NULL
					|| _stricmp((STRLWR(pNhanVien->nhanVien.maNhanVien)).c_str(), (STRLWR(giaTriTimKiem)).c_str()) == 0
					|| strstr((STRLWR(pNhanVien->nhanVien.ngaySinh)).c_str(), STRLWR(giaTriTimKiem).c_str()) != NULL
					|| strstr((STRLWR(pNhanVien->nhanVien.chucVu)).c_str(), (STRLWR(giaTriTimKiem)).c_str()) != 0
					|| strstr((STRLWR(pNhanVien->nhanVien.ho + " " + pNhanVien->nhanVien.ten)).c_str(), (STRLWR(giaTriTimKiem)).c_str()) != NULL)
				{
					Node_NhanVien *pSaoChep = SaoChepNodeNhanVien(pNhanVien);
					if (ds_TimKiem == NULL) {
						ds_TimKiem = pSaoChep;
					}
					else
					{
						Node_NhanVien *pNode = ds_TimKiem;
						ds_TimKiem = pSaoChep;
						pSaoChep->next = pNode;
					}
				}
				pNhanVien = pNhanVien->next;
			}
			if (pDonVi->next == ds_DonVi)
			{
				break;
			}
			pDonVi = pDonVi->next;
		}
		return ds_TimKiem;
	}
}

//tim 1 nhan vien theo ma nhan vien tra ve null neu khong tim thay, nguoc lai tra ve Node_NhanVien tuong ung
Node_NhanVien *TimKiemTheoMaNhanVien(DonVi *ds_DonVi, string maNhanVien) {
	if (ds_DonVi == NULL) {
		return NULL;
	}
	else
	{
		DonVi *pDonVi = ds_DonVi;
		while (true)
		{
			Node_NhanVien *pCanBo = pDonVi->canBo;
			while (true)
			{
				if (pCanBo == NULL) break;
				if (_stricmp((pCanBo->nhanVien.maNhanVien).c_str(), maNhanVien.c_str()) == 0)
				{
					return pCanBo;
				}
				pCanBo = pCanBo->next;
			}
			Node_NhanVien *pNhanVien = pDonVi->nhanVien;
			while (true)
			{
				if (pNhanVien == NULL) break;
				if (_stricmp((pNhanVien->nhanVien.maNhanVien).c_str(), maNhanVien.c_str()) == 0)
				{
					return pNhanVien;
				}
				pNhanVien = pNhanVien->next;
			}
			if (pDonVi->next == ds_DonVi)
			{
				break;
			}
			pDonVi = pDonVi->next;
		}
	}
	return NULL;
}

void ThemMotNhanVien(DonVi *&ds_DonVi) {
	NhanVien nhanVien;
	cout << "Nhap Thong tin nhan vien can them: " << endl;
	cout << "Ho: ";
	cin.ignore();//xoa bo bo dem
	getline(cin, nhanVien.ho);
	cout << "Ten: ";
	cin.sync();   //xoa bo dem
	getline(cin, nhanVien.ten);
	cout << "Ma nhan vien: ";
	string maNhanVien;
	cin.sync();
	getline(cin, maNhanVien);
	do
	{
		if (TimKiemTheoMaNhanVien(ds_DonVi, maNhanVien) == NULL) break;
		else
		{
			cout << "Ma nhan vien ban vua nhap da ton tai vui long nhan lai ma nhan vien: ";
			getline(cin, maNhanVien);
		}
	} while (true);
	nhanVien.maNhanVien = maNhanVien;
	cout << "Don vi: ";
	cin.sync();
	getline(cin, nhanVien.donVi);
	cout << "Chuc vu: ";
	cin.sync();
	getline(cin, nhanVien.chucVu);
	cout << "Ngay thang nam sinh : ";
	cin.sync();
	getline(cin, nhanVien.ngaySinh);
	cout << "Que quan: ";
	cin.sync();
	getline(cin, nhanVien.queQuan);
	cout << "Dia chi: ";
	cin.sync();
	getline(cin, nhanVien.diaChi);
	cout << "Email: ";
	cin.sync();
	getline(cin, nhanVien.email);
	cout << "So dien thoai: ";
	cin.sync();
	getline(cin, nhanVien.sdt);
	cout << "Ngay bat dau lam viec: ";
	cin.sync();
	getline(cin, nhanVien.ngayBatDauLamViec);
	char ch;
	cout << "Nhap gian lam viec (y/n)?";
	cin >> ch;
	if (ch == 'y' || ch == 'Y') {
		cout << "Nhap thoi gian lam viec:" << endl;
		while (true)
		{
			ThoiGian thoiGian;
			cout << "Ngay lam viec: ";
			cin.ignore();
			getline(cin, thoiGian.ngayThangNam);
			cout << "Thoi gian bat dau: " << endl;
			cout << "Thoi gian den (gio phut): ";
			cin >> thoiGian.gioDen >> thoiGian.phutDen;
			cout << "Thoi gian ve (gio phut): ";
			cin >> thoiGian.gioVe >> thoiGian.phutVe;
			nhanVien.DS_ThoiGianLamViec.push_back(thoiGian);
			cout << "Nhap tiep (y/n)? ";
			cin >> ch;
			if (ch == 'n') break;
		}
	}
	Node_NhanVien *nodeNhanVien = new Node_NhanVien;
	nodeNhanVien->nhanVien = nhanVien;
	nodeNhanVien->next = NULL;
	Insert(ds_DonVi, nodeNhanVien);
}

//tinh thoi gian lam viec cua nhan vien theo khung thoi gian 8:30->16:30, 
//tra ve thoi gian lam viec tuong ung cua nhan vien lam tron theo gio, neu nhan vien lam du tra ve 0,
//thieu tra ve gia tri am, nguoc lai neu lam them tra ve gia tri duong tuong ung voi so gio thieu,thua
int TinhThoiGian(vector<ThoiGian> ds_ThoiGian)
{
	if (ds_ThoiGian.size() == 0) {
		return 1000;
	}
	else
	{
		int TongThoiGian = 0;
		for (int i = 0; i < ds_ThoiGian.size(); i++)
		{
			if (ds_ThoiGian[i].gioDen > GIO_DEN) {
				TongThoiGian -= (ds_ThoiGian[i].gioDen - 1 - GIO_DEN) * 60 + (60 - ds_ThoiGian[i].phutDen) + PHUT_DEN;
			}
			else
			{
				if (ds_ThoiGian[i].gioDen < GIO_DEN) {
					TongThoiGian += (GIO_DEN - 1 - ds_ThoiGian[i].gioDen) * 60 + (60 - ds_ThoiGian[i].phutDen) + PHUT_DEN;
				}
				else
				{
					if (ds_ThoiGian[i].phutDen >= PHUT_DEN) TongThoiGian -= ds_ThoiGian[i].phutDen - PHUT_DEN;
					else TongThoiGian += PHUT_DEN - ds_ThoiGian[i].phutDen;
				}
			}
			if (ds_ThoiGian[i].gioVe < GIO_VE) {
				TongThoiGian -= (GIO_VE - 1 - ds_ThoiGian[i].gioVe) * 60 + (60 - ds_ThoiGian[i].phutVe) + PHUT_VE;
			}
			else
			{
				if (ds_ThoiGian[i].gioVe > GIO_VE) {
					TongThoiGian += (ds_ThoiGian[i].gioVe - 1 - GIO_VE) * 60 + (60 - PHUT_VE) + ds_ThoiGian[i].phutVe;
				}
				else
				{
					if (ds_ThoiGian[i].phutVe <= PHUT_VE) TongThoiGian -= PHUT_VE - ds_ThoiGian[i].phutVe;
					else TongThoiGian += ds_ThoiGian[i].phutVe - PHUT_VE;
				}
			}
		}
		if (TongThoiGian < 0) {
			if (TongThoiGian % 60 <= -30) {
				return (int)TongThoiGian / 60 - 1;
			}
			else
			{
				return (int)TongThoiGian / 60;
			}
		}
		else
		{
			if (TongThoiGian % 60 >= 30) {
				return (int)TongThoiGian / 60 + 1;
			}
			else
			{
				return (int)TongThoiGian / 60;
			}
		}
	}
}

void HienThiTrangThaiLamViec(DonVi *ds_DonVi, string maNhanVien) {
	Node_NhanVien *pNhanVien = TimKiemTheoMaNhanVien(ds_DonVi, maNhanVien);
	if (pNhanVien == NULL) {
		cout << "Khong co nhan vien mang ma nay trong cong ty." << endl;
		return;
	}
	else
	{
		int TongThoiGian = TinhThoiGian(pNhanVien->nhanVien.DS_ThoiGianLamViec);
		if (TongThoiGian == 1000) {
			cout << "Khong co thong tin ngay lam viec cua nhan vien nay" << endl;
			return;
		}
		else
		{
			cout << "Danh sach thoi gian lam viec: " << endl;
			for (int i = 0; i < pNhanVien->nhanVien.DS_ThoiGianLamViec.size(); i++) {
				xuatThoiGian(pNhanVien->nhanVien.DS_ThoiGianLamViec[i]);
			}
			cout << endl;
			if (TongThoiGian < 0) {
				cout << "Thoi gian thieu cua nhan vien nay la: " << (0 - TongThoiGian) << endl;
			}
			else
			{
				if (TongThoiGian > 0) {
					cout << "Tong thoi gian lam them cua nhan vien nay la: " << TongThoiGian << endl;
				}
				else
				{
					cout << "Nhan vien nay lam du thoi gian" << endl;
				}
			}
		}
	}
}

Node_NhanVien *searchNode(DonVi *ds_DonVi, DonVi *&pDonVi, string maNhanVien) {
	if (ds_DonVi == NULL) {
		return NULL;
	}
	else
	{
		pDonVi = ds_DonVi;
		while (true)
		{
			Node_NhanVien *pCanBo = pDonVi->canBo;
			if (_stricmp(pCanBo->nhanVien.maNhanVien.c_str(), maNhanVien.c_str()) == 0) return pCanBo;
			else
			{
				while (true)
				{
					if (pCanBo->next == NULL) break;
					if (_stricmp((pCanBo->next->nhanVien.maNhanVien).c_str(), maNhanVien.c_str()) == 0)
					{
						return pCanBo;
					}
					pCanBo = pCanBo->next;
				}
			}
			Node_NhanVien *pNhanVien = pDonVi->nhanVien;
			if (_stricmp(pNhanVien->nhanVien.maNhanVien.c_str(), maNhanVien.c_str()) == 0) return pNhanVien;
			else
			{
				while (true)
				{
					if (pNhanVien->next == NULL) break;
					if (_stricmp((pNhanVien->next->nhanVien.maNhanVien).c_str(), maNhanVien.c_str()) == 0)
					{
						return pNhanVien;
					}
					pNhanVien = pNhanVien->next;
				}
			}
			if (pDonVi->next == ds_DonVi)
			{
				break;
			}
			pDonVi = pDonVi->next;
		}
	}
	return NULL;
}

// cap nhat thong tin 1 nhan vien theo ma nhan vien tra ve -1 neu khong co nhan vien nay trong cong ty, 
//tra ve 0 neu cap nhat thanh cong, tra ve 1 neu cap nhat don vi ma nguoi nhap vao ten don vi khong ton tai
int UpdateInfo_NhanVien(DonVi *&ds_DonVi, string maNhanVien) {
	Node_NhanVien *pNhanVien = TimKiemTheoMaNhanVien(ds_DonVi, maNhanVien);
	if (pNhanVien == NULL) {
		return -1;
	}
	else
	{
		int LuaChon;
		cout << "Chon muc can cap nhat: " << endl;
		cout << "1. Ho" << endl;
		cout << "2. Ten" << endl;
		cout << "3. Ngay sinh" << endl;
		cout << "4. Que quan" << endl;
		cout << "5. Dia chi" << endl;
		cout << "6. SDT" << endl;
		cout << "7. Email" << endl;
		cout << "8. Chuc vu" << endl;
		cout << "9. Don Vi" << endl;
		cout << "10. Ngay bat dau lam viec" << endl;
		cout << "Ban chon: ";
		cin >> LuaChon;
		if (cin.fail() || LuaChon < 1 || LuaChon > 10) { //neu khong phai la so nguyen
			cin.clear(); // bo qua co loi
			cin.ignore(32767, '\n'); //xoa di tat ca cac ki tu trong bo nho dem den khi gap \n
			system("cls");
			cout << "Ban chon sai! vui long thu lai!" << endl;
			return 2;
		}
		switch (LuaChon)
		{
		case 1: {
			string ho;
			cout << "Nhap ho: ";
			cin.ignore();
			getline(cin, ho);
			pNhanVien->nhanVien.ho = ho;
			break;
		}
		case 2: {
			string ten;
			cout << "Nhap ten: ";
			cin.ignore();
			getline(cin, ten);
			pNhanVien->nhanVien.ten = ten;
			break;
		}
		case 3: {
			string ngaySinh;
			cout << "Nhap ngay sinh: ";
			cin.ignore();
			getline(cin, ngaySinh);
			pNhanVien->nhanVien.ngaySinh = ngaySinh;
			break;
		}
		case 4: {
			string queQuan;
			cout << "Nhap que quan: ";
			cin.ignore();
			getline(cin, queQuan);
			pNhanVien->nhanVien.queQuan = queQuan;
			break;
		}
		case 5: {
			string diaChi;
			cout << "Nhap dia chi: ";
			cin.ignore();
			getline(cin, diaChi);
			pNhanVien->nhanVien.diaChi = diaChi;
			break;
		}
		case 6: {
			string SDT;
			cout << "Nhap SDT: ";
			cin.ignore();
			getline(cin, SDT);
			pNhanVien->nhanVien.sdt = SDT;
			break;
		}
		case 7: {
			string email;
			cout << "Nhap Email: ";
			cin.ignore();
			getline(cin, email);
			pNhanVien->nhanVien.email = email;
			break;
		}
		case 8: {
			string chucVu;
			cout << "Nhap chuc vu: ";
			cin.ignore();
			getline(cin, chucVu);

			if (_stricmp(pNhanVien->nhanVien.chucVu.c_str(), "nhan vien") != 0) {
				pNhanVien->nhanVien.chucVu = chucVu;
				if (_stricmp(chucVu.c_str(), "nhan vien") == 0) {
					DonVi *pDonVi;
					Node_NhanVien *pNode = searchNode(ds_DonVi, pDonVi, maNhanVien);
					if (_stricmp(pNode->nhanVien.maNhanVien.c_str(), maNhanVien.c_str()) == 0) {
						if (pNode->next == NULL) {
							Node_NhanVien *p = pDonVi->canBo;
							pDonVi->canBo = NULL;
							Node_NhanVien *p1 = pDonVi->nhanVien;
							pDonVi->nhanVien = p;
							p->next = p1;
						}
						else {
							Node_NhanVien *p = pDonVi->canBo;
							pDonVi->canBo = pDonVi->canBo->next;
							Node_NhanVien *p1 = pDonVi->nhanVien;
							pDonVi->nhanVien = p;
							p->next = p1;
						}
					}
					else
					{
						Node_NhanVien *pTemp = pNode->next;
						pNode->next = pTemp->next;
						Node_NhanVien *pNV = pDonVi->nhanVien;
						pDonVi->nhanVien = pTemp;
						pTemp->next = pNV;
					}
					pDonVi->soNhanVien++;
				}
			}
			else
			{
				pNhanVien->nhanVien.chucVu = chucVu;
				if (_stricmp(chucVu.c_str(), "nhan vien") != 0) {
					DonVi *pDonVi;
					Node_NhanVien *pNode = searchNode(ds_DonVi, pDonVi, maNhanVien);
					if (_stricmp(pNode->nhanVien.maNhanVien.c_str(), maNhanVien.c_str()) == 0) {
						if (pNode->next == NULL) {
							Node_NhanVien *p = pDonVi->nhanVien;
							pDonVi->nhanVien = NULL;
							Node_NhanVien *p1 = pDonVi->canBo;
							pDonVi->canBo = p;
							p->next = p1;
						}
						else
						{
							Node_NhanVien *p = pDonVi->nhanVien;
							pDonVi->nhanVien = pNode->next;
							Node_NhanVien *p1 = pDonVi->canBo;
							pDonVi->canBo = p;
							p->next = p1;
						}
					}
					else
					{
						Node_NhanVien *pTemp = pNode->next;
						pNode->next = pTemp->next;
						Node_NhanVien *pCB = pDonVi->canBo;
						pDonVi->canBo = pTemp;
						pTemp->next = pCB;
					}
					pDonVi->soNhanVien--;
				}
			}
			break;
		}
		case 9: {
			string donVi;
			cout << "Nhap Don Vi: ";
			cin.ignore();
			getline(cin, donVi);
			if (_stricmp(pNhanVien->nhanVien.donVi.c_str(), donVi.c_str()) != 0) {
				DonVi *pDonVi;
				Node_NhanVien *pNode = searchNode(ds_DonVi, pDonVi, maNhanVien);
				DonVi *pDonVi1 = ds_DonVi;
				int n = 0;
				while (true)
				{
					if (_stricmp(pDonVi1->tenDonVi.c_str(), donVi.c_str()) == 0) {
						n++;
						pNhanVien->nhanVien.donVi = donVi;
						if (_stricmp(pNhanVien->nhanVien.chucVu.c_str(), "nhan vien") == 0) {
							if (_stricmp(pNode->nhanVien.maNhanVien.c_str(), maNhanVien.c_str()) == 0) {
								pDonVi->nhanVien = pDonVi->nhanVien->next;
								Node_NhanVien *pTemp = pDonVi1->nhanVien;
								pDonVi1->nhanVien = pNode;
								pNode->next = pTemp;
							}
							else
							{
								Node_NhanVien *pTemp = pNode->next;
								pNode->next = pTemp->next;
								Node_NhanVien *p = pDonVi->nhanVien;
								pDonVi->nhanVien = pTemp;
								pTemp->next = p;
							}
							pDonVi->soNhanVien--;
							pDonVi1++;
						}
						else
						{
							if (_stricmp(pNode->nhanVien.maNhanVien.c_str(), maNhanVien.c_str()) == 0) {
								pDonVi->canBo = pDonVi->canBo->next;
								Node_NhanVien *pTemp = pDonVi1->canBo;
								pDonVi1->canBo = pNode;
								pNode->next = pTemp;
							}
							else
							{
								Node_NhanVien *pTemp = pNode->next;
								pNode->next = pTemp->next;
								Node_NhanVien *p = pDonVi->canBo;
								pDonVi->canBo = pTemp;
								pTemp->next = p;
							}
						}
					}
					if (pDonVi1->next == ds_DonVi) break;
					pDonVi1 = pDonVi1->next;
				}
				if (n == 0) return 1;
			}
			break;
		}
		case 10: {
			string ngayBatDauLamViec;
			cout << "Nhap ngay Bat dau lam viec: ";
			cin.ignore();
			getline(cin, ngayBatDauLamViec);
			pNhanVien->nhanVien.ngayBatDauLamViec = ngayBatDauLamViec;
			break;
		}
		default:
			break;
		}
		return 0;
	}
}

int main()
{
	ifstream input;
	input.open("NhanVien.txt", ios_base::in);
	if (input.fail()) {
		cout << "Failed to open this file!" << endl;
		system("pause");
		return -1;
	}
	DonVi *ds_DonVi;
	create_LinkList_DonVi(ds_DonVi);
	cin.sync();
	int n = DocFile(input, ds_DonVi);
	if (n == -1) {
		cout << "file rong! Vui long them thong tin vao file hoac chon 2 de them nhan vien vao cong ty!" << endl;
		/*	system("pause");
			return -1;*/
	}
	int Lua_Chon;
	do
	{
		cout << "-------------------------------------------menu----------------------------------------------" << endl;
		cout << "1. Hien thi cac thong tin co ban ve BKCorporation?" << endl;
		cout << "2. Tim kiem thong tin cua nhan vien?" << endl;
		cout << "3. Hien thi tinh trang lam viec cua nhan vien?" << endl;
		cout << "4. Hien thi thong tin cua mot don vi?" << endl;
		cout << "5. Them nhan vien moi?" << endl;
		cout << "6. Cap nhat thong tin co ban cua mot nhan vien?" << endl;
		cout << "7. Thoat!" << endl;
		cout << "Ban chon: ";
		cin >> Lua_Chon;
		if (cin.fail() || Lua_Chon < 1 || Lua_Chon > 7) { //neu khong phai la so nguyen
			cin.clear(); // bo qua co loi
			cin.ignore(32767, '\n'); //xoa di tat ca cac ki tu trong bo nho dem den khi gap \n
			system("cls");
			cout << "Ban chon sai! vui long thu lai!" << endl;
		}
		else
		{
			system("cls");
			switch (Lua_Chon)
			{
			case 1: {
				cout << "Thong tin co ban ve cong ty BKCorporation: " << endl;
				XuatThongTinCoBanVeCongTy(ds_DonVi);
				break;
			}
			case 2: {
				if (ds_DonVi == NULL) {
					cout << "Danh sach cong ty rong!" << endl;
					break;
				}
				cout << "Nhap thong tin tim kiem: ";
				string giaTriTimKiem;
				cin.ignore();
				getline(cin, giaTriTimKiem);
				Node_NhanVien *pNode;
				pNode = Search(ds_DonVi, giaTriTimKiem);
				if (pNode == NULL) {
					cout << "Khong tim thay thong tin ban vua nhap" << endl;
				}
				else
				{
					cout << left << setw(15) << "Ho" << setw(7) << "Ten" << setw(8) << "Ma NV" << setw(12) << "Ngay Sinh"
						<< setw(10) << "Que Quan" << setw(20) << "Dia Chi" << setw(20)
						<< "Don Vi" << setw(10) << "Chuc Vu" << endl;
					while (true)
					{
						if (pNode == NULL) break;
						xuatThongTinCoBanMotNhanVien(pNode->nhanVien);
						pNode = pNode->next;
					}
				}
				break;
			}
			case 3: {
				if (ds_DonVi == NULL) {
					cout << "Danh sach cong ty rong!" << endl;
					break;
				}
				cout << "Nhap ma nhan vien: ";
				string maNhanVien;
				cin.ignore();
				getline(cin, maNhanVien);
				HienThiTrangThaiLamViec(ds_DonVi, maNhanVien);
				break;
			}
			case 4: {
				if (ds_DonVi == NULL) {
					cout << "Danh sach cong ty rong!" << endl;
					break;
				}
				string tenDonVi;
				cout << "Nhap ten don vi can tim: ";
				cin.ignore();
				getline(cin, tenDonVi);
				xuatThongTinCoBanVeMotDonVi(ds_DonVi, tenDonVi);
				break;
			}
			case 5: {
				ThemMotNhanVien(ds_DonVi);
				break;
			}
			case 6: {
				if (ds_DonVi == NULL) {
					cout << "Danh sach cong ty rong!" << endl;
					break;
				}
				cout << "Nhap ma nhan vien:";
				cin.ignore();
				string maNhanVien;
				getline(cin, maNhanVien);
				int n = UpdateInfo_NhanVien(ds_DonVi, maNhanVien);
				if (n == 0) {
					cout << "Cap nhat thong tin thanh cong!" << endl;
				}
				else
				{
					if (n == 1) cout << "Khong co don vi ban vua nhap" << endl;
					else
					{
						if (n == -1) cout << "Khong co nhan vien mang ma nay trong cong ty." << endl;
					}
				}
				break;
			}
			case 7: {
				break;
			}
			}
		}
	} while (Lua_Chon != 7);
	input.close();// dong file
	system("pause");
	return 0;
}