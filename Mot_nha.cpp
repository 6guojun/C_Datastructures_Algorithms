#include<stdio.h>
#include<windows.h>
void beep(int hz){
	Beep(hz,300);
}
int main(){
	int do1=262;
	int re=294;
	int mi=330;
	int fa=350;
	int sol=392;
	int la=440;
	int si=494;
	int do2=523;
	int re2=588;
	int mi2=660;
	int fa2=700;
	int sol2=784;
	int la2=880;
	int si2=988;
	/*Khi hai ta v? m?t nh�, kh�p d�i mi chung m?t giu?ng
Mi2 Mi2 Mi2 ��2 ��2 Si, R�2 ��2 Si Si Si La
Khi hai ta chung m?t du?ng, ta vui chung m?t n?i vui
Mi2 Mi2 Mi2 ��2 ��2 Si, R�2 R�2 R�2 R�2 Sol2 Mi2
Nu?c m?t roi m?t d�ng, s?ng chung nhau m?t d?i
Mi2 Mi2 ��2 Sol La, Mi2 R�2 R�2 ��2 ��2*/
	beep(mi2);
	beep(mi2);
	beep(mi2);
	beep(do2);
	beep(do2);
	beep(si);
	beep(si);
	beep(re2);
	beep(do2);
	beep(si);
	beep(si);
	beep(si);
	beep(la);
	Sleep(500);
	//��i khi mo c�ng m?t gi?c, th?c gi?c chung m?t gi?
	//��2 ��2 Si Sol La ��2, Mi2 Mi2 R�2 ��2 ��2
	
}
