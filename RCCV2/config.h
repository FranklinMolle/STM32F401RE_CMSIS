#ifndef CONFIG_H
#define CONFIG_H

#include "stm32f4xx.h" 
/***************************************************
 * LATENCY
 * 0WS - 0<HCKL<=30
 * 1WS - 30<HCKL<=60
 * 2WS - 60<HCKL<=84
 * 
 ***************************************************
*/
/*PARA 84Mhz -> M=16, N=336*/
#define	PLLM	16	// 	0 - 63
#define	PLLN	100	//	0 - 511
#define	PLLP	1		//	0 -> 2
									//	1 -> 4
									//	2 -> 6
									//	3 -> 8
#define LATENCY		0

extern uint32_t freq;		/*llamo a la variable padre */

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
	RCC->PLLCFGR |= (PLLM<<0);
	//N
	RCC->PLLCFGR &=~ RCC_PLLCFGR_PLLN;
	RCC->PLLCFGR |= (PLLN<<6);
	//P
	RCC->PLLCFGR &=~ RCC_PLLCFGR_PLLP;
	RCC->PLLCFGR |= (PLLP<<16);
	/*4. Habilitar y esperar que el pll este listo (RCC_CR)*/
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));	
	/*6. opcional configurar los prescalers HHB, APBx (RCC_CFGR)*/
	//APB1 -> 2
	RCC->CFGR |= RCC_CFGR_PPRE1_2;
	RCC->CFGR &=~ RCC_CFGR_PPRE1_1;
	RCC->CFGR &=~ RCC_CFGR_PPRE1_0;
	/*7. configurar la latencia de la flash (FLASH_ACR)*/
	FLASH->ACR |= (LATENCY<<0);
	/*8. Seleccionar el reloj habilitado como la fuente del sistema (RCC_CFGR)*/
	RCC->CFGR |= 2<<0;//PLL
}

void Select_PLL(void){
	PLL_config();
	SystemCoreClockUpdate();							/*se actualiza el valor de la variable SystemCoreClock*/
	freq = SystemCoreClock;								/*se lee el nuevo valor de la frecuencia del sysclk*/
}

#endif