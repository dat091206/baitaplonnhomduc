#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SinhVien {
    int maSo;
    char hoTen[50];
    float diemTB;
    struct SinhVien *next;
} SinhVien;

SinhVien *head = NULL;

// ham de tao sinh vien moi 
SinhVien* taoSinhVien(int maSo, char hoTen[], float diemTB) {
    SinhVien *sv = (SinhVien*)malloc(sizeof(SinhVien)); //cap phat bo nho dong
    sv->maSo = maSo;
    strcpy(sv->hoTen, hoTen);
    sv->diemTB = diemTB;
    sv->next = NULL;
    return sv;
}

// 8.1. make a student list or something like that lol
void taoDanhSach() {
    int maSo;
    char hoTen[50];
    float diemTB;
    SinhVien *last = NULL;

    printf("\n=== TAO DANH SACH SINH VIEN ===\n"); //this is easier than java ngl
    while (1) {
        printf("Nhap ma so (<=0 de dung): ");
        scanf("%d", &maSo);
        if (maSo <= 0) break;

        fflush(stdin);
        printf("Nhap ho ten: ");
        gets(hoTen);

        printf("Nhap diem trung binh: ");
        scanf("%f", &diemTB);

        SinhVien *sv = taoSinhVien(maSo, hoTen, diemTB);
        if (head == NULL)
            head = sv;
        else
            last->next = sv;
        last = sv;
    }
}

// to print the list abave
void inDanhSach() {
    SinhVien *p = head;
    int i = 1;
    printf("\n=== DANH SACH SINH VIEN ===\n");
    while (p != NULL) {
        printf("%d. Ma so: %d | Ho ten: %s | DTB: %.2f\n", i++, p->maSo, p->hoTen, p->diemTB);
        p = p->next;
    }
    if (head == NULL) printf("Danh sach rong!\n");
}

// 8.2 find the position base on their numbers or id, lineaer search
void timViTriTheoMaSo() {
    int ma;
    printf("\nNhap ma so sinh vien can tim: ");
    scanf("%d", &ma);
    SinhVien *p = head;
    int pos = 1;
    while (p != NULL) {
        if (p->maSo == ma) {
            printf("Sinh vien co ma %d o vi tri thu %d trong danh sach.\n", ma, pos);
            return;
        }
        p = p->next;
        pos++;
    }
    printf("Khong tim thay sinh vien co ma so %d.\n", ma);
}

// 8.3 find sv with dtb, lineaer search too
void timTheoDTB() {
    float diem;
    printf("\nNhap diem trung binh can tim: ");
    scanf("%f", &diem);
    SinhVien *p = head;
    int found = 0;
    printf("\n=== SINH VIEN CO DTB = %.2f ===\n", diem);
    while (p != NULL) {
        if (p->diemTB == diem) {
            printf("Ma: %d | Ten: %s | DTB: %.2f\n", p->maSo, p->hoTen, p->diemTB);
            found = 1;
        }
        p = p->next;
    }
    if (!found) printf("Khong co sinh vien nao co DTB = %.2f\n", diem);
}

// 8.4. use selection sort aka chon truc tiep
void sapXepTheoTen() {
    if (head == NULL) return;
    SinhVien *i, *j;
    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->hoTen, j->hoTen) > 0) {
                int tmpMa = i->maSo;
                float tmpDiem = i->diemTB;
                char tmpTen[50];
                strcpy(tmpTen, i->hoTen);

                i->maSo = j->maSo;
                i->diemTB = j->diemTB;
                strcpy(i->hoTen, j->hoTen);

                j->maSo = tmpMa;
                j->diemTB = tmpDiem;
                strcpy(j->hoTen, tmpTen);
            }
        }
    }
    printf("\nDanh sach da duoc sap xep theo ten tang dan.\n");
}

// 8.5 Xoa toàn bo SV co ÐTB < 5.0, neu head<5, head = next node, va next<5 next = next next node
void xoaSVThapDiem() {
    SinhVien *p = head, *prev = NULL;
    while (p != NULL) {
        if (p->diemTB < 5.0) {
            if (p == head) {
                head = p->next;
                free(p);
                p = head;
            } else {
                prev->next = p->next;
                free(p);
                p = prev->next;
            }
        } else {
            prev = p;
            p = p->next;
        }
    }
    printf("\nDa xoa tat ca sinh vien co DTB < 5.0\n");
}

// 8.6. print 7<dtb<8
void inSVTheoKhoangDiem() {
    SinhVien *p = head;
    int found = 0;
    printf("\n=== SINH VIEN CO DTB TU 7.0 DEN 8.0 ===\n");
    while (p != NULL) {
        if (p->diemTB >= 7.0 && p->diemTB <= 8.0) {
            printf("Ma: %d | Ten: %s | DTB: %.2f\n", p->maSo, p->hoTen, p->diemTB);
            found = 1;
        }
        p = p->next;
    }
    if (!found) printf("Khong co sinh vien nao trong khoang diem nay.\n");
}

// c;ear data
void giaiPhong() {
    SinhVien *p = head;
    while (p != NULL) {
        SinhVien *temp = p;
        p = p->next;
        free(temp);
    }
}

int main() {
    int chon;
    do {
        printf("\n========== MENU QUAN LY SINH VIEN ==========\n");
        printf("1. Tao danh sach sinh vien\n");
        printf("2. Tim vi tri theo ma so\n");
        printf("3. Tim kiem theo diem trung binh\n");
        printf("4. Sap xep danh sach theo ten tang dan\n");
        printf("5. Xoa sinh vien co DTB < 5.0\n");
        printf("6. In danh sach sinh vien co DTB tu 7.0 den 8.0\n");
        printf("7. In toan bo danh sach\n");
        printf("0. Thoat\n");
        printf("Chon: ");
        scanf("%d", &chon);

        switch (chon) {
            case 1: taoDanhSach(); break;
            case 2: timViTriTheoMaSo(); break;
            case 3: timTheoDTB(); break;
            case 4: sapXepTheoTen(); break;
            case 5: xoaSVThapDiem(); break;
            case 6: inSVTheoKhoangDiem(); break;
            case 7: inDanhSach(); break;
            case 0: giaiPhong(); printf("Da thoat chuong trinh.\n"); break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while (chon != 0);

    return 0;
}

