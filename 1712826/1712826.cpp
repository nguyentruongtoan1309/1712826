﻿#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//Cấu trúc thông tin sinh viên
struct ThongTin
{
	string MSSV, Ten, Khoa, Email, NgaySinh, HinhAnh, MoTa, *SoThich;
};

//Hàm kiểm tra tổng số sinh viên
//Output: 
//1. Số sinh viên hợp lệ (lớn hơn 0 và nhỏ hơn hoặc bằng số sinh viên trong dữ liệu)
//0. Không thỏa điều kiện trên
int KiemTraTongSoSinhVien(int Tong_SV)
{
	//Mở file csv và đọc file csv
	ifstream Filecsv("SinhVien.csv");
	if (!Filecsv)
	{
		perror("Mo file that bai.\n");
	}

	//Đếm số sinh viên trong dữ liệu
	string TempStr; //Chuỗi tạm chứa thông tin
	int Count = 0; //Biến đếm số sinh viên
	while (!Filecsv.eof())
	{
		getline(Filecsv, TempStr);
		Count += 1;
	}

	//Kiểm tra tổng sinh viên với số sinh viên người dùng nhập
	if (Tong_SV > Count)
	{
		return 0;
	}
	return 1;
}

//Hàm chuẩn hóa chuỗi thông tin
void ChuanHoaThongTin(string &SinhVien)
{
	for (int i = 1; i < SinhVien.length() - 1; i++)
	{
		if (SinhVien[i] == ',' && SinhVien[i + 1] == ' ' && SinhVien[i - 1] == '\"')
		{
			SinhVien.erase(i, 3);
		}
	}
}
//Hàm tái cấp phát bộ nhớ
void TaiCapPhatBoNho(string *&SinhVien_CT, int SV_index)
{
	string *temp = new string[SV_index];
	for (int i = 0; i < SV_index; i++)
	{
		*(temp + i) = *(SinhVien_CT + i);
	}
	SinhVien_CT = new string[SV_index + 1];
	for (int i = 0; i < SV_index; i++)
	{
		*(SinhVien_CT + i) = *(temp + i);
	}
	delete[] temp;
}

