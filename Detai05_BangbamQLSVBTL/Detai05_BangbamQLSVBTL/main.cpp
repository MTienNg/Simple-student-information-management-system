#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>

#define SIZE 100
#define HASH_TABLE_SIZE 100
#define MAX_DETAI 100
#define MAX_SV_PER_SLOT 10 // Số lượng sinh viên tối đa trong mỗi ô của bảng băm
struct SinhVienList {
	struct SinhVien* data[MAX_SV_PER_SLOT];
	int count;
};

//Sinh Vien
struct SinhVien {
	char maSV[6];
	char hoSV[8];
	char tenSV[14];
	char ngaythangnamsinh[12];
	char sdt[12];
};
struct HocPhan {
	char maHP[6];
	char tenHP[15];
	char ngaybatdau[12];
	char ngayketthuc[13];

};
struct DeTai {
	char maDT[5];
	char tenDT[47];
	int soluongsv;
	HocPhan maHP;
};

struct KetQua {
	SinhVien maSV;
	DeTai maDT;
	float diembaocao;
	float diemcaidat;
	float diemtrinhbay;

};
//De tai



////CÂU 1
///*-----------KHAI BÁO CÁC CẤU TRÚC CHO BẢNG BĂM-----------*/
struct HashNode {
	char key[20];
	void* data; // Con trỏ đến dữ liệu
};

// Khởi tạo bảng băm
struct HashNode* hashTable[SIZE];

// Hash Function
unsigned int hashFunction(char* str) {
	unsigned int hash = 0;
	while (*str) {
		hash = hash * 31 + *str++;
	}
	return hash % HASH_TABLE_SIZE;
}

// Hàm thêm phần tử vào bảng băm
void insert(void* data, char* key) {
	int index = hashFunction(key);
	struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
	strcpy(newNode->key, key);
	newNode->data = data;
	// Thêm newNode vào bảng băm tại chỉ mục index
	hashTable[index] = newNode;
}

// Hàm tìm kiếm phần tử trong bảng băm
void* search(char* key) {
	int index = hashFunction(key);
	if (hashTable[index] != NULL && strcmp(hashTable[index]->key, key) == 0) {
		return hashTable[index]->data; // Trả về dữ liệu tại chỉ mục index nếu key khớp
	}
	return NULL; // Trả về NULL nếu không tìm thấy
}
///*-----------------------------------------------------------------*/





//CÂU 2
/*------------- ĐỌC DỮ LIỆU TỪ FILE -------------*/
void docDuLieuHocPhan(struct HocPhan& hp, struct DeTai& dt) {
	FILE* fp1 = fopen("hocphan.txt", "r");
	if (fp1 == NULL) {
		printf("Khong the mo file hocphan.txt!\n");
		return;
	}
	while (fscanf(fp1, "%s %s %s %[^\n]", hp.maHP, hp.ngaybatdau, hp.ngayketthuc, hp.tenHP) == 4) {

	}
	fclose(fp1);
}

void docDuLieuSinhVien(struct SinhVien& sv) {
	FILE* fp1 = fopen("sinhvien.txt", "r");
	if (fp1 == NULL) {
		printf("Khong the mo file sinhvien.txt!\n");
		return;
	}
	while (fscanf(fp1, "%s %s %s %s %[^\n]", sv.maSV, sv.ngaythangnamsinh, sv.sdt, sv.hoSV, sv.tenSV) == 5) {
	}
	fclose(fp1);

}

void docDuLieuDeTai(struct DeTai& dt, struct HocPhan& hp) {
	FILE* fp = fopen("detai.txt", "r");
	if (fp == NULL) {
		printf("Khong the mo file detai.txt!\n");
		return;
	}
	while (fscanf(fp, "%s %s %d %[^\n] ", dt.maDT, hp.maHP, &dt.soluongsv, dt.tenDT) == 4) {
	}
	fclose(fp);
}

