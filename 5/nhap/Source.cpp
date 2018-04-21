#include<stdio.h>
#include<cstdlib>
#include<conio.h>
#include<wchar.h>
#include <fcntl.h> 
#include <io.h> 

struct HS{
	wchar_t *mssv;
	wchar_t *ten;
	wchar_t *nghanh;
	int      khoa_hoc;
	wchar_t *ngay_sinh;
	wchar_t *image;
	wchar_t *mo_ta;
	wchar_t *gmail;
	wchar_t **so_thich;
};

wchar_t *get_data(FILE *file){
	wchar_t c;
	c = fgetwc(file);
	wchar_t * line = (wchar_t*)malloc(sizeof(wchar_t));

	if (line){
		int i = 0;
		while (c != '\n'){

			if (feof(file)){
				if (line)
					free(line);
				return NULL;
			}

			*(line + i) = c;
			line = (wchar_t*)realloc(line, (i + 2)*sizeof(wchar_t));
			c = fgetwc(file);
			i++;
		}
		*(line + i) = '\0';
	}
}


void replace(wchar_t *&nguon, wchar_t *tim, wchar_t *thay){
	
}

void check(wchar_t *&nguon, HS hs1, HS hs2){
	if (wcsstr(nguon, hs1.mssv) != NULL){
		replace(nguon,hs1.mssv, hs2.mssv);
	}

	if (wcsstr(nguon, hs1.ten) != NULL){
		replace(nguon,hs1.ten, hs2.ten);
	}

	if (wcsstr(nguon, hs1.nghanh) != NULL){
		replace(nguon,hs1.nghanh, hs2.nghanh);
	}

/*	if (khóa học) != NULL){
		//lm riêng trong này
	}*/

	if (wcsstr(nguon, hs1.ngay_sinh) != NULL){
		replace(nguon,hs1.ngay_sinh, hs2.ngay_sinh);
	}

	if (wcsstr(nguon, hs1.image) != NULL){
		replace(nguon,hs1.image, hs2.image);
	}

	if (wcsstr(nguon, hs1.mo_ta) != NULL){
		replace(nguon,hs1.mo_ta, hs2.mo_ta);
	}

	if (wcsstr(nguon, hs1.gmail) != NULL){
		replace(nguon, hs1.gmail, hs2.gmail);
	}

	//sở thích bỏ qua ;


}

void newfile(FILE *nguon, FILE *dich, HS hs1, HS hs2){
	wchar_t *line;
	line = get_data(nguon);

	while (line != NULL)	{
		

		fputws(line, dich);
		line = get_data(nguon);
	} 

}

void main(){
	_setmode(_fileno(stdout), _O_U16TEXT); //needed for output
	_setmode(_fileno(stdin), _O_U16TEXT); //needed for input
	// nhớ chuyển font của console sang Consolas (size 16)

	HS hs1, hs2;

	hs1.mssv =L"1212123" ;
	hs1.ten =L"Nguyễn Văn A" ;
	hs1.nghanh =L"Công nghệ thông tin" ;
	hs1.khoa_hoc = 2013;
	hs1.gmail = L"nva@gmail.com";
	hs1.ngay_sinh =L"20/01/1994" ;
	hs1.mo_ta = L"Tôi là một người rất thân thiện.";
	hs1.so_thich[0] =L"Âm nhạc: POP, Balad" ;
	hs1.so_thich[1] =L"Ẩm thực: bún riêu, bún thịt nướng" ;

	hs2.mssv = L"1712830";
	hs2.ten = L"NGÔ NHA TRANG";
	hs2.nghanh = L"Công nghệ thông tin";
	hs2.khoa_hoc = 2017;
	hs2.gmail = L"NGONHATRANG@gmail.com";
	hs2.ngay_sinh = L"07/11/1999";
	hs2.mo_ta = L"CUTE, DỄ THƯƠNG, HIỀN LÀNH, ĐÁNG MẾN";
	hs2.so_thich[0] = L"Âm nhạc: US-UK, DANCE";
	hs2.so_thich[1] = L"Ẩm thực: trà sữa size L , socola bạc hà chân châu đen";
	hs2.so_thich[2] = L"free time: go to take a shit :)))";

	FILE *f = _wfopen(L"1712830.htm", L"w+,ccs=UTF-16LE");

	FILE *nguon = _wfopen(L"1212123.htm", L"r+,ccs=UTF-16LE");


	if (nguon == NULL || f == NULL)
		wprintf(L"không mở được file\n");
	else
		wprintf(L"đã mở xong file\n");
}