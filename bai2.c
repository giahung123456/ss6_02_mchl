#include <stdio.h>
#include <string.h>

#define MAX 100
#define GIA_PHAT_MOI_NGAY 5000
#define HAN_MUC_CHUAN 14

int main() {
    // Khai bao cac mang song song va bien dem
    char maPhieu[MAX][15];
    char tenSach[MAX][50];
    int soNgayMuon[MAX];
    int tienPhat[MAX];
    int soLuong = 0;

    int luaChon;

    do {
        printf("\n================ HET THONG QUAN LY MUON TRA SACH (LIBRARY_WMS) ================\n");
        printf("1. Them luot muon sach moi\n");
        printf("2. Hien thi danh sach muon sach\n");
        printf("3. Cap nhat so ngay muon theo Ma phieu\n");
        printf("4. Xoa luot muon sach theo Ma phieu\n");
        printf("5. Thong ke danh sach phieu muon bi phat (Qua han > 14 ngay)\n");
        printf("6. Thoat chuong trinh\n");
        printf("==============================================================================\n");
        printf("Lua chon cua ban: ");

        if (scanf("%d", &luaChon) != 1) {
            while (getchar() != '\n');
            printf("Lua chon khong hop le. Vui long thu lai!\n");
            continue;
        }
        while (getchar() != '\n'); // Don bo dem sau khi doc so lua chon

        switch (luaChon) {
            case 1: {
                printf("\n=== THEM LUOT MUON SACH MOI ===\n");
                if (soLuong >= MAX) {
                    printf("He thong day, khong the them phieu muon moi!\n");
                    break;
                }

                char tempMa[15];
                int daTonTai = 0;

                // Nhap va kiem tra trung ma phieu
                do {
                    daTonTai = 0;
                    printf("Nhap ma phieu muon (khong khoang trang): ");
                    scanf("%14s", tempMa);
                    while (getchar() != '\n'); // Don bo dem ban phim

                    for (int i = 0; i < soLuong; i++) {
                        if (strcmp(maPhieu[i], tempMa) == 0) {
                            daTonTai = 1;
                            printf("Loi: Ma phieu '%s' da ton tai! Vui long nhap ma khac.\n", tempMa);
                            break;
                        }
                    }
                } while (daTonTai);

                strcpy(maPhieu[soLuong], tempMa);

                // Nhap ten sach bang fgets
                printf("Nhap ten sach: ");
                if (fgets(tenSach[soLuong], sizeof(tenSach[soLuong]), stdin) != NULL) {
                    size_t len = strlen(tenSach[soLuong]);
                    if (len > 0 && tenSach[soLuong][len - 1] == '\n') {
                        tenSach[soLuong][len - 1] = '\0';
                    }
                }

                // Nhap so ngay muon hop le (> 0)
                int ngay = 0;
                do {
                    printf("Nhap so ngay muon thuc te (> 0): ");
                    if (scanf("%d", &ngay) != 1) {
                        while (getchar() != '\n');
                        printf("Loi: Vui long nhap mot so nguyen hop le!\n");
                        continue;
                    }
                    while (getchar() != '\n');

                    if (ngay <= 0) {
                        printf("Loi: So ngay muon phai lon hon 0!\n");
                    }
                } while (ngay <= 0);

                soNgayMuon[soLuong] = ngay;

                // Tinh tien phat
                if (ngay > HAN_MUC_CHUAN) {
                    tienPhat[soLuong] = (ngay - HAN_MUC_CHUAN) * GIA_PHAT_MOI_NGAY;
                } else {
                    tienPhat[soLuong] = 0;
                }

                printf("--> Tien phat tu dong tinh: %d VND\n", tienPhat[soLuong]);
                soLuong++;
                printf("--> Them luot muon sach thanh cong!\n");
                break;
            }

            case 2: {
                printf("\n================================ DANH SACH MUON SACH ================================\n");
                if (soLuong == 0) {
                    printf("Danh sach muon sach hien dang rong!\n");
                    break;
                }

                printf("%-4s | %-10s | %-32s | %-10s | %-15s\n", "STT", "Ma Phieu", "Ten Sach", "So Ngay", "Tien Phat (VND)");
                printf("--------------------------------------------------------------------------------------\n");

                long tongTienPhat = 0;
                for (int i = 0; i < soLuong; i++) {
                    printf("%-4d | %-10s | %-32s | %-10d | %-15d\n", 
                           i + 1, maPhieu[i], tenSach[i], soNgayMuon[i], tienPhat[i]);
                    tongTienPhat += tienPhat[i];
                }

                printf("--------------------------------------------------------------------------------------\n");
                printf("Tong tien phat toan he thong: %ld VND\n", tongTienPhat);
                break;
            }

            case 3: {
                printf("\n=== CAP NHAT SO NGAY MUON ===\n");
                if (soLuong == 0) {
                    printf("Danh sach muon sach hien dang rong!\n");
                    break;
                }

                char timMa[15];
                printf("Nhap ma phieu muon can cap nhat: ");
                scanf("%14s", timMa);
                while (getchar() != '\n');

                int index = -1;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], timMa) == 0) {
                        index = i;
                        break;
                    }
                }

                if (index == -1) {
                    printf("Khong tim thay phieu muon co ma: %s\n", timMa);
                } else {
                    printf("Tim thay phieu muon cua sach: %s (So ngay hien tai: %d)\n", tenSach[index], soNgayMuon[index]);
                    
                    int ngayMoi = 0;
                    do {
                        printf("Nhap so ngay muon thuc te moi (> 0): ");
                        if (scanf("%d", &ngayMoi) != 1) {
                            while (getchar() != '\n');
                            printf("Loi: Vui long nhap mot so nguyen hop le!\n");
                            continue;
                        }
                        while (getchar() != '\n');

                        if (ngayMoi <= 0) {
                            printf("Loi: So ngay muon phai lon hon 0!\n");
                        }
                    } while (ngayMoi <= 0);

                    soNgayMuon[index] = ngayMoi;
                    tienPhat[index] = (ngayMoi > HAN_MUC_CHUAN) ? (ngayMoi - HAN_MUC_CHUAN) * GIA_PHAT_MOI_NGAY : 0;

                    printf("--> Tien phat moi: %d VND\n", tienPhat[index]);
                    printf("--> Cap nhat so ngay muon thanh cong!\n");
                }
                break;
            }

            case 4: {
                printf("\n=== XOA LUOT MUON SACH ===\n");
                if (soLuong == 0) {
                    printf("Danh sach muon sach hien dang rong!\n");
                    break;
                }

                char timMa[15];
                printf("Nhap ma phieu muon can xoa: ");
                scanf("%14s", timMa);
                while (getchar() != '\n');

                int index = -1;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], timMa) == 0) {
                        index = i;
                        break;
                    }
                }

                if (index == -1) {
                    printf("Khong tim thay phieu muon co ma: %s\n", timMa);
                } else {
                    // Don mang tu vi tri index den soLuong - 2
                    for (int i = index; i < soLuong - 1; i++) {
                        strcpy(maPhieu[i], maPhieu[i + 1]);
                        strcpy(tenSach[i], tenSach[i + 1]);
                        soNgayMuon[i] = soNgayMuon[i + 1];
                        tienPhat[i] = tienPhat[i + 1];
                    }
                    soLuong--;
                    printf("Xoa phieu muon thanh cong!\n");
                }
                break;
            }

            case 5: {
                printf("\n=================== DANH SACH PHIEU MUON BI PHAT (> 14 NGAY) ===================\n");
                int coViPham = 0;

                for (int i = 0; i < soLuong; i++) {
                    if (soNgayMuon[i] > HAN_MUC_CHUAN) {
                        if (!coViPham) {
                            printf("%-4s | %-10s | %-32s | %-10s | %-15s\n", "STT", "Ma Phieu", "Ten Sach", "So Ngay", "Tien Phat (VND)");
                            printf("--------------------------------------------------------------------------------------\n");
                            coViPham = 1;
                        }
                        printf("%-4d | %-10s | %-32s | %-10d | %-15d\n", 
                               i + 1, maPhieu[i], tenSach[i], soNgayMuon[i], tienPhat[i]);
                    }
                }

                if (!coViPham) {
                    printf("Khong co luot muon nao bi qua han phat!\n");
                } else {
                    printf("--------------------------------------------------------------------------------------\n");
                }
                break;
            }

            case 6:
                printf("\nDa thoat chuong trinh quan ly LIBRARY_WMS. Hen gap lai!\n");
                break;

            default:
                printf("Lua chon khong hop le. Vui long thu lai!\n");
                break;
        }

    } while (luaChon != 6);

    return 0;
}