void docDuLieuKetQua(struct KetQua& kq, struct SinhVien& sv, struct DeTai& dt, struct HocPhan& hp) {
	FILE* fp = fopen("ketqua.txt", "r");
	if (fp == NULL) {
		printf("Khong the mo file ketqua.txt!\n");
		return;
	}
	while (fscanf(fp, "%s %s %f %f %f", sv.maSV, dt.maDT, &kq.diembaocao, &kq.diemcaidat, &kq.diemtrinhbay) == 5) {

	}

	fclose(fp);
}
/*-----------------------------------------------------------*/


//CÂU 3
//them de tai
void addDeTai(struct DeTai& dt) {
	FILE* fp = fopen("detai.txt", "a");
	if (fp == NULL) {
		printf("Khong the mo file detai.txt!\n");
		return;
	}

	printf("Nhap ma de tai: ");
	scanf("%s", dt.maDT);
	fprintf(fp, "%s ", dt.maDT); // Ghi ma de tai với khoảng cách 10 ký tự

	printf("Nhap ten de tai: ");
	getchar(); // Xóa bộ nhớ đệm
	fgets(dt.tenDT, sizeof(dt.tenDT), stdin);
	dt.tenDT[strcspn(dt.tenDT, "\n")] = '\0'; // Loại bỏ ký tự xuống dòng thừa
	fprintf(fp, "%-42s", dt.tenDT); // Ghi ten de tai với khoảng cách 5 ký tự


	printf("Nhap ma hoc phan: ");
	scanf("%s", dt.maDT);
	fprintf(fp, "%s\n", dt.maDT); // Ghi ma hoc phan và xuống dòng
	//Nhap so luong sv
	do {
		printf("Nhap so luong sinh vien (lon hon 1): ");
		scanf("%d", &dt.soluongsv);
		if (dt.soluongsv <= 1) {
			printf("So luong sinh vien phai lon hon 1. Vui long nhap lai.\n");
		}
	} while (dt.soluongsv <= 1);
	fprintf(fp, "%d ", dt.soluongsv); // Ghi so luong sinh vien

	fclose(fp);
}


//cau 4
//tim kiem theo ma sinh vien
void searchSVmssv(char check[]) {
	FILE* fp = fopen("sinhvien.txt", "r");
	if (fp == NULL) {
		printf("Khong the mo file sinhvien.txt!\n");
		return;
	}
	char line[100]; // Đảm bảo đủ lớn để đọc dữ liệu từ mỗi dòng
	struct SinhVienList* table[HASH_TABLE_SIZE] = { NULL };

	// Đọc từng dòng trong tệp và thêm vào bảng băm
	while (fgets(line, sizeof(line), fp)) {
		struct SinhVien* sv = (struct SinhVien*)malloc(sizeof(struct SinhVien));
		if (sv == NULL) {
			printf("Loi cap phat bo nho!\n");
			fclose(fp);
			return;
		}
		// Lấy mã số sinh viên từ dòng hiện tại
		strncpy(sv->maSV, line, 4);
		sv->maSV[4] = '\0'; // Kết thúc chuỗi

		// Băm mã số sinh viên và thêm vào bảng băm
		unsigned int index = hashFunction(sv->maSV);
		if (table[index] == NULL) {
			table[index] = (struct SinhVienList*)malloc(sizeof(struct SinhVienList));
			for (int i = 0; i < MAX_SV_PER_SLOT; i++) {
				table[index]->data[i] = NULL;
			}
			table[index]->count = 0;
		}
		if (table[index]->count < MAX_SV_PER_SLOT) {
			table[index]->data[table[index]->count++] = sv;
		}
		else {
			printf("Khong the them sinh vien vao vi tri %d\n", index);
			free(sv); // Giải phóng bộ nhớ khi không thể thêm vào bảng băm
		}
	}
	fclose(fp);

	// Tìm kiếm sinh viên bằng mã số sinh viên
	unsigned int index = hashFunction(check);
	if (table[index] != NULL) {
		for (int i = 0; i < table[index]->count; i++) {
			if (strcmp(table[index]->data[i]->maSV, check) == 0) {
				printf("Tim thay sinh vien trong danh sach\n");
				return;
			}
		}
	}
	printf("Khong tim thay sinh vien trong danh sach!\n");
}

