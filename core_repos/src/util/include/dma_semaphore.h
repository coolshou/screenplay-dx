/*
 * PORTABLE semaphore function for DMA Project	
 * Walker Wang, wwang@redsonic.com
 *
 */
#ifndef __DMA_SEMAPHORE__
#define __DMA_SEMAPHORE__
/*
 * A work around method for UPnP Renderer because it didn't need semaphore at all. We define it to null here to
 * downsize the compiled binary
 */
#ifdef DOWNSIZE_FOR_NOMMU
#define dma_sem_t int
#define dma_sem_init(x,y,z)
#define dma_sem_destroy(x)
#define dma_sem_wait(x)
#define dma_sem_trywait(x)
#define dma_sem_post(x)
#else
#include <semaphore.h>
#define dma_sem_t sem_t
#define dma_sem_init(x,y,z) sem_init(x,y,z)
#define dma_sem_destroy(x) sem_destroy(x)
#define dma_sem_wait(x) sem_wait(x)
#define dma_sem_trywait(x) sem_trywait(x)
#define dma_sem_post(x) sem_post(x)
#endif
#endif
