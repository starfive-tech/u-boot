#include <asm/insn-def.h>

#define CMO_OP(_op, _start, _size, _cachesize)				\
asm volatile(								\
	"mv a0, %1\n\t"							\
	"j 2f\n\t"							\
	"3:\n\t"							\
	CBO_##_op(a0)							\
	"add a0, a0, %0\n\t"						\
	"2:\n\t"							\
	"bltu a0, %2, 3b\n\t"						\
	: : "r"(_cachesize),						\
	    "r"((unsigned long)(_start) & ~((_cachesize) - 1UL)),	\
	    "r"((unsigned long)(_start) + (_size))			\
	: "a0")

void flush_dcache_range(unsigned long start, unsigned long end)
{
	CMO_OP(FLUSH, start, end - start, CONFIG_SYS_CACHELINE_SIZE);
}

void invalidate_dcache_range(unsigned long start, unsigned long end)
{
	 CMO_OP(INVAL, start, end - start, CONFIG_SYS_CACHELINE_SIZE);
}
