#include <REGX52.h>

sbit T = P2^0;
sbit N = P2^1;

sbit D = P0^0;
sbit GHT = P0^1;
sbit M = P0^2;
sbit GHD = P0^3;
sbit S = P0^4;
sbit K = P0^5;
int main(){
	while (1){
		if (!D && !S && GHT && GHD && K && M)
		{
			T=1;
			N=0;
		}
		if (!D && !S && !GHT && GHD && K && M)
		{
			T=1;
			N=1;
		}
		if (D && !S && GHT && GHD && K && !M)
		{
			T=0;
			N=1;
		}
		if (D && !S && GHT && !GHD && K && !M)
		{
			T=1;
			N=1;
		}
		if (!K){
			T=1; N=1;
		}
		if (!S && D && M){
			T=1; N=1;
		}
		if (S) {
			T=1; N=1;
		}
	}
}

	