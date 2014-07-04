#ifndef _VM_H
#define _VM_H 

#include "mm.h"
#include "memlayout.h"
#include "mmu.h"

class VirtualMemoryManager 
{
    public:
        static VirtualMemoryManager* get();

        bool init(PhysicalMemoryManager* pmm);

        page_t* walk(page_directory_t* pgdir, void* vaddr, bool create = false);
        void map_pages(page_directory_t* pgdir, void *vaddr, u32 size,
                u32 paddr, u32 flags);

        /**
         * Causes the specified page directory to be loaded into the
         * CR3 register.
         **/
        void switch_page_directory(page_directory_t *pgdir);
        page_directory_t* current_directory() const { return _current_pdir; }
        void flush_tlb_entry(u32 vaddr); 

        void dump_page_directory(page_directory_t* pgdir);
        page_directory_t* create_address_space();

        // alloc one kernel page and return vaddr 
        void* alloc_page();
        void free_page(void* vaddr);

        // kernel heap allocation
        void* kmalloc(size_t size, int align);
        void kfree(void* ptr);
        //for debug
        void dump_heap();

    private:
        struct kheap_block_head
        {
            u32 size;
            struct kheap_block_head* prev;
            struct kheap_block_head* next;
            void* ptr;
            u32 used;
            char data[1];
        };

        static VirtualMemoryManager* _instance;
        PhysicalMemoryManager* _pmm;
        page_directory_t* _current_pdir;

        kheap_block_head* _kheap_ptr;
        u32* _kern_heap_start;
        u32* _kern_heap_limit;

        kheap_block_head* find_block(kheap_block_head** last, size_t size);
        void split_block(kheap_block_head* h, size_t size);
        kheap_block_head* merge_block(kheap_block_head* h);
        kheap_block_head* align_block(kheap_block_head* h, int align);
        bool aligned(void* ptr, int align);
        void* ksbrk(size_t size);

        void test_malloc();

        VirtualMemoryManager();
};

#endif
