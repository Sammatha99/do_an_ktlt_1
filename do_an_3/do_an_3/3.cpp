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
	wchar_t *khoa_hoc;
	wchar_t *ngay_sinh;
	wchar_t *mo_ta;

	wchar_t *so_thich;
};


wchar_t *get_data(FILE *file){
	wchar_t c;
	c = fgetwc(file);
	wchar_t * line = (wchar_t*)malloc(sizeof(wchar_t));

	if (line){
		int i = 0;
		while (c != '\n'){
			*(line + i) = c;
			line = (wchar_t*)realloc(line, (i + 2)*sizeof(wchar_t));
			c = fgetwc(file);
			i++;
		}
		*(line + i) = '\0';
	}
	return line;
}

void chuan_hoa(wchar_t *&line){
	for (int i = 0; i<wcslen(line); i++){

		if (line[i] == '"'){
			line[i] = '.';

			while (line[i] != '"')
				i++;

			line[i] = '.';
		}

		if (line[i] == ',')
			line[i] = '.';
	}
}

void truyen(wchar_t *nguon, wchar_t *&dich){
	dich = (wchar_t*)malloc((wcslen(nguon) + 1)*sizeof(wchar_t));
	for (int i = 0; i < wcslen(nguon); i++)
		dich[i] = nguon[i];
	dich[wcslen(nguon)] = '\0';
}

void so_thich_keo_dai(wchar_t *nguon, wchar_t *&dich){
	wchar_t *s = L"\n- ";
	int x = (wcslen(nguon) + wcslen(dich) + 2 +wcslen(s));
	

	dich = (wchar_t*)realloc(dich, x*sizeof(wchar_t));
	wcsncat(dich, s, wcslen(s));
	wcsncat(dich, nguon, wcslen(nguon));
}

void tach(wchar_t *nguon, HS &hs){
	const wchar_t *s = L".";
	wchar_t *token;

	token = wcstok(nguon, s);
	truyen(token, hs.mssv);

	token = wcstok(NULL, s);
	truyen(token, hs.ten);


	token = wcstok(NULL, s);
	truyen(token, hs.nghanh);


	token = wcstok(NULL, s);
	truyen(token, hs.khoa_hoc);


	token = wcstok(NULL, s);
	truyen(token, hs.ngay_sinh);


	token = wcstok(NULL, s);
	truyen(token, hs.mo_ta);

	token = wcstok(NULL, s);

	if (token != NULL){

		truyen(token, hs.so_thich);
		token = wcstok(NULL, s);
		while (token != NULL){

			so_thich_keo_dai(token, hs.so_thich);
			token=wcstok(NULL, s);
		}
	}

}

void main(){
	_setmode(_fileno(stdout), _O_U16TEXT); //needed for output
	_setmode(_fileno(stdin), _O_U16TEXT); //needed for input
	// nhớ chuyển font của console sang Consolas (size 16)
	HS hs;
	FILE *f = _wfopen(L"4.csv", L"r+,ccs=UTF-16LE");


	if (f == NULL)
		wprintf(L"không mở được file \n");
	else{
		wprintf(L"đã mở xong file\n");

		wchar_t *line;
		line = get_data(f);
		wprintf(L"%s\n\n\n\n", line);
		chuan_hoa(line);
		wprintf(L"chuẩn hóa:\n%s\n\n", line);

		tach(line, hs);
		wprintf(L"sau khi tách xong la : \n\n\n");
		wprintf(L"mssv : %s\ntên : %s\nnghành theo học : %s\nkhóa học hiện tại: %s\nngày sinh : %s\nmô tả : %s\n",hs.mssv, hs.ten, hs.nghanh, hs.khoa_hoc, hs.ngay_sinh, hs.mo_ta);
		wprintf(L"so thich :\n- %s\n", hs.so_thich);
	}

}