void kiemTraSinhVienTheoDeTai(char madetai[], char checksv[]) {
	FILE* fp = fopen("ketqua.txt", "r");
	if (fp == NULL) {
		printf("Khong the mo file ketqua.txt!\n");
		return;
	}
	struct KetQua kq;
	struct SinhVien sv;
	struct DeTai dt;

	int found = 0;
	while (fscanf(fp, "%s %s %f %f %f", sv.maSV, dt.maDT, &kq.diembaocao, &kq.diemcaidat, &kq.diemtrinhbay) == 5) {
		if (stricmp(dt.maDT, madetai) == 0 && stricmp(sv.maSV, checksv) == 0) {
			searchSVmssv(sv.maSV);
			found = 1;
			break;
		}
	}
	if (!found) {
		printf("Khong tim thay sinh vien trong danh sach!\n");
	}
	fclose(fp);
}

void kiemTraSinhVienTheoHocPhan(char mahocphan[], char checksv[]) {
	FILE* fp = fopen("detai.txt", "r");
	if (fp == NULL) {
		printf("Khong the mo file detai.txt!\n");
		return;
	}
	struct DeTai dt;
	struct HocPhan hp;

	int found = 0;

	while (fscanf(fp, "%s %s %d %[^\n]", dt.maDT, hp.maHP, &dt.soluongsv, dt.tenDT) == 4) {
		if (stricmp(hp.maHP, mahocphan) == 0) {
			kiemTraSinhVienTheoDeTai(dt.maDT, checksv);
			found = 1;
			break;
		}
	}
	if (!found) {
		printf("Khong tim thay sinh vien trong danh sach!\n");
		
	}
	fclose(fp);
}
void kq(char detai[]) {
	FILE* fp = fopen("ketqua.txt", "r");
	if (fp == NULL) {
		printf("Khong the mo file ketqua.txt!\n");
		return;
	}
	struct KetQua kq;
	struct DeTai dt;
	struct SinhVien sv;
	float score = 0;

	printf("\nMa sinh vien       | Diem bao cao    | Diem cai dat    | Diem trinh bay\n");
	printf("------------------------------------------------------------------------\n");

	while (fscanf(fp, "%s %s %f %f %f", sv.maSV, dt.maDT, &kq.diembaocao, &kq.diemcaidat, &kq.diemtrinhbay) == 5) {
		if (strcmp(detai, dt.maDT) == 0) {
			printf("%-18s |     %-9.1f   |     %-9.1f   |     %-9.1f\n\n", sv.maSV, kq.diembaocao, kq.diemcaidat, kq.diemtrinhbay);

		}

	}
	fclose(fp);
}
void kqsvhocphan(char hocphan[]) {
	FILE* fp = fopen("detai.txt", "r");
	if (fp == NULL) {
		printf("Khong the mo file detai.txt!\n");
		return;
	}
	struct DeTai dt;
	struct HocPhan hp;
	printf("\nKet qua cua hoc phan %s\n", hocphan);
	printf("-----------------------------------------------------------------------\n");

	while (fscanf(fp, "%s %s %d %[^\n] ", dt.maDT, hp.maHP, &dt.soluongsv, dt.tenDT) == 4) {
		// Loại bỏ ký tự xuống dòng cuối cùng từ mỗi chuỗi
		dt.maDT[strcspn(dt.maDT, "\n")] = '\0';
		dt.tenDT[strcspn(dt.tenDT, "\n")] = '\0';
		hp.maHP[strcspn(hp.maHP, "\n")] = '\0';


		if (strcmp(hocphan, hp.maHP) == 0) {
			printf("\nMa de tai: %s\n", dt.maDT);
			kq(dt.maDT);
		}

	}
	fclose(fp);
}

