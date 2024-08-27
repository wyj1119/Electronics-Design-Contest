//-----------------------------------------------------------------
// HD44780(KS0066U)�ں˵��ַ���LCD�ӳ����ͷ�ļ�
// ͷ�ļ���:CharLCD.h
// ��    ��:���ǵ���
// ��ʼ����: 2014-02-2 
// �������: 2014-02-2 
// �޸�����: 2014-03-03
// ��ǰ�汾: V1.0.2
// ��ʷ�汾:
//	  -V1.0:(2014-02-02)������Һ����ʾ����
//	-V1.0.1: (2014-02-16)ͷ�ļ��в���������ͷ�ļ�
//	-V1.0.2: (2014-03-03)����Һ����IO����
//-----------------------------------------------------------------

#ifndef _CHARLCD_H
#define _CHARLCD_H

//----------------------------------------------------------------
// IO�ڲ���
//-----------------------------------------------------------------
#define LCM_RS_set (GPIO_SetBits(GPIOD,GPIO_Pin_0))            
#define LCM_RS_clr (GPIO_ResetBits(GPIOD,GPIO_Pin_0))            
#define LCM_RW_set (GPIO_SetBits(GPIOD,GPIO_Pin_1))           
#define LCM_RW_clr (GPIO_ResetBits(GPIOD,GPIO_Pin_1))           
#define LCM_E_set	 (GPIO_SetBits(GPIOA,GPIO_Pin_8))         
#define LCM_E_clr	 (GPIO_ResetBits(GPIOA,GPIO_Pin_8))          

//-----------------------------------------------------------------
// �ⲿ��������
//-----------------------------------------------------------------
extern void GPIO_LCM_Configuration(void);
extern void LCM_Init (void);								// LCM��ʼ��,ʹ��ʱ������Ҫѡ��
extern void WrCLcdC (u8 lcdcomm);						// дLCM��ָ�����
extern void WrCLcdD (u8 lcddata);						// дLCMҪ��ʾ������
extern void WriteString (u8 x, u8 y, u8 *s);// ָ��λ����ʾһ���ַ���
extern void CG_Write (void);           			// ���Զ�����ַ��͵�CGRAM
extern void Wr_CodeData (void);            	// д������ͬ���ֳ���
// ��ʾʮ�����޷����ַ�����
extern void WrCLcd_char_num (u8 x, u8 y, u8 num);	
// ��ʾʮ�����޷�����������
extern void WrCLcd_int_num (u8 x, u8 y, u16  num);
// ��ʾʮ�����޷��ų���������
extern void WrCLcd_long_num (u8 x, u8 y, unsigned long num);
extern void Wr_In1 (void);						   		// ��һ����ʾ
extern void Wr_In2 (void);						   		// �ڶ�����ʾ
extern void CL_Enter (void);					   		// ��һ�й��������ʾ
extern void CR_Enter (void);					   		// �ڶ��й��������ʾ
extern void L_Enter (void);					      	// ��һ�л���������ʾ
extern void R_Enter (void);					      	// �ڶ��л���������ʾ
extern void CGWrite (void);					      	// ��ʾ��Ʒ��Ϣ

#endif

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
