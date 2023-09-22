#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int harga[20], index = 0;
char nama[150][200];

void read(){
	FILE *read;
	read = fopen("menurestoran.txt", "r");
	
	while(!feof(read)){
		fscanf(read, "%[^|]|%d\n", &nama[index], &harga[index]);
		index++;
	}
	fclose(read);
}

void printdata(){
	printf("Terdapat Menu :\n");
	for(int i = 0; i < index; i++){
		printf("%-10s - Rp %d\n",nama[i], harga[i]);
	}	
	printf("\n");
}

void judul(){
	printf("=====================\n");
	printf("RESTORAN JAYA SENTOSA\n");
	printf("=====================\n\n");	
}

int validasi(char nama1[20]){
	for(int x = 0; x < index; x++){
		if(strcmp(nama1, nama[x]) == 0){
			return 0;
			break;
		}
	}
	return 1;
}

void order(){
	int kasus;
	printf("Jumlah jenis makanan yang ingin di pesan : ");
	scanf("%d", &kasus); getchar();
	
	char nama1[kasus][20];
	int jumlah[index];
	
	for(int i = 0; i < kasus; i++){
		printf("\nPesanan Makanan #%d :\n", i + 1);
		scanf("%s", &nama1[i]);
		
		ceknama:
		do{
			if(validasi(nama1[i]) != 0){
				printf("\nMenu Makanan Tidak Ada\n");
				printf("Pesanan Makanan #%d :\n", i + 1);
				scanf("%s", &nama1[i]);
				goto ceknama;
			}
		}while(validasi(nama1[i]) != 0);
		
		printf("Jumlah Makanan #%d :\n", i+1);
		scanf("%d", &jumlah[i]);
	}
	int harga1[kasus];
	int total[kasus];
	for(int j = 0; j < kasus; j++){
		for(int k = 0; k < index; k++){
			if(strcmp(nama1[j], nama[k]) == 0){
				harga1[j] = harga[k];
				total[j] = harga[k] * jumlah[j];	
			}
		}
	}
	printf("\n\n");
	printf("====================BON========================\n");
	printf("No.    Nama 	 Jumlah      Harga      Total        \n");
	for(int i = 0; i < kasus; i++){
			printf("%-5d%-13s %-9d%6d%11d\n", i + 1, nama1[i], jumlah[i], harga1[i], total[i]);
		}
	long int total_jumlah;
	for(int z = 0; z < kasus; z++){
		total_jumlah = total_jumlah + total[z];
	}
	printf("\nTotal Pembayaran : Rp %ld\n", total_jumlah);
	printf("\n\n            Selamat Menikmati\n");
	printf("===============================================\n");
}

void tambahmenu(){
	if(index < 10){
		backmenu:
		printf("Nama makanan untuk tambahan menu\n");getchar();
		scanf("%[^\n]", &nama[index]);
		
		while(validasi(nama[index]) == 0){
			printf("Menu makanan sudah tersedia\n");
			goto backmenu;
		}
		
		printf("Masukan harga untuk %s\n", nama[index]);
		scanf("%d", &harga[index]);
		index++;
		printf("\n");
		printdata();
	}else if(index >= 10){	
		printf("Menu makanan sudah memenuhi batas\n");getchar();	
	}
}

void bubblesortname(){
	char tempname[200];
	int tempprice;
	
	for(int i = 0; i < index; i++){
		for(int j = 0; j < index - 1; j++){
			if(strcmp(nama[j], nama[j + 1]) > 0){
				strcpy(tempname, nama[j]);
				strcpy(nama[j], nama[j+ 1]);
				strcpy(nama[j + 1], tempname);
				//				
				tempprice = harga[j];
				harga[j] = harga[j + 1];
				harga[j + 1] = tempprice;
			}
		}
	}
}

void mergesortname(int left, int right){
	if(left < right){
		int mid = (left + right)/2;
		mergesortname(left, mid);
		mergesortname(mid + 1, right);
		char tempname[right - left + 1][200];
		int tempprice[right - left + 1];
		int leftpivot = left;
		int rightpivot = mid + 1;
		int tempIdx = 0;
		
		while(leftpivot <= mid && rightpivot <= right){
			if(strcmp(nama[leftpivot], nama[rightpivot]) < 0){
				strcpy(tempname[tempIdx], nama[leftpivot]);
				tempprice[tempIdx] = harga[leftpivot];
				leftpivot++;
			}else{
				strcpy(tempname[tempIdx], nama[rightpivot]);
				tempprice[tempIdx] = harga[rightpivot];
				rightpivot++;
			}tempIdx++;
		}
			
		while(leftpivot <= mid){
			strcpy(tempname[tempIdx], nama[leftpivot]);
			tempprice[tempIdx] = harga[leftpivot];
			leftpivot++;
			tempIdx++;
		}
			
		while(rightpivot <= right){
			strcpy(tempname[tempIdx], nama[rightpivot]);
			tempprice[tempIdx] = harga[rightpivot];
			rightpivot++;
			tempIdx++;
		}
			
		for(int i = left; i <= right; i++){
			strcpy(nama[i], tempname[i - left]);
			harga[i] = tempprice[i - left];
		}
	}
}