void thongtinsv(char mssv[]) {
	FILE* fp = fopen("sinhvien.txt", "r");
	if (fp == NULL) {
		printf("Khong the mo file sinhvien.txt!\n");
		return;
	}
	struct SinhVien sv;
	while (fscanf(fp, "%s %s %s %s %[^\n]", sv.maSV, sv.ngaythangnamsinh, sv.sdt, sv.hoSV, sv.tenSV) == 5) {


		fgetc(fp); // Đọc và bỏ qua ký tự xuống dòng

		// Kiểm tra xem mã sinh viên có khớp với mã đã cho không
		if (strcmp(sv.maSV, mssv) == 0) {
			printf("Ma sinh vien: %s\n", sv.maSV);
			printf("Ho va ten       : %s %s\n", sv.hoSV, sv.tenSV);
			printf("Ngay thang nam sinh: %s\n", sv.ngaythangnamsinh);
			printf("So dien thoai: %s\n\n", sv.sdt);

			fclose(fp);
			return; // Thoát khỏi hàm sau khi in thông tin sinh viên
		}
	}
	fclose(fp);
}
float diemtongket(float a, float b, float c) {

	float score = ((a * 0.4) + (b * 0.2) + (c * 0.4));
	return score;
}

void diem() {
	FILE* fp = fopen("ketqua.txt", "r");
	if (fp == NULL) {
		printf("Khong the mo file ketqua.txt!\n");
		return;
	}

	struct KetQua kq;
	struct DeTai dt;
	struct SinhVien sv;
	float max_score = -1; // Khởi tạo điểm lớn nhất với giá trị không thể đạt được
	char max_score_maSV[20]; // Lưu mã sinh viên có điểm cao nhất
	int num_max_scores = 0; // Số lượng sinh viên có điểm cao nhất
	struct SinhVien max_score_sv[100]; // Danh sách sinh viên có điểm cao nhất
	while (fscanf(fp, "%s %s %f %f %f", sv.maSV, dt.maDT, &kq.diembaocao, &kq.diemcaidat, &kq.diemtrinhbay) == 5) {
		// Tính điểm trung bình
		float score = diemtongket(kq.diembaocao, kq.diemtrinhbay, kq.diemcaidat);
		// Nếu điểm mới tính được lớn hơn điểm lớn nhất hiện tại, cập nhật điểm lớn nhất và mã sinh viên
		if (score > max_score) {
			max_score = score;
			strcpy(max_score_maSV, sv.maSV);
			num_max_scores = 1; // Đặt số lượng sinh viên có điểm cao nhất là 1
			max_score_sv[0] = sv; // Lưu thông tin của sinh viên có điểm cao nhất
		}
		else if (score == max_score) {
			// Nếu điểm mới tính được bằng điểm lớn nhất hiện tại, thêm sinh viên vào danh sách
			strcpy(max_score_sv[num_max_scores].maSV, sv.maSV);
			num_max_scores++; // Tăng số lượng sinh viên có điểm cao nhất
		}
	}

	fclose(fp);

	// Kiểm tra xem có điểm lớn nhất nào không
	if (max_score >= 0) {
		// In ra điểm lớn nhất và thông tin của tất cả sinh viên có điểm đó
		printf("Diem trung binh lon nhat la: %.2f\n", max_score);
		printf("Thong tin sinh vien co diem cao nhat: \n\n");
		for (int i = 0; i < num_max_scores; i++) {
			printf("Sinh vien %d:\n", i + 1);
			thongtinsv(max_score_sv[i].maSV);
		}
	}
	else {
		printf("Khong tim thay diem trung binh nao cho de tai \n");
	}
}
void thongtinHP(char maDT[]) {
	FILE* fp = fopen("detai.txt", "r");
	if (fp == NULL) {
		printf("Khong the mo file detai.txt!\n");
		return;
	}
	struct DeTai dt;
	struct HocPhan hp;
	while (fscanf(fp, "%s %s %d %[^\n]", dt.maDT, hp.maHP, &dt.soluongsv, dt.tenDT) == 4) {
		fgetc(fp); // Đọc và bỏ qua ký tự xuống dòng

		if (strcmp(dt.maDT, maDT) == 0) {
			printf("Ma hoc phan: %s\n", hp.maHP);
			fclose(fp);
			return;
		}
	}
	fclose(fp);
}

