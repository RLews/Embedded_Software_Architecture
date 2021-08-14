/*!
************************************************************************************************************************
* @file srv_memory.c
* @brief 内存管理服务
* @details Reference ATK32 malloc code.
* @author Lews Hammond
* @date 2019-8-9
************************************************************************************************************************
*/

#include "srv_memory.h"

#if (USER_MEMORY_MANAGE_ENABLE == D_STD_ENABLE)

//内存池(4字节对齐)
__align(4) u8 mem1base[MEM1_MAX_SIZE] ;													//内部SRAM内存池

__align(4) u8 mem2base[MEM2_MAX_SIZE] __attribute__((at(0X68000000)));					//外部SRAM内存池

//内存管理表
u16 mem1mapbase[MEM1_ALLOC_TABLE_SIZE];													//内部SRAM内存池MAP

u16 mem2mapbase[MEM2_ALLOC_TABLE_SIZE] __attribute__((at(0X68000000+MEM2_MAX_SIZE)));	//外部SRAM内存池MAP

//内存管理参数	   
const u32 memtblsize[2]={MEM1_ALLOC_TABLE_SIZE,MEM2_ALLOC_TABLE_SIZE};		//内存表大小
const u32 memblksize[2]={MEM1_BLOCK_SIZE,MEM2_BLOCK_SIZE};					//内存分块大小
const u32 memsize[2]={MEM1_MAX_SIZE,MEM2_MAX_SIZE};							//内存总大小


//内存管理控制器
struct _m_mallco_dev mallco_dev=
{
	Srv_MemInit,				//内存初始化
	Srv_MemPerused,			//内存使用率
	mem1base,mem2base,		//内存池
	mem1mapbase,mem2mapbase,//内存管理状态表
	0,0,  					//内存管理未就绪
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
	Srv_MemSet(mallco_dev.memmap[memx], 0,memtblsize[memx]*2);//内存状态表数据清零  
	Srv_MemSet(mallco_dev.membase[memx], 0,memsize[memx]);	//内存池所有数据清零  
	mallco_dev.memrdy[memx]=1;								//内存管理初始化OK  
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
    u16 nmemb;	//需要的内存块数  
	u16 cmemb=0;//连续空内存块数
    u32 i = 0;  
    
    if(!mallco_dev.memrdy[memx])
    {
    	mallco_dev.init(memx);//未初始化,先执行初始化 
    }
    
    if(size==0)
    {
    	return 0XFFFFFFFF;//不需要分配
    }
    
    nmemb=size/memblksize[memx];  	//获取需要分配的连续内存块数
    if(size%memblksize[memx])nmemb++;  
    for(offset=memtblsize[memx]-1;offset>=0;offset--)//搜索整个内存控制区  
    {     
		if(!mallco_dev.memmap[memx][offset])
		{
			cmemb++;//连续空内存块数增加
		}
		else
		{
			cmemb=0;								//连续内存块清零
		}
		
		if(cmemb == nmemb)							//找到了连续nmemb个空内存块
		{
            for(i=0;i<nmemb;i++)  					//标注内存块非空 
            {  
                mallco_dev.memmap[memx][offset+i]=nmemb;  
            }  
            
            return (offset*memblksize[memx]);//返回偏移地址  
		}
    }  
    
    return 0XFFFFFFFF;//未找到符合分配条件的内存块 
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
	
    if(!mallco_dev.memrdy[memx])//未初始化,先执行初始化
	{
		mallco_dev.init(memx);    
        return 1;//未初始化  
    }
    
    if(offset<memsize[memx])//偏移在内存池内. 
    {  
        int index=offset/memblksize[memx];			//偏移所在内存块号码  
        int nmemb=mallco_dev.memmap[memx][index];	//内存块数量
        for(i=0;i<nmemb;i++)  						//内存块清零
        {  
            mallco_dev.memmap[memx][index+i]=0;  
        }  
        return 0;  
    }
    else
    {
    	return 2;//偏移超区了.
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
		memx = D_IN_SRAM; //外部内存异常，切换至内部
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
		memx = D_IN_SRAM; //外部内存异常，切换至内部
	}
	
    if(ptr==NULL)
    {
    	return;//地址为0.  
    }
    
 	offset=(u32)ptr-(u32)mallco_dev.membase[memx];  
    Srv_MemFree(memx,offset);//释放内存   
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
		memx = D_IN_SRAM; //外部内存异常，切换至内部
	}

    offset=Srv_MemMalloc(memx,size);  
    
    if(offset==0XFFFFFFFF)
    {
    	return NULL;     
    }
    else  
    {  									   
	    Srv_MemCopy((void*)((u32)mallco_dev.membase[memx]+offset),ptr,size);	//拷贝旧内存内容到新内存   
        Srv_Free(memx,ptr);  											  		//释放旧内存
        return (void*)((u32)mallco_dev.membase[memx]+offset);  				//返回新内存首地址
    }  
#else
	(void)memx;
	return realloc(ptr, size);
#endif
}

