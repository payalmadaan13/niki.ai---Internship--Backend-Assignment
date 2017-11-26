#include<iostream>

#define MOD 1000000007

using namespace std;


/*
concept used to solve the problem
(1 1)^n     (Fn+1 Fn)
         =  
(1 0)       (Fn   Fn-1)
*/

//main function to cal. the no. of binary sequences(bs)
unsigned long long int length_bs(unsigned long long int );

//Auxilary helper functions to cal. nth term
void Aux_Power(unsigned long long int F[2][2], unsigned long long int );
void Aux_Multiply(unsigned long long int F[2][2], unsigned long long int M[2][2]);


int main()
{
	int test;
	cin>>test;
	
	while(test--)
	{
	
		//as the input is order of 10^15 so take unsigned long long 
		unsigned long long int bs_len;
		cin>>bs_len;
		
		cout<<length_bs(bs_len)<<endl;
	}
	
	return 0;
}


unsigned long long int length_bs(unsigned long long int len)
{
	if(len == 0)
		return 0;
	if(len == 1)
		return 2;		// 0 & 1
	if(len == 2)
		return 3;		// 01,10,11
	
	// smae recursive as fibonacci so calculate efficiently	
	unsigned long long int F[2][2] = {{1,1},{1,0}};
	
	Aux_Power(F, len-2);
	
	/* as we need len th power but in this the initial 
	cond. are F1 = 2 F2 = 3 so multiply result
	 F00 with F1 and F01 with F2*/
	return (F[0][0]*3+F[0][1]*2)%MOD;
}


void Aux_Power(unsigned long long int F[2][2], unsigned long long int len)
{
	if( len == 0 || len == 1)
		return;
		
	unsigned long long int M[2][2] = {{1,1},{1,0}};
	
	//recursively call for half len and multiply the power to get len
	Aux_Power(F, len/2);
	Aux_Multiply(F, F);
	
	//if len is odd then after power F is need to multiply once again by original F to get odd power
	if( len % 2 )
		Aux_Multiply(F, M);
	
	return;
}


void Aux_Multiply(unsigned long long int F[2][2], unsigned long long int M[2][2])
{
	// Matrix multiplication of 2 matrices of order 2x2
	unsigned long long int F00 = ((F[0][0]*M[0][0])%MOD + (F[0][1]*M[1][0])%MOD)%MOD;
	unsigned long long int F01 = ((F[0][0]*M[0][1])%MOD + (F[0][1]*M[1][1])%MOD)%MOD;
	unsigned long long int F10 = ((F[1][0]*M[0][0])%MOD + (F[1][1]*M[1][0])%MOD)%MOD;
	unsigned long long int F11 = ((F[1][0]*M[0][1])%MOD + (F[1][1]*M[1][1])%MOD)%MOD;
	
	//assign the updated values after multiplication to F matrix itself
	F[0][0] = F00;
	F[0][1] = F01;
	F[1][0] = F10;
	F[1][1] = F11;
	
	return;
}