void timLopHocPhan() {
	FILE* fp = fopen("ketqua.txt", "r");
	if (fp == NULL) {
		printf("Khong the mo file ketqua.txt!\n");
		return;
	}

	struct KetQua kq;
	struct DeTai dt;
	struct SinhVien sv;
	float max_score = -1; // Khởi tạo điểm lớn nhất với giá trị không thể đạt được
	char max_score_maDT[20]; // Lưu mã sinh viên có điểm cao nhất
	int num_max_scores = 0; // Số lượng sinh viên có điểm cao nhất
	struct DeTai max_score_dt[100]; // Danh sách sinh viên có điểm cao nhất
	while (fscanf(fp, "%s %s %f %f %f", sv.maSV, dt.maDT, &kq.diembaocao, &kq.diemcaidat, &kq.diemtrinhbay) == 5) {
		// Tính điểm trung bình
		float score = diemtongket(kq.diembaocao, kq.diemtrinhbay, kq.diemcaidat);
		// Nếu điểm mới tính được lớn hơn điểm lớn nhất hiện tại, cập nhật điểm lớn nhất và mã sinh viên
		if (score > max_score) {
			max_score = score;
			strcpy(max_score_maDT, dt.maDT);
			num_max_scores = 1; // Đặt số lượng sinh viên có điểm cao nhất là 1
			max_score_dt[0] = dt; // Lưu thông tin của sinh viên có điểm cao nhất
		}
		else if (score == max_score) {
			// Nếu điểm mới tính được bằng điểm lớn nhất hiện tại, thêm sinh viên vào danh sách
			strcpy(max_score_dt[num_max_scores].maDT, dt.maDT);
			num_max_scores++; // Tăng số lượng sinh viên có điểm cao nhất
		}
	}

	fclose(fp);

	// Kiểm tra xem có điểm lớn nhất nào không
	if (max_score >= 0) {
		// In ra điểm lớn nhất và thông tin của tất cả sinh viên có điểm đó
		for (int i = 0; i < num_max_scores; i++) {

			thongtinHP(max_score_dt[i].maDT);
		}
	}
	else {
		printf("Khong tim thay diem trung binh nao cho de tai \n");
	}
}

//cau 6
// Hàm so sánh mã sinh viên
int compareMasv(const void* a, const void* b) {
    const struct SinhVien* dt1 = (const struct SinhVien*)a;
    const struct SinhVien* dt2 = (const struct SinhVien*)b;
    return strcmp(dt1->maSV, dt2->maSV);
}

// Hàm kiểm tra đề tài
void kiemtraDeTai(char madetai[]) {
    FILE* fp = fopen("ketqua.txt", "r");
    if (fp == NULL) {
        printf("Khong the mo file ketqua.txt!\n");
        return;
    }

    struct KetQua dskq[30];
    struct DeTai dsdt[30];
    struct SinhVien dssv[30];

    int j = 0;

    // Đọc dữ liệu từ file
    while (fscanf(fp, "%s %s %f %f %f", dssv[j].maSV, dsdt[j].maDT, &dskq[j].diembaocao, &dskq[j].diemcaidat, &dskq[j].diemtrinhbay) == 5) {
        if (stricmp(dsdt[j].maDT, madetai) == 0) {
            j++;
        }
    }
    fclose(fp);

    // Sắp xếp danh sách kết quả theo mã sinh viên
    qsort(dskq, j, sizeof(struct KetQua), compareMasv);

    // In ra danh sách sinh viên
	for (int k = 0; k < j; k++) {
		printf("| %-10s | %-10.2f | %-10.2f | %-10.2f |\n", dssv[k].maSV, dskq[k].diembaocao, dskq[k].diemcaidat, dskq[k].diemtrinhbay);
	}
	printf("\n");
}

