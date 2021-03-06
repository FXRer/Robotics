/*
    This file is part of AutoQuad.

    AutoQuad is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AutoQuad is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with AutoQuad.  If not, see <http://www.gnu.org/licenses/>.

    Copyright � 2011, 2012, 2013  Bill Nesbitt
*/

#include "aq.h"
#include "pwm.h"
#include "digital.h"

RCC_ClocksTypeDef rccClocks;
digitalPin *sysoff, *en1, *en2;

void rccConfiguration(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);

    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;

    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    // exclude PA13 & PA14 for SWD
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All & ~(GPIO_Pin_13 | GPIO_Pin_14);
    GPIO_Init(GPIOA, &GPIO_InitStructure);

#ifdef RCC_EN1_PORT
    en1 = digitalInit(RCC_EN1_PORT, RCC_EN1_PIN);
    digitalHi(en1);
#endif
#ifdef RCC_EN2_PORT
    en2 = digitalInit(RCC_EN2_PORT, RCC_EN2_PIN);
    digitalLo(en2);
#endif
#ifdef RCC_SYSOFF_PORT
    sysoff = digitalInit(RCC_SYSOFF_PORT, RCC_SYSOFF_PIN);
    digitalLo(sysoff);
#endif

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1 | RCC_AHB1Periph_DMA2, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    // enable timer clocks
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_TIM9 | RCC_APB2Periph_TIM10 | RCC_APB2Periph_TIM11, ENABLE);

    SYSCFG_CompensationCellCmd(ENABLE);

    // Clear reset flags
    RCC_ClearFlag();

    RCC_GetClocksFreq(&rccClocks);

    pwmZeroTimers();
}