void bubblesortprice(){
	int tempprice;
	char tempname[200];
	for(int i = 0; i < index; i++){
		for(int j = 0; j < index - 1; j++){
			if(harga[j] > harga[j + 1]){
				tempprice = harga[j];
				harga[j] = harga[j + 1];
				harga[j + 1] = tempprice;
					//
				strcpy(tempname, nama[j]);
				strcpy(nama[j], nama[j + 1]);
				strcpy(nama[j + 1], tempname);
			}
		}
	}
}

void mergesortprice(int left, int right){
	if(left < right){
		int mid = (left + right)/2;
		mergesortprice(left, mid);
		mergesortprice(mid + 1, right);
		int tempprice[right - left + 1];
		char tempname[right - left + 1][200];
		int leftpivot = left;
		int rightpivot = mid + 1;
		int tempIdx = 0;
		
		while(leftpivot <= mid && rightpivot <= right){
			if(harga[leftpivot] < harga[rightpivot]){
				tempprice[tempIdx] = harga[leftpivot];
				strcpy(tempname[tempIdx], nama[leftpivot]);
				leftpivot++;
			}else{
				tempprice[tempIdx] = harga[rightpivot];
				strcpy(tempname[tempIdx], nama[rightpivot]);
				rightpivot++;
			}tempIdx++;
		}
			
		while(leftpivot <= mid){
			tempprice[tempIdx] = harga[leftpivot];
			strcpy(tempname[tempIdx], nama[leftpivot]);
			leftpivot++;
			tempIdx++;
		}
			
		while(rightpivot <= right){
			tempprice[tempIdx] = harga[rightpivot];
			strcpy(tempname[tempIdx], nama[rightpivot]);
			rightpivot++;
			tempIdx++;
		}
			
		for(int i = left; i <= right; i++){
			harga[i] = tempprice[i - left];
			strcpy(nama[i], tempname[i - left]);
		}
	}
}

int main(){
	read();
	
	mainmenu:
		system("cls");
		judul();
		int nomor;
		do{
			system("cls");
			printf("Menu Utama : \n"); 
			printf("\n");
			printf("1. Show Menu\n");
			printf("2. Add New Menu\n");
			printf("3. Sort by Food Name\n");
			printf("4. Sort by Price Name\n");
			printf("5. Order Food\n");
			printf("6. Exit\n");
			printf("Nomor : ");
			scanf(" %d", &nomor);
		}while ( 1 > nomor || 6 < nomor);
		
		char enter;
		switch(nomor)
		{
			case(1):
				system("cls");
				printdata();getchar();
				printf("Enter untuk lanjut...\n");
				scanf("%c", &enter);
				goto mainmenu;
				break;
			
			case(2):
				system("cls");
				tambahmenu();getchar();
				printf("Enter untuk lanjut...\n");
				scanf("%c", &enter);
				goto mainmenu;
				break;
		
			case(3):
				system("cls");
				int tanda;
				do{
					system("cls");
					printf("Tentukin cara untuk sorting nama :\n");
					printf("1. Bubble Sort\n");
					printf("2. Merge Sort\n");
					scanf("%d", &tanda);
				}while(1 > tanda || 2 < tanda);
	
				if(tanda == 1){
					bubblesortname();
				}else if(tanda == 2){
					mergesortname(0, index - 1);
				}
				printf("\n");
				printdata();getchar();
				printf("Enter untuk lanjut...\n");
				scanf("%c", &enter);
				goto mainmenu;
				break;
			
			case(4):
				system("cls");
				int poin;
				do{
					system("cls");
					printf("Tentukin cara untuk sorting nama :\n");
					printf("1. Bubble Sort\n");
					printf("2. Merge Sort\n");
					scanf("%d", &poin);
				}while(1 > poin || 2 < poin);
	
				if(tanda == 1){
					bubblesortprice();
				}else if(tanda == 2){
					mergesortprice(0, index - 1);
				}
				printf("\n");
				printdata();getchar();
				printf("Enter untuk lanjut...\n");
				scanf("%c", &enter);
				goto mainmenu;
				break;
				
			case(5):
				system("cls");
				printdata();
				order(); getchar();
				printf("Enter untuk lanjut...\n");
				scanf("%c", &enter);
				goto mainmenu;
				break;
				
			case(6):
				printf("\n");
				printdata();
				printf("\nTerima Kasih, Ditunggu Orderan Selanjutnya\n");
				break;
		}
	
	return 0;
}
