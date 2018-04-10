#include<stdio.h>
#include<cstdlib>
#include<conio.h>
#include<wchar.h>
#include <fcntl.h> 
#include <io.h> 

struct HS{
	wchar_t *ten;
	wchar_t *lop;
	wchar_t *MoTa;
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

void truyen(wchar_t *nguon, wchar_t *&dich){
	dich = (wchar_t*)malloc((wcslen(nguon) + 1)*sizeof(wchar_t));
	for (int i = 0; i < wcslen(nguon); i++)
		dich[i] = nguon[i];
	dich[wcslen(nguon)] = '\0';
}

void tach(wchar_t *nguon, HS &hs){
//	char s[2] = ",";
	const wchar_t *s= L"," ;
	wchar_t *token;

	token = wcstok(nguon, s);
	truyen(token, hs.ten);

	token = wcstok(NULL, s);
	truyen(token, hs.lop);

	token = wcstok(NULL, s);
	truyen(token, hs.MoTa);
}



void main(){
	_setmode(_fileno(stdout), _O_U16TEXT); //needed for output
	_setmode(_fileno(stdin), _O_U16TEXT); //needed for input
	// nhớ chuyển font của console sang Consolas (size 16)

	FILE *f = _wfopen(L"thong_tin_ca_nhan.csv", L"r+,ccs=UTF-16LE");
	HS hs;

	if (f == NULL)
		wprintf(L"không mở được file \n");
	else
		wprintf(L"đã mở xong file\n");

	wchar_t *line;
	line = get_data(f);
	wprintf(L"%s\n\n\n\n", line, wcslen(line));

	wprintf(L"sau khi tách ra thì ta có các thông tin sau\n");

	tach(line, hs);

	wprintf(L"tên : %s\nlớp : %s\nmô tả : %s\n", hs.ten, hs.lop, hs.MoTa);

}