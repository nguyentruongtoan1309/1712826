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
