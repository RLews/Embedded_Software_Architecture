/*!
************************************************************************************************************************
* @file srv_memory.c
* @brief �ڴ�������
* @details Reference ATK32 malloc code.
* @author Lews Hammond
* @date 2019-8-9
************************************************************************************************************************
*/

#include "srv_memory.h"

#if (USER_MEMORY_MANAGE_ENABLE == D_STD_ENABLE)

//�ڴ��(4�ֽڶ���)
__align(4) u8 mem1base[MEM1_MAX_SIZE] ;													//�ڲ�SRAM�ڴ��

__align(4) u8 mem2base[MEM2_MAX_SIZE] __attribute__((at(0X68000000)));					//�ⲿSRAM�ڴ��

//�ڴ�����
u16 mem1mapbase[MEM1_ALLOC_TABLE_SIZE];													//�ڲ�SRAM�ڴ��MAP

u16 mem2mapbase[MEM2_ALLOC_TABLE_SIZE] __attribute__((at(0X68000000+MEM2_MAX_SIZE)));	//�ⲿSRAM�ڴ��MAP

//�ڴ�������	   
const u32 memtblsize[2]={MEM1_ALLOC_TABLE_SIZE,MEM2_ALLOC_TABLE_SIZE};		//�ڴ���С
const u32 memblksize[2]={MEM1_BLOCK_SIZE,MEM2_BLOCK_SIZE};					//�ڴ�ֿ��С
const u32 memsize[2]={MEM1_MAX_SIZE,MEM2_MAX_SIZE};							//�ڴ��ܴ�С


//�ڴ���������
struct _m_mallco_dev mallco_dev=
{
	Srv_MemInit,				//�ڴ��ʼ��
	Srv_MemPerused,			//�ڴ�ʹ����
	mem1base,mem2base,		//�ڴ��
	mem1mapbase,mem2mapbase,//�ڴ����״̬��
	0,0,  					//�ڴ����δ����
};

static uint32_t Srv_MemMalloc(uint8_t memx, uint32_t size);
static uint8_t Srv_MemFree(uint8_t memx, uint32_t offset);

#endif

/*!
************************************************************************************************************************
* @brief memory copy
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond
* @date 2019-8-9
************************************************************************************************************************
*/

void Srv_MemCopy(void *des, const void *src, uint32_t len)
{
	u8 *xdes = des;
	const u8 *xsrc = src; 

	if ((des == NULL) || (src == NULL))
	{
		return;
	}

    while(len--)
    {
    	*xdes++ = *xsrc++;  
    }
}

/*!
************************************************************************************************************************
* @brief 
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond
* @date 2019-8-9
************************************************************************************************************************
*/

void Srv_MemSet(void *s,u8 c,u32 count)
{
	u8 *xs = s;  

	if (s == NULL)
	{
		return;
	}
	
    while(count--)
    {
    	*xs++=c;  
    }
}

/*!
************************************************************************************************************************
* @brief Memory initial
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond
* @date 2019-8-9
************************************************************************************************************************
*/

void Srv_MemInit(uint8_t memx)
{
#if (USER_MEMORY_MANAGE_ENABLE == D_STD_ENABLE)
	Srv_MemSet(mallco_dev.memmap[memx], 0,memtblsize[memx]*2);//�ڴ�״̬����������  
	Srv_MemSet(mallco_dev.membase[memx], 0,memsize[memx]);	//�ڴ��������������  
	mallco_dev.memrdy[memx]=1;								//�ڴ�����ʼ��OK  
#endif
}

/*!
************************************************************************************************************************
* @brief get memory used
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond
* @date 2019-8-9
************************************************************************************************************************
*/

uint8_t Srv_MemPerused(uint8_t memx)
{
#if (USER_MEMORY_MANAGE_ENABLE == D_STD_ENABLE)
	u32 used = 0;  
    u32 i = 0;
    
    for(i = 0; i < memtblsize[memx]; i++)  
    {  
        if(mallco_dev.memmap[memx][i])
        {
        	used++; 
        }
    } 
    
    return (used*100)/(memtblsize[memx]);  
#else
	return 0U;
#endif
}

#if (USER_MEMORY_MANAGE_ENABLE == D_STD_ENABLE)

/*!
************************************************************************************************************************
* @brief 
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond
* @date 2019-8-9
************************************************************************************************************************
*/

