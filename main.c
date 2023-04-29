#include <stdio.h>

enum Stavy{OPR1, OPE, OPR2, VYS};

enum Stavy stav = OPR1;

int flag0 = 0;
int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int flag4 = 0;

struct KalkulData{
	double a;
	double b;
	char ope;
	char prev_ope;
	double vys;
};

int isOperator(char z);
void zadejOperand(char *str, struct KalkulData *ka);
void zadejOperator(char *str, struct KalkulData *ka);


int main(int argc, char **argv)
{
	
	char radek[10];
	struct KalkulData kalkuldata;
	
	while(1){
		switch(stav){
		
			case OPR1: {
				
				zadejOperand(radek, &kalkuldata);
				
				if(flag4){
					flag0 = flag1 = flag2 = flag3 = flag4 = 0; 
					stav = OPR1;
					break;
				}
				
				if(flag3){
					stav = VYS;
					break;
				}
				
				if(flag1){
					stav = OPR2;
					break;
				}
				stav = OPE;
			}
			break;
		
			case OPE: {

				zadejOperator(radek, &kalkuldata);
				
				if(flag4){
					flag0 = flag1 = flag2 = flag3 = flag4 = 0; 
					stav = OPR1;
					break;
				}

				stav = OPR2;
			}	
			break;
		
			case OPR2: {
				
				zadejOperand(radek, &kalkuldata);
				
				if(flag4){
					flag0 = flag1 = flag2 = flag3 = flag4 = 0; 
					stav = OPR1;
					break;
				}
				
				stav = VYS;
			}
			break;
		
			case VYS: {
			
				switch(kalkuldata.ope){
					case '+': printf("vysledek: %lf\n", kalkuldata.a + kalkuldata.b);
					kalkuldata.vys = kalkuldata.a + kalkuldata.b;
					break;
					
					case '-': printf("vysledek: %lf\n", kalkuldata.a - kalkuldata.b);
					kalkuldata.vys = kalkuldata.a - kalkuldata.b;
					break;
					
					case '*': printf("vysledek: %lf\n", kalkuldata.a * kalkuldata.b);
					kalkuldata.vys = kalkuldata.a * kalkuldata.b;
					break;
					
					case '/': printf("vysledek: %lf\n", kalkuldata.a / kalkuldata.b);
					kalkuldata.vys = kalkuldata.a / kalkuldata.b;
					break;
				}
				kalkuldata.prev_ope = kalkuldata.ope;
			
				stav = OPR1;
				flag0 = 1;
			}	
			break;
		}
	}
	
	return 0;
}


int isOperator(char z){
	return (z == '+' || z == '-' || z == '*' || z == '/') ? 1 : 0;
}


void zadejOperand(char *str, struct KalkulData *ka){
	
	puts("zadej operand_cislo");
	fgets(str, 10, stdin);
	
	double *d = NULL;
	char znak;
	
	if(stav == OPR1) 
		d = &ka->a;
	else if(stav == OPR2)
		d = &ka->b;
	
	if(sscanf(str, "%c", &znak) == 1){
		if(znak == 'x'){
			flag4 = 1;
			return;
		} 
	}

	while(sscanf(str, "%lf", d) == 0){
		flag1 = 0;
		flag3 = 0;
		if(flag0 && stav == OPR1){
			flag0 = 0;
			sscanf(str, "%c", &ka->ope);
			
			if(isOperator(ka->ope)){
				ka->a = ka->vys;
				flag1 = 1;
				flag2 = 1;
				return;
				
			}else if(ka->ope == '=' && flag2){ 
				flag3 = 1;
				ka->ope = ka->prev_ope;
				ka->a = ka->vys;
				return;
			}
		}
		puts("zadej operand_cislo!");
		fgets(str, 10, stdin);
	}
	flag0 = 0;
}

void zadejOperator(char *str, struct KalkulData *ka){
	do{
		puts("zadej operator: +,-,*,/ ");
		fgets(str, 10, stdin);
		sscanf(str, "%c", &ka->ope);
		if(ka->ope == 'x'){
			flag4 = 1;
			return;
		}
	}while(!isOperator(ka->ope));
}
