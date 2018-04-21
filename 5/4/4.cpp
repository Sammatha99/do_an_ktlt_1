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


void tach(wchar_t *nguon, HS &hs){
	const wchar_t *s = L"\t";
	wchar_t *token;
	int i = 1;

	token = wcstok(nguon, s);
	truyen(token, hs.mssv);

	token = wcstok(NULL, s);
	truyen(token, hs.ten);


	token = wcstok(NULL, s);
	truyen(token, hs.nghanh);


	//khóa học chuyển đổi int
	token = wcstok(NULL, s);
	hs.khoa_hoc = 0;

	for (int i = 0; i < wcslen(token); i++)
		hs.khoa_hoc = hs.khoa_hoc * 10 + token[i] - L'0';



	token = wcstok(NULL, s);
	truyen(token, hs.ngay_sinh);

	token = wcstok(NULL, s);
	truyen(token, hs.image);

	token = wcstok(NULL, s);
	truyen(token, hs.mo_ta);

	token = wcstok(NULL, s);
	truyen(token, hs.gmail);

	//sở thích
	token = wcstok(NULL, s);

	if (token != NULL){
		hs.so_thich = (wchar_t **)malloc(sizeof(wchar_t*));
		hs.so_thich[0] = (wchar_t*)malloc(sizeof(wchar_t));
		truyen(token, hs.so_thich[0]);
	
		token = wcstok(NULL, s);


		while (token != NULL){
			hs.so_thich = (wchar_t**)realloc(hs.so_thich, sizeof(wchar_t**)*(i+1));
			truyen(token, hs.so_thich[i]);
			token = wcstok(NULL, s);
			i++;
		}

		hs.so_thich[i] = NULL;
	}

	else
		hs.so_thich = NULL;


}


void main(){
	_setmode(_fileno(stdout), _O_U16TEXT); //needed for output
	_setmode(_fileno(stdin), _O_U16TEXT); //needed for input
	// nhớ chuyển font của console sang Consolas (size 16)
	HS *hs;
	int i = 0;
	FILE *f = _wfopen(L"5.csv", L"r+,ccs=UTF-16LE");


	if (f == NULL)
		wprintf(L"không mở được file \n");

	else{
		wprintf(L"đã mở xong file\n");

		wchar_t *line;

		line = get_data(f);
		if (line != NULL){
			hs = (HS*)malloc(sizeof(HS));

			while (line != NULL){
				hs = (HS*)realloc(hs, sizeof(HS)*(i+1));
				chuan_hoa(line);
				tach(line, hs[i]);


				wprintf(L"sau khi tách xong la , thành viên thứ %d\n", i + 1);
				wprintf(L"mssv : %s\ntên : %s\nnghành theo học : %s\nkhóa học hiện tại: %d\nngày sinh : %s\nhình ảnh : %s\nmô tả : %s\ngmail: %s\n", hs[i].mssv, hs[i].ten, hs[i].nghanh, hs[i].khoa_hoc, hs[i].ngay_sinh,hs[i].image, hs[i].mo_ta, hs[i].gmail);
				if (hs[i].so_thich != NULL){
					int j = 0;
					while (hs[i].so_thich[j] != NULL){
						wprintf(L"-%s\n", hs[i].so_thich[j]);
						j++;
					}
				}

				else
					wprintf(L"con mẹ này không có sở thích , thứ nhạt nhẽo :))\n");

				wprintf(L"\n\n\n");

				line = get_data(f);
				i++;
			}
		}
	}

	wprintf(L"tổng số lượng sinh viên là : %d", i);
}