//Hàm tách thông tin từ chuỗi thông tin các sinh viên
void TachThongTin(string SinhVien, ThongTin SV[], int index, string *&SinhVien_CT, int SV_index, int *&ThuocTinh)
{
	//Chuẩn hóa chuỗi thông tin
	ChuanHoaThongTin(SinhVien);

	//Chuyển string thành char *
	char *c = (char*)SinhVien.c_str();
	char *nl = NULL;
	char temp[] = "\"";

	//Cấp phát vùng nhớ cho SinhVien_CT và gán số thuộc tính của sinh viên là 0
	SinhVien_CT = new string[1];
	ThuocTinh[index] = 0;

	//Tách dữ liệu từ file
	char *p = strtok_s(c, temp, &nl);
	while (p != NULL)
	{
		int n = strlen(p);
		for (int i = 0; i < n; i++)
		{
			SinhVien_CT[SV_index].push_back(p[i]);
		}
		SV_index++;
		TaiCapPhatBoNho(SinhVien_CT, SV_index);
		p = strtok_s(NULL, temp, &nl);
		//Cộng thuộc tính với số gia 1
		ThuocTinh[index] += 1;
	}

	//Đưa dữ liệu vào trong struct (trừ sở thích)
	SV[index].MSSV = SinhVien_CT[0];
	SV[index].Ten = SinhVien_CT[1];
	SV[index].Khoa = SinhVien_CT[2];
	SV[index].Email = SinhVien_CT[3];
	SV[index].NgaySinh = SinhVien_CT[4];
	SV[index].HinhAnh = SinhVien_CT[5];
	SV[index].MoTa = SinhVien_CT[6];

	//Đưa sở thích vào struct
	SV[index].SoThich = new string[SV_index - 6];
	for (int i = 0; i < SV_index - 6; i++)
	{
		SV[index].SoThich[i] = SinhVien_CT[i + 7];
	}
}
//Hàm get information
//Output: (Thông tin của các sinh viên)
//1. Số sinh viên hợp lệ
//0. Số sinh viên không hợp lệ
int GetInformation(ThongTin *&SV, int &Tong_SV, string *&SinhVien, string *&SinhVien_CT, int *&ThuocTinh, int &SV_index)
{
	//Nhập tổng số sinh viên
	cout << "Nhap tong so sinh vien: ";
	cin >> Tong_SV;
	cout << endl;
	while (Tong_SV <= 0)
	{
		cout << "So sinh vien khong hop le, moi nhap lai: ";
		cin >> Tong_SV;
	}

	//Kiểm tra tổng sinh viên có hợp lệ không
	int Test = KiemTraTongSoSinhVien(Tong_SV);
	if (Test == 0)
	{
		return 0;
	}

	//Cấp phát bộ nhớ cho các con trỏ
	SV = new ThongTin[Tong_SV];
	SinhVien = new string[Tong_SV];
	SV_index = 0;
	ThuocTinh = new int[Tong_SV];

	//Lấy thông tin từ file csv
	//Mở file csv và đọc file csv
	ifstream Filecsv("SinhVien.csv");
	if (!Filecsv)
	{
		perror("Mo file that bai.\n");
	}
	//Lấy thông tin và đưa vào chuỗi thông tin các sinh viên
	for (int i = 0; i < Tong_SV; i++)
	{
		getline(Filecsv, SinhVien[i]);
		//Tách từ chuỗi tổng đưa vào các thuộc tính các sinh viên
		TachThongTin(SinhVien[i], SV, i, SinhVien_CT, SV_index, ThuocTinh);
	}

	return 1;
}
//Hàm tải thông tin
//Input: Thông tin sinh viên được chứa trong các struct
//Output: Thông tin trong struct ban đầu được đưa lên file html
void TaiThongTin(ThongTin *&SV, string HTML, int index, int *ThuocTinh)
{
	//Mo file
	string FileName;
	FileName = "Profiles/" + SV[index].MSSV + ".html";
	ofstream f1(FileName);

	//Dua thong tin len file
	//Name
	int in = 0;
	char *temp;
	do
	{
		temp = (char*)SV[index].Ten.c_str();
		in = HTML.find("$name", in + 1, 5);
		if (in != std::string::npos)
		{
			HTML.replace(in, 5, temp);
		}
	} while (in != std::string::npos);

	//MSSV
	in = 0;
	do
	{
		temp = (char*)SV[index].MSSV.c_str();
		in = HTML.find("$id", in + 1, 3);
		if (in != std::string::npos)
		{
			HTML.replace(in, 3, temp);
		}
	} while (in != std::string::npos);

	//Khoa
	in = 0;
	do
	{
		temp = (char*)SV[index].Khoa.c_str();
		in = HTML.find("$faculty", in + 1, 8);
		if (in != std::string::npos)
		{
			HTML.replace(in, 8, temp);
		}
	} while (in != std::string::npos);

	//Ngay sinh
	in = 0;
	temp = (char*)SV[index].NgaySinh.c_str();
	in = HTML.find("$birthday");
	HTML.replace(in, 9, temp);

	//Mo ta
	in = 0;
	temp = (char*)SV[index].MoTa.c_str();
	in = HTML.find("$info");
	HTML.replace(in, 5, temp);

	//Hinh anh
	in = 0;
	temp = (char*)SV[index].HinhAnh.c_str();
	in = HTML.find("$avatar");
	HTML.replace(in, 7, temp);

	//Email
	in = 0;
	temp = (char*)SV[index].Email.c_str();
	in = HTML.find("$email");
	HTML.replace(in, 11, temp);

	//Email
	in = 0;
	temp = (char*)SV[index].Email.c_str();
	in = HTML.find("$email");
	HTML.replace(in, 11, temp);

	//So thich
	in = 0;
	int ThuocTinhSoThich = ThuocTinh[index] - 7;
	in = HTML.find("$hobbies");
	string Hobbies = "";
	for (int k = 0; k < ThuocTinhSoThich; k++)
	{
		Hobbies += "<li>" + SV[index].SoThich[k] + "</li>" + "\n";
	}
	temp = (char*)Hobbies.c_str();
	HTML.replace(in, 8, temp);

	//Dua du lieu vao html
	f1 << HTML;
	f1.close();
}
//Hàm Get Template
//Input: chuỗi HTML
//Output: dữ liệu html template chứa vào chuỗi HTML
void GetTemplate(string &HTML)
{
	//Mở file html
	ifstream f;
	f.open("Personal.txt");
	if (!f)
	{
		perror("Mo file that bai.\n");
	}
	string T; //Chuỗi tạm
	while (!f.eof())
	{
		getline(f, T);
		HTML += T;
		HTML += "\n";
	}

	//Đóng file
	f.close();
}
void main()
{
	//Khai báo các biến sử dụng
	string HTML; //Chuỗi chứa cấu trúc file HTML
	ThongTin *SV = NULL; //Con trỏ cấu trúc thông tin sinh vien
	int Tong_SV; //Biến chứa tổng số sinh viên
	string *SinhVien = NULL; //Con trỏ chứa thông tin của sinh viên
	string *SinhVien_CT = NULL; //Con trỏ chứa thuộc tính của sinh viên
	int SV_index; //Chỉ mục các thuộc tính các sinh viên
	int *ThuocTinh = NULL; //Con trỏ chứa số thuộc tính của các sinh viên

						   //Lấy thông tin sinh viên
	int Test = GetInformation(SV, Tong_SV, SinhVien, SinhVien_CT, ThuocTinh, SV_index);
	if (Test == 0)
	{
		cout << "Error. The number of students is out of memory!" << endl << endl;
		system("pause");
		return;
	}

	//Lấy template từ file html
	GetTemplate(HTML);

	//Đưa thông tin trong struct vào file html
	for (int i = 0; i < Tong_SV; i++)
	{
		TaiThongTin(SV, HTML, i, ThuocTinh);
	}

	//Thông báo hoàn tất
	cout << "All the transmission are completed. Please check your files for any mistake!" << endl << endl;

	//Giải phóng vùng nhớ
	delete[] SV;
	delete[] SinhVien;
	delete[] SinhVien_CT;
	delete[] ThuocTinh;

	system("pause");
}