// Hàm sắp xếp sinh viên theo đề tài
void Sapxepsinhvien() {
	FILE* fp = fopen("detai.txt", "r");
	if (fp == NULL) {
		printf("Không thể mở file detai.txt!\n");
		return;
	}

	struct DeTai dt;
	struct HocPhan hp;

	// Đọc dữ liệu từ file
	while (fscanf(fp, "%s %s %d %[^\n]", dt.maDT, hp.maHP, &dt.soluongsv, dt.tenDT) == 4) {
		// Xử lý chuỗi để loại bỏ khoảng trắng, tab và xuống dòng
		char* token = strtok(dt.maDT, " \t\n");
		if (token != NULL) {
			strncpy(dt.maDT, token, sizeof(dt.maDT));
			dt.maDT[sizeof(dt.maDT) - 1] = '\0';
		}

		char* token1 = strtok(dt.tenDT, " \t\n");
		if (token1 != NULL) {
			strncpy(dt.tenDT, token1, sizeof(dt.tenDT));
			dt.tenDT[sizeof(dt.tenDT) - 1] = '\0';
		}

		printf("HocPhan: %s\n", hp.maHP);
		printf("Danh sach sinh vien:\n");
		kiemtraDeTai(dt.maDT);
	}
	fclose(fp);
}



//cau 7
int compare(const void* a, const void* b) {
	const struct DeTai* dt1 = (const struct DeTai*)a;
	const struct DeTai* dt2 = (const struct DeTai*)b;
	return dt2->soluongsv - dt1->soluongsv; // Sắp xếp giảm dần theo số lượng sinh viên
}
void inthongtindetai(struct DeTai& dt) {
	FILE* fp = fopen("detai.txt", "r");
	if (fp == NULL) {
		printf("Khong the mo file detai.txt!\n");
		return;
	}
	struct DeTai danhSachDeTai[30];
	struct HocPhan danhSachHocPhan[30];

	int count = 0;

	// Đọc thông tin của từng đề tài từ tệp
	while (fscanf(fp, "%s %s %d %[^\n]", danhSachDeTai[count].maDT, danhSachHocPhan[count].maHP, &danhSachDeTai[count].soluongsv, danhSachDeTai[count].tenDT) == 4) {
		// Lọc các đề tài có số lượng sinh viên không vượt quá 3
		if (danhSachDeTai[count].soluongsv <= 3) {
			count++;
		}

	}
	fclose(fp);
	// Sắp xếp lại mảng các đề tài theo thứ tự giảm dần của số lượng sinh viên
	qsort(danhSachDeTai, count, sizeof(struct DeTai), compare);
	printf("| %-10s | %-10s | %-20s | %-50s |\n", "MaDeTai", "MaHocPhan", "SoLuongSV", "TenDeTai");
	printf("|------------|------------|----------------------|----------------------------------------------------|\n");
	// In ra thông tin của các đề tài đã sắp xếp
	for (int i = 0; i < count; i++) {
		printf("| %-10s | %-10s | %-20d | %-50s |\n",
			danhSachDeTai[i].maDT,
			danhSachHocPhan[i].maHP,
			danhSachDeTai[i].soluongsv,
			danhSachDeTai[i].tenDT);
	}

	fclose(fp);
}
//cau 8
void BangdiemSinhVien(char mssv[]) {
	struct SinhVien sv;
	FILE* fp1 = fopen("sinhvien.txt", "r");
	if (fp1 == NULL) {
		printf("Khong the mo file sinhvien.txt!\n");
		return;
	}
	FILE* fp2 = fopen("ketquahoctap.txt", "a");
	if (fp2 == NULL) {
		printf("Loi mo file!");
		fclose(fp2); // Đóng file trước khi thoát
		return;
	}
	while (fscanf(fp1, "%s %s %s %s %[^\n]", sv.maSV, sv.ngaythangnamsinh, sv.sdt, sv.hoSV, sv.tenSV) == 5) {
		if (strcmp(mssv, sv.maSV) == 0) {
			fprintf(fp2, "Ma Sinh Vien: %s\n", sv.maSV);
			fprintf(fp2, "Ho Sinh Vien: %s\n", sv.hoSV);
			fprintf(fp2, "Ten Sinh Vien: %s\n", sv.tenSV);
			continue;

		}
	}
	fclose(fp1); // Đóng file ở cuối hàm
	fclose(fp2);
}
void BangdiemDeTai(char madetai[]) {
	struct KetQua kq;
	struct DeTai dt;
	struct SinhVien sv;
	FILE* fp = fopen("ketqua.txt", "r");
	if (fp == NULL) {
		printf("Khong the mo file ketqua.txt!\n");
		return;
	}
	FILE* fp2 = fopen("ketquahoctap.txt", "a"); // Mở file ở chế độ ghi tiếp
	if (fp2 == NULL) {
		printf("Loi mo file!");
		fclose(fp2);
		return;
	}
	while (fscanf(fp, "%s %s %f %f %f", sv.maSV, dt.maDT, &kq.diembaocao, &kq.diemcaidat, &kq.diemtrinhbay) == 5) {
		if (stricmp(dt.maDT, madetai) == 0) {
			BangdiemSinhVien(sv.maSV); // Gọi hàm để in thông tin sinh viên
			fprintf(fp2, "Diem tong ket: %f\n", diemtongket(kq.diembaocao, kq.diemtrinhbay, kq.diemcaidat));
			continue;

		}
	}
	fclose(fp);
	fclose(fp2);
}

