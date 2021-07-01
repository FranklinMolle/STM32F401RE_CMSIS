#include "stm32f4xx.h"                  // Device header

void HSI_config(void);
void HSE_config(void);
void PLL_config(void);

/*variables globales*/
uint32_t freq;													/*para monitorear la frecuencia del sysclk*/
/*funcion principal*/
int main(void){
	
	freq = SystemCoreClock;								/*se lee el valor inicial del rcc*/
	//HSI_config();
	//SystemCoreClockUpdate();							/*se actualiza el valor de la variable SystemCoreClock*/
	//freq = SystemCoreClock;								/*se lee el nuevo valor de la frecuencia del sysclk*/
	
	PLL_config();
	SystemCoreClockUpdate();
	freq = SystemCoreClock;
	while(1){
		
	}

}


void HSI_config(void){
	/* HABILITAMOS EL HSI */
	RCC->CR |= RCC_CR_HSION;
	/* PREGUNTAMOS SI EL HSI ESTA LISTO Y ESTABLE */
	while(!(RCC->CR & RCC_CR_HSIRDY));
	/* SELECCIONES EL RELOJ DEL SISTEMA */
	RCC->CFGR &=~ RCC_CFGR_SW;
	//COMPROBAR SWS SI ESTA LISTO EL CLOCK
	//
	//******** faltaaaaaa!!!!
	//
}

void HSE_config(void){
	
}

void PLL_config(void){
	/*1. Deshabilitar el pll (RCC_CR)*/
	RCC->CR &=~ RCC_CR_PLLON;
	/*2. configurar la fuente de reloj del PLL (RCC_PLLCFGR_SRC)*/
	RCC->PLLCFGR &=~ RCC_PLLCFGR_PLLSRC;//SELECCIONAMOS EL HSI
	/*3. configurar los parametros del pll (RCC_PLLCFGR)*/
	//M
	RCC->PLLCFGR &=~ RCC_PLLCFGR_PLLM;
	RCC->PLLCFGR |= 16<<0;//PLLM = 16
	//N
	RCC->PLLCFGR &=~ RCC_PLLCFGR_PLLN;
	RCC->PLLCFGR |= 336<<6;//PLLN = 336
	//P
	RCC->PLLCFGR &=~ RCC_PLLCFGR_PLLP_1;//PLLP = 4
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLP_0;
	/*4. Habilitar y esperar que el pll este listo (RCC_CR)*/
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));	
	/*6. opcional configurar los prescalers HHB, APBx (RCC_CFGR)*/
	//APB1 -> 2
	RCC->CFGR |= RCC_CFGR_PPRE1_2;
	RCC->CFGR &=~ RCC_CFGR_PPRE1_1;
	RCC->CFGR &=~ RCC_CFGR_PPRE1_0;
	/*7. configurar la latencia de la flash (FLASH_ACR)*/
	FLASH->ACR |= (1<<0);
	/*8. Seleccionar el reloj habilitado como la fuente del sistema (RCC_CFGR)*/
	RCC->CFGR |= 2<<0;//PLL
}