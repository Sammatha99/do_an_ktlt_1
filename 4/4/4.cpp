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
	wchar_t *gmail;
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

		if ( line[i] == '"' && line [i-1]=='\t'){
			line[i] = '\t';

			while (!(line[i] == '"' && line[i+1] == ','))
				i++;

			line[i] = '\t';
		}

		if (line[i] == ',')
			line[i] = '\t';
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
	int x = (wcslen(nguon) + wcslen(dich) + 2 + wcslen(s));


	dich = (wchar_t*)realloc(dich, x*sizeof(wchar_t));
	wcsncat(dich, s, wcslen(s));
	wcsncat(dich, nguon, wcslen(nguon));
}

void tach(wchar_t *nguon, HS &hs){
	const wchar_t *s = L"\t";
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
	truyen(token, hs.gmail);

	token = wcstok(NULL, s);

	if (token != NULL){

		truyen(token, hs.so_thich);
		token = wcstok(NULL, s);
		while (token != NULL){

			so_thich_keo_dai(token, hs.so_thich);
			token = wcstok(NULL, s);
		}
	}

	else
		hs.so_thich = NULL;
}



void main(){
	_setmode(_fileno(stdout), _O_U16TEXT); //needed for output
	_setmode(_fileno(stdin), _O_U16TEXT); //needed for input
	// nhớ chuyển font của console sang Consolas (size 16)
	HS hs[10];
	int i = 0;
	FILE *f = _wfopen(L"5.csv", L"r+,ccs=UTF-16LE");


	if (f == NULL)
		wprintf(L"không mở được file \n");
	else{
		wprintf(L"đã mở xong file\n");

		wchar_t *line;

		line = get_data(f);

		while (line != NULL){
			chuan_hoa(line);
			tach(line, hs[i]);


			wprintf(L"sau khi tách xong la : \n\n\n");
			wprintf(L"mssv : %s\ntên : %s\nnghành theo học : %s\nkhóa học hiện tại: %s\nngày sinh : %s\nmô tả : %s\ngmail: %s\n", hs[i].mssv, hs[i].ten, hs[i].nghanh, hs[i].khoa_hoc, hs[i].ngay_sinh, hs[i].mo_ta, hs[i].gmail);
			if (hs[i].so_thich != NULL)
				wprintf(L"so thich :\n- %s\n", hs[i].so_thich);
			else
				wprintf(L"con mẹ này không có sở thích , thứ nhạt nhẽo :))\n");
			wprintf(L"\n\n\n");


			i++;
			line = get_data(f);
		}
	}
}