static uint32_t Srv_MemMalloc(uint8_t memx, uint32_t size)
{
	signed long offset=0;  
    u16 nmemb;	//��Ҫ���ڴ����  
	u16 cmemb=0;//�������ڴ����
    u32 i = 0;  
    
    if(!mallco_dev.memrdy[memx])
    {
    	mallco_dev.init(memx);//δ��ʼ��,��ִ�г�ʼ�� 
    }
    
    if(size==0)
    {
    	return 0XFFFFFFFF;//����Ҫ����
    }
    
    nmemb=size/memblksize[memx];  	//��ȡ��Ҫ����������ڴ����
    if(size%memblksize[memx])nmemb++;  
    for(offset=memtblsize[memx]-1;offset>=0;offset--)//���������ڴ������  
    {     
		if(!mallco_dev.memmap[memx][offset])
		{
			cmemb++;//�������ڴ��������
		}
		else
		{
			cmemb=0;								//�����ڴ������
		}
		
		if(cmemb == nmemb)							//�ҵ�������nmemb�����ڴ��
		{
            for(i=0;i<nmemb;i++)  					//��ע�ڴ��ǿ� 
            {  
                mallco_dev.memmap[memx][offset+i]=nmemb;  
            }  
            
            return (offset*memblksize[memx]);//����ƫ�Ƶ�ַ  
		}
    }  
    
    return 0XFFFFFFFF;//δ�ҵ����Ϸ����������ڴ�� 
}

/*!
************************************************************************************************************************
* @brief 
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond
* @date 2019-8-9
************************************************************************************************************************
*/

static uint8_t Srv_MemFree(uint8_t memx, uint32_t offset)
{
	int i = 0;
	
    if(!mallco_dev.memrdy[memx])//δ��ʼ��,��ִ�г�ʼ��
	{
		mallco_dev.init(memx);    
        return 1;//δ��ʼ��  
    }
    
    if(offset<memsize[memx])//ƫ�����ڴ����. 
    {  
        int index=offset/memblksize[memx];			//ƫ�������ڴ�����  
        int nmemb=mallco_dev.memmap[memx][index];	//�ڴ������
        for(i=0;i<nmemb;i++)  						//�ڴ������
        {  
            mallco_dev.memmap[memx][index+i]=0;  
        }  
        return 0;  
    }
    else
    {
    	return 2;//ƫ�Ƴ�����.
    }
}
#endif

/*!
************************************************************************************************************************
* @brief 
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond
* @date 2019-8-9
************************************************************************************************************************
*/

void * Srv_Malloc(uint8_t memx, uint32_t size)
{
#if (USER_MEMORY_MANAGE_ENABLE == D_STD_ENABLE)
	u32 offset = 0;

	if (Hal_GetInitStatus() == EN_HAL_SRAM_INIT_ERR)
	{
		memx = D_IN_SRAM; //�ⲿ�ڴ��쳣���л����ڲ�
	}
	
	offset = Srv_MemMalloc(memx,size);  	   				   
    if(offset==0XFFFFFFFFUL)
    {
    	return NULL;  
    }
    else
    {
    	return (void*)((u32)mallco_dev.membase[memx]+offset); 
    }
#else
	(void)memx;
	return malloc(size);
#endif
}

/*!
************************************************************************************************************************
* @brief 
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond
* @date 2019-8-9
************************************************************************************************************************
*/

void Srv_Free(uint8_t memx, void *ptr)
{
#if (USER_MEMORY_MANAGE_ENABLE == D_STD_ENABLE)
	u32 offset = 0;  

	if (Hal_GetInitStatus() == EN_HAL_SRAM_INIT_ERR)
	{
		memx = D_IN_SRAM; //�ⲿ�ڴ��쳣���л����ڲ�
	}
	
    if(ptr==NULL)
    {
    	return;//��ַΪ0.  
    }
    
 	offset=(u32)ptr-(u32)mallco_dev.membase[memx];  
    Srv_MemFree(memx,offset);//�ͷ��ڴ�   
#else
	(void)memx;
	free(ptr);
#endif
}

/*!
************************************************************************************************************************
* @brief 
* @param[in] 
* @param[out] 
* @returns 
* @pre 
* @note 
* @author Lews Hammond
* @date 2019-8-9
************************************************************************************************************************
*/

void * Srv_Realloc(uint8_t memx, void *ptr, uint32_t size)
{
#if (USER_MEMORY_MANAGE_ENABLE == D_STD_ENABLE)
	u32 offset = 0;

	if (Hal_GetInitStatus() == EN_HAL_SRAM_INIT_ERR)
	{
		memx = D_IN_SRAM; //�ⲿ�ڴ��쳣���л����ڲ�
	}

    offset=Srv_MemMalloc(memx,size);  
    
    if(offset==0XFFFFFFFF)
    {
    	return NULL;     
    }
    else  
    {  									   
	    Srv_MemCopy((void*)((u32)mallco_dev.membase[memx]+offset),ptr,size);	//�������ڴ����ݵ����ڴ�   
        Srv_Free(memx,ptr);  											  		//�ͷž��ڴ�
        return (void*)((u32)mallco_dev.membase[memx]+offset);  				//�������ڴ��׵�ַ
    }  
#else
	(void)memx;
	return realloc(ptr, size);
#endif
}