void BangDiem(char hocphan[]) {
	FILE* fp = fopen("detai.txt", "r");
	if (fp == NULL) {
		printf("Khong the mo file detai.txt!\n");
		return;
	}
	struct DeTai dt;
	struct HocPhan hp;
	struct SinhVien sv;
	int found = 0;
	char maDTCanTim[6];
	FILE* fp1 = fopen("hocphan.txt", "r");
	if (fp1 == NULL) {
		printf("Khong the mo file hocphan.txt!\n");
		return;
	}
	while (fscanf(fp1, "%s %s %s %[^\n]", hp.maHP, hp.ngaybatdau, hp.ngayketthuc, hp.tenHP) == 4) {

	}
	FILE* fp2 = fopen("ketquahoctap.txt", "a");
	if (fp2 == NULL) {
		printf("Loi mo file!");
		return;
	}

	while (fscanf(fp, "%s %s %d %[^\n]", dt.maDT, hp.maHP, &dt.soluongsv, dt.tenDT) == 4) {


		char* token = strtok(dt.maDT, " \t\n"); // cắt chuỗi theo dấu cách, tab, và dấu xuống dòng
		if (token != NULL) {
			strncpy(dt.maDT, token, sizeof(dt.maDT)); // sao chép chuỗi không có khoảng trắng vào maSV
			dt.maDT[sizeof(dt.maDT) - 1] = '\0'; // đảm bảo kết thúc chuỗi
		}
		char* token1 = strtok(dt.tenDT, " \t\n"); // cắt chuỗi theo dấu cách, tab, và dấu xuống dòng
		if (token1 != NULL) {
			strncpy(dt.tenDT, token1, sizeof(dt.tenDT)); // sao chép chuỗi không có khoảng trắng vào maSV
			dt.tenDT[sizeof(dt.tenDT) - 1] = '\0'; // đảm bảo kết thúc chuỗi
		}

		if (strcmp(hocphan, hp.maHP) == 0) {
			fprintf(fp2, "Ma hoc phan: %s\n", hp.maHP);
			fprintf(fp2, "Ten hoc phan: %s\n", hp.tenHP);
			while (fscanf(fp, "%s %s %d %[^\n]", dt.maDT, dt.maHP, &dt.soluongsv, dt.tenDT) == 4) {
				if (strcmp(hp.maHP, hocphan) == 0) {
					BangdiemDeTai(dt.maDT);
				}
			}
		}

	}
	fclose(fp2); // Đóng file ở cuối hàm
	fclose(fp);
	fclose(fp1);
}


