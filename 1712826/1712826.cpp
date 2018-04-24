#include <iostream>
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