void tieuchi() {
	printf("\n               ******************************* CHỌN TIÊU CHÍ TÌM KIẾM *******************************\n\n");
	printf("                              0. Quay lai\n");
	printf("                              1. Ma sinh vien\n");
	printf("                              2. Ten đe tai\n");
	printf("                              3. Ten hoc phan\n\n");
	printf("               ***************************************************************************************\n");
}


void menu() {
	printf("\n               *************************************** MENU ***************************************\n\n");
	printf("                              1. Them de tai vao danh sach cac de tai\n");
	printf("                              2. Tim kiem sinh vien\n");
	printf("                              3. In ra ket qua cua sinh vien theo ten hoc phan\n");
	printf("                              4. In ra thong tin sinh vien co diem tong ket cao nhat\n");
	printf("                              5. Tim lop hoc phan co sinh vien cao diem nhat\n");
	printf("                              6. Sap xep danh sach sinh vien theo ten lop học phan\n");
	printf("                              7. In ra thong tin cua cac de tai co so luong SV <= 3\n");
	printf("                              8. In ra bang diem cua sinh vien hoc lop hoc phan\n\n");
	printf("               ************************************************************************************\n");
}

void process();
void processtieuchi() {
	int luachon;
	do {
		tieuchi();
		printf("Nhap lua chon cua ban: \n");
		scanf("%d", &luachon);
		printf("\n----------------------------------------------------------------------------------\n");

		switch (luachon) {
		case 1:
			char ma_sinh_vien[5];
			printf("Nhap ma so sinh vien can tim kiem (VD: SV01): ");
			scanf("%s", &ma_sinh_vien);
			searchSVmssv(ma_sinh_vien);
			getch();
			system("cls");

			break;
		case 2:
			char detai[6];
			char masv[6];
			printf("Nhap ma sv can tim kiem (VD: SV01): ");
			scanf("%s", masv);
			printf("Nhap ten de tai can tim kiem (VD: DT01): ");
			scanf("%s", detai);
			kiemTraSinhVienTheoDeTai(detai, masv);
			getch();
			system("cls");

			break;
		case 3:
			char hocphan[5];
			char sv[6];
			printf("Nhap ma sinh vien can kiem tra (VD: SV01): ");
			scanf("%s", sv);
			printf("Nhap hoc phan can tim kiem (VD: HP01): ");
			scanf("%s", hocphan);
			kiemTraSinhVienTheoHocPhan(hocphan, sv);
			getch();
			system("cls");
			break;

		}

	} while (luachon != 0);
	system("cls");
	process();
}

void process() {
	int choice;
	struct HocPhan hp;
	struct DeTai dt;
	struct SinhVien s;
	struct KetQua kq;
	do {
		menu();
		printf("Nhap lua chon cua ban: ");
		scanf("%d", &choice);
		printf("\n----------------------------------------------------------------------------------\n");

		switch (choice) {
		case 1:
			addDeTai(dt);
			getch();
			system("cls");

			break;
		case 2:
			printf("Chon tieu chi cua ban: ");
			system("cls");
			processtieuchi();
			getch();

			break;
		case 3:
			char hoc_phan[5];
			printf("Nhap hoc phan can xem diem: ");
			scanf("%s", hoc_phan);
			kqsvhocphan(hoc_phan);
			getch();
			system("cls");

			break;
		case 4:
			diem();
			getch();
			system("cls");

			break;
		case 5:
			timLopHocPhan();
			getch();
			system("cls");

			break;
		case 6:
			printf("\n");
			Sapxepsinhvien();
			break;
		case 7:
			inthongtindetai(dt);
			getch();
			system("cls");

			break;
		case 8:
			char hocphan[5];
			printf("Nhap hoc phan can xem diem: ");
			scanf("%s", hocphan);
			BangDiem(hocphan);
			getch();
			system("cls");

			break;

		}

	} while (choice != 0);
}

int main() {

	process();
	getch